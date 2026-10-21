#pragma once

#include "list.h"
#include "str.h"

namespace cst {

    inline dint basic_hasher(const void *key, const dint size) {
        const u8 *bytes = (const u8*)key;

        u64 hash = 14695981039346656037ull;

        for (dint i = 0; i < size; i++) {
            hash ^= bytes[i];
            hash *= 1099511628211ull;
        }

        return hash;
    };

    inline dint string_hasher(void *key, dint size) {
        cst::string* string = static_cast<cst::string*>(key);
        return basic_hasher(string->c_str, string->size);
    }

    struct untyped_map {
        struct bucket {
            dint hash = 0;
            dint distance = 0;
            bool occupied = false;
            void *key = nullptr; // bytes after this struct
            void *val = nullptr; // bytes after ksize
        };
        
        untyped_list map_list;

        bool initialized = false;
        dint key_size = 0;
        dint val_size = 0;
        dint used = 0;

        dint (*hasher)(const void *key, const dint size) = basic_hasher;

        void init(dint key_size, dint value_size);
        void clear(void);

        void rehash(dint new_capacity);

        void *get(void *key);
        dint insert(void *key, void *val);
        void remove(void *key);
        void *operator[](void *key);
    };

    template<typename key, typename val>
    struct map {
        untyped_map data;

        void init(dint, dint) {
            data.init(sizeof(key), sizeof(val));
        }
        
        void clear(void) {
            data.clear();
        }

        void rehash(dint s) {
            data.rehash(s);
        }

        val *get(key& k) {
            return static_cast<val*>(data.get(&k));
        }
        
        dint insert(key& k, val v) {
            data.insert(&k, &v);
        }
        
        void remove(key& k) {
            data.remove(&k);
        }
        void *operator[](key& k) {
            data[&k];
        }
    };
}