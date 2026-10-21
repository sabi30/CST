#pragma once

#include "type.h"

namespace cst {
    i32 get_random_linux(void);

    void scramble();
    void seed(u32 seed);
    f64 rand();
}