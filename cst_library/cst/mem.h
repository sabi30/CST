#pragma once

#include "func.h"
#include "type.h"
#include "flags.h"

namespace cst {
    enum PROT : u32 {
         NONE = 0,
         READ = 1 << 0,
         WRITE = 1 << 1,
         EXEC = 1 << 2,  
    };


    void *mmap(dint size, u8 prot_flags = PROT::READ | PROT::WRITE, i32 fd = -1);
    u32 unmap(void *map, dint size);
    u32 mmodify(void *ptr, dint size, u8 prot_flags);

    void *malloc(dint size);       
    void *calloc(dint type_size, dint size);             
    void *realloc(void*, dint);                            
    void free(void*);                                      

    // c++ extension
    template<typename T>
    T *alloc(dint size) {
        T* new_alloc = static_cast<T*>(malloc(sizeof(T) + size));
        *new_alloc = T{};
        return new_alloc;
    }

    template<typename T>
    T *alloc() {
        T* new_alloc = static_cast<T*>(malloc(sizeof(T)));
        *new_alloc = T{};
        return new_alloc;
    }

    template<typename T>
    T *malloc(dint size) {
        T* new_alloc = static_cast<T*>(malloc(size));
        return new_alloc;
    }

    template<typename T>
    T *realloc(dint type_size, dint size) {
        return static_cast<T*>(calloc(type_size, size));
    }

    void pre_alloc();
    void clear_memory();

    extern void* (*galloc)(dint);                 // MAIN ALLOC
    extern void (*gfree)(void*);                  // MAIN FREE
    extern void *(*grealloc)(void*, dint);        // MAIN REALLOC

    struct memoryinfo_t {
        bool read;
        bool write;
        bool execute;
    };

    namespace memory_profiler {
        extern dint MEMORY_USAGE_PEAK;
        extern dint MEMORY_USAGE_AVG;
        extern dint MEMORY_USAGE;

        extern dint MAP_USAGE_PEAK;
        extern dint MAP_USAGE_AVG;
        extern dint MAP_USAGE;

        void map_allocated(dint size);
        void map_freed(dint size);
        
        void allocated(dint size);
        void freed(dint size);
    }
}