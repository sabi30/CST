#pragma once
#include "type.h"

namespace cst {

    // List (aka Vector)
    struct alignas(64) untyped_list {
        void *ptr = nullptr;
        dint size = 0;
        dint capacity = 0;
        dint val_size = 0;
        bool fixed_capacity = false;

        void init(dint);
        void clear(void);

        void copy(const untyped_list& other);
        void move(untyped_list&& other) noexcept;

        void resize(dint);
        void reserve(dint);

        dint insert(const void *val);
        void remove(const dint key);

        dint find(void *addr);

        void insert_first(const void *val);
        void remove_first(const dint key);

        void *begin(void);
        void *end(void);
    
        void *operator[](dint key);
        const void *operator[](dint) const;

        untyped_list& operator=(const untyped_list&);
        untyped_list& operator=(untyped_list&& other) noexcept;
        untyped_list& operator<<(const untyped_list&);
    };

    // Template Wrapper of List, handles casting
    template<typename T>
    struct list {
        untyped_list data;

        void init() {
            data.init(sizeof(T));
        }

        void clear() {
            data.clear();
        }

        void destroy() {
            data.clear();
        }
            
        dint insert(const T& val) {
            return data.insert(&val);
        }

        void remove(const dint key) {
            data.remove(key);
        }

        dint find(const T& val) {
            return data.find(&val);
        }

        void insert_first(const T val) {
            data.insert_first(&val);
        }

        void remove_first(const dint key) {
            data.remove_first(key);
        }

        void resize(dint count) { 
            data.resize(count);
        }

        void reserve(dint count) {
            data.reserve(count);
        }

        // some more stuff
        bool empty() const {
            return data.size == 0;
        }

        T& back() {
            return *static_cast<T*>(data[data.size - 1]);
        }

        const T& back() const {
            return *static_cast<const T*>(data[data.size - 1]);
        }

        void pop_back() {
            if (data.size > 0) {
                data.size--; 
            }
        }

        dint push_back(const T& val) {
            return data.insert(&val); 
        }

        T* operator[](dint key) {
            return static_cast<T*>(data[key]);
        }

        const T* operator[](dint key) const {
            return static_cast<T*>(data[key]);
        }

        list& operator=(const list& other) {
            data = other;
            return *this;
        };

        list& operator=(list&& other) noexcept {
            data = other;
            return *this;
        };

        list& operator<<(const list& other) {
            data << other;
            return *this;
        };

        T *begin() {
            return static_cast<T*>(data.ptr);
        };

        T *end() {
            return static_cast<T*>(data.end());
        }   
        
        dint size() {
            return data.size;
        };
    };


}
