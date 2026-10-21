#include "info.h"

void cst::free(void *ptr) {
    if (!ptr) return;
    
    sBlock *block = reinterpret_cast<sBlock*>(ptr) - 1;
    if (block->type == MEMORY_MAPPED) {
        unmap(block, sizeof(sBlock) + block->size);
        return;
    }
    
    sContainer *container = reinterpret_cast<sContainer*>(block->parent);

    if (!container) return;

    allocator_spinlock.lock();

    block->next = container->free;
    container->free = block;

    #if ENABLE_PROFILER
    memory_profiler::freed(TYPE_TO_SIZE[container->type]);
    #endif

    SIZE_TYPE type = container->type;

    /*if (!container->used && container->timer_start_using > START_TIMER_DEAD) {
        if (free_containers[block->type] == container) {
            if (container->next) {free_containers[block->type] = container->next; goto skip; }
            if (container->prev) free_containers[block->type] = container->prev;
        }
skip:
        _destroy_container(container);
        return;
    }*/
    
    if (!free_containers[type] || !free_containers[type]->free) {
        free_containers[type] = container;
    }

    allocator_spinlock.unlock();
}