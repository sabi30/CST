#pragma once

#include "type.h"

namespace cst {
    using THREAD_FUNC = void *(*)(void *args);
    using thread_id = sint;

    thread_id spawn_thread(THREAD_FUNC, void *args);
    void *join_thread(thread_id);
    bool detach_thread(thread_id);

    unsigned int get_tid(void);
}