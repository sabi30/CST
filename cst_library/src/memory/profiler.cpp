#include "mem.h"

namespace {
    dint submit_count = 0;
    dint MEMORY_ALLTIME_USAGE = 0;
    dint map_submit_count = 0;
    dint MAP_ALLTIME_USAGE = 0;
}

namespace cst::memory_profiler {
    dint MEMORY_USAGE_PEAK = 0;
    dint MEMORY_USAGE_AVG = 0;
    dint MEMORY_USAGE = 0;

    dint MAP_USAGE_PEAK = 0;
    dint MAP_USAGE_AVG = 0;
    dint MAP_USAGE = 0;
}

void cst::memory_profiler::map_allocated(dint size) {
    MAP_USAGE += size;
    MAP_ALLTIME_USAGE += size;
    if (MAP_USAGE_PEAK < MAP_USAGE) {
        MAP_USAGE_PEAK = MAP_USAGE;
    }

    map_submit_count++;
    MAP_USAGE_AVG = MAP_ALLTIME_USAGE / map_submit_count;
}

void cst::memory_profiler::map_freed(dint size) {
    if ((MAP_USAGE - size) < 0) MAP_USAGE = 0; else MAP_USAGE = MAP_USAGE - size;

    submit_count++;
    MAP_USAGE_AVG = MAP_ALLTIME_USAGE / submit_count;
}

void cst::memory_profiler::allocated(dint size) {  
    MEMORY_USAGE += size;
    MEMORY_ALLTIME_USAGE += size;
    if (MEMORY_USAGE_PEAK < MEMORY_USAGE) {
        MEMORY_USAGE_PEAK = MEMORY_USAGE;
    }

    submit_count++;
    MEMORY_USAGE_AVG = MEMORY_ALLTIME_USAGE / submit_count;
}

void cst::memory_profiler::freed(dint size) {
    if ((MEMORY_USAGE - size) < 0) MEMORY_USAGE = 0; else MEMORY_USAGE = MEMORY_USAGE - size;

    submit_count++;
    MEMORY_USAGE_AVG = MEMORY_ALLTIME_USAGE / submit_count;
}
