# CST / C & C++ Standard Library ((Downforce Studio))
**Version:** 0.0.0

**CST** is an unified, lightweight C and C++ Library.

### Purpose

* **Zero Template overhead:** No Template nesting, by providing Template wrappers
* **Unified Cross-Platform API:** Fixing the API gap between Windows and POSIX
* **Custom User-Defined Implementations:** Custom Allocators, Custom Operators

### Status
* **C++ Status:** Active, full priority.
* **C Status:** Closed, Coming soon. ( why: I will downgrade the C++ functions to C functions, this means C Status will be active after C++ has a full version )

### Supported Build Configurations
* **Compilers:** Clang++, g++
* **Build Files:** Meson, CMake (Coming Soon)

### Integration
* **Dynamic Library:** full priority, removing header compile times
* **Static Library:** full priority
* **Free Standing Static Library:** coming later

### type.h
* **Integers:** i8, i16, i32, i64, i128, u8, u16, u32, u64, u128
* **Size:** dint (aka size_t), sint (aka ssize_t)
* **Floats:** f16, f32, f64, f128, fp16, bf16

### simd.h
* **Integers:**  u8x16, i32x4, i32x8, i64x2, 
* **Floats:** f32x2, f32x4

First source release comes at Version: 0.1.0
