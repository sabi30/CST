#pragma once

#include "type.h"
#include "mem.h"
#include "flags.h"
#include "atomic.h"

#include "macro.h"

HEADER_HIDDEN
 
#define CACHE_ALIGNED alignas(128)

// pre allocated
#define SIZE_THREAD 128U
#define SIZE_THREAD_CONTAINER (SIZE_THREAD * 20)

#define SIZE_TINY          64U          // 64 bytes
#define SIZE_TINY_CONTAINER (SIZE_TINY * 400)       

#define SIZE_SMALL         512U        // 500 bytes
#define SIZE_SMALL_CONTAINER (SIZE_SMALL * 200)

#define SIZE_MEDIUM        5120U       // 5 kilobytes
#define SIZE_MEDIUM_CONTAINER (SIZE_MEDIUM * 100)

#define SIZE_BIG           11200U     // 112 kilobytes
#define SIZE_BIG_CONTAINER (SIZE_BIG * 50)

#define START_TIMER_DEAD 20U


enum SIZE_TYPE : u8 {
    TINY, // 64 b
    SMALL, // 5 kb
    MEDIUM, // 50 kb
    BIG, // 2 mb
    MEMORY_MAPPED, // user defined ( memory mapped )
    COUNT
};

const u32 TYPE_TO_SIZE[4] = {
    SIZE_TINY, SIZE_SMALL, SIZE_MEDIUM, SIZE_BIG
};

const u32 TYPE_TO_SIZE_CONTAINER[4] = {
    SIZE_TINY_CONTAINER, SIZE_SMALL_CONTAINER, SIZE_MEDIUM_CONTAINER, SIZE_BIG_CONTAINER
};

__attribute__((always_inline)) static inline SIZE_TYPE get_type(dint size) {
    bool is_tiny   = (size <= SIZE_TINY);
    bool is_small  = (size <= SIZE_SMALL);
    bool is_medium = (size <= SIZE_MEDIUM);
    bool is_big    = (size <= SIZE_BIG);

    u32 type = !is_tiny + !is_small + !is_medium + !is_big;
    return static_cast<SIZE_TYPE>(type);
}

struct alignas(32) sBlock {
    sBlock *next;
    u32 size;
    SIZE_TYPE type;
    void *parent;
};

struct CACHE_ALIGNED sContainer {
    // ptrs
    sBlock *free = nullptr;
    sContainer *next = nullptr;
    sContainer *prev = nullptr;
    u8 *payload = nullptr;

    // threading
    u32 thread_id = 0;
    u64 id = 0;

    // info
    u32 size = 0;
    u32 virtual_size = 0;
    u32 used = 0;
    SIZE_TYPE type;
    u64 timer_start_using = 0;
};

extern sContainer *start_container;
extern sContainer *last_container;
extern sContainer *free_containers[SIZE_TYPE::COUNT];
    
extern thread_local sContainer thread_containers[SIZE_TYPE::MEDIUM];

// handles memory mapping and prev container linking
sContainer *_create_container(SIZE_TYPE, sContainer *prev_container);

// handles unmapping and prev container linking + next container linking
void _destroy_container(sContainer*);

extern cst::atomic::spinlock allocator_spinlock; 

HEADER_VISIBLE