#define symhidden __attribute__((visibility("hidden")))
#define symvisible __attribute__((visibility("default")))

#define HEADER_HIDDEN _Pragma("GCC visibility push(hidden)")
#define HEADER_VISIBLE _Pragma("GCC visibility pop")

#define unlikely(x) __builtin_expect(!!(x), 0)
#define likely(x) __builtin_expect(!!(x), 1)