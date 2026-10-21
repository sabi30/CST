#include "info.h"

sContainer *start_container = nullptr;
sContainer *last_container = nullptr;
sContainer *free_containers[SIZE_TYPE::COUNT] = {nullptr};

thread_local sContainer *thread_container[SIZE_TYPE::COUNT] = {nullptr};

cst::atomic::spinlock allocator_spinlock;

// public 
namespace cst {
    void* (*galloc)(dint) = cst::malloc;                 
    void (*gfree)(void*) = cst::free;                  
    void *(*grealloc)(void*, dint) = cst::realloc;    
}
