#include "info.h"

static bool PRE_ALLOCATED = false;

void cst::pre_alloc() { 
    if (PRE_ALLOCATED) return;

    start_container = _create_container(SIZE_TYPE::TINY, nullptr);
    free_containers[SIZE_TYPE::TINY] = start_container;

    start_container->next = _create_container(SIZE_TYPE::SMALL, start_container);
    free_containers[SIZE_TYPE::SMALL] = start_container->next;

    start_container->next->next = _create_container(SIZE_TYPE::MEDIUM, start_container->next);
    free_containers[SIZE_TYPE::MEDIUM] = start_container->next->next;

    start_container->next->next->next = _create_container(SIZE_TYPE::BIG, start_container->next->next);
    free_containers[SIZE_TYPE::BIG] = start_container->next->next->next;

    last_container = free_containers[SIZE_TYPE::BIG];

    PRE_ALLOCATED = true;
}

void cst::clear_memory() {  
    sContainer *container = start_container;
    while (container) {
        sContainer *enemy = container;
        container = container->next;
        _destroy_container(enemy);
    }

    for (dint i = 0; i < 6; i++) {
        free_containers[i] = 0;
    }

    last_container = nullptr;

    PRE_ALLOCATED = false;
}