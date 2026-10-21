#include "map.h"
#include "mem_util.h"
#include <string.h> // For memcmp, memset, memcpy

// recode this

void cst::untyped_map::init(dint ksize, dint vsize) {
    key_size = ksize;
    val_size = vsize;
    used = 0; 

    dint entry_size = sizeof(bucket) + ksize + vsize;
    map_list.init(entry_size);
    map_list.resize(20);

    for (dint i = 0; i < map_list.capacity; i++) {
        bucket *b = (bucket*)map_list[i];
        b->occupied = false;
        b->distance = 0;
        b->hash = 0;
    }

    initialized = true;
}

void *cst::untyped_map::get(void *key) {
    if (!initialized || used == 0 || map_list.capacity == 0)
        return nullptr;

    dint hash = hasher(key, key_size);
    dint index = (hash % map_list.capacity + map_list.capacity) % map_list.capacity;
    dint distance = 0;

    while (true) {
        void *raw = map_list[index];
        bucket *b = (bucket*)raw;

        if (!b->occupied || b->distance < distance) 
            return nullptr;

        void *stored_key = (u8*)raw + sizeof(bucket);

        if (b->hash == hash && memcmp(stored_key, key, key_size) == 0) {
            return (u8*)stored_key + key_size;
        }

        index = (index + 1 >= map_list.capacity) ? 0 : index + 1;
        distance++;
    }
}

dint cst::untyped_map::insert(void *key, void *val) {
    if (!initialized || map_list.capacity == 0)
        return -1;

    if ((used + 1) * 10 >= map_list.capacity * 7) {
        rehash(map_list.capacity * 10 / 7);
    }

    dint hash = hasher(key, key_size);
    dint entry_size = sizeof(bucket) + key_size + val_size;

    u8 *tmp = new u8[entry_size]; 

    bucket *tmp_bucket = (bucket*)tmp;
    tmp_bucket->hash = hash;
    tmp_bucket->distance = 0;
    tmp_bucket->occupied = true;

    void *tmp_key = tmp + sizeof(bucket);
    void *tmp_val = (u8*)tmp_key + key_size;

    memcpy(tmp_key, key, key_size);
    memcpy(tmp_val, val, val_size);

    dint index = (hash % map_list.capacity + map_list.capacity) % map_list.capacity;
    u8 *swap_buf = new u8[entry_size];

    while (true) {
        void *raw = map_list[index];
        bucket *current = (bucket*)raw;

        void *current_key = (u8*)raw + sizeof(bucket);
        void *current_val = (u8*)current_key + key_size;

        if (!current->occupied) {
            memcpy(raw, tmp, entry_size);
            delete[] tmp;
            delete[] swap_buf;
            used++;
            return 0;
        }

        if (current->hash == tmp_bucket->hash && memcmp(current_key, tmp_key, key_size) == 0) {
            memcpy(current_val, tmp_val, val_size);
            delete[] tmp;
            delete[] swap_buf;
            return 1;
        }

        if (current->distance < tmp_bucket->distance) {
            memcpy(swap_buf, raw, entry_size);
            memcpy(raw, tmp, entry_size);
            memcpy(tmp, swap_buf, entry_size);
            tmp_bucket = (bucket*)tmp;
        }

        index = (index + 1 >= map_list.capacity) ? 0 : index + 1;
        tmp_bucket->distance++;
    }
}

void cst::untyped_map::remove(void *key) {
    if (!initialized || used == 0 || map_list.capacity == 0)
        return;

    dint hash = hasher(key, key_size);
    dint index = (hash % map_list.capacity + map_list.capacity) % map_list.capacity;
    dint distance = 0;

    while (true) {
        void *raw = map_list[index];
        bucket *b = (bucket*)raw;

        void *stored_key = (u8*)raw + sizeof(bucket);

        if (!b->occupied || b->distance < distance) return;
        if (b->hash == hash && memcmp(stored_key, key, key_size) == 0) break;

        index = (index + 1 >= map_list.capacity) ? 0 : index + 1;
        distance++;
    }

    dint hole = index;
    dint entry_size = sizeof(bucket) + key_size + val_size;

    while (true) {
        dint next = (hole + 1 >= map_list.capacity) ? 0 : hole + 1;
        void *next_raw = map_list[next];
        bucket *next_b = (bucket*)next_raw;

        if (!next_b->occupied || next_b->distance == 0) break;

        memcpy(map_list[hole], next_raw, entry_size);
        
        bucket *hole_b = (bucket*)map_list[hole];
        hole_b->distance--;

        hole = next;
    }
    
    bucket *final_b = (bucket*)map_list[hole];
    final_b->occupied = false;

    used--;
}

void cst::untyped_map::rehash(dint new_capacity) {
    if (new_capacity <= map_list.capacity) return;
    
    dint old_capacity = map_list.capacity;
    dint entry_size = sizeof(bucket) + key_size + val_size;
    
    u8 *old_data = new u8[old_capacity * entry_size];
    for (dint i = 0; i < old_capacity; i++) {
        memcpy(old_data + i * entry_size, map_list[i], entry_size);
    }

    map_list.init(entry_size);
    map_list.resize(new_capacity);
    
    used = 0;

    for (dint i = 0; i < map_list.capacity; i++) {
        bucket *b = (bucket*)map_list[i];
        b->occupied = false;
        b->distance = 0;
        b->hash = 0;
    }

    for (dint i = 0; i < old_capacity; i++) {
        void *raw = old_data + i * entry_size;
        bucket *b = (bucket*)raw;

        if (b->occupied) {
            void *key = (u8*)raw + sizeof(bucket);
            void *val = (u8*)key + key_size;
            insert(key, val);
        }
    }

    delete[] old_data;
}

void *cst::untyped_map::operator[](void *key) {
    void *result = get(key);
    if (!result) {
        u8 *default_val = new u8[val_size];
        memset(default_val, 0, val_size);
        
        insert(key, default_val);
        delete[] default_val; 
        result = get(key);
    }
    return result;
}