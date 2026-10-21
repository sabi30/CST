#include "math.h"

f32 cst::abs(f32 num) {
    if (num < 0) return -num;
    return num;
}

f32 cst::max(f32 n, f32 max) {
    if (n < max) return max;
    return n;
}

f32 cst::min(f32 n, f32 min) {
    if (n > min) return min;
    return n;
}

f32 cst::clamp(f32 start, f32 max, f32 min) {
    if (start > min) return min;
    if (start < max) return max;
    return start;
}

f32 cst::sqrt(f32 num) {
    if (num < 0.0) return 0.0;
    if (num == 0.0) return 0.0;

    f32 x = num;
    f32 y = 1.0;
    f64 tolerance = 0.0001;

    while (x - y > tolerance) {
        x = (x + y) / 2.0;
        y = num / x;
    }

    return x;
}

// float 64

f64 cst::abs(f64 num) {
    if (num < 0) return -num;
    return num;
}

f64 cst::max(f64 n, f64 max) {
    if (n < max) return max;
    return n;
}

f64 cst::min(f64 n, f64 min) {
    if (n > min) return min;
    return n;
}

f64 cst::clamp(f64 start, f64 max, f64 min) {
    if (start > min) return min;
    if (start < max) return max;
    return start;
}

f64 cst::sqrt(f64 num) {
    if (num < 0.0) return 0.0;
    if (num == 0.0) return 0.0;

    f64 x = num;
    f64 y = 1.0;
    f64 tolerance = 0.0001;

    while (x - y > tolerance) {
        x = (x + y) / 2.0;
        y = num / x;
    }

    return x;
}

f32 cst::lerp(f32 a, f32 b, f32 t) {
    return a + t * (a - b);
}

f64 cst::lerp(f64 a, f64 b, f64 t) {
    return a + t * (a - b);
}

f32 cst::fmod(f32 x, f32 y) {
    if (y == 0.0f) return 0.0f;
    
    f32 division = x / y;
    f32 int_part = (division < 0.0f) ? static_cast<f32>(static_cast<int>(-division)) * -1.0f 
                                        : static_cast<f32>(static_cast<int>(division));
                                        
    return x - int_part * y;
}

f64 cst::fmod(f64 x, f64 y) {
    if (y == 0.0) return 0.0;
    
    f64 division = x / y;
    f64 int_part = (division < 0.0) ? static_cast<f64>(static_cast<long long>(-division)) * -1.0 
                                    : static_cast<f64>(static_cast<long long>(division));
                                    
    return x - int_part * y;
}

f32 cst::exp(f32 x) {
    if (x == 0.0f) return 1.0f;
    if (x < -87.0f) return 0.0f; 
    if (x > 88.7f) return 3.40282347e+38f; 

    const f32 ln2_inv = 1.4426950408889634f; 
    const f32 ln2 = 0.6931471805599453f;

    f32 z = x * ln2_inv;
    int k = static_cast<int>(z);
    if (z < 0.0f && static_cast<f32>(k) != z) k--;

    f32 r = x - static_cast<f32>(k) * ln2;

    f32 poly = 1.0f + r * (1.0f + r * (0.5f + r * (0.16666667f + r * (0.04166667f + r * 0.00833333f))));

    // some way to speed up shit. magic speed 
    union {
        u32 i;
        f32 f;
    } u;
    
    u.i = static_cast<u32>(k + 127) << 23;

    return poly * u.f;
}

f64 cst::exp(f64 x) {
    if (x == 0.0) return 1.0;
    if (x < -708.0) return 0.0;
    if (x > 709.7) return 1.7976931348623157e+308;

    const f64 ln2_inv = 1.44269504088896340359;
    const f64 ln2 = 0.69314718055994530942;

    f64 z = x * ln2_inv;
    long long k = static_cast<long long>(z);
    if (z < 0.0 && static_cast<f64>(k) != z) k--;

    f64 r = x - static_cast<f64>(k) * ln2;

    // at this point i dont know anymore. forgive me for using gemini once for this shit
    f64 poly = 1.0 + r * (1.0 + r * (0.5 + r * (0.16666666666666666f + r * (0.041666666666666664f + r * (0.008333333333333333f + r * 0.0013888888888888888f)))));

    union {
        u64 i;
        f64 f;
    } u;
    
    u.i = static_cast<u64>(k + 1023) << 52;

    return poly * u.f;
}

f32 cst::log(f32 x) {
    if (x <= 0.0f) return 0.0f; 

    union {
        f32 f;
        u32 i;
    } u = { x };

    int e = static_cast<int>((u.i >> 23) & 0xFF) - 127;
    u.i = (u.i & 0x007FFFFF) | 0x3F800000; 
    f32 m = u.f;

    f32 z = (m - 1.0f) / (m + 1.0f);
    f32 z2 = z * z;
    
    f32 series = z * (2.0f + z2 * (0.66666667f + z2 * (0.4f + z2 * 0.28571429f)));

    const f32 ln2 = 0.6931471805599453f;
    return series + static_cast<f32>(e) * ln2;
}

f64 cst::log(f64 x) {
    if (x <= 0.0) return 0.0;

    union {
        f64 f;
        u64 i;
    } u = { x };

    long long e = static_cast<long long>((u.i >> 52) & 0x7FF) - 1023;
    u.i = (u.i & 0x000FFFFFFFFFFFFFULL) | 0x3FF0000000000000ULL;
    f64 m = u.f;

    f64 z = (m - 1.0) / (m + 1.0);
    f64 z2 = z * z;
    f64 series = z * (2.0 + z2 * (0.6666666666666666 + z2 * (0.4 + z2 * (0.2857142857142857 + z2 * 0.2222222222222222))));

    const f64 ln2 = 0.69314718055994530942;
    return series + static_cast<f64>(e) * ln2;
}

f32 cst::pow(f32 base, f32 exp_val) {
    if (exp_val == 0.0f) return 1.0f;
    if (base == 0.0f) return 0.0f;
    if (base == 1.0f) return 1.0f;
    
    int int_exp = static_cast<int>(exp_val);
    if (static_cast<f32>(int_exp) == exp_val) {
        bool negative = false;
        if (int_exp < 0) {
            negative = true;
            int_exp = -int_exp;
        }

        f32 result = 1.0f;
        f32 current_base = base;
        while (int_exp > 0) {
            if (int_exp & 1) result *= current_base;
            current_base *= current_base;
            int_exp >>= 1;
        }
        return negative ? (1.0f / result) : result;
    }

    if (base < 0.0f) return 0.0f; 
    return cst::exp(exp_val * cst::log(base));
}

f64 cst::pow(f64 base, f64 exp_val) {
    if (exp_val == 0.0) return 1.0;
    if (base == 0.0) return 0.0;
    if (base == 1.0) return 1.0;

    long long int_exp = static_cast<long long>(exp_val);
    if (static_cast<f64>(int_exp) == exp_val) {
        bool negative = false;
        if (int_exp < 0) {
            negative = true;
            int_exp = -int_exp;
        }

        f64 result = 1.0;
        f64 current_base = base;
        while (int_exp > 0) {
            if (int_exp & 1) result *= current_base;
            current_base *= current_base;
            int_exp >>= 1;
        }
        return negative ? (1.0 / result) : result;
    }

    if (base < 0.0) return 0.0;
    return cst::exp(exp_val * cst::log(base));
}