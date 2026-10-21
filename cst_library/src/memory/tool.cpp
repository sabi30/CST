#include "info.h"

static u64 CONTAINER_COUNTER = 0;

static void _init_blocks(sContainer *container) {
    u32 DATA_SIZE = TYPE_TO_SIZE[container->type];
    u32 stride = (sizeof(sBlock) + DATA_SIZE + 7) & ~7U;

    sBlock *prev_block = nullptr;
    
    dint i = 0;
    while (i + stride <= container->size && (i32)(container->size - (i + stride)) >= stride) {
        sBlock *block = reinterpret_cast<sBlock*>(container->payload + i);
        block->next = nullptr;
        block->type = container->type;
        block->size = DATA_SIZE; // direct size call
        block->parent = container; // direct free

        if (prev_block) {
            prev_block->next = block;
        }

        prev_block = block;

        i += stride;
    }

    container->free = reinterpret_cast<sBlock*>(container->payload);
}

sContainer *_create_container(SIZE_TYPE type, sContainer *prev_container) {
    u32 alloc_size = TYPE_TO_SIZE_CONTAINER[type];
    
    sContainer *container = (sContainer*)cst::mmap(alloc_size + sizeof(sContainer));
    if (!container) return nullptr;
     
    container->payload = (u8*)(container + 1);
    container->size = alloc_size;
    container->type = type;
    container->virtual_size = alloc_size / TYPE_TO_SIZE[type];
    container->used = 0;
    container->id = CONTAINER_COUNTER++;
    container->thread_id = 0;    
    container->next = nullptr;
    
    container->prev = prev_container;

    if (prev_container) {
        prev_container->next = container;
    }

    _init_blocks(container);
    return container;
}

void _destroy_container(sContainer* container) {
    if (!container) return;

    if (container->prev) {
        container->prev->next = container->next;
    }
    
    if (container->next) {
        container->next->prev = container->prev;
    }
    
    cst::unmap(container, container->size + sizeof(sContainer));
}