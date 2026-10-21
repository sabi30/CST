#pragma once

#include "type.h"
#include "simd.h"

#define CST_MATH_EXT

namespace cst {

    f32 abs(f32);
    f64 abs(f64);

    f32 sqrt(f32); 
    f64 sqrt(f64);

    f32 clamp(f32, f32, f32);
    f64 clamp(f64, f64, f64);

    f32 max(f32, f32);
    f64 max(f64, f64);

    f32 min(f32, f32);
    f64 min(f64, f64);

    f32 lerp(f32, f32, f32);
    f64 lerp(f64, f64, f64);

    f32 fmod(f32, f32);
    f64 fmod(f64, f64);

    f32 exp(f32);
    f64 exp(f64);

    f32 log(f32);
    f64 log(f64);

    f32 pow(f32, f32);
    f64 pow(f64, f64);

    #ifdef CST_MATH_EXT

    struct vec2 {
        union {
            simd::f32x2 data;
            struct {
                f32 x, y;
            };
        };

        vec2() : data{0,0} {}
        vec2(f32 x, f32 y) : data{x, y} {}
        vec2(simd::f32x2 simd) : data(simd) {}

        // add
        vec2& operator+=(const vec2 opp) {
            this->data += opp.data;
            return *this;
        }

        vec2 operator+(const vec2 opp) const {
            return vec2(this->data + opp.data);
        }

        // sub
        vec2& operator-=(const vec2 opp) {
            this->data -= opp.data;
            return *this;
        }

        vec2 operator-(const vec2 opp) const {
            return vec2(this->data - opp.data);
        }

        // mul
        vec2& operator*=(const vec2 opp) {
            this->data *= opp.data;
            return *this;
        }

        vec2 operator*(const vec2 opp) const {
            return vec2(this->data * opp.data);
        }

        // div
        vec2& operator/=(const vec2 opp) {
            this->data /= opp.data;
            return *this;
        }

        vec2 operator/(const vec2 opp) const {
            return vec2(this->data / opp.data);
        }

        vec2 pow(const f32 num) const {
            return vec2(cst::pow(x, num), cst::pow(y, num));
        }

        f32 length() const {
            simd::f32x2 squared = data * data;
            return cst::sqrt(squared[0] + squared[1]);
        }

        f32 dot(const vec2 opp) const {
            simd::f32x2 mul = data * opp.data; 
            return mul[0] + mul[1];
        }

        f32 cross(const vec2 opp) const {
            return (x * opp.y) - (y * opp.x);
        }
    };
    
    struct vec3 {
        union {
            simd::f32x4 data;
            struct {
                f32 x, y, z, w; // who is he?? (w)
            };
            struct {
                f32 r, g, b, a; // who is he?? (a)
            };
        };

        vec3() : data{0,0,0,0} {}
        vec3(f32 x, f32 y, f32 z) : data{x, y, z} {}
        vec3(simd::f32x4 simd) : data(simd) {}

        // add
        vec3& operator+=(const vec3 opp) {
            this->data += opp.data;
            return *this;
        }

        vec3 operator+(const vec3 opp) const {
            return vec3(this->data + opp.data);
        }

        vec3 operator+(const f32 opp) const {
            return vec3(this->data + opp);
        }

        // sub
        vec3& operator-=(const vec3 opp) {
            this->data -= opp.data;
            return *this;
        }

        vec3 operator-(const vec3 opp) const {
            return vec3(this->data - opp.data);
        }

        vec3 operator-(const f32 opp) const {
            return vec3(this->data - opp);
        }

        // mul
        vec3& operator*=(const vec3 opp) {
            this->data *= opp.data;
            return *this;
        }

        vec3 operator*(const vec3 opp) const {
            return vec3(this->data * opp.data);
        }

        vec3 operator*(const f32 opp) const {
            return vec3(this->data * opp);
        }

        // div
        vec3& operator/=(const vec3 opp) {
            this->data /= opp.data;
            return *this;
        }

        vec3 operator/(const vec3 opp) const {
            return vec3(this->data / opp.data);
        }

        vec3 operator/(const f32 opp) const {
            return vec3(this->data / opp);
        }

        vec3 pow(const f32 num) const {
            return vec3(cst::pow(x, num), cst::pow(y, num), cst::pow(z, num));
        }

        f32 length() const {
            simd::f32x4 squared = data * data;
            return cst::sqrt(squared[0] + squared[1] + squared[2]);
        }

        f32 dot(const vec3 opp) const {
            simd::f32x4 mul = data * opp.data; 
            return mul[0] + mul[1] + mul[2];
        }

        vec3 cross(const vec3 opp) const {
            return vec3(
                (y * opp.z) - (z * opp.y),
                (z * opp.x) - (x * opp.z),
                (x * opp.y) - (y * opp.x)
            );
        }
    };

    struct vec4 {
        union {
            simd::f32x4 data;
            struct {
                f32 x, y, z, w; // who is he?? (w)
            };
            struct {
                f32 r, g, b, a; // who is he?? (a)
            };
        };

        vec4() : data{0,0,0,0} {}
        vec4(f32 x, f32 y, f32 z, f32 w) : data{x, y, z, w} {}
        vec4(simd::f32x4 simd) : data(simd) {}

        // add
        vec4& operator+=(const vec4 opp) {
            this->data += opp.data;
            return *this;
        }

        vec4 operator+(const vec4 opp) const {
            return vec4(this->data + opp.data);
        }

        vec4 operator+(const f32 opp) const {
            return vec4(this->data + opp);
        }

        // sub
        vec4& operator-=(const vec4 opp) {
            this->data -= opp.data;
            return *this;
        }

        vec4 operator-(const vec4 opp) const {
            return vec4(this->data - opp.data);
        }

        vec4 operator-(const f32 opp) const {
            return vec4(this->data - opp);
        }

        // mul
        vec4& operator*=(const vec4 opp) {
            this->data *= opp.data;
            return *this;
        }

        vec4 operator*(const vec4 opp) const {
            return vec4(this->data * opp.data);
        }

        vec4 operator*(const f32 opp) const {
            return vec4(this->data * opp);
        }

        // div
        vec4& operator/=(const vec4 opp) {
            this->data /= opp.data;
            return *this;
        }

        vec4 operator/(const vec4 opp) const {
            return vec4(this->data / opp.data);
        }

        vec4 operator/(const f32 opp) const {
            return vec4(this->data / opp);
        }

        vec4 pow(const f32 num) const {
            return vec4(cst::pow(x, num), cst::pow(y, num), cst::pow(z, num), cst::pow(w, num));
        }

        f32 length() const {
            simd::f32x4 squared = data * data;
            return cst::sqrt(squared[0] + squared[1] + squared[2] + squared[3]);
        }

        f32 dot(const vec4 opp) const {
            simd::f32x4 mul = data * opp.data; 
            return mul[0] + mul[1] + mul[2] + mul[3];
        }

        vec4 cross(const vec4 opp) const {
            return vec4(
                (y * opp.z) - (z * opp.y),
                (z * opp.x) - (x * opp.z),
                (x * opp.y) - (y * opp.x),
                0.0f
            );
        }
    };

    struct mat2 {
        vec2 columns[2]; 

        mat2() {
            columns[0] = vec2(1.0f, 0.0f);
            columns[1] = vec2(0.0f, 1.0f);
        }

        mat2(vec2 c0, vec2 c1) {
            columns[0] = c0;
            columns[1] = c1;
        }

        vec2& operator[](int i) { return columns[i]; }
        const vec2& operator[](int i) const { return columns[i]; }

        mat2 operator*(const mat2& other) const {
            return mat2(
                vec2(
                    columns[0].x * other.columns[0].x + columns[1].x * other.columns[0].y,
                    columns[0].y * other.columns[0].x + columns[1].y * other.columns[0].y
                ),
                vec2(
                    columns[0].x * other.columns[1].x + columns[1].x * other.columns[1].y,
                    columns[0].y * other.columns[1].x + columns[1].y * other.columns[1].y
                )
            );
        }

        vec2 operator*(const vec2& v) const {
            return vec2(
                columns[0].x * v.x + columns[1].x * v.y,
                columns[0].y * v.x + columns[1].y * v.y
            );
        }
    };

    struct mat3 {
        vec3 columns[3]; 

        mat3() {
            columns[0] = vec3(1.0f, 0.0f, 0.0f);
            columns[1] = vec3(0.0f, 1.0f, 0.0f);
            columns[2] = vec3(0.0f, 0.0f, 1.0f);
        }

        mat3(vec3 c0, vec3 c1, vec3 c2) {
            columns[0] = c0;
            columns[1] = c1;
            columns[2] = c2;
        }

        vec3& operator[](int i) { return columns[i]; }
        const vec3& operator[](int i) const { return columns[i]; }

        mat3 operator*(const mat3& other) const {
            mat3 result;
            for (int col = 0; col < 3; ++col) {
                result.columns[col] = 
                    columns[0] * other.columns[col].x +
                    columns[1] * other.columns[col].y +
                    columns[2] * other.columns[col].z;
            }
            return result;
        }

        vec3 operator*(const vec3& v) const {
            return vec3(
                columns[0].x * v.x + columns[1].x * v.y + columns[2].x * v.z,
                columns[0].y * v.x + columns[1].y * v.y + columns[2].y * v.z,
                columns[0].z * v.x + columns[1].z * v.y + columns[2].z * v.z
            );
        }
    };

    struct mat4 {
        vec4 columns[4]; // [Column 0, Column 1, Column 2, Column 3]

        mat4() {
            columns[0] = vec4(1.0f, 0.0f, 0.0f, 0.0f);
            columns[1] = vec4(0.0f, 1.0f, 0.0f, 0.0f);
            columns[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
            columns[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        }

        mat4(vec4 c0, vec4 c1, vec4 c2, vec4 c3) {
            columns[0] = c0;
            columns[1] = c1;
            columns[2] = c2;
            columns[3] = c3;
        }

        vec4& operator[](int i) { return columns[i]; }
        const vec4& operator[](int i) const { return columns[i]; }

        mat4 operator*(const mat4& other) const {
            mat4 result;
            for (int col = 0; col < 4; ++col) {
                result.columns[col] = 
                    columns[0] * other.columns[col].x +
                    columns[1] * other.columns[col].y +
                    columns[2] * other.columns[col].z +
                    columns[3] * other.columns[col].w;
            }
            return result;
        }

        vec4 operator*(const vec4& v) const {
            return vec4(
                columns[0].x * v.x + columns[1].x * v.y + columns[2].x * v.z + columns[3].x * v.w,
                columns[0].y * v.x + columns[1].y * v.y + columns[2].y * v.z + columns[3].y * v.w,
                columns[0].z * v.x + columns[1].z * v.y + columns[2].z * v.z + columns[3].z * v.w,
                columns[0].w * v.x + columns[1].w * v.y + columns[2].w * v.z + columns[3].w * v.w
            );
        }
    };
    
    #endif
}