#pragma once
#include "type.h"

namespace cst::atomic {

    struct spinlock {
        volatile unsigned char state = 0;

        inline void lock() {
            while (__atomic_test_and_set(&state, __ATOMIC_ACQUIRE)) {

                #if defined(__x86_64__) || defined(_M_X64)
                __builtin_ia32_pause();
                #elif defined(__aarch64__)
                __asm__ __volatile__("yield" ::: "memory");
                #endif
            }
        }

        inline void unlock() {
            __atomic_clear(&state, __ATOMIC_RELEASE);
        }
    };

    struct mutex {
        void init();
        
        void lock();
        void unlock();

        void destroy();
    };

}