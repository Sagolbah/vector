#pragma once

#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <memory>
#include <variant>
#include <algorithm>

template<typename T>

struct vector {
    struct bigvector {
        struct storage {
            size_t size_;
            size_t capacity_;
            size_t ref_count;
            T data[];  // flexible size, using to make_storage() comfortably
        };
        storage *store = nullptr;

        storage *make_storage(size_t cp) {
            return static_cast<storage *> (operator new(sizeof(storage) + sizeof(T) * cp));
        }

        void unique_copy() {
            if (!store || store->ref_count == 1) {
                return;
            }
            storage *tmp = make_storage(store->capacity_);
            try {
                std::uninitialized_copy(begin(), end(), tmp->data);
            } catch (...) {
                operator delete(tmp);
                throw;
            }
            tmp->size_ = store->size_;
            tmp->capacity_ = store->capacity_;
            tmp->ref_count = 1;
            store->ref_count--;
            store = tmp;
        }

        //  Constructors

        bigvector() noexcept = default;

        bigvector(bigvector const &other) noexcept : store(other.store) {
            if (store) {
                store->ref_count++;
            }
        }

        template<typename InputIterator>
        bigvector(InputIterator beg, InputIterator en) {
            ptrdiff_t len = std::distance(beg, en);
            if (len <= 0) {
                store = nullptr;
            } else {
                store = make_storage((size_t) len);
                try {
                    std::uninitialized_copy(begin(), end(), store->data);
                } catch (...) {
                    operator delete(store);
                    throw;
                }
            }
        }

        bigvector(size_t cnt, T const &elem) {
            if (cnt == 0) {
                store = nullptr;
            } else {
                store = make_storage(cnt);
                try {
                    std::uninitialized_fill_n(store->data, cnt, elem);
                } catch (...) {
                    operator delete(store);
                    store = nullptr;
                    throw;
                }
                store->size_ = cnt;
                store->capacity_ = cnt;
                store->ref_count = 1;
            }
        }

        bigvector &operator=(bigvector const &other) {
            if (other.store == store) {
                return *this;
            }
            if (store) {
                std::destroy(begin(), end());
                operator delete(store);
            } else {
                store->ref_count--;
            }
            store = other.store;
            if (store) {
                store->ref_count++;
            }
            return *this;
        }

        ~bigvector() {
            if (store) {
                if (store->ref_count > 1) {
                    store->ref_count--;
                } else {
                    std::destroy(begin(), end());
                    operator delete(store);
                }
            }
        }


        // Iterator stuff

        T const *begin() const noexcept {
            return store ? store->data : nullptr;
        }

        T const *end() const noexcept {
            return store ? store->data + store->size_ : nullptr;
        }

        T *begin() {
            return store ? store->data : nullptr;
        }

        T *end() {
            return store ? store->data + store->size_ : nullptr;
        }


        // Operators

        T &operator[](size_t index) {
            if (store && index >= store->size_) {
                throw std::runtime_error("vector index out of range");
            }
            unique_copy();
            return store->data[index];
        }

        T const &operator[](size_t index) const {
            if (store && index >= store->size_) {
                throw std::runtime_error("vector index out of range");
            }
            return store->data[index];
        }

        friend bool operator==(bigvector const &a, bigvector const &b) {
            if (a.store == b.store)
                return true;
            if (a.store->size_ != b.store->size_)
                return false;
            return std::equal(a.begin(), a.end(), b.begin(), b.end());
        }

        friend void swap(bigvector &a, bigvector &b) {
            std::swap(a.store, b.store);
        }

        // Methods


        T &front() {
            unique_copy();
            return operator[](0);
        }

        T const &front() const {
            return operator[](0);
        }

        T &back() {
            unique_copy();
            return operator[](store->size_ - 1);
        }

        T const &back() const {
            return operator[](store->size_ - 1);
        }

        size_t size() const noexcept {
            return store ? store->size_ : 0;
        }

        size_t capacity() const noexcept {
            return store ? store->capacity_ : 0;
        }


        void push_back(T const &elem) {
            if (size() == capacity() || store->ref_count > 1) {
                size_t cap_needed;
                if (size() == capacity()) {
                    if (capacity() > 0) {
                        cap_needed = capacity() * 2;
                    } else {
                        cap_needed = 2;
                    }
                } else {
                    cap_needed = capacity();
                }
                storage *tmp = make_storage(cap_needed);
                try {
                    std::uninitialized_copy(begin(), end(), tmp->data);
                } catch (...) {
                    operator delete(tmp);
                    throw;
                }
                // add new
                try {
                    new(tmp->data + size()) T(elem);
                } catch (...) {
                    std::destroy(tmp->data, tmp->data + size());
                    operator delete(tmp);
                    throw;
                }
                if (!store) {
                    tmp->size_ = 1;
                } else {
                    tmp->size_ = store->size_ + 1;
                    if (store->ref_count == 1) {
                        std::destroy(begin(), end());
                        operator delete(store);
                    } else {
                        store->ref_count--;
                    }
                }
                tmp->capacity_ = cap_needed;
                tmp->ref_count = 1;
                store = tmp;
                return;
            }
            try {
                new(store->data + store->size_) T(elem);
                store->size_++;
            } catch (...) {
                throw;
            }
        }

        void pop_back() {
            unique_copy();
            std::destroy_at(store->data + (--store->size_));
        }

        T *data() {
            unique_copy();
            return store ? store->data : nullptr;
        }

        T const *data() const noexcept {
            return store ? store->data : nullptr;
        }

        void reserve(size_t cap) {
            if (cap <= capacity()) {
                return;
            }
            storage *tmp = make_storage(cap);
            try {
                std::uninitialized_copy(begin(), end(), tmp->data);
            } catch (...) {
                operator delete(tmp);
                throw;
            }
            if (!store) {
                tmp->size_ = 0;
            } else {
                tmp->size_ = store->size_;
                if (store->ref_count == 1) {
                    std::destroy(begin(), end());
                    operator delete(store);
                } else {
                    store->ref_count--;
                }
            }
            tmp->capacity_ = cap;
            tmp->ref_count = 1;
            store = tmp;
        }

        void shrink_to_fit() {
            if (size() == capacity()) {
                return;
            }
            if (size() == 0) {
                if (store->ref_count == 1) {
                    std::destroy(begin(), end());
                    operator delete(store);
                } else {
                    store->ref_count--;
                    store = nullptr;
                }
            } else {
                storage *tmp = make_storage(store->size_);
                try {
                    std::uninitialized_copy(begin(), end(), tmp->data);
                } catch (...) {
                    operator delete(tmp);
                    throw;
                }
                tmp->capacity_ = store->size_;
                tmp->size_ = store->size_;
                tmp->ref_count = 1;
                if (store->ref_count == 1) {
                    std::destroy(begin(), end());
                    operator delete(store);
                } else {
                    store->ref_count--;
                }
                store = tmp;
            }
        }

        void resize(size_t sz, T const &elem) {
            if (sz <= size()) {
                shorten(sz);
            } else {
                resize_job(sz, elem);
            }
        }

        void clear() {
            resize(0);
        }

        T *insert(T const *pos, T const &elem) {
            size_t index = pos - begin();
            if (const_cast<T *>(pos) == end()) {
                push_back(elem);
                return begin() + index;
            }
            if (size() == capacity() || store->ref_count > 1) {
                size_t cap_needed;
                if (size() == capacity()) {
                    if (capacity() > 0) {
                        cap_needed = capacity() * 2;
                    } else {
                        cap_needed = 2;
                    }
                } else {
                    cap_needed = capacity();
                }
                storage *tmp = make_storage(cap_needed);
                try {
                    std::uninitialized_copy(begin(), const_cast<T *>(pos), tmp->data);
                } catch (...) {
                    operator delete(tmp);
                    throw;
                }
                try {
                    new(tmp->data + index) T(elem);
                } catch (...) {
                    std::destroy(tmp->data, tmp->data + index);
                    operator delete(tmp);
                    throw;
                }
                try {
                    std::uninitialized_copy(const_cast<T *>(pos), end(), tmp->data + index + 1);
                } catch (...) {
                    std::destroy(tmp->data, tmp->data + index + 1);
                    operator delete(tmp);
                    throw;
                }
                tmp->size_ = store->size_ + 1;
                tmp->capacity_ = cap_needed;
                tmp->ref_count = 1;
                if (store->ref_count == 1) {
                    std::destroy(begin(), end());
                    operator delete(store);
                } else {
                    store->ref_count--;
                }
                store = tmp;
                return begin() + index;
            }
            std::uninitialized_copy(&elem, (&elem) + 1, end());
            store->size_++;
            std::rotate(begin() + index, end() - 1, end());
            return begin() + index;
        }

        T *erase(T const *beg, T const *en) {
            if (beg == en) {
                return begin() + (beg - begin());
            }
            size_t left = beg - begin();
            size_t right = en - begin();
            if (en == end()) {
                unique_copy();
                std::destroy(begin() + left, end());
                store->size_ -= (right - left);
                return begin() + left;
            }
            if (store->ref_count > 1) {
                storage *tmp = make_storage(store->capacity_);
                try {
                    std::uninitialized_copy(begin(), const_cast<T *>(beg), tmp->data);
                } catch (...) {
                    operator delete(tmp);
                }
                try {
                    std::uninitialized_copy(const_cast<T *>(en), end(), store->data + left);
                } catch (...) {
                    std::destroy(tmp->data, tmp->data + left);
                    operator delete(tmp);
                    throw;
                }
                tmp->size_ = store->size_ - right + left;
                tmp->capacity_ = store->capacity_;
                tmp->ref_count = 1;
                if (store->ref_count == 1) {
                    std::destroy(begin(), end());
                } else {
                    store->ref_count--;
                }
                store = tmp;
                return begin() + left;
            }
            std::move(begin() + right, end(), begin() + left);
            std::destroy(begin() + size() - right + left, end());
            store->size_ -= (right - left);
            return begin() + left;
        }


    private:
        void shorten(size_t sz) {
            if (sz == size()) {
                return;
            }
            if (store->ref_count == 1) {
                std::destroy(begin() + sz, end());
                store->size_ = sz;
            } else {
                storage *tmp = make_storage(store->capacity_);
                try {
                    std::uninitialized_copy(begin(), begin() + sz, tmp->data);
                } catch (...) {
                    operator delete(tmp);
                    throw;
                }
                tmp->size_ = sz;
                tmp->capacity_ = store->capacity_;
                tmp->ref_count = 1;
                store->ref_count--;
                store = tmp;
            }
        }

        void resize_job(size_t sz, T const &elem) {
            size_t new_cap = std::max(capacity(), sz);
            if (!store || new_cap > capacity() || store->ref_count > 1) {
                storage *tmp = make_storage(new_cap);
                try {
                    std::uninitialized_copy(begin(), end(), tmp->data);
                } catch (...) {
                    operator delete(tmp);
                    throw;
                }
                try {
                    std::fill_n(tmp->data + size(), sz - size(), elem);
                } catch (...) {
                    std::destroy(tmp->data, tmp->data + size());
                    operator delete(tmp);
                }
                tmp->size_ = sz;
                tmp->capacity_ = new_cap;
                tmp->ref_count = 1;
                if (store) {
                    if (store->ref_count == 1) {
                        std::destroy(begin(), end());
                        operator delete(store);
                    } else {
                        store->ref_count--;
                    }
                }
                store = tmp;
                return;
            }
            std::fill_n(begin() + size(), sz - size(), elem);
            store->size_ = sz;
        }
    };  //  BIGVECTOR

    // VECTOR:
private:
    std::variant<std::monostate, T, bigvector> vec_data;

public:
    typedef T value_type;
    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    vector() noexcept = default;

    vector(vector const &other) = default;

    vector &operator=(vector const &other) = default;

    template<typename InputIterator>
    vector(InputIterator beg, InputIterator en) {
        ptrdiff_t len = std::distance(beg, en);
        if (len > 1) {
            vec_data = bigvector(beg, en);
        } else if (len == 1) {
            vec_data = T(*beg);
        }
    }

    template<typename InputIterator>
    void assign(InputIterator beg, InputIterator en) {
        *this = vector(beg, en);
    }

    T &operator[](size_t index) {
        if (vec_data.index() == 1) {
            return std::get<1>(vec_data);
        }
        return std::get<2>(vec_data)[index];
    }

    T const &operator[](size_t index) const {
        if (vec_data.index() == 1) {
            return std::get<1>(vec_data);
        }
        return std::get<2>(vec_data)[index];
    }

    T &front() {
        return (vec_data.index() == 1) ? (std::get<1>(vec_data)) : (std::get<2>(vec_data).front());
    }

    T const &front() const {
        return (vec_data.index() == 1) ? (std::get<1>(vec_data)) : (std::get<2>(vec_data).front());
    }

    T &back() {
        return (vec_data.index() == 1) ? (std::get<1>(vec_data)) : (std::get<2>(vec_data).back());
    }

    T const &back() const {
        return (vec_data.index() == 1) ? (std::get<1>(vec_data)) : (std::get<2>(vec_data).back());
    }

    size_t size() const noexcept {
        if (vec_data.index() == 0) {
            return 0;
        } else if (vec_data.index() == 1) {
            return 1;
        }
        return std::get<2>(vec_data).size();
    }

    size_t capacity() const noexcept {
        if (vec_data.index() == 0) {
            return 0;
        } else if (vec_data.index() == 1) {
            return 1;
        }
        return std::get<2>(vec_data).capacity();
    }

    void push_back(T const &elem) {
        if (vec_data.index() == 0) {
            vec_data = T(elem);
        } else if (vec_data.index() == 1) {
            bigvector tmp;
            tmp.push_back(std::get<1>(vec_data));
            tmp.push_back(elem);
            vec_data = tmp;
        } else {
            std::get<2>(vec_data).push_back(elem);
        }
    }

    void pop_back() {
        if (vec_data.index() == 0) {
            throw std::runtime_error("attempt to pop_back in empty vector");
        } else if (vec_data.index() == 1) {
            vec_data = std::monostate();
        } else {
            std::get<2>(vec_data).pop_back();
        }
    }

    T *data() {
        switch (vec_data.index()) {
            case 0:
                return nullptr;
            case 1:
                return &std::get<1>(vec_data);
            default:
                return std::get<2>(vec_data).data();
        }
    }

    T const *data() const noexcept {
        switch (vec_data.index()) {
            case 0:
                return nullptr;
            case 1:
                return &std::get<1>(vec_data);
            default:
                return std::get<2>(vec_data).data();
        }
    }

    iterator begin() {
        return data();
    }

    iterator end() {
        return begin() + size();
    }

    const_iterator begin() const noexcept {
        return data();
    }

    const_iterator end() const noexcept {
        return begin() + size();
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const noexcept {
        return std::make_reverse_iterator(end());
    }

    const_reverse_iterator rend() const noexcept {
        return std::make_reverse_iterator(begin());
    }

    bool empty() const noexcept {
        return size() == 0;
    }

    void reserve(size_t cap) {
        bigvector tmp;
        switch (vec_data.index()) {
            case 0:
                if (cap == 0) return;
                break;
            case 1:
                if (cap < 1) return;
                tmp.push_back(std::get<1>(vec_data));
                break;
            default:
                std::get<2>(vec_data).reserve(cap);
                return;
        }
        tmp.reserve(cap);
        vec_data = tmp;
    }

    void shrink_to_fit() {
        if (vec_data.index() != 2)
            return;
        std::get<2>(vec_data).shrink_to_fit();
    }

    void resize(size_t sz) {
        resize_job(sz, T());
    }

    void resize(size_t sz, T const &elem) {
        resize_job(sz, elem);
    }

    iterator insert(const_iterator pos, T const &val) {
        bigvector tmp;
        size_t index = const_cast<iterator> (pos) - begin();
        if (vec_data.index() == 0) {
            vec_data = T(val);
            return begin();
        }
        if (vec_data.index() == 1) {
            tmp.push_back(std::get<1>(vec_data));
            tmp.insert(tmp.begin() + index, val);
            vec_data = tmp;
            return begin() + index;
        }
        return std::get<2>(vec_data).insert(pos, val);
    }

    iterator erase(const_iterator ind) {
        return erase(ind, ind + 1);
    }

    iterator erase(const_iterator beg, const_iterator en) {
        if (beg == en) {
            return begin() + (beg - begin());
        }
        if (vec_data.index() == 1) {
            vec_data = std::monostate();
            return begin();
        }
        return std::get<2>(vec_data).erase(beg, en);
    }

    void clear() {
        if (vec_data.index() != 2) {
            vec_data = std::monostate();
        } else {
            std::get<2>(vec_data).clear();
        }
    }

    friend bool operator==(vector const &a, vector const &b) {
        if (a.vec_data.index() == 2 && b.vec_data.index() == 2) {
            return std::get<2>(a.vec_data) == std::get<2>(b.vec_data);
        }
        return std::equal(a.begin(), a.end(), b.begin(), b.end());
    }

    friend bool operator!=(vector const &a, vector const &b) {
        return !(a == b);
    }

    friend bool operator<(vector const &a, vector const &b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    friend bool operator>(vector const &a, vector const &b) {
        return b < a;
    }

    friend bool operator<=(vector const &a, vector const &b) {
        return !(a > b);
    }

    friend bool operator>=(vector const &a, vector const &b) {
        return !(a < b);
    }

    friend void swap(vector &a, vector &b) {
        std::swap(a.vec_data, b.vec_data);
    }

private:
    void resize_job(size_t sz, T const &elem) {
        bigvector tmp;
        switch (vec_data.index()) {
            case 0:
                if (sz == 0) return;
                if (sz == 1) {
                    vec_data = elem;
                    return;
                }
                break;
            case 1:
                if (sz == 0) {
                    vec_data = std::monostate();
                    return;
                }
                if (sz == 1) {
                    return;
                }
                tmp.push_back(std::get<1>(vec_data));
                break;
            default:
                std::get<2>(vec_data).resize(sz, elem);
                return;
        }
        tmp.resize(sz, elem);
        vec_data = tmp;
    }
};