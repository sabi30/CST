#include "info.h"
#include "mem_util.h"
#include "io.h"
#include "clock.h"

#include "atomic.h"

void *cst::malloc(dint size) {
    if (unlikely(!size)) return nullptr;

    SIZE_TYPE type = get_type(size);

    #if ENABLE_PROFILER
    memory_profiler::allocated(TYPE_TO_SIZE[type]);
    #endif

    if (unlikely(type == MEMORY_MAPPED)) {
        sBlock *mmap_block = reinterpret_cast<sBlock*>(mmap(sizeof(sBlock) + size));
        if (unlikely(!mmap_block)) return nullptr;
        mmap_block->type = MEMORY_MAPPED;
        mmap_block->size = size;
        return mmap_block + 1;
    }

    allocator_spinlock.lock();

    sContainer *free_container = free_containers[type];

    // fast path
    if (likely(free_container && free_container->free)) {
        sBlock *block = free_container->free;
        free_container->free = block->next;

        allocator_spinlock.unlock();
        return block + 1;
    }

    // slow path
    allocator_spinlock.unlock();

    free_container = _create_container(type, last_container);
    if (unlikely(!free_container)) {

        return nullptr;
    }

    allocator_spinlock.lock();

    if (likely(free_containers[type] != nullptr)) {
        _destroy_container(free_container);
        sContainer *existing_container = free_containers[type];
        sBlock *block = existing_container->free;
        existing_container->free = block->next;

        allocator_spinlock.unlock();

        return block + 1;
    }

    last_container = free_container;
    free_containers[type] = free_container;

    sBlock *block = free_container->free;
    free_container->free = block->next;

    allocator_spinlock.unlock();
    return block + 1;
}

void *cst::realloc(void *ptr, dint size) {
    if (!size) return nullptr;
    if (!ptr) return malloc(size);

    sBlock *block_header = reinterpret_cast<sBlock*>(ptr) - 1;
    dint block_size = block_header->size;

    void *new_ptr = malloc(size);
    if (!new_ptr) {
        return nullptr;
    }

    dint copy_size = (block_size < size) ? block_size : size;

    memcpy(new_ptr, ptr, copy_size);
    free(ptr);
    return new_ptr;
}
