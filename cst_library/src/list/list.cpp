#include "list.h"
#include "mem.h"
#include "mem_util.h"
#include "io.h"

void cst::untyped_list::copy(const untyped_list& other) {
    size = other.size;
    capacity = other.capacity;
    val_size = other.val_size;

    if (other.ptr && other.size > 0) {
        ptr = galloc(other.capacity * other.val_size);
        memcpy(ptr, other.ptr, other.size * other.val_size);
    }
}

void cst::untyped_list::move(untyped_list&& other) noexcept {
    ptr = other.ptr;
    size = other.size;
    capacity = other.capacity;
    val_size = other.val_size;

    other.ptr = nullptr;
    other.size = 0;
    other.capacity = 0;
}

dint cst::untyped_list::insert(const void *val) {
    if (size >= capacity) {
        if (fixed_capacity) {
            return -1;
        }

        capacity = capacity == 0 ? 4 : capacity * 2;
        void *new_list = grealloc(ptr, capacity * val_size);
        if (!new_list) return -1;
        ptr = new_list;
    }

    char *dest = (char*)ptr + (size * val_size);
    memcpy(dest, val, val_size);
    return size++;
}

void cst::untyped_list::remove(const dint key) {
    if (key < 0 || key >= size) return;

    char *target = (char*)ptr + (key * val_size);
    char *next = target + val_size;
    dint bytes_to_move = (size - key - 1) * val_size;

    if (bytes_to_move > 0) {
        memmove(target, next, bytes_to_move);
    }

    size--;

    if (size < capacity * 0.5f && capacity * 0.5f > 4) {
        if (fixed_capacity) {
            return;
        }

        capacity = capacity * 0.5f;
        void *new_list = grealloc(ptr, capacity * val_size);
        if (!new_list) return;
        ptr = new_list;
    }
}

dint cst::untyped_list::find(void *addr) {
    if (!addr) {
        return DINT_MAX;
    }

    dint start = reinterpret_cast<dint>(ptr);
    dint end = reinterpret_cast<dint>(addr);

    if ((end < start) || (end >= start + (val_size * size))) {
        return DINT_MAX;
    }

    dint offset = end - start;

    if (offset % val_size != 0) {
        return DINT_MAX;
    }

    dint index = offset / val_size;

    return index;
}

void cst::untyped_list::insert_first(const void *val) {
    if (size >= capacity) {
        capacity = capacity == 0 ? 4 : capacity * 2;
        void *new_list = grealloc(ptr, capacity * val_size);
        if (!new_list) return;
        ptr = new_list;
    }

    if (size > 0) {
        char *dest = (char*)ptr + val_size;
        memmove(dest, ptr, size * val_size);
    }

    memcpy(ptr, val, val_size);
    size++;
}

void cst::untyped_list::remove_first(const dint key) {
    remove(key);
}

void cst::untyped_list::resize(dint new_size) {
    if (!ptr) {
        ptr = cst::malloc(new_size * val_size);
        capacity = new_size;
        size = new_size;
        return;
    }
    void *new_ptr = cst::realloc(ptr, new_size * val_size);
    if (!new_ptr) {
        cst::print("realloc failed\n");
        return;
    }

    ptr = new_ptr;
    capacity = new_size;
    size = new_size;
}

void cst::untyped_list::reserve(dint reserve_size) {
    if (ptr || reserve_size <= capacity) return;
    ptr = galloc(reserve_size * val_size); // Unified to galloc
    capacity = reserve_size;
}

void *cst::untyped_list::operator[](dint key) {
    if (key < 0 || key >= size) return nullptr;
    return (char*)ptr + (key * val_size);
}

const void *cst::untyped_list::operator[](dint key) const {
    if (key < 0 || key >= size) return nullptr;
    return (const char*)ptr + (key * val_size);
}

cst::untyped_list& cst::untyped_list::operator=(const cst::untyped_list& other) {
    if (this != &other) {
        if (ptr) gfree(ptr);
        val_size = other.val_size;
        size = other.size;
        capacity = other.capacity;
        if (other.ptr && other.size > 0) {
            ptr = galloc(capacity * val_size);
            memcpy(ptr, other.ptr, size * val_size);
        } else {
            ptr = nullptr;
        }
    }
    return *this;
}

cst::untyped_list& cst::untyped_list::operator=(untyped_list&& other) noexcept {
    if (this != &other) {
        if (ptr) gfree(ptr);
        ptr = other.ptr;
        val_size = other.val_size;
        size = other.size;
        capacity = other.capacity;
        other.ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

cst::untyped_list& cst::untyped_list::operator<<(const untyped_list& other) {
    if (other.val_size != val_size) return *this;
    for (dint i = 0; i < other.size; i++) {
        insert(other[i]);
    }
    return *this;
}

void *cst::untyped_list::begin(void) {
    return ptr;
}

void *cst::untyped_list::end(void) {
    if (size <= 0) {
        return ptr;
    }
    return static_cast<u8*>(ptr) + (size * val_size);
}

void cst::untyped_list::init(dint s) {
    ptr = nullptr;
    size = 0;
    capacity = 0;
    val_size = s;
}

void cst::untyped_list::clear(void) {
    if (ptr) gfree(ptr);
    size = 0;
    capacity = 0;
}
