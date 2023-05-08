/*
* MIT License
*
* Copyright (c) 2023 Ransel117
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef RANMATH_H
#define RANMATH_H

#ifdef __cplusplus
//extern "C" {
#endif /* __cplusplus */

#define RM_CC 0
#define RM_CL 1

#ifndef RM_SSE_ENABLE
#if defined(__SSE__)    || defined(__SSE2__)   ||    \
    defined(_M_X64)     || defined(_M_AMD64)   ||    \
    defined(_M_IX86_FP) || defined(__x86_64__) ||    \
    defined(__amd64__)  || defined(__i386__)
#define RM_SSE_ENABLE 1
#else
#define RM_SSE_ENABLE 0
#endif /* Check for sse2 intrinsics*/
#endif /* Check if already defined */

#ifndef RM_NEON_ENABLE
#if defined(__ARM_NEON)  || defined(__ARM_NEON__) ||    \
    defined(__aarch64__) || defined(__arm__)
#define RM_NEON_ENABLE 1
#else
#define RM_NEON_ENABLE 0
#endif /* Check for neon intrinsics */
#endif /* Check if already defined */

#if RM_SSE_ENABLE || RM_NEON_ENABLE
#define RM_SIMD 1
#else
#define RM_SIMD 0
#endif /* Check for SIMD */

/* GCC-compatible compiler (gcc, clang) */
#if defined(__GNUC__) || defined(__clang__) || defined(__PCC__)
#define RM_COMPILER RM_CC
#define RM_INLINE   static inline __attribute__((always_inline))
#define RM_ALIGN(x) __attribute__((aligned(x)))
/* Microsoft cl */
#elif defined(_MSC_VER)
#define RM_COMPILER RM_CL
#define RM_INLINE   static inline __forceinline
#define RM_ALIGN(x) __declspec(align(x))
/* Unknown */
#else
#define RM_COMPILER RM_CC /* Temporary, might change */
#define RM_INLINE   static inline
#define RM_ALIGN(x)
#endif /* Check compiler for alignment of vectors */

/* ---------------- TYPES ---------------- */
#ifndef RANTYPES_H
#define RANTYPES_H

#include <stdint.h>
#include <stddef.h>

#ifndef __bool_true_false_are_defined
#define bool  _Bool
#define true  1
#define false 0

#define __bool_true_false_are_defined 1
#endif /* __bool_true_false_are_defined */

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
typedef size_t   usize;
#endif /* RANTYPES_H */

typedef struct RM_ALIGN(4)  f32_cvt_s f32_cvt;
typedef struct RM_ALIGN(8)  f64_cvt_s f64_cvt;
typedef struct RM_ALIGN(4)  vec2_s    vec2;
typedef struct RM_ALIGN(4)  vec3_s    vec3;
typedef struct RM_ALIGN(4)  vec4_s    vec4;
typedef struct RM_ALIGN(16) mat2_s    mat2;
typedef struct RM_ALIGN(16) mat3_s    mat3;
typedef struct RM_ALIGN(16) mat4_s    mat4;

struct RM_ALIGN(4) f32_cvt_s {
    union {
        f32 f;
        u32 u;
    };
};
struct RM_ALIGN(8) f64_cvt_s {
    union {
        f64 f;
        u64 u;
    };
};
struct RM_ALIGN(4) vec2_s {
    union {
        struct {f32 x, y;};
        struct {f32 u, v;};
        struct {f32 r, g;};
        f32    raw[2];
    };
};
struct RM_ALIGN(4) vec3_s {
    union {
        struct {f32 x, y, z;};
        struct {f32 r, g, b;};
        vec2   xy;
        struct {f32 _;  vec2 yz;};
        vec2   rg;
        struct {f32 __; vec2 gb;};
        f32    raw[3];
    };
};
struct RM_ALIGN(4) vec4_s {
    union {
        struct {f32  x, y, z, w;};
        struct {f32  r, g, b, a;};
        struct {vec2 xy, zw;};
        struct {vec2 rg, ba;};
        vec3   xyz;
        struct {f32 _;  vec3 yzw;};
        vec3   rgb;
        struct {f32 __; vec3 gba;};
        f32    raw[4];
    };
};
struct RM_ALIGN(16) mat2_s {
    union {
        vec2 cols[2];
        vec4 v;
        f32  raw[2][2];
        f32  rawv[4];
    };
};
struct RM_ALIGN(16) mat3_s {
    union {
        vec3 cols[3];
        f32  raw[3][3];
    };
};
struct RM_ALIGN(16) mat4_s {
    union {
        vec4 cols[4];
        f32  raw[4][4];
    };
};

#define as_u32(_x)                  (((f32_cvt){.f = (_x)}).u)
#define as_f32(_x)                  (((f32_cvt){.u = (_x)}).f)
#define as_u64(_x)                  (((f64_cvt){.f = (_x)}).u)
#define as_f64(_x)                  (((f64_cvt){.u = (_x)}).f)
#define rm_vec2(_x, _y)             ((vec2){{{.x=(_x), .y=(_y)}}})
#define rm_vec3(_x, _y, _z)         ((vec3){{{.x=(_x), .y=(_y), .z=(_z)}}})
#define rm_vec4(_x, _y, _z, _w)     ((vec4){{{.x=(_x), .y=(_y), .z=(_z), .w=(_w)}}})
#define rm_mat2(_c0, _c1)           ((mat2){{{(_c0), (_c1)}}})
#define rm_mat3(_c0, _c1, _c2)      ((mat3){{{(_c0), (_c1), (_c2)}}})
#define rm_mat4(_c0, _c1, _c2, _c3) ((mat4){{{(_c0), (_c1), (_c2), (_c3)}}})

/* ---------------- CONSTANTS ---------------- */
#define RM_E_X           (0x4005BF0A8B145769)
#define RM_E_F_X         (0x402DF854)
#define RM_LOG2E_X       (0x3FF71547652B82FE)
#define RM_LOG2E_X_F_X   (0x3FB8AA3B)
#define RM_LOG10E_X      (0x3FDBCB7B1526E50E)
#define RM_LOG10E_F_X    (0x3EDE5BD9)
#define RM_LN2_X         (0x3FE62E42FEFA39EF)
#define RM_LN2_F_X       (0x3F317218)
#define RM_LN10_X        (0x40026BB1BBB55516)
#define RM_LN10_F_X      (0x40135D8E)
#define RM_PI_X          (0x400921FB54442D18)
#define RM_PI_F_X        (0x40490FDB)
#define RM_PI_2_X        (0x3FF921FB54442D18)
#define RM_PI_2_F_X      (0x3FC90FDB)
#define RM_PI_4_X        (0x3FE921FB54442D18)
#define RM_PI_4_F_X      (0x3F490FDB)
#define RM_2PI_X         (0x401921FB54442D18)
#define RM_2PI_F_X       (0x40C90FDB)
#define RM_3PI_2_X       (0x4012D97C7F3321D2)
#define RM_3PI_2_F_X     (0x4096CBE4)
#define RM_PI2_X         (0x4023BD3CC9BE45DE)
#define RM_PI2_F_X       (0x411DE9E6)
#define RM_PI3_X         (0x403F019B59389D7C)
#define RM_PI3_F_X       (0x41F80CDB)
#define RM_PI4_X         (0x40585A2E8C290826)
#define RM_PI4_F_X       (0x42C2D174)
#define RM_1_PI_X        (0x3FD45F306DC9C883)
#define RM_1_PI_F_X      (0x3EA2F983)
#define RM_1_2PI_X       (0x3FC45F306DC9C883)
#define RM_1_2PI_F_X     (0x3E22F983)
#define RM_1_PI_2_X      (0x3FE45F306DC9C883)
#define RM_1_PI_2_F_X    (0x3F22F983)
#define RM_SQRTPI_X      (0x3FFC5BF891B4EF6B)
#define RM_SQRTPI_F_X    (0x3FE2DFC5)
#define RM_1_SQRTPI_X    (0x3FE20DD750429B6D)
#define RM_1_SQRTPI_F_X  (0x3F106EBB)
#define RM_2_SQRTPI_X    (0x3FF20DD750429B6D)
#define RM_2_SQRTPI_F_X  (0x3F906EBB)
#define RM_SQRT2_X       (0x3FF6A09E667F3BCD)
#define RM_SQRT2_F_X     (0x3FB504F3)
#define RM_1_SQRT2_X     (0x3FE6A09E667F3BCD)
#define RM_1_SQRT2_F_X   (0x3F3504F3)
#define RM_MAKE_DEG_X    (0x404CA5DC1A63C1F8)
#define RM_MAKE_DEG_F_X  (0x42652EE1)
#define RM_MAKE_RAD_X    (0x3F91DF46A2529D39)
#define RM_MAKE_RAD_F_X  (0x3C8EFA35)
#define RM_FLT_EPSILON_X (0x34000032)
#define RM_DBL_EPSILON_X (0x3CB0000000000000)
#define RM_SMALL_NUM_X   (0x2540000000000000)
#define RM_SMALL_NUM_F_X (0x00000100)
#define RM_NAN_X         (0x7FFFFFFFFFFFFFFF)
#define RM_NAN_F_X       (0x7FFFFFFF)
#define RM_INF_X         (0x7FF0000000000000)
#define RM_INF_F_X       (0x7F800000)

#define RM_E             as_f64(RM_E_X)
#define RM_E_F           as_f32(RM_E_F_X)
#define RM_LOG2E         as_f64(RM_LOG2E_X)
#define RM_LOG2E_F       as_f32(RM_LOG2E_F_X)
#define RM_LOG10E        as_f64(RM_LOG2E_X)
#define RM_LOG10E_F      as_f32(RM_LOG10E_F_X)
#define RM_LN2           as_f64(RM_LN2_X)
#define RM_LN2_F         as_f32(RM_LN2_F_X)
#define RM_LN10          as_f64(RM_LN10_X)
#define RM_LN10_F        as_f32(RM_LN10_F_X)
#define RM_PI            as_f64(RM_PI_X)
#define RM_PI_F          as_f32(RM_PI_F_X)
#define RM_PI_2          as_f64(RM_PI_2_X)
#define RM_PI_2_F        as_f32(RM_PI_2_F_X)
#define RM_PI_4          as_f64(RM_PI_4_X)
#define RM_PI_4_F        as_f32(RM_PI_4_F_X)
#define RM_2PI           as_f64(RM_2PI_X)
#define RM_2PI_F         as_f32(RM_2PI_F_X)
#define RM_3PI_2         as_f64(RM_3PI_2_X)
#define RM_3PI_2_F       as_f32(RM_3PI_2_F_X)
#define RM_PI2           as_f64(RM_PI2_X)
#define RM_PI2_F         as_f32(RM_PI2_F_X)
#define RM_PI3           as_f64(RM_PI3_X)
#define RM_PI3_F         as_f32(RM_PI3_F_X)
#define RM_PI4           as_f64(RM_PI4_X)
#define RM_PI4_F         as_f32(RM_PI4_F_X)
#define RM_1_PI          as_f64(RM_1_PI_X)
#define RM_1_PI_F        as_f32(RM_1_PI_F_X)
#define RM_1_2PI         as_f64(RM_1_2PI_X)
#define RM_1_2PI_F       as_f32(RM_1_2PI_F_X)
#define RM_1_PI_2        as_f64(RM_1_PI_2_X)
#define RM_1_PI_2_F      as_f32(RM_1_PI_2_F_X)
#define RM_SQRTPI        as_f64(RM_SQRTPI_X)
#define RM_SQRTPI_F      as_f32(RM_SQRTPI_F_X)
#define RM_1_SQRTPI      as_f64(RM_1_SQRTPI_X)
#define RM_1_SQRTPI_F    as_f32(RM_1_SQRTPI_F_X)
#define RM_2_SQRTPI      as_f64(RM_2_SQRTPI_X)
#define RM_2_SQRTPI_F    as_f32(RM_2_SQRTPI_F_X)
#define RM_SQRT2         as_f64(RM_SQRT2_X)
#define RM_SQRT2_F       as_f32(RM_SQRT2_F_X)
#define RM_1_SQRT2       as_f64(RM_1_SQRT2_X)
#define RM_1_SQRT2_F     as_f32(RM_1_SQRT2_F_X)
#define RM_MAKE_DEG      as_f64(RM_MAKE_DEG_X)
#define RM_MAKE_DEG_F    as_f32(RM_MAKE_DEG_F_X)
#define RM_MAKE_RAD      as_f64(RM_MAKE_RAD_X)
#define RM_MAKE_RAD_F    as_f32(RM_MAKE_RAD_F_X)
#define RM_FLT_EPSILON   as_f32(RM_FLT_EPSILON_X)
#define RM_DBL_EPSILON   as_f64(RM_DBL_EPSILON_X)
/* for 128 decimals of precision in rm_eq_f64 */
#define RM_SMALL_NUM     as_f64(RM_SMALL_NUM_X)
/* for 42 decimals of precision in rm_eq_f32 */
#define RM_SMALL_NUM_F   as_f32(RM_SMALL_NUM_F_X)
#define RM_NAN           as_f64(RM_NAN_X)
#define RM_NAN_F         as_f32(RM_NAN_F_X)
#define RM_INF           as_f64(RM_INF_X)
#define RM_INF_F         as_f32(RM_INF_F_X)

/* ----------------- METHODS ----------------- */
RM_INLINE bool rm_f32_eq(const f32, const f32);
RM_INLINE bool rm_f64_eq(const f64, const f64);
RM_INLINE bool rm_f32_eq_eps(const f32, const f32);
RM_INLINE bool rm_f64_eq_eps(const f64, const f64);
RM_INLINE f32  rm_f32_scalbn(f32, i32);
RM_INLINE f64  rm_f64_scalbn(f64, i32);
RM_INLINE i8   rm_i8_sign(const i8);
RM_INLINE i8   rm_i16_sign(const i16);
RM_INLINE i8   rm_i32_sign(const i32);
RM_INLINE i8   rm_i64_sign(const i64);
RM_INLINE i8   rm_f32_sign(const f32);
RM_INLINE i8   rm_f64_sign(const f64);
RM_INLINE i32  rm_i32_pow(const i32, const i32);
RM_INLINE i64  rm_i64_pow(const i64, const i64);
/* FP pow functions are not implemented yet */
RM_INLINE f32  rm_f32_pow(const f32, const f32);
RM_INLINE f64  rm_f64_pow(const f64, const f64);
RM_INLINE i8   rm_i8_pow2(const i8);
RM_INLINE i16  rm_i16_pow2(const i16);
RM_INLINE i32  rm_i32_pow2(const i32);
RM_INLINE i64  rm_i64_pow2(const i64);
RM_INLINE f32  rm_f32_pow2(const f32);
RM_INLINE f64  rm_f64_pow2(const f64);
RM_INLINE f32  rm_f32_rsqrt(const f32);
RM_INLINE f64  rm_f64_rsqrt(const f64);
RM_INLINE f32  rm_f32_sqrt(const f32);
RM_INLINE f64  rm_f64_sqrt(const f64);
RM_INLINE i8   rm_i8_abs(const i8);
RM_INLINE i16  rm_i16_abs(const i16);
RM_INLINE i32  rm_i32_abs(const i32);
RM_INLINE i64  rm_i64_abs(const i64);
RM_INLINE f32  rm_f32_abs(const f32);
RM_INLINE f64  rm_f64_abs(const f64);
RM_INLINE i8   rm_i8_min(const i8, const i8);
RM_INLINE i16  rm_i16_min(const i16, const i16);
RM_INLINE i32  rm_i32_min(const i32, const i32);
RM_INLINE i64  rm_i64_min(const i64, const i64);
RM_INLINE f32  rm_f32_min(const f32, const f32);
RM_INLINE f64  rm_f64_min(const f64, const f64);
RM_INLINE i8   rm_i8_max(const i8, const i8);
RM_INLINE i16  rm_i16_max(const i16, const i16);
RM_INLINE i32  rm_i32_max(const i32, const i32);
RM_INLINE i64  rm_i64_max(const i64, const i64);
RM_INLINE f32  rm_f32_max(const f32, const f32);
RM_INLINE f64  rm_f64_max(const f64, const f64);
RM_INLINE i8   rm_i8_clamp(const i8, const i8, const i8);
RM_INLINE i16  rm_i16_clamp(const i16, const i16, const i16);
RM_INLINE i32  rm_i32_clamp(const i32, const i32, const i32);
RM_INLINE i64  rm_i64_clamp(const i64, const i64, const i64);
RM_INLINE f32  rm_f32_clamp(const f32, const f32, const f32);
RM_INLINE f64  rm_f64_clamp(const f64, const f64, const f64);
RM_INLINE f32  rm_f32_trunc(const f32);
RM_INLINE f64  rm_f64_trunc(const f64);
RM_INLINE i8   rm_i8_fmod(const i8, const i8);
RM_INLINE i16  rm_i16_fmod(const i16, const i16);
RM_INLINE i32  rm_i32_fmod(const i32, const i32);
RM_INLINE i64  rm_i64_fmod(const i64, const i64);
RM_INLINE f32  rm_f32_fmod(const f32, const f32);
RM_INLINE f64  rm_f64_fmod(const f64, const f64);
RM_INLINE f32  rm_f32_floor(const f32);
RM_INLINE f64  rm_f64_floor(const f64);
RM_INLINE f32  rm_f32_ceil(const f32);
RM_INLINE f64  rm_f64_ceil(const f64);
RM_INLINE f32  rm_f32_round(const f32);
RM_INLINE f64  rm_f64_round(const f64);
RM_INLINE i8   rm_i8_wrap_max(const i8, const i8);
RM_INLINE i16  rm_i16_wrap_max(const i16, const i16);
RM_INLINE i32  rm_i32_wrap_max(const i32, const i32);
RM_INLINE i64  rm_i64_wrap_max(const i64, const i64);
RM_INLINE f32  rm_f32_wrap_max(const f32, const f32);
RM_INLINE f64  rm_f64_wrap_max(const f64, const f64);
RM_INLINE i8   rm_i8_wrap(const i8, const i8, const i8);
RM_INLINE i16  rm_i16_wrap(const i16, const i16, const i16);
RM_INLINE i32  rm_i32_wrap(const i32, const i32, const i32);
RM_INLINE i64  rm_i64_wrap(const i64, const i64, const i64);
RM_INLINE f32  rm_f32_wrap(const f32, const f32, const f32);
RM_INLINE f64  rm_f64_wrap(const f64, const f64, const f64);
RM_INLINE f32  rm_f32_cos_step(const f64);
RM_INLINE f64  rm_f64_cos_step(const f64, const f64);
RM_INLINE f32  rm_f32_sin_step(const f64);
RM_INLINE f64  rm_f64_sin_step(const f64, const f64, const i32);
RM_INLINE f32  rm_f32_tan_step(const f64, const i32);
RM_INLINE f64  rm_f64_tan_step(const f64, const f64, const i32);
RM_INLINE i32  rm_f32_pi_2_rem(const f32, f64*);
RM_INLINE i32  rm_f64_pi_2_rem(const f64, f64*);
RM_INLINE i32  rm_pi_2_rem_large(f64*, f64*, const i32, const i32, const i32);
RM_INLINE f32  rm_f32_cos(const f32);
RM_INLINE f64  rm_f64_cos(const f64);
RM_INLINE f32  rm_f32_sin(const f32);
RM_INLINE f64  rm_f64_sin(const f64);
RM_INLINE f32  rm_f32_tan(const f32);
RM_INLINE f64  rm_f64_tan(const f64);
RM_INLINE f32  rm_f32_acos(const f32);
RM_INLINE f64  rm_f64_acos(const f64);
RM_INLINE f32  rm_f32_asin(const f32);
RM_INLINE f64  rm_f64_asin(const f64);
RM_INLINE f32  rm_f32_atan(const f32);
RM_INLINE f64  rm_f64_atan(const f64);
RM_INLINE f32  rm_f32_atan2(const f32, const f32);
RM_INLINE f64  rm_f64_atan2(const f64, const f64);
RM_INLINE f32  rm_f32_rad2deg(const f32);
RM_INLINE f64  rm_f64_rad2deg(const f64);
RM_INLINE f32  rm_f32_deg2rad(const f32);
RM_INLINE f64  rm_f64_deg2rad(const f64);

RM_INLINE vec2 rm_vec2_copy(const vec2);
RM_INLINE vec2 rm_vec2_abs(const vec2);
RM_INLINE f32  rm_vec2_max(const vec2);
RM_INLINE f32  rm_vec2_min(const vec2);
RM_INLINE vec2 rm_vec2_maxv(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_minv(const vec2, const vec2);
RM_INLINE f32  rm_vec2_hadd(const vec2);
RM_INLINE vec2 rm_vec2_zero(void);
RM_INLINE vec2 rm_vec2_one(void);
RM_INLINE vec2 rm_vec2_set(const f32, const f32);
RM_INLINE vec2 rm_vec2_fill(const f32);
RM_INLINE f32  rm_vec2_dot(const vec2, const vec2);
RM_INLINE f32  rm_vec2_cross(const vec2, const vec2);
RM_INLINE f32  rm_vec2_norm2(const vec2);
RM_INLINE f32  rm_vec2_norm(const vec2);
RM_INLINE f32  rm_vec2_norm_one(const vec2);
RM_INLINE f32  rm_vec2_norm_inf(const vec2);
RM_INLINE vec2 rm_vec2_add(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_adds(const vec2, const f32);
RM_INLINE vec2 rm_vec2_sub(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_subs(const vec2, const f32);
RM_INLINE vec2 rm_vec2_mul(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_scale(const vec2, const f32);
RM_INLINE vec2 rm_vec2_scale_as(const vec2, const f32);
RM_INLINE vec2 rm_vec2_scale_aniso(const vec2, const f32, const f32);
RM_INLINE vec2 rm_vec2_div(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_divs(const vec2, const f32);
RM_INLINE vec2 rm_vec2_negate(const vec2);
RM_INLINE vec2 rm_vec2_normalize(const vec2);
RM_INLINE vec2 rm_vec2_rotate(const vec2, const f32);
RM_INLINE f32  rm_vec2_distance2(const vec2, const vec2);
RM_INLINE f32  rm_vec2_distance(const vec2, const vec2);
RM_INLINE vec2 rm_vec2_clamp(const vec2, const f32, const f32);
RM_INLINE vec2 rm_vec2_wrap(const vec2, const f32, const f32);
RM_INLINE vec2 rm_vec2_center(const vec2, const vec2);

RM_INLINE vec3 rm_vec3_copy(const vec3);
RM_INLINE vec2 rm_vec3_copy2(const vec3);
RM_INLINE vec3 rm_vec3_abs(const vec3);
RM_INLINE f32  rm_vec3_max(const vec3);
RM_INLINE f32  rm_vec3_min(const vec3);
RM_INLINE vec3 rm_vec3_maxv(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_minv(const vec3, const vec3);
RM_INLINE f32  rm_vec3_hadd(const vec3);
RM_INLINE vec3 rm_vec3_zero(void);
RM_INLINE vec3 rm_vec3_one(void);
RM_INLINE vec3 rm_vec3_set(const f32, const f32, const f32);
RM_INLINE vec3 rm_vec3_fill(const f32);
RM_INLINE vec3 rm_vec3_make(const vec2, const f32);
RM_INLINE f32  rm_vec3_dot(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_cross(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_crossn(const vec3, const vec3);
RM_INLINE f32  rm_vec3_norm2(const vec3);
RM_INLINE f32  rm_vec3_norm(const vec3);
RM_INLINE f32  rm_vec3_norm_one(const vec3);
RM_INLINE f32  rm_vec3_norm_inf(const vec3);
RM_INLINE vec3 rm_vec3_add(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_adds(const vec3, const f32);
RM_INLINE vec3 rm_vec3_sub(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_subs(const vec3, const f32);
RM_INLINE vec3 rm_vec3_mul(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_scale(const vec3, const f32);
RM_INLINE vec3 rm_vec3_scale_as(const vec3, const f32);
RM_INLINE vec3 rm_vec3_scale_aniso(const vec3, const f32, const f32, const f32);
RM_INLINE vec3 rm_vec3_div(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_divs(const vec3, const f32);
RM_INLINE vec3 rm_vec3_negate(const vec3);
RM_INLINE vec3 rm_vec3_normalize(const vec3);
RM_INLINE vec3 rm_vec3_rotate(const vec3, const f32, const vec3);
RM_INLINE f32  rm_vec3_distance2(const vec3, const vec3);
RM_INLINE f32  rm_vec3_distance(const vec3, const vec3);
RM_INLINE vec3 rm_vec3_clamp(const vec3, const f32, const f32);
RM_INLINE vec3 rm_vec3_wrap(const vec3, const f32, const f32);
RM_INLINE vec3 rm_vec3_center(const vec3, const vec3);

RM_INLINE vec4 rm_vec4_copy(const vec4);
RM_INLINE vec3 rm_vec4_copy3(const vec4);
RM_INLINE vec4 rm_vec4_abs(const vec4);
RM_INLINE f32  rm_vec4_max(const vec4);
RM_INLINE f32  rm_vec4_min(const vec4);
RM_INLINE vec4 rm_vec4_maxv(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_minv(const vec4, const vec4);
RM_INLINE f32  rm_vec4_hadd(const vec4);
RM_INLINE vec4 rm_vec4_zero(void);
RM_INLINE vec4 rm_vec4_one(void);
RM_INLINE vec4 rm_vec4_set(const f32, const f32, const f32, const f32);
RM_INLINE vec4 rm_vec4_fill(const f32);
RM_INLINE vec4 rm_vec4_make(const vec3, const f32);
RM_INLINE f32  rm_vec4_dot(const vec4, const vec4);
RM_INLINE f32  rm_vec4_norm2(const vec4);
RM_INLINE f32  rm_vec4_norm(const vec4);
RM_INLINE f32  rm_vec4_norm_one(const vec4);
RM_INLINE f32  rm_vec4_norm_inf(const vec4);
RM_INLINE vec4 rm_vec4_add(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_adds(const vec4, const f32);
RM_INLINE vec4 rm_vec4_sub(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_subs(const vec4, const f32);
RM_INLINE vec4 rm_vec4_mul(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_scale(const vec4, const f32);
RM_INLINE vec4 rm_vec4_scale_as(const vec4, const f32);
RM_INLINE vec4 rm_vec4_div(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_divs(const vec4, const f32);
RM_INLINE vec4 rm_vec4_negate(const vec4);
RM_INLINE vec4 rm_vec4_normalize(const vec4);
RM_INLINE f32  rm_vec4_distance2(const vec4, const vec4);
RM_INLINE f32  rm_vec4_distance(const vec4, const vec4);
RM_INLINE vec4 rm_vec4_clamp(const vec4, const f32, const f32);
RM_INLINE vec4 rm_vec4_wrap(const vec4, const f32, const f32);
RM_INLINE vec4 rm_vec4_center(const vec4, const vec4);

RM_INLINE mat2 rm_mat2_copy(const mat2);
RM_INLINE mat2 rm_mat2_identity(void);
RM_INLINE void rm_mat2_identity_array(mat2*, const usize);
RM_INLINE mat2 rm_mat2_zero(void);
RM_INLINE mat2 rm_mat2_mul(const mat2, const mat2);
RM_INLINE vec2 rm_mat2_mul_vec2(const mat2, const vec2);
RM_INLINE mat2 rm_mat2_scale(const mat2, const f32);
RM_INLINE mat2 rm_mat2_transpose(const mat2);
RM_INLINE f32  rm_mat2_trace(const mat2);
RM_INLINE f32  rm_mat2_det(const mat2);
RM_INLINE mat2 rm_mat2_inv(const mat2);
RM_INLINE mat2 rm_mat2_swap_col(const mat2, const u32, const u32);
RM_INLINE mat2 rm_mat2_swap_row(const mat2, const u32, const u32);
RM_INLINE f32  rm_mat2_rmc(const vec2, const mat2, const vec2);

RM_INLINE mat3 rm_mat3_copy(const mat3);
RM_INLINE mat3 rm_mat3_identity(void);
RM_INLINE void rm_mat3_identity_array(mat3*, const usize);
RM_INLINE mat3 rm_mat3_zero(void);
RM_INLINE mat3 rm_mat3_mul(const mat3, const mat3);
RM_INLINE vec3 rm_mat3_mul_vec3(const mat3, const vec3);
RM_INLINE mat3 rm_mat3_scale(const mat3, const f32);
RM_INLINE mat3 rm_mat3_transpose(const mat3);
RM_INLINE f32  rm_mat3_trace(const mat3);
RM_INLINE f32  rm_mat3_det(const mat3);
RM_INLINE mat3 rm_mat3_inv(const mat3);
RM_INLINE mat3 rm_mat3_swap_col(const mat3, const u32, const u32);
RM_INLINE mat3 rm_mat3_swap_row(const mat3, const u32, const u32);
RM_INLINE f32  rm_mat3_rmc(const vec3, const mat3, const vec3);

RM_INLINE mat4 rm_mat4_copy(const mat4);
RM_INLINE mat4 rm_mat4_identity(void);
RM_INLINE void rm_mat4_identity_array(mat4*, const usize);
RM_INLINE mat4 rm_mat4_zero(void);
RM_INLINE mat3 rm_mat4_pick3(const mat4);
RM_INLINE mat3 rm_mat4_pick3t(const mat4);
RM_INLINE void rm_mat4_insert_mat3(const mat3, mat4);
RM_INLINE mat4 rm_mat4_mul(const mat4, const mat4);
RM_INLINE vec4 rm_mat4_mul_vec4(const mat4, const vec4);
RM_INLINE vec3 rm_mat4_mul_vec3(const mat4, const vec3, const f32);
RM_INLINE mat4 rm_mat4_scale(const mat4, const f32);
RM_INLINE mat4 rm_mat4_scale_aniso(const mat4, const f32, const f32, const f32);
RM_INLINE mat4 rm_mat4_transpose(const mat4);
RM_INLINE mat4 rm_mat4_translate(const f32, const f32, const f32);
RM_INLINE mat4 rm_mat4_translate_vec3(const vec3);
RM_INLINE f32  rm_mat4_trace(const mat4);
RM_INLINE f32  rm_mat4_trace3(const mat4);
RM_INLINE f32  rm_mat4_det(const mat4);
RM_INLINE mat4 rm_mat4_inv(const mat4);
RM_INLINE mat4 rm_mat4_swap_col(const mat4, const u32, const u32);
RM_INLINE mat4 rm_mat4_swap_row(const mat4, const u32, const u32);
RM_INLINE f32  rm_mat4_rmc(const vec4, const mat4, const vec4);
RM_INLINE mat4 rm_mat4_ortho(const f32, const f32, const f32, const f32, const f32, const f32);
RM_INLINE mat4 rm_mat4_frustum(const f32, const f32, const f32, const f32, const f32, const f32);
RM_INLINE mat4 rm_mat4_perspective(const f32, const f32, const f32, const f32);

#ifdef __cplusplus
//}
#endif /* __cplusplus */
#endif /* RANMATH_H */

#ifdef RANMATH_IMPLEMENTATION
#ifdef __cplusplus
//extern "C" {
#endif /* __cplusplus */

#if RM_SIMD
#ifndef _MM_SHUFFLE
#define _MM_SHUFFLE(x, y, z, w) (((w) << 6) | ((z) << 4) | ((y) << 2) | ((x)))
#endif /* Check if already defined so it's not redefined */

#if RM_SSE_ENABLE
#include <emmintrin.h>

#define RM_VEC __m128

#define rmm_load(v)                    _mm_load_ps((v))
#define rmm_store(v, a)                _mm_store_ps((v), (a))
#define rmm_set(x, y, z, w)            _mm_set_ps((w), (z), (y), (x))
#define rmm_set1(x)                    _mm_set_ps1((x))
#define rmm_cvts32_f32(x)              _mm_cvtepi32_ps((x))
#define rmm_cvtf32_s32(x)              _mm_cvtps_epi32((x))
#define rmm_cvttf32_s32(x)             _mm_cvttps_epi32((x))
#define rmm_casts32_f32(x)             _mm_castsi128_ps((x))
#define rmm_castf32_s32(x)             _mm_castps_si128((x))
#define rmm_unpack_lo(a, b)            _mm_unpacklo_ps((a), (b))
#define rmm_unpack_hi(a, b)            _mm_unpackhi_ps((a), (b))
#define rmm_add(a, b)                  _mm_add_ps((a), (b))
#define rmm_sub(a, b)                  _mm_sub_ps((a), (b))
#define rmm_mul(a, b)                  _mm_mul_ps((a), (b))
#define rmm_div(a, b)                  _mm_div_ps((a), (b))
#define rmm_min(a, b)                  _mm_min_ps((a), (b))
#define rmm_max(a, b)                  _mm_max_ps((a), (b))
#define rmm_abs(x)                     _mm_and_ps(rmm_casts32_f32(_mm_set1_epi32(0x7FFFFFFF)), (x))
#define rmm_neg(x)                     rmm_sub(rmm_set1(0), (x))
#define rmm_shuffle(v, x, y, z, w)     _mm_shuffle_ps((v), (v), _MM_SHUFFLE((w), (z), (y), (x)))
#define rmm_shuffle2(v, u, x, y, z, w) _mm_shuffle_ps((v), (u), _MM_SHUFFLE((w), (z), (y), (x)))
#define rmm_fmadd(a, b, c)             rmm_add(rmm_mul((a), (b)), (c))
RM_INLINE f32 rmm_hadd(RM_VEC x) {
#if RM_COMPILER == RM_CL
    return x.m128_f32[0] + x.m128_f32[1] + x.m128_f32[2] + x.m128_f32[3];
#else
    return x[0] + x[1] + x[2] + x[3];
#endif /* Microsoft */
}
RM_INLINE RM_VEC rmm_rcp(RM_VEC x) {
    RM_VEC rcp;

    rcp = _mm_rcp_ps(x);

    return rmm_mul(rcp, rmm_sub(rmm_set1(2), rmm_mul(rcp, x)));
}
#define rmm_eq(a, b)     _mm_cmple_ps(rmm_abs(rmm_sub(rmm_max((a), (b)), rmm_min((a), (b)))), \
                                      rmm_set1(RM_SMALL_NUM_F))
#define rmm_eq_eps(a, b) _mm_cmple_ps(rmm_abs(rmm_sub(rmm_max((a), (b)), rmm_min((a), (b)))), \
                                      rmm_set1(RM_FLT_EPSILON))
#endif /* RM_SSE_ENABLE */

#if RM_NEON_ENABLE
#include <arm_neon.h>

#define RM_VEC float32x4_t

#define rmm_load(v)         vld1q_f32((v))
#define rmm_store(v, a)     vst1q_f32((v), (a))
#define rmm_set(x, y, z, w) (RM_VEC){(x), (y), (z), (w)}
#define rmm_set1(x)         vdupq_n_f32((x))
#define rmm_cvts32_f32(x)   vcvtq_f32_s32((x))
#define rmm_cvtf32_s32(x)   vcvtnq_s32_f32((x))
#define rmm_cvttf32_s32(x)  vcvtq_s32_f32((x))
#define rmm_casts32_f32(x)  vreinterpretq_f32_s32((x))
#define rmm_castf32_s32(x)  vreinterpretq_s32_f32((x))
#if defined(__aarch64__)
#define rmm_unpack_lo(a, b) vzip1q_f32((a), (b))
#define rmm_unpack_hi(a, b) vzip2q_f32((b), (a))
#define rmm_fmadd(a, b, c)  vfmaq_f32((c), (a), (b))
#define rmm_hadd(x)         vaddvq_f32((x))
#else
RM_INLINE RM_VEC rmm_unpack_lo(RM_VEC a, RM_VEC b) {
    float32x2x2_t res;

    res = vzip_f32(vget_low_f32(a), vget_low_f32(b));

    return vcombine_f32(res.val[0], res.val[1]);
}
RM_INLINE RM_VEC rmm_unpack_hi(RM_VEC a, RM_VEC b) {
    float32x2x2_t res;

    res = vzip_f32(vget_high_f32(a), vget_high_f32(b));

    return vcombine_f32(res.val[0], res.val[1]);
}
#define rmm_fmadd(a, b, c)  vmlaq_f32((c), (a), (b))
RM_INLINE RM_VEC rmm_hadd(RM_VEC x) {
    float32x2_t tmp = vadd_f32(vget_high_f32(x), vget_low_f32(x));

    return vget_lane_f32(vpadd_f32(tmp, tmp), 0);
}
#endif /* __aarch64__ */
#define rmm_add(a, b)       vaddq_f32((a), (b))
#define rmm_sub(a, b)       vsubq_f32((a), (b))
#define rmm_mul(a, b)       vmulq_f32((a), (b))
#define rmm_div(a, b)       vdivq_f32((a), (b))
#define rmm_min(a, b)       vminq_f32((a), (b))
#define rmm_max(a, b)       vmaxq_f32((a), (b))
#define rmm_abs(x)          vabsq_f32((x))
#define rmm_neg(x)          vnegq_f32((x))
RM_INLINE RM_VEC rmm_shuffle(RM_VEC v, u32 x, u32 y, u32 z, u32 w) {
    u32 imm;

    imm = _MM_SHUFFLE(w, z, y, x);

    return rmm_set(v[(imm >> 6) & 0x3], v[(imm >> 4) & 0x3], v[(imm >> 2) & 0x3], v[imm & 0x3]);
}
RM_INLINE RM_VEC rmm_shuffle2(RM_VEC v, RM_VEC u, u32 x, u32 y, u32 z, u32 w) {
    u32 imm;

    imm = _MM_SHUFFLE(w, z, y, x);

    return rmm_set(v[(imm >> 6) & 0x3], v[(imm >> 4) & 0x3], u[(imm >> 2) & 0x3], u[imm & 0x3]);
}
RM_INLINE RM_VEC rmm_rcp(RM_VEC x) {
    RM_VEC rcp;

    rcp = vrecpeq_f32(x);

    return rmm_mul(rcp, rmm_sub(rmm_set1(2), rmm_mul(rcp, x)));
}
#define rmm_eq(a, b) rmm_casts32_f32(vcleq_f32(rmm_abs(rmm_sub(rmm_max((a), (b)), rmm_min((a), (b)))), \
                                               rmm_set1(RM_SMALL_NUM_F)))
#define rmm_eq_eps(a, b) rmm_casts32_f32(vcleq_f32(rmm_abs(rmm_sub(rmm_max((a), (b)), rmm_min((a), (b)))), \
                                                   rmm_set1(RM_FLT_EPSILON)))
#endif /* RM_NEON_ENABLE */

RM_INLINE RM_VEC rmm_hadd4(RM_VEC a, RM_VEC b, RM_VEC c, RM_VEC d) {
    RM_VEC s1, s2;

    /* [a0+a2 c0+c2 a1+a3 c1+c3] */
    s1 = rmm_add(rmm_unpack_lo(a, c), rmm_unpack_hi(a, c));
    /* [b0+b2 d0+d2 b1+b3 d1+d3] */
    s2 = rmm_add(rmm_unpack_lo(b, d), rmm_unpack_hi(b, d));
    /* [a0+a2 b0+b2 c0+c2 d0+d2] + [a1+a3 b1+b3 c1+c3 d1+d3] */

    return rmm_add(rmm_unpack_lo(s1, s2), rmm_unpack_hi(s1, s2));
}
#define rmm_trunc(x)        rmm_cvts32_f32(rmm_cvttf32_s32((x)))
#define rmm_fmod(a, b)      rmm_sub((a), rmm_mul(rmm_trunc(rmm_div((a), (b))), (b)))
#define rmm_fmadds(a, b, c) rmm_fmadd((a), (b), rmm_set1((c)))
#endif /* RM_SIMD */

#define RM_SIGN(x)              (((x) > 0) - ((x) < 0))
#define RM_ABS(x)               (((x) < 0) ? -(x) : (x))
#define RM_MIN(a, b)            (((a) < (b)) ? (a) : (b))
#define RM_MAX(a, b)            (((a) > (b)) ? (a) : (b))
#define RM_CLAMP(val, min, max) (RM_MIN(RM_MAX((val), (min)), (max)))
#define RM_POW2(x)              ((x) * (x))
#define RM_POW4(x)              (RM_POW2(RM_POW2((x))))

#define RM_EXTRACT_WORDS(hi, lo, d) do {  \
        u64 __u = as_u64((d));            \
        (hi) = __u >> 32;                 \
        (lo) = (u32)__u;                  \
    } while(0);
#define RM_GET_HIGH_WORD(hi, d)     do {(hi) = as_u64((d)) >> 32;} while(0);
#define RM_GET_LOW_WORD(lo, d)      do {(lo) = (u32)as_u64((d));} while(0);
#define RM_INSERT_WORDS(d, hi, lo)  do {(d) = as_f64(((u64)(hi) << 32) | (u32)(lo));} while(0);
#define RM_SET_HIGH_WORD(d, hi)     RM_INSERT_WORDS(d, hi, (u32)as_u64((d)))
#define RM_SET_LOW_WORD(d, lo)      RM_INSERT_WORDS(d, as_u64((d)) >> 32, lo)
#define RM_GET_FLOAT_WORD(w, d)     do {(w) = as_u32((d));} while(0);
#define RM_SET_FLOAT_WORD(d, w)     do {(d) = as_f32((w));} while(0);

#define RM_VEC2_FILL(x) rm_vec2((x), (x))
#define RM_VEC3_FILL(x) rm_vec3((x), (x), (x))
#define RM_VEC4_FILL(x) rm_vec4((x), (x), (x), (x))

#define RM_MAT2_FILL(x) rm_mat2(RM_VEC2_FILL((x)), RM_VEC2_FILL((x)))
#define RM_MAT3_FILL(x) rm_mat3(RM_VEC3_FILL((x)), RM_VEC3_FILL((x)),   \
                                RM_VEC3_FILL((x)))
#define RM_MAT4_FILL(x) rm_mat4(RM_VEC4_FILL((x)), RM_VEC4_FILL((x)),   \
                                RM_VEC4_FILL((x)), RM_VEC4_FILL((x)))

#define RM_MAT2_IDENTITY (mat2){{{rm_vec2(1, 0), rm_vec2(0, 1)}}}
#define RM_MAT3_IDENTITY (mat3){{{rm_vec3(1, 0, 0), rm_vec3(0, 1, 0), rm_vec3(0, 0, 1)}}}
#define RM_MAT4_IDENTITY (mat4){{{rm_vec4(1, 0, 0, 0), rm_vec4(0, 1, 0, 0), \
                    rm_vec4(0, 0, 1, 0), rm_vec4(0, 0, 0, 1)}}}

RM_INLINE bool rm_f32_eq(const f32 a, const f32 b) {
    return rm_f32_abs(rm_f32_max(a, b) - rm_f32_min(a, b)) <= RM_SMALL_NUM_F;
}
RM_INLINE bool rm_f64_eq(const f64 a, const f64 b) {
    return rm_f64_abs(rm_f64_max(a, b) - rm_f64_min(a, b)) <= RM_SMALL_NUM;
}
RM_INLINE bool rm_f32_eq_eps(const f32 a, const f32 b) {
    return rm_f32_abs(rm_f32_max(a, b) - rm_f32_min(a, b)) <= RM_FLT_EPSILON;
}
RM_INLINE bool rm_f64_eq_eps(const f64 a, const f64 b) {
    return rm_f64_abs(rm_f64_max(a, b) - rm_f64_min(a, b)) <= RM_DBL_EPSILON;
}
RM_INLINE f32 rm_f32_scalbn(float x, int n) {
    f32_cvt u;
    f32 y;

    y = x;
    if (n > 127) {
        y *= 0x1p127F;
        n -= 127;

        if (n > 127) {
            y *= 0x1p127F;
            n -= 127;

            if (n > 127) n = 127;
        }
    } else if (n < -126) {
        y *= 0x1p-126F * 0x1p24F;
        n += 126 - 24;

        if (n < -126) {
            y *= 0x1p-126F * 0x1p24F;
            n += 126 - 24;

            if (n < -126) n = -126;
        }
    }
    u.u = (u32)(0x0000007F + n) << 23;
    x = y * u.f;

    return x;
}
RM_INLINE f64 rm_f64_scalbn(f64 x, i32 n) {
    f64_cvt u;
    f64 y;

    y = x;
    if (n > 1023) {
        y *= 0x1p1023;
        n -= 1023;

        if (n > 1023) {
            y *= 0x1p1023;
            n -= 1023;

            if (n > 1023) n = 1023;
        }
    } else if (n < -1022) {
        /* make sure final n < -53 to avoid double
           rounding in the subnormal range */
        y *= 0x1p-1022 * 0x1p53;
        n += 1022 - 53;

        if (n < -1022) {
            y *= 0x1p-1022 * 0x1p53;
            n += 1022 - 53;

            if (n < -1022) n = -1022;
        }
    }
    u.u = (u64)(0x000003FF + n) << 52;
    x = y * u.f;

    return x;
}
RM_INLINE i8 rm_i8_sign(const i8 x) {
    return RM_SIGN(x);
}
RM_INLINE i8 rm_i16_sign(const i16 x) {
    return RM_SIGN(x);
}
RM_INLINE i8 rm_i32_sign(const i32 x) {
    return RM_SIGN(x);
}
RM_INLINE i8 rm_i64_sign(const i64 x) {
    return RM_SIGN(x);
}
RM_INLINE i8 rm_f32_sign(const f32 x) {
    return RM_SIGN(x);
}
RM_INLINE i8 rm_f64_sign(const f64 x) {
    return RM_SIGN(x);
}
RM_INLINE i32 rm_i32_pow(const i32 x, const i32 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;
    i32 i, val, x2, ap;

    val = 1;
    x2 = (p < 0) ? 1 / x : x;
    ap = rm_i32_abs(p);
    for (i = 0; i < ap; ++i) {
        val *= x2;
    }

    return val;
}
RM_INLINE i64 rm_i64_pow(const i64 x, const i64 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;
    i64 i, val, x2, ap;

    val = 1;
    x2 = (p < 0) ? 1 / x : x;
    ap = rm_i64_abs(p);
    for (i = 0; i < ap; ++i) {
        val *= x2;
    }

    return val;
}
/* NOTE: UNIMPLEMENTED */
RM_INLINE f32 rm_f32_pow(const f32 x, const f32 p) {
    if (rm_f32_eq(p, 0)) return 1;
    if (rm_f32_eq(x, 0)) {
        if (p < 0) return RM_INF;
        return 0;
    }
    f32 ap, tp, dp, val, xsqrt;
    usize i;

    ap = rm_f32_abs(p);
    tp = rm_f32_trunc(ap);
    dp = ap - tp;
    val = 1;

    for (i = 0; i < tp; ++i) {
        val *= x;
    }
    if (!rm_f32_eq(dp, 0)) {
        xsqrt = rm_f32_sqrt(x);
        if (rm_f32_eq(dp, 0.5)) {
            val *= xsqrt;
        }
    }

    return (p < 0) ? 1 / val : val;
}
RM_INLINE f64 rm_f64_pow(const f64 x, const f64 p) {
    if (rm_f64_eq(p, 0)) return 1;
    if (rm_f64_eq(x, 0)) {
        if (p < 0) return RM_INF;
        return 0;
    }
    f64 ap, tp, dp, val, xsqrt;
    usize i;

    ap = rm_f64_abs(p);
    tp = rm_f64_trunc(ap);
    dp = ap - tp;
    val = 1;

    for (i = 0; i < tp; ++i) {
        val *= x;
    }

    while (!rm_f64_eq(dp, 0)) {
        xsqrt = rm_f64_sqrt(x);

        if (dp > 0.75 || rm_f64_eq(dp, 0.75)) {
            val *= xsqrt * rm_f64_sqrt(xsqrt);
            dp -= 0.75;
        }
        if (dp > 0.5 || rm_f64_eq(dp, 0.5)) {
            val *= xsqrt;
            dp -= 0.5;
        }
        if (dp > 0.25 || rm_f64_eq(dp, 0.25)) {
            val *= rm_f64_sqrt(xsqrt);
            dp -= 0.25;
        }
    }

    return (p < 0) ? 1 / val : val;
}
/* END UNIMPLEMENTED */
RM_INLINE i8 rm_i8_pow2(const i8 x) {
    return RM_POW2(x);
}
RM_INLINE i16 rm_i16_pow2(const i16 x) {
    return RM_POW2(x);
}
RM_INLINE i32 rm_i32_pow2(const i32 x) {
    return RM_POW2(x);
}
RM_INLINE i64 rm_i64_pow2(const i64 x) {
    return RM_POW2(x);
}
RM_INLINE f32 rm_f32_pow2(const f32 x) {
    return RM_POW2(x);
}
RM_INLINE f64 rm_f64_pow2(const f64 x) {
    return RM_POW2(x);
}
RM_INLINE f32 rm_f32_rsqrt(const f32 x) {
    if (x < 0) return RM_NAN_F;
    if (rm_f32_eq(x, 0)) return RM_INF_F;
    f32_cvt c;
    f32 xh;

    c.f = x;
    xh = 0.5F * x;

    c.u = 0x5F375A86 - (c.u >> 1);

    /* Newton-Raphson iterations for accuracy */
    c.f *= 1.5F - (rm_f32_pow2(c.f) * xh);
    c.f *= 1.5F - (rm_f32_pow2(c.f) * xh);
    c.f *= 1.5F - (rm_f32_pow2(c.f) * xh);

    return c.f;
}
RM_INLINE f64 rm_f64_rsqrt(const f64 x) {
    if (x < 0) return RM_NAN;
    if (rm_f64_eq(x, 0)) return RM_INF;
    f64_cvt c;
    f64 xh;

    c.f = x;
    xh = 0.5 * x;

    c.u = 0x5FE6EB50C7B537A9 - (c.u >> 1);

    /* Newton-Raphson iterations for accuracy */
    c.f *= 1.5 - (rm_f64_pow2(c.f) * xh);
    c.f *= 1.5 - (rm_f64_pow2(c.f) * xh);
    c.f *= 1.5 - (rm_f64_pow2(c.f) * xh);
    c.f *= 1.5 - (rm_f64_pow2(c.f) * xh);

    return c.f;
}
/* sqrt(x) = x * 1/sqrt(x) */
RM_INLINE f32 rm_f32_sqrt(const f32 x) {
    if (x < 0) return RM_NAN_F;
    if (x == 0 || x == 1) return x;

    return x * rm_f32_rsqrt(x);
}
RM_INLINE f64 rm_f64_sqrt(const f64 x) {
    if (x < 0) return RM_NAN;
    if (x == 0 || x == 1) return x;

    return x * rm_f64_rsqrt(x);
}
RM_INLINE i8 rm_i8_abs(const i8 x) {
    return RM_ABS(x);
}
RM_INLINE i16 rm_i16_abs(const i16 x) {
    return RM_ABS(x);
}
RM_INLINE i32 rm_i32_abs(const i32 x) {
    return RM_ABS(x);
}
RM_INLINE i64 rm_i64_abs(const i64 x) {
    return RM_ABS(x);
}
RM_INLINE f32 rm_f32_abs(const f32 x) {
    return RM_ABS(x);
}
RM_INLINE f64 rm_f64_abs(const f64 x) {
    return RM_ABS(x);
}
RM_INLINE i8 rm_i8_min(const i8 a, const i8 b) {
    return RM_MIN(a, b);
}
RM_INLINE i16 rm_i16_min(const i16 a, const i16 b) {
    return RM_MIN(a, b);
}
RM_INLINE i32 rm_i32_min(const i32 a, const i32 b) {
    return RM_MIN(a, b);
}
RM_INLINE i64 rm_i64_min(const i64 a, const i64 b) {
    return RM_MIN(a, b);
}
RM_INLINE f32 rm_f32_min(const f32 a, const f32 b) {
    return RM_MIN(a, b);
}
RM_INLINE f64 rm_f64_min(const f64 a, const f64 b) {
    return RM_MIN(a, b);
}
RM_INLINE i8 rm_i8_max(const i8 a, const i8 b) {
    return RM_MAX(a, b);
}
RM_INLINE i16 rm_i16_max(const i16 a, const i16 b) {
    return RM_MAX(a, b);
}
RM_INLINE i32 rm_i32_max(const i32 a, const i32 b) {
    return RM_MAX(a, b);
}
RM_INLINE i64 rm_i64_max(const i64 a, const i64 b) {
    return RM_MAX(a,b);
}
RM_INLINE f32 rm_f32_max(const f32 a, const f32 b) {
    return RM_MAX(a, b);
}
RM_INLINE f64 rm_f64_max(const f64 a, const f64 b) {
    return RM_MAX(a, b);
}
RM_INLINE i8 rm_i8_clamp(const i8 val, const i8 min, const i8 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i16 rm_i16_clamp(const i16 val, const i16 min, const i16 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i32 rm_i32_clamp(const i32 val, const i32 min, const i32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i64 rm_i64_clamp(const i64 val, const i64 min, const i64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32 rm_f32_clamp(const f32 val, const f32 min, const f32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f64 rm_f64_clamp(const f64 val, const f64 min, const f64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32 rm_f32_trunc(const f32 x) {
    return (i32)x;
}
RM_INLINE f64 rm_f64_trunc(const f64 x) {
    return (i64)x;
}
RM_INLINE i8 rm_i8_fmod(const i8 a, const i8 b) {
    return a % b;
}
RM_INLINE i16 rm_i16_fmod(const i16 a, const i16 b) {
    return a % b;
}
RM_INLINE i32 rm_i32_fmod(const i32 a, const i32 b) {
    return a % b;
}
RM_INLINE i64 rm_i64_fmod(const i64 a, const i64 b) {
    return a % b;
}
RM_INLINE f32 rm_f32_fmod(const f32 a, const f32 b) {
    return a - rm_f32_trunc(a / b) * b;
}
RM_INLINE f64 rm_f64_fmod(const f64 a, const f64 b) {
    return a - rm_f64_trunc(a / b) * b;
}
RM_INLINE f32 rm_f32_floor(const f32 x) {
    if (rm_f32_eq(x, 0)) return x;
    i32 ix;

    ix = rm_f32_trunc(x);

    return (x < 0) ? ix - 1 : ix;
}
RM_INLINE f64 rm_f64_floor(const f64 x) {
    if (rm_f64_eq(x, 0)) return x;
    i64 ix;

    ix = rm_f64_trunc(x);

    return (x < 0) ? ix - 1 : ix;
}
RM_INLINE f32 rm_f32_ceil(const f32 x) {
    if (rm_f32_eq(x, 0)) return x;
    i32 ix;

    ix = rm_f32_trunc(x);

    return (x < 0) ? ix : ix + 1;
}
RM_INLINE f64 rm_f64_ceil(const f64 x) {
    if (rm_f64_eq(x, 0)) return x;
    i64 ix;

    ix = rm_f64_trunc(x);

    return (x < 0) ? ix : ix + 1;
}
RM_INLINE f32 rm_f32_round(const f32 x) {
    if (rm_f32_eq(x, 0)) return x;
    bool c1, c2;

    c1 = (rm_f32_abs(x) - rm_i32_abs(rm_f32_trunc(x))) < 0.5F;
    c2 = x < 0;

    return (c1) ? ((c2) ? rm_f32_ceil(x) : rm_f32_floor(x)) :
        ((c2) ? rm_f32_floor(x) : rm_f32_ceil(x));
}
RM_INLINE f64 rm_f64_round(const f64 x) {
    if (rm_f64_eq(x, 0)) return x;
    bool c1, c2;

    c1 = (rm_f64_abs(x) - rm_i64_abs(rm_f64_trunc(x))) < 0.5;
    c2 = x < 0;

    return (c1) ? ((c2) ? rm_f64_ceil(x) : rm_f64_floor(x)) :
        ((c2) ? rm_f64_floor(x) : rm_f64_ceil(x));
}
RM_INLINE i8 rm_i8_wrap_max(const i8 val, const i8 max) {
    return rm_i8_fmod(max + rm_i8_fmod(val, max), max);
}
RM_INLINE i16 rm_i16_wrap_max(const i16 val, const i16 max) {
    return rm_i16_fmod(max + rm_i16_fmod(val, max), max);
}
RM_INLINE i32 rm_i32_wrap_max(const i32 val, const i32 max) {
    return rm_i32_fmod(max + rm_i32_fmod(val, max), max);
}
RM_INLINE i64 rm_i64_wrap_max(const i64 val, const i64 max) {
    return rm_i64_fmod(max + rm_i64_fmod(val, max), max);
}
RM_INLINE f32 rm_f32_wrap_max(const f32 val, const f32 max) {
    return rm_f32_fmod(max + rm_f32_fmod(val, max), max);
}
RM_INLINE f64 rm_f64_wrap_max(const f64 val, const f64 max) {
    return rm_f64_fmod(max + rm_f64_fmod(val, max), max);
}
RM_INLINE i8 rm_i8_wrap(const i8 val, const i8 min, const i8 max) {
    i8 tmax;

    tmax = max - min;

    return min + rm_i8_fmod(tmax + rm_i8_fmod(val - min, tmax), tmax);
}
RM_INLINE i16 rm_i16_wrap(const i16 val, const i16 min, const i16 max) {
    i16 tmax;

    tmax = max - min;

    return min + rm_i16_fmod(tmax + rm_i16_fmod(val - min, tmax), tmax);
}
RM_INLINE i32 rm_i32_wrap(const i32 val, const i32 min, const i32 max) {
    i32 tmax;

    tmax = max - min;

    return min + rm_i32_fmod(tmax + rm_i32_fmod(val - min, tmax), tmax);
}
RM_INLINE i64 rm_i64_wrap(const i64 val, const i64 min, const i64 max) {
    i64 tmax;

    tmax = max - min;

    return min + rm_i64_fmod(tmax + rm_i64_fmod(val - min, tmax), tmax);
}
RM_INLINE f32 rm_f32_wrap(const f32 val, const f32 min, const f32 max) {
    f32 tmax;

    tmax = max - min;

    return min + rm_f32_fmod(tmax + rm_f32_fmod(val - min, tmax), tmax);
}
RM_INLINE f64 rm_f64_wrap(const f64 val, const f64 min, const f64 max) {
    f64 tmax;

    tmax = max - min;

    return min + rm_f64_fmod(tmax + rm_f64_fmod(val - min, tmax), tmax);
}
RM_INLINE f32 rm_f32_cos_step(const f64 x) {
    f64 r, w, z, C0, C1, C2, C3;

    C0 = -0x1FFFFFFD0C5E81.0p-54; /* -0.499999997251031003120 */
    C1 = 0x155553E1053A42.0p-57;  /* 0.0416666233237390631894 */
    C2 = -0x16C087E80F1E27.0p-62; /* -0.00138867637746099294692 */
    C3 = 0x199342E0EE5069.0p-68;  /* 0.0000243904487962774090654 */

    z = rm_f32_pow2(x);
    w = rm_f32_pow2(z);
    r = C2 + z * C3;

    return ((1 + z * C0) + w * C1) + (w * z) * r;
}
RM_INLINE f64 rm_f64_cos_step(const f64 x, const f64 y) {
    f64 hz, z, r, w, C1, C2, C3, C4, C5, C6;

    C1 = 4.16666666666666019037e-02;  /* 0x3FA55555, 0x5555554C */
    C2 = -1.38888888888741095749e-03; /* 0xBF56C16C, 0x16C15177 */
    C3 = 2.48015872894767294178e-05;  /* 0x3EFA01A0, 0x19CB1590 */
    C4 = -2.75573143513906633035e-07; /* 0xBE927E4F, 0x809C52AD */
    C5 = 2.08757232129817482790e-09;  /* 0x3E21EE9E, 0xBDB4B1C4 */
    C6 = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

    z = rm_f64_pow2(x);
    w = rm_f64_pow2(z);
    r = z * (C1 + z * (C2 + z * C3)) + rm_f64_pow2(w) * (C4 + z * (C5 + z * C6));
    hz = 0.5 * z;
    w = 1 - hz;

    return w + (((1 - w) - hz) + (z * r - x * y));
}
RM_INLINE f32 rm_f32_sin_step(const f64 x) {
    f64 r, s, w, z, S1, S2, S3, S4;

    S1 = -0x15555554CBAC77.0p-55; /* -0.166666666416265235595 */
    S2 = 0x111110896EFBB2.0p-59;  /* 0.0083333293858894631756 */
    S3 = -0x1A00F9E2CAE774.0p-65; /* -0.000198393348360966317347 */
    S4 = 0x16CD878C3B46A7.0p-71;  /* 0.0000027183114939898219064 */

    z = rm_f32_pow2(x);
    w = rm_f32_pow2(z);
    r = S3 + z * S4;
    s = z * x;

    return (x + s * (S1 + z * S2)) + s * w * r;
}
RM_INLINE f64 rm_f64_sin_step(const f64 x, const f64 y, const i32 iy) {
    f64 z, r, v, w, S1, S2, S3, S4, S5, S6;

    S1 = -1.66666666666666324348e-01; /* 0xBFC55555, 0x55555549 */
    S2 = 8.33333333332248946124e-03;  /* 0x3F811111, 0x1110F8A6 */
    S3 = -1.98412698298579493134e-04; /* 0xBF2A01A0, 0x19C161D5 */
    S4 = 2.75573137070700676789e-06;  /* 0x3EC71DE3, 0x57B1FE7D */
    S5 = -2.50507602534068634195e-08; /* 0xBE5AE5E6, 0x8A2B9CEB */
    S6 = 1.58969099521155010221e-10;  /* 0x3DE5D93A, 0x5ACFD57C */

    z = rm_f64_pow2(x);
    w = rm_f64_pow2(z);
    r = S2 + z * (S3 + z * S4) + z * w * (S5 + z * S6);
    v = z * x;

    if (iy == 0) return x + v * (S1 + z * r);

    return x - ((z * (0.5 * y - v * r) - y) - v * S1);
}
RM_INLINE f32 rm_f32_tan_step(const f64 x, const i32 odd) {
    f64 z, r, w, s, t, u, T0, T1, T2, T3, T4, T5;

    T0 = 0x15554D3418C99F.0p-54; /* 0.333331395030791399758 */
    T1 = 0x1112FD38999F72.0p-55; /* 0.133392002712976742718 */
    T2 = 0x1b54C91D865AFE.0p-57; /* 0.0533812378445670393523 */
    T3 = 0x191DF3908C33CE.0p-58; /* 0.0245283181166547278873 */
    T4 = 0x185DADFCECF44E.0p-61; /* 0.00297435743359967304927 */
    T5 = 0x1362B9BF971BCD.0p-59; /* 0.00946564784943673166728 */

    z = rm_f32_pow2(x);
    r = T4 + z * T5;
    t = T2 + z * T3;
    w = rm_f32_pow2(z);
    s = z * x;
    u = T0 + z * T1;
    r = (x + s * u) + (s * w) * (t + w * r);

    return odd ? -1.0 / r : r;
}
RM_INLINE f64 rm_f64_tan_step(f64 x, f64 y, const i32 odd) {
    u32 hx;
    i32 big, sign;
    f64 z, r, v, w, s, a, w0, a0, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, pio4lo;

    T0 = 3.33333333333334091986e-01; /* 3FD55555, 55555563 */
    T1 = 1.33333333333201242699e-01; /* 3FC11111, 1110FE7A */
    T2 = 5.39682539762260521377e-02; /* 3FABA1BA, 1BB341FE */
    T3 = 2.18694882948595424599e-02; /* 3F9664F4, 8406D637 */
    T4 = 8.86323982359930005737e-03; /* 3F8226E3, E96E8493 */
    T5 = 3.59207910759131235356e-03; /* 3F6D6D22, C9560328 */
    T6 = 1.45620945432529025516e-03; /* 3F57DBC8, FEE08315 */
    T7 = 5.88041240820264096874e-04; /* 3F4344D8, F2F26501 */
    T8 = 2.46463134818469906812e-04; /* 3F3026F7, 1A8D1068 */
    T9 = 7.81794442939557092300e-05; /* 3F147E88, A03792A6 */
    T10 = 7.14072491382608190305e-05; /* 3F12B80F, 32F0A7E9 */
    T11 = -1.85586374855275456654e-05; /* BEF375CB, DB605373 */
    T12 = 2.59073051863633712884e-05; /* 3EFB2A70, 74BF7AD4 */
    pio4lo = 3.06161699786838301793e-17; /* 3C81A626, 33145C07 */

    RM_GET_HIGH_WORD(hx, x);
    big = (hx & 0x7FFFFFFF) >= 0x3FE59428; /* |x| >= 0.6744 */
    if (big) {
        sign = hx >> 31;
        if (sign) {
            x = -x;
            y = -y;
        }
        x = (RM_PI_4 - x) + (pio4lo - y);
        y = 0;
    }
    z = rm_f64_pow2(x);
    w = rm_f64_pow2(z);
    /*
     * Break x^5*(T[1]+x^2*T[2]+...) into
     * x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
     * x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
     */
    r = T1 + w * (T3 + w * (T5 + w * (T7 + w * (T9 + w * T11))));
    v = z * (T2 + w * (T4 + w * (T6 + w * (T8 + w * (T10 + w * T12)))));
    s = z * x;
    r = y + z * (s * (r + v) + y) + s * T0;
    w = x + r;
    if (big) {
        s = 1 - 2 * odd;
        v = s - 2 * (x + (r - rm_f64_pow2(w) / (w + s)));

        return sign ? -v : v;
    }
    if (!odd) return w;
    /* -1.0 / (x + r) has up to 2ulp error, so compute it accurately */
    w0 = w;
    RM_SET_LOW_WORD(w0, 0);
    /* w0 + v = r + x */
    v = r - (w0 - x);
    a0 = a = -1.0 / w;
    RM_SET_LOW_WORD(a0, 0);

    return a0 + a * (1 + a0 * w0 + a0 * v);
}
RM_INLINE i32 rm_f32_pi_2_rem(const f32 x, f64* y) {
    u32 ix;
    i32 n, sign, e0;
    f32_cvt u;
    f64 tx, ty, fn, pio2_1, pio2_1t;

    u = (f32_cvt){{x}};
    pio2_1 = 1.57079631090164184570e+00;  /* 0x3FF921FB, 0x50000000 */
    pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */

    ix = u.u & 0x7FFFFFFF;
    /* 25+53 bit pi is good enough for medium size */
    if (ix < 0x4DC90FDB) {  /* |x| ~< 2^28*(pi/2), medium size */
        /* Use a specialized rint() to get fn. */
        fn = (f64)x * RM_1_PI_2;
        n = (i32)fn;
        *y = x - fn * pio2_1 - fn * pio2_1t;
        /* Matters with directed rounding. */
        if (!(*y < -RM_PI_4)) {
            n--;
            fn--;
            *y = x - fn * pio2_1 - fn * pio2_1t;
        } else if (!(*y > RM_PI_4)) {
            n++;
            fn++;
            *y = x - fn * pio2_1 - fn * pio2_1t;
        }

        return n;
    }
    if (ix >= RM_INF_F_X) {  /* x is inf or NaN */
        *y = RM_INF_F;

        return 0;
    }
    /* scale x into [2^23, 2^24-1] */
    sign = u.u >> 31;
    e0 = (ix >> 23) - (0x0000007F + 23);  /* e0 = ilogb(|x|)-23, positive */
    u.u = ix - (e0 << 23);
    tx = u.f;
    n = rm_pi_2_rem_large(&tx, &ty, e0, 1, 0);

    if (sign) {
        *y = -ty;

        return -n;
    }
    *y = ty;

    return n;
}
RM_INLINE i32 rm_f64_pi_2_rem(const f64 x, f64* y) {
    u32 ix;
    i32 sign, n, ex, ey, i;
    f64_cvt u;
    f64 z, w, t, r, fn, pio2_1, pio2_1t, pio2_2, pio2_2t, pio2_3, pio2_3t, tx[3], ty[2];

    pio2_1 = 1.57079632673412561417E+00; /* 0x3FF921FB, 0x54400000 */
    pio2_1t = 6.07710050650619224932E-11; /* 0x3DD0B461, 0x1A626331 */
    pio2_2 = 6.07710050630396597660E-11; /* 0x3DD0B461, 0x1A600000 */
    pio2_2t = 2.02226624879595063154E-21; /* 0x3BA3198A, 0x2E037073 */
    pio2_3 = 2.02226624871116645580E-21; /* 0x3BA3198A, 0x2E000000 */
    pio2_3t = 8.47842766036889956997E-32; /* 0x397B839A, 0x252049C1 */

    u = (f64_cvt){{x}};
    sign = u.u >> 63;
    ix = (u.u >> 32) & 0x7FFFFFFF;

    /* |x| ~<= 5pi/4 */
    if (ix <= 0x400F6A7A) {
        /* |x| ~= pi/2 or 2pi/2 */
        /* cancellation -- use medium case */
        if ((ix & 0x000FFFFF) == 0x000921FB) goto medium;

        /* |x| ~<= 3pi/4 */
        if (ix <= 0x4002D97C) {
            if (!sign) {
                /* one round good to 85 bits */
                z = x - pio2_1;
                y[0] = z - pio2_1t;
                y[1] = (z - y[0]) - pio2_1t;

                return 1;
            }
            z = x + pio2_1;
            y[0] = z + pio2_1t;
            y[1] = (z - y[0]) + pio2_1t;

            return -1;
        }
        if (!sign) {
            z = x - 2 * pio2_1;
            y[0] = z - 2 * pio2_1t;
            y[1] = (z - y[0]) - 2 * pio2_1t;

            return 2;
        }
        z = x + 2 * pio2_1;
        y[0] = z + 2 * pio2_1t;
        y[1] = (z - y[0]) + 2 * pio2_1t;

        return -2;
    }
    /* |x| ~<= 9pi/4 */
    if (ix <= 0x401C463B) {
        /* |x| ~<= 7pi/4 */
        if (ix <= 0x4015FDBC) {
            /* |x| ~= 3pi/2 */
            if (ix == RM_3PI_2_F_X) goto medium;

            if (!sign) {
                z = x - 3 * pio2_1;
                y[0] = z - 3 * pio2_1t;
                y[1] = (z - y[0]) - 3 * pio2_1t;

                return 3;
            }
            z = x + 3 * pio2_1;
            y[0] = z + 3 * pio2_1t;
            y[1] = (z - y[0]) + 3 * pio2_1t;

            return -3;
        }
        /* |x| ~= 4pi/2 */
        if (ix == RM_2PI_F_X) goto medium;

        if (!sign) {
            z = x - 4 * pio2_1;
            y[0] = z - 4 * pio2_1t;
            y[1] = (z - y[0]) - 4 * pio2_1t;

            return 4;
        }
        z = x + 4 * pio2_1;
        y[0] = z + 4 * pio2_1t;
        y[1] = (z - y[0]) + 4 * pio2_1t;

        return -4;
    }
    /* |x| ~< 2^20*(pi/2), medium size */
    if (ix < 0x413921FB) {
    medium:
        /* rint(x/(pi/2)) */
        fn = (f64)x * RM_1_PI_2;
        n = (i32)fn;
        r = x - fn * pio2_1;
        w = fn * pio2_1t;

        /* 1st round, good to 85 bits */
        /* Matters with directed rounding. */
        if (!(r - w < -RM_PI_4)) {
            n--;
            fn--;
            r = x - fn * pio2_1;
            w = fn * pio2_1t;
        } else if (!((r - w) > RM_PI_4)) {
            n++;
            fn++;
            r = x - fn * pio2_1;
            w = fn * pio2_1t;
        }

        y[0] = r - w;
        u.f = y[0];
        ey = (u.u >> 52) & 0x000007FF;
        ex = ix >> 20;
        /* 2nd round, good to 118 bits */
        if ((ex - ey) > 16) {
            t = r;
            w = fn * pio2_2;
            r = t - w;
            w = fn * pio2_2t - ((t - r) - w);
            y[0] = r - w;
            u.f = y[0];
            ey = (u.u >> 52) & 0x000007FF;

            /* 3rd round, good to 151 bits, covers all cases */
            if (ex - ey > 49) {
                t = r;
                w = fn * pio2_3;
                r = t - w;
                w = fn * pio2_3t - ((t - r) - w);
                y[0] = r - w;
            }
        }
        y[1] = (r - y[0]) - w;

        return n;
    }
    /*
     * all other (large) arguments
     */
    if (ix >= RM_INF_F_X) {  /* x is inf or NaN */
        y[0] = y[1] = RM_INF;

        return 0;
    }
    /* set z = scalbn(|x|,-ilogb(x)+23) */
    u.f = x;
    u.u &= (u64)-1 >> 12;
    u.u |= (u64)(0x000003FF + 23) << 52;
    z = u.f;
    for (i = 0; i < 2; i++) {
        tx[i] = (f64)(i32)z;
        z = (z - tx[i]) * 0x1p24;
    }
    tx[i] = z;

    /* skip zero terms, first term is non-zero */
    while (rm_f64_eq(tx[i], 0)) i--;

    n = rm_pi_2_rem_large(tx, ty, (i32)(ix >> 20) - (0x000003FF + 23), i + 1, 1);
    if (sign) {
        y[0] = -ty[0];
        y[1] = -ty[1];

        return -n;
    }
    y[0] = ty[0];
    y[1] = ty[1];

    return n;
}
static const i32 ipio2[66] = {
    0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
    0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
    0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
    0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
    0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
    0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
    0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
    0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
    0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
    0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
    0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B
};
static const f64 PIo2[8] = {
    1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
    7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
    5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
    3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
    1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
    1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
    2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
    2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
};
RM_INLINE i32 rm_pi_2_rem_large(f64* x, f64* y, const i32 e0, const i32 nx, const i32 prec) {
    i32 jz, jx, jv, jp, jk, carry, n, i, j, k, m, q0, ih, iq[20];
    f64 z, fw, f[20], fq[20], q[20];
    /* initial value for jk */
    const i32 init_jk[4] = {3,4,4,6};

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx = nx - 1;
    jv = (e0 - 3) / 24;
    if (jv < 0) jv = 0;

    q0 = e0 - 24 * (jv + 1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv - jx;
    m = jx + jk;
    for (i = 0; i <= m; ++i, ++j) f[i] = j < 0 ? 0 : (f64)ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i = 0; i <= jk; ++i) {
        for (j = 0, fw = 0; j <= jx; ++j) fw += x[j] * f[jx + i - j];

        q[i] = fw;
    }

    jz = jk;
 recompute:
    /* distill q[] into iq[] reversingly */
    for (i = 0, j = jz, z = q[jz]; j > 0; ++i, --j) {
        fw = (f64)(i32)(0x1p-24 * z);
        iq[i] = (i32)(z - 0x1p24 * fw);
        z  = q[j - 1] + fw;
    }

    /* compute n */
    z = rm_f64_scalbn(z, q0);  /* actual value of z */
    z -= 8 * rm_f64_floor(z * 0.125); /* trim off integer >= 8 */
    n = (i32)z;
    z -= (f64)n;
    ih = 0;
    if (q0 > 0) { /* need iq[jz-1] to determine n */
        i = iq[jz - 1] >> (24 - q0);
        n += i;
        iq[jz - 1] -= i << (24 - q0);
        ih = iq[jz - 1] >> (23 - q0);
    }
    else if (q0 == 0) ih = iq[jz - 1] >> 23;
    else if (z >= 0.5) ih = 2;

    if (ih > 0) { /* q > 0.5 */
        n += 1;
        carry = 0;
        for (i = 0; i <  jz; ++i) { /* compute 1-q */
            j = iq[i];
            if (carry == 0) {
                if (j != 0) {
                    carry = 1;
                    iq[i] = 0x1000000 - j;
                }
            } else
                iq[i] = 0x00FFFFFF - j;
        }
        if (q0 > 0) { /* rare case: chance is 1 in 12 */
            switch(q0) {
            case 1:
                iq[jz-1] &= 0x07FFFFF;
                break;
            case 2:
                iq[jz-1] &= 0x03FFFFF;
                break;
            }
        }
        if (ih == 2) {
            z = 1 - z;

            if (carry != 0) z -= rm_f64_scalbn(1, q0);
        }
    }

    /* check if recomputation is needed */
    if (rm_f64_eq(z, 0)) {
        j = 0;
        for (i = jz - 1; i >= jk; --i) j |= iq[i];

        /* needs recomputation */
        if (j == 0) {
            /* k = no. of terms needed */
            for (k = 1; iq[jk - k] == 0; ++k);

            /* add q[jz+1] to q[jz+k] */
            for (i = jz + 1; i <= jz + k; ++i) {
                f[jx + i] = (f64)ipio2[jv + i];
                for (j = 0, fw = 0; j <= jx; ++j) fw += x[j] * f[jx + i - j];

                q[i] = fw;
            }
            jz += k;

            goto recompute;
        }
    }

    /* chop off zero terms */
    if (rm_f64_eq(z, 0)) {
        jz -= 1;
        q0 -= 24;

        while (iq[jz] == 0) {
            jz--;
            q0 -= 24;
        }
    } else {
        /* break z into 24-bit if necessary */
        z = rm_f64_scalbn(z, -q0);
        if (z >= 0x1p24) {
            fw = (f64)(i32)(0x1p-24 * z);
            iq[jz] = (i32)(z - 0x1p24 * fw);
            jz += 1;
            q0 += 24;
            iq[jz] = (i32)fw;
        } else iq[jz] = (i32)z;
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = rm_f64_scalbn(1, q0);
    for (i = jz; i >= 0; --i) {
        q[i] = fw * (f64)iq[i];
        fw *= 0x1p-24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i = jz; i >= 0; --i) {
        for (fw = 0, k = 0; k <= jp && k <= jz - i; ++k) fw += PIo2[k] * q[i + k];

        fq[jz - i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
    case 0:
        fw = 0;
        for (i = jz; i >= 0; --i) fw += fq[i];

        y[0] = ih == 0 ? fw : -fw;
        break;
    case 1:
    case 2:
        fw = 0;
        for (i = jz; i >= 0; --i) fw += fq[i];

        // TODO: drop excess precision here once double_t is used
        fw = (f64)fw;
        y[0] = ih == 0 ? fw : -fw;
        fw = fq[0] - fw;
        for (i = 1; i <= jz; ++i) fw += fq[i];

        y[1] = ih == 0 ? fw : -fw;
        break;
    case 3: /* painful */
        for (i = jz; i > 0; --i) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (i = jz; i > 1; --i) {
            fw = fq[i - 1] + fq[i];
            fq[i] += fq[i - 1] - fw;
            fq[i - 1] = fw;
        }
        for (fw = 0, i = jz; i >= 2; --i) fw += fq[i];

        if (ih == 0) {
            y[0] = fq[0]; y[1] = fq[1]; y[2] = fw;
        } else {
            y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
        }
    }

    return n & 7;
}
RM_INLINE f32 rm_f32_cos(const f32 x) {
    u32 ix, n, sign;
    f64 y;

    ix = as_u32(x);
    sign = ix >> 31;
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN_F;

    /* |x| ~<= pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-12 */
        return (ix < 0x39800000) ? 1 : rm_f32_cos_step(x);
        /* raise inexact if x != 0 */
    }
    /* |x| ~<= 5*pi/4 */
    if (ix <= 0x407B53D1) {
        /* |x|  ~> 3*pi/4 */
        return (ix > 0x4016CBE3) ? -rm_f32_cos_step(sign ? x + RM_PI : x - RM_PI)
            : rm_f32_sin_step((sign) ? x + RM_PI_2 : RM_PI_2 - x);
    }
    /* |x| ~<= 9*pi/4 */
    if (ix <= 0x40e231d5) {
        /* |x| ~> 7*pi/4 */
        return (ix > 0x40AFEDDF) ? rm_f32_cos_step((sign) ? (x + RM_2PI) : (x - RM_2PI))
            : rm_f32_sin_step((sign) ? (-x - RM_3PI_2) : (x - RM_3PI_2));
    }

    /* general argument reduction needed */
    n = rm_f32_pi_2_rem(x, &y);

    switch (n & 3) {
    case 0:  return  rm_f32_cos_step(y);
    case 1:  return  rm_f32_sin_step(-y);
    case 2:  return -rm_f32_cos_step(y);
    default: return  rm_f32_sin_step(y);
    }
}
RM_INLINE f64 rm_f64_cos(const f64 x) {
    u32 ix, n;
    f64 y[2];

    RM_GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN;

    /* |x| ~< pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-27 * sqrt(2) */
        return (ix < 0x3E46A09E) ? 1 : rm_f64_cos_step(x, 0);
        /* raise inexact if x!=0 */
    }

    /* argument reduction */
    n = rm_f64_pi_2_rem(x, y);

    switch (n & 3) {
    case 0:  return  rm_f64_cos_step(y[0], y[1]);
    case 1:  return -rm_f64_sin_step(y[0], y[1], 1);
    case 2:  return -rm_f64_cos_step(y[0], y[1]);
    default: return  rm_f64_sin_step(y[0], y[1], 1);
    }
}
RM_INLINE f32 rm_f32_sin(const f32 x) {
    u32 ix;
    i32 n, sign;
    f64 y;

    ix = as_u32(x);
    sign = ix >> 31;
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN_F;

    /* |x| ~<= pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-12 */
        return (ix < 0x39800000) ? x : rm_f32_sin_step(x);
        /* raise inexact if x!=0 and underflow if subnormal */
    }
    /* |x| ~<= 5*pi/4 */
    if (ix <= 0x407B53D1) {
        /* |x| ~<= 3pi/4 */
        if (ix <= 0x4016CBE3) {
            return (sign) ? -rm_f32_cos_step(x + RM_PI_2) : rm_f32_cos_step(x - RM_PI_2);
        }

        return rm_f32_sin_step(sign ? -(x + RM_PI) : -(x - RM_PI));
    }
    /* |x| ~<= 9*pi/4 */
    if (ix <= 0x40E231D5) {
        /* |x| ~<= 7*pi/4 */
        if (ix <= 0x40AFEDDF) {
            return (sign) ? rm_f32_cos_step(x + RM_3PI_2) : -rm_f32_cos_step(x - RM_3PI_2);
        }

        return rm_f32_sin_step(sign ? x + RM_2PI : x - RM_2PI);
    }

    /* general argument reduction needed */
    n = rm_f32_pi_2_rem(x, &y);
    switch (n & 3) {
    case 0:  return rm_f32_sin_step(y);
    case 1:  return rm_f32_cos_step(y);
    case 2:  return rm_f32_sin_step(-y);
    default: return -rm_f32_cos_step(y);
    }
}
RM_INLINE f64 rm_f64_sin(const f64 x) {
    f64 y[2];
    u32 ix, n;

    /* High word of x. */
    RM_GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN;

    /* |x| ~< pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-26 */
        return (ix < 0x3E500000) ? x : rm_f64_sin_step(x, 0, 0);
        /* raise inexact if x != 0 and underflow if subnormal*/
    }

    /* argument reduction needed */
    n = rm_f64_pi_2_rem(x, y);
    switch (n & 3) {
    case 0:  return  rm_f64_sin_step(y[0], y[1], 1);
    case 1:  return  rm_f64_cos_step(y[0], y[1]);
    case 2:  return -rm_f64_sin_step(y[0], y[1], 1);
    default: return -rm_f64_cos_step(y[0], y[1]);
    }
}
RM_INLINE f32 rm_f32_tan(const f32 x) {
    f64 y;
    u32 ix, n, sign;

    ix = as_u32(x);
    sign = ix >> 31;
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN_F;

    /* |x| ~<= pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-12 */
        return (ix < 0x39800000) ? x : rm_f32_tan_step(x, 0);
        /* raise inexact if x!=0 and underflow if subnormal */
    }
    /* |x| ~<= 5*pi/4 */
    if (ix <= 0x407B53D1) {
        /* |x| ~<= 3pi/4 */
        return (ix <= 0x4016CBE3) ? rm_f32_tan_step((sign ? x + RM_PI_2 : x - RM_PI_2), 1)
            : rm_f32_tan_step((sign ? x + RM_PI : x - RM_PI), 0);
    }
    /* |x| ~<= 9*pi/4 */
    if (ix <= 0x40E231D5) {
        /* |x| ~<= 7*pi/4 */
        return (ix <= 0x40AFEDDF) ? rm_f32_tan_step((sign ? x + RM_3PI_2 : x - RM_3PI_2), 1)
            : rm_f32_tan_step((sign ? x + RM_2PI : x - RM_2PI), 0);
    }
    /* argument reduction */
    n = rm_f32_pi_2_rem(x, &y);

    return rm_f32_tan_step(y, n & 1);
}
RM_INLINE f64 rm_f64_tan(const f64 x) {
    f64 y[2];
    u32 ix, n;

    RM_GET_HIGH_WORD(ix, x);
    ix &= 0x7FFFFFFF;

    if (ix >= RM_INF_F_X) return RM_NAN;

    /* |x| ~< pi/4 */
    if (ix <= RM_PI_4_F_X) {
        /* |x| < 2**-27 */
        return (ix < 0x3E400000) ? x : rm_f64_tan_step(x, 0, 0);
        /* raise inexact if x!=0 and underflow if subnormal */
    }
    /* argument reduction */
    n = rm_f64_pi_2_rem(x, y);

    return rm_f64_tan_step(y[0], y[1], n & 1);
}
RM_INLINE f32 rm_f32_acos(const f32 x) {
    f32 u, wx;

    wx = rm_f32_wrap(x, -1, 1);

    u = 3.2746921e-10;
    u = u * wx - 4.4469136e+3;
    u = u * wx - 1.699231e-9;
    u = u * wx + 2.0796239e+4;
    u = u * wx + 3.7578104e-9;
    u = u * wx - 4.0958535e+4;
    u = u * wx - 4.6153898e-9;
    u = u * wx + 4.4122843e+4;
    u = u * wx + 3.4378718e-9;
    u = u * wx - 2.8251035e+4;
    u = u * wx - 1.5913952e-9;
    u = u * wx + 1.0933702e+4;
    u = u * wx + 4.505914e-10;
    u = u * wx - 2.4859131e+3;
    u = u * wx - 7.3686135e-11;
    u = u * wx + 3.0608094e+2;
    u = u * wx + 6.1595331e-12;
    u = u * wx - 1.7306201e+1;
    u = u * wx - 2.0129396e-13;
    u = u * wx - 7.1853541e-1;

    return u * wx + 1.5707963;
}
RM_INLINE f64 rm_f64_acos(const f64 x) {
    f64 u, wx;

    wx = rm_f64_wrap(x, -1, 1);

    u = -5.4130790091039394e-28;
    u = u * wx - 4.4480837030957942e+3;
    u = u * wx + 2.8088414585483633e-27;
    u = u * wx + 2.0801769015729236e+4;
    u = u * wx - 6.2117021682647652e-27;
    u = u * wx - 4.0969537399240268e+4;
    u = u * wx + 7.6293071798295526e-27;
    u = u * wx + 4.4134814439494655e+4;
    u = u * wx - 5.6828654884956575e-27;
    u = u * wx - 2.8258775791130758e+4;
    u = u * wx + 2.630611595430223e-27;
    u = u * wx + 1.093672698677737e+4;
    u = u * wx - 7.448393617335392e-28;
    u = u * wx - 2.4866073426040822e+3;
    u = u * wx + 1.2180540096175114e-28;
    u = u * wx + 3.0616723894904099e+2;
    u = u * wx - 1.018191887981769e-29;
    u = u * wx - 1.7311077585808664e+1;
    u = u * wx + 3.3274663966689927e-31;
    u = u * wx - 7.1845459696544851e-1;

    return u * wx + 1.5707963267948966;
}
RM_INLINE f32 rm_f32_asin(const f32 x) {
    f32 u, wx;

    wx = rm_f32_wrap(x, -1, 1);

    u = -2.0602686e-10;
    u = u * wx + 4.4469136e+3;
    u = u * wx + 1.0690691e-9;
    u = u * wx - 2.0796239e+4;
    u = u * wx - 2.364222e-9;
    u = u * wx + 4.0958535e+4;
    u = u * wx + 2.903767e-9;
    u = u * wx - 4.4122843e+4;
    u = u * wx - 2.162933e-9;
    u = u * wx + 2.8251035e+4;
    u = u * wx + 1.0012244e-9;
    u = u * wx - 1.0933702e+4;
    u = u * wx - 2.8348904e-10;
    u = u * wx + 2.4859131e+3;
    u = u * wx + 4.6359544e-11;
    u = u * wx - 3.0608094e+2;
    u = u * wx - 3.8752629e-12;
    u = u * wx + 1.7306201e+1;
    u = u * wx + 1.2664386e-13;
    u = u * wx + 7.1853541e-1;
    return u * wx - 6.8948906e-16;
}
RM_INLINE f64 rm_f64_asin(const f64 x) {
    f64 u, wx;

    wx = rm_f64_wrap(x, -1, 1);

    u = 1.1974955090042064e-28;
    u = u * wx + 4.4480837030957942e+3;
    u = u * wx - 6.2137926057600319e-28;
    u = u * wx - 2.0801769015729236e+4;
    u = u * wx + 1.3741690149466498e-27;
    u = u * wx + 4.0969537399240268e+4;
    u = u * wx - 1.6877753066774072e-27;
    u = u * wx - 4.4134814439494655e+4;
    u = u * wx + 1.2571783802348478e-27;
    u = u * wx + 2.8258775791130758e+4;
    u = u * wx - 5.8195078367857512e-28;
    u = u * wx - 1.093672698677737e+4;
    u = u * wx + 1.6477531347785027e-28;
    u = u * wx + 2.4866073426040822e+3;
    u = u * wx - 2.6946109668607808e-29;
    u = u * wx - 3.0616723894904099e+2;
    u = u * wx + 2.2524707492945266e-30;
    u = u * wx + 1.7311077585808664e+1;
    u = u * wx - 7.3611082706755614e-32;
    u = u * wx + 7.1845459696544851e-1;

    return u * wx + 4.0076297309073265e-34;
}
RM_INLINE f32 rm_f32_atan(const f32 x) {
    return rm_f32_asin(x / rm_f32_sqrt(rm_f32_pow2(x) + 1));
}
RM_INLINE f64 rm_f64_atan(const f64 x) {
    return rm_f64_asin(x / rm_f64_sqrt(rm_f32_pow2(x) + 1));
}
RM_INLINE f32 rm_f32_atan2(const f32 y, const f32 x) {
    if (rm_f32_eq(y, 0)) {
        if (x < 0) return RM_PI;
        return 0;
    }
    if (rm_f32_eq(x, 0)) {
        if (y < 0) return -RM_PI_2;
        return RM_PI_2;
    }

    return rm_f32_atan(y / x);
}
RM_INLINE f64 rm_f64_atan2(const f64 y, const f64 x) {
    if (rm_f64_eq(y, 0)) {
        if (x < 0) return RM_PI;
        return 0;
    }
    if (rm_f64_eq(x, 0)) {
        if (y < 0) return -RM_PI_2;
        return RM_PI_2;
    }

    return rm_f64_atan(y / x);
}
RM_INLINE f32 rm_f32_rad2deg(const f32 x) {
    return RM_MAKE_DEG_F * x;
}
RM_INLINE f64 rm_f64_rad2deg(const f64 x) {
    return RM_MAKE_DEG * x;
}
RM_INLINE f32 rm_f32_deg2rad(const f32 x) {
    return RM_MAKE_RAD_F * x;
}
RM_INLINE f64 rm_f64_deg2rad(const f64 x) {
    return RM_MAKE_RAD * x;
}

RM_INLINE vec2 rm_vec2_copy(const vec2 v) {
    vec2 dest;

    dest.x = v.x;
    dest.y = v.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_abs(const vec2 v) {
    vec2 dest;

    dest.x = rm_f32_abs(v.x);
    dest.y = rm_f32_abs(v.y);

    return dest;
}
RM_INLINE f32 rm_vec2_max(const vec2 v) {
    return rm_f32_max(v.x, v.y);
}
RM_INLINE f32 rm_vec2_min(const vec2 v) {
    return rm_f32_min(v.x, v.y);
}
RM_INLINE vec2 rm_vec2_maxv(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = rm_f32_max(a.x, b.x);
    dest.y = rm_f32_max(a.y, b.y);

    return dest;
}
RM_INLINE vec2 rm_vec2_minv(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = rm_f32_min(a.x, b.x);
    dest.y = rm_f32_min(a.y, b.y);

    return dest;
}
RM_INLINE f32 rm_vec2_hadd(const vec2 v) {
    return v.x + v.y;
}
RM_INLINE vec2 rm_vec2_zero(void) {
    vec2 dest;

    dest = RM_VEC2_FILL(0);

    return dest;
}
RM_INLINE vec2 rm_vec2_one(void) {
    vec2 dest;

    dest = RM_VEC2_FILL(1);

    return dest;
}
RM_INLINE vec2 rm_vec2_set(const f32 x, const f32 y) {
    vec2 dest;

    dest = rm_vec2(x, y);

    return dest;
}
RM_INLINE vec2 rm_vec2_fill(const f32 x) {
    vec2 dest;

    dest = RM_VEC2_FILL(x);

    return dest;
}
RM_INLINE f32 rm_vec2_dot(const vec2 a, const vec2 b) {
    return a.x * b.x + a.y * b.y;
}
RM_INLINE f32 rm_vec2_cross(const vec2 a, const vec2 b) {
    return a.x * b.y - b.x * a.y;
}
RM_INLINE f32 rm_vec2_norm2(const vec2 v) {
    return rm_vec2_dot(v, v);
}
RM_INLINE f32 rm_vec2_norm(const vec2 v) {
    return rm_f32_sqrt(rm_vec2_norm2(v));
}
RM_INLINE f32 rm_vec2_norm_one(const vec2 v) {
    return rm_vec2_hadd(rm_vec2_abs(v));
}
RM_INLINE f32 rm_vec2_norm_inf(const vec2 v) {
    return rm_vec2_max(rm_vec2_abs(v));
}
RM_INLINE vec2 rm_vec2_add(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = a.x + b.x;
    dest.y = a.y + b.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_adds(const vec2 v, const f32 s) {
    vec2 dest;

    dest.x = v.x + s;
    dest.y = v.y + s;

    return dest;
}
RM_INLINE vec2 rm_vec2_sub(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = a.x - b.x;
    dest.y = a.y - b.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_subs(const vec2 v, const f32 s) {
    vec2 dest;

    dest.x = v.x - s;
    dest.y = v.y - s;

    return dest;
}
RM_INLINE vec2 rm_vec2_mul(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = a.x * b.x;
    dest.y = a.y * b.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_scale(const vec2 v, const f32 s) {
    vec2 dest;

    dest.x = v.x * s;
    dest.y = v.y * s;

    return dest;
}
RM_INLINE vec2 rm_vec2_scale_as(const vec2 v, const f32 s) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec2_zero() : rm_vec2_scale(v, s / norm);
}
RM_INLINE vec2 rm_vec2_scale_aniso(const vec2 v, const f32 x, const f32 y) {
    vec2 dest;

    dest.x = v.x * x;
    dest.y = v.y * y;

    return dest;
}
RM_INLINE vec2 rm_vec2_div(const vec2 a, const vec2 b) {
    vec2 dest;

    dest.x = a.x / b.x;
    dest.y = a.y / b.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_divs(const vec2 v, const f32 s) {
    vec2 dest;

    dest = rm_vec2_scale(v, 1.0F / s);

    return dest;
}
RM_INLINE vec2 rm_vec2_negate(const vec2 v) {
    vec2 dest;

    dest.x = -v.x;
    dest.y = -v.y;

    return dest;
}
RM_INLINE vec2 rm_vec2_normalize(const vec2 v) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec2_zero() : rm_vec2_scale(v, 1.0F / norm);
}
RM_INLINE vec2 rm_vec2_rotate(const vec2 v, const f32 a) {
    f32 c, s;
    vec2 dest;

    c = rm_f32_cos(a);
    s = rm_f32_sin(a);

    dest.x = c * v.x - s * v.y;
    dest.y = s * v.x + c * v.y;

    return dest;
}
RM_INLINE f32 rm_vec2_distance2(const vec2 a, const vec2 b) {
    return rm_f32_pow2(b.x - a.x) + rm_f32_pow2(b.y - a.y);
}
RM_INLINE f32 rm_vec2_distance(const vec2 a, const vec2 b) {
    return rm_f32_sqrt(rm_vec2_distance2(a, b));
}
RM_INLINE vec2 rm_vec2_clamp(const vec2 v, const f32 min, const f32 max) {
    vec2 dest;

    dest.x = rm_f32_clamp(v.x, min, max);
    dest.y = rm_f32_clamp(v.y, min, max);

    return dest;
}
RM_INLINE vec2 rm_vec2_wrap(const vec2 v, const f32 min, const f32 max) {
    vec2 dest;

    dest.x = rm_f32_wrap(v.x, min, max);
    dest.y = rm_f32_wrap(v.y, min, max);

    return dest;
}
RM_INLINE vec2 rm_vec2_center(const vec2 a, const vec2 b) {
    return rm_vec2_scale(rm_vec2_add(a, b), 0.5F);
}

RM_INLINE vec3 rm_vec3_copy(const vec3 v) {
    vec3 dest;

    dest.x = v.x;
    dest.y = v.y;
    dest.z = v.z;

    return dest;
}
RM_INLINE vec2 rm_vec3_copy2(const vec3 v) {
    vec2 dest;

    dest.x = v.x;
    dest.y = v.y;

    return dest;
}
RM_INLINE vec3 rm_vec3_abs(const vec3 v) {
    vec3 dest;

    dest.x = rm_f32_abs(v.x);
    dest.y = rm_f32_abs(v.y);
    dest.z = rm_f32_abs(v.z);

    return dest;
}
RM_INLINE f32 rm_vec3_max(const vec3 v) {
    return rm_f32_max(rm_f32_max(v.x, v.y), v.z);
}
RM_INLINE f32 rm_vec3_min(const vec3 v) {
    return rm_f32_min(rm_f32_min(v.x, v.y), v.z);
}
RM_INLINE vec3 rm_vec3_maxv(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = rm_f32_max(a.x, b.x);
    dest.y = rm_f32_max(a.y, b.y);
    dest.z = rm_f32_max(a.z, b.z);

    return dest;
}
RM_INLINE vec3 rm_vec3_minv(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = rm_f32_min(a.x, b.x);
    dest.y = rm_f32_min(a.y, b.y);
    dest.z = rm_f32_min(a.z, b.z);

    return dest;
}
RM_INLINE f32 rm_vec3_hadd(const vec3 v) {
    return v.x + v.y + v.z;
}
RM_INLINE vec3 rm_vec3_zero(void) {
    vec3 dest;

    dest = RM_VEC3_FILL(0);

    return dest;
}
RM_INLINE vec3 rm_vec3_one(void) {
    vec3 dest;

    dest = RM_VEC3_FILL(1);

    return dest;
}
RM_INLINE vec3 rm_vec3_set(const f32 x, const f32 y, const f32 z) {
    vec3 dest;

    dest = rm_vec3(x, y, z);

    return dest;
}
RM_INLINE vec3 rm_vec3_fill(const f32 x) {
    vec3 dest;

    dest = RM_VEC3_FILL(x);

    return dest;
}
RM_INLINE vec3 rm_vec3_make(const vec2 v, const f32 last) {
    vec3 dest;

    dest = rm_vec3(v.x, v.y, last);

    return dest;
}
RM_INLINE f32 rm_vec3_dot(const vec3 a, const vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
RM_INLINE vec3 rm_vec3_cross(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = a.y * b.z - a.z * b.y;
    dest.y = a.z * b.x - a.x * b.z;
    dest.z = a.x * b.y - a.y * b.x;

    return dest;
}
RM_INLINE vec3 rm_vec3_crossn(const vec3 a, const vec3 b) {
    return rm_vec3_normalize(rm_vec3_cross(a, b));
}
RM_INLINE f32 rm_vec3_norm2(const vec3 v) {
    return rm_vec3_dot(v, v);
}
RM_INLINE f32 rm_vec3_norm(const vec3 v) {
    return rm_f32_sqrt(rm_vec3_norm2(v));
}
RM_INLINE f32 rm_vec3_norm_one(const vec3 v) {
    return rm_vec3_hadd(rm_vec3_abs(v));
}
RM_INLINE f32 rm_vec3_norm_inf(const vec3 v) {
    return rm_vec3_max(rm_vec3_abs(v));
}
RM_INLINE vec3 rm_vec3_add(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = a.x + b.x;
    dest.y = a.y + b.y;
    dest.z = a.z + b.z;

    return dest;
}
RM_INLINE vec3 rm_vec3_adds(const vec3 v, const f32 s) {
    vec3 dest;

    dest.x = v.x + s;
    dest.y = v.y + s;
    dest.z = v.z + s;

    return dest;
}
RM_INLINE vec3 rm_vec3_sub(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = a.x - b.x;
    dest.y = a.y - b.y;
    dest.z = a.z - b.z;

    return dest;
}
RM_INLINE vec3 rm_vec3_subs(const vec3 v, const f32 s) {
    vec3 dest;

    dest.x = v.x - s;
    dest.y = v.y - s;
    dest.z = v.z - s;

    return dest;
}
RM_INLINE vec3 rm_vec3_mul(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = a.x * b.x;
    dest.y = a.y * b.y;
    dest.z = a.z * b.z;

    return dest;
}
RM_INLINE vec3 rm_vec3_scale(const vec3 v, const f32 s) {
    vec3 dest;

    dest.x = v.x * s;
    dest.y = v.y * s;
    dest.z = v.z * s;

    return dest;
}
RM_INLINE vec3 rm_vec3_scale_as(const vec3 v, const f32 s) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec3_zero() : rm_vec3_scale(v, s / norm);
}
RM_INLINE vec3 rm_vec3_scale_aniso(const vec3 v, const f32 x, const f32 y, const f32 z) {
    vec3 dest;

    dest.x = v.x * x;
    dest.y = v.y * y;
    dest.z = v.z * z;

    return dest;
}
RM_INLINE vec3 rm_vec3_div(const vec3 a, const vec3 b) {
    vec3 dest;

    dest.x = a.x / b.x;
    dest.y = a.y / b.y;
    dest.z = a.z / b.z;

    return dest;
}
RM_INLINE vec3 rm_vec3_divs(const vec3 v, const f32 s) {
    vec3 dest;

    dest = rm_vec3_scale(v, 1.0F / s);

    return dest;
}
RM_INLINE vec3 rm_vec3_negate(const vec3 v) {
    vec3 dest;

    dest.x = -v.x;
    dest.y = -v.y;
    dest.z = -v.z;

    return dest;
}
RM_INLINE vec3 rm_vec3_normalize(const vec3 v) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec3_zero() : rm_vec3_scale(v, 1.0F / norm);
}
RM_INLINE vec3 rm_vec3_rotate(const vec3 v, const f32 a, const vec3 axis) {
    f32 c, s;
    vec3 v1, v2, k, dest;

    c = rm_f32_cos(a);
    s = rm_f32_sin(a);

    k = rm_vec3_normalize(axis);

    v1 = rm_vec3_scale(v, c);

    v2 = rm_vec3_cross(k, v);
    v2 = rm_vec3_scale(v2, s);

    v1 = rm_vec3_add(v1, v2);

    v2 = rm_vec3_scale(k, rm_vec3_dot(k, v) * (1.0F - c));

    dest = rm_vec3_add(v1, v2);

    return dest;
}
RM_INLINE f32 rm_vec3_distance2(const vec3 a, const vec3 b) {
    return rm_f32_pow2(a.x - b.x) + rm_f32_pow2(a.y - b.y) + rm_f32_pow2(a.z - b.z);
}
RM_INLINE f32 rm_vec3_distance(const vec3 a, const vec3 b) {
    return rm_f32_sqrt(rm_vec3_distance2(a, b));
}
RM_INLINE vec3 rm_vec3_clamp(const vec3 v, const f32 min, const f32 max) {
    vec3 dest;

    dest.x = rm_f32_clamp(v.x, min, max);
    dest.y = rm_f32_clamp(v.y, min, max);
    dest.z = rm_f32_clamp(v.z, min, max);

    return dest;

}
RM_INLINE vec3 rm_vec3_wrap(const vec3 v, const f32 min, const f32 max) {
    vec3 dest;

    dest.x = rm_f32_wrap(v.x, min, max);
    dest.y = rm_f32_wrap(v.y, min, max);
    dest.z = rm_f32_wrap(v.z, min, max);

    return dest;
}
RM_INLINE vec3 rm_vec3_center(const vec3 a, const vec3 b) {
    return rm_vec3_scale(rm_vec3_add(a, b), 0.5F);
}

RM_INLINE vec4 rm_vec4_copy(const vec4 v) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_load(v.raw));
#else
    dest.x = v.x;
    dest.y = v.y;
    dest.z = v.z;
    dest.w = v.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec3 rm_vec4_copy3(const vec4 v) {
    vec3 dest;

    dest.x = v.x;
    dest.y = v.y;
    dest.z = v.z;

    return dest;
}
RM_INLINE vec4 rm_vec4_abs(const vec4 v) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_abs(rmm_load(v.raw)));
#else
    dest.x = rm_f32_abs(v.x);
    dest.y = rm_f32_abs(v.y);
    dest.z = rm_f32_abs(v.z);
    dest.w = rm_f32_abs(v.w);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE f32 rm_vec4_max(const vec4 v) {
    return rm_f32_max(rm_f32_max(rm_f32_max(v.x, v.y), v.z), v.w);
}
RM_INLINE f32 rm_vec4_min(const vec4 v) {
    return rm_f32_min(rm_f32_min(rm_f32_min(v.x, v.y), v.z), v.w);
}
RM_INLINE vec4 rm_vec4_maxv(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_max(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = rm_f32_max(a.x, b.x);
    dest.y = rm_f32_max(a.y, b.y);
    dest.z = rm_f32_max(a.z, b.z);
    dest.w = rm_f32_max(a.w, b.w);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_minv(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_min(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = rm_f32_min(a.x, b.x);
    dest.y = rm_f32_min(a.y, b.y);
    dest.z = rm_f32_min(a.z, b.z);
    dest.w = rm_f32_min(a.w, b.w);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE f32 rm_vec4_hadd(const vec4 v) {
#if RM_SIMD
    return rmm_hadd(rmm_load(v.raw));
#else
    return v.x + v.y + v.z + v.w;
#endif /* RM_SIMD */
}
RM_INLINE vec4 rm_vec4_zero(void) {
    vec4 dest;

    dest = RM_VEC4_FILL(0);

    return dest;
}
RM_INLINE vec4 rm_vec4_one(void) {
    vec4 dest;

    dest = RM_VEC4_FILL(1);

    return dest;
}
RM_INLINE vec4 rm_vec4_set(const f32 x, const f32 y, const f32 z, const f32 w) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_set(x, y, z, w));
#else
    dest = rm_vec4(x, y, z, w);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_fill(const f32 x) {
    vec4 dest;

    dest = RM_VEC4_FILL(x);

    return dest;
}
RM_INLINE vec4 rm_vec4_make(const vec3 v, const f32 last) {
    vec4 dest;

    dest = rm_vec4(v.x, v.y, v.z, last);

    return dest;
}
RM_INLINE f32 rm_vec4_dot(const vec4 a, const vec4 b) {
#if RM_SIMD
    return rmm_hadd(rmm_mul(rmm_load(a.raw), rmm_load(b.raw)));
#else
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
#endif /* RM_SIMD */
}
RM_INLINE f32 rm_vec4_norm2(const vec4 v) {
    return rm_vec4_dot(v, v);
}
RM_INLINE f32 rm_vec4_norm(const vec4 v) {
    return rm_f32_sqrt(rm_vec4_norm2(v));
}
RM_INLINE f32 rm_vec4_norm_one(const vec4 v) {
    return rm_vec4_hadd(rm_vec4_abs(v));
}
RM_INLINE f32 rm_vec4_norm_inf(const vec4 v) {
    return rm_vec4_max(rm_vec4_abs(v));
}
RM_INLINE vec4 rm_vec4_add(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_add(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = a.x + b.x;
    dest.y = a.y + b.y;
    dest.z = a.z + b.z;
    dest.w = a.w + b.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_adds(const vec4 v, const f32 s) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_add(rmm_load(v.raw), rmm_set1(s)));
#else
    dest.x = v.x + s;
    dest.y = v.y + s;
    dest.z = v.z + s;
    dest.w = v.w + s;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_sub(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_sub(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = a.x - b.x;
    dest.y = a.y - b.y;
    dest.z = a.z - b.z;
    dest.w = a.w - b.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_subs(const vec4 v, const f32 s) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_sub(rmm_load(v.raw), rmm_set1(s)));
#else
    dest.x = v.x - s;
    dest.y = v.y - s;
    dest.z = v.z - s;
    dest.w = v.w - s;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_mul(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_mul(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = a.x * b.x;
    dest.y = a.y * b.y;
    dest.z = a.z * b.z;
    dest.w = a.w * b.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_scale(const vec4 v, const f32 s) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_mul(rmm_load(v.raw), rmm_set1(s)));
#else
    dest.x = v.x * s;
    dest.y = v.y * s;
    dest.z = v.z * s;
    dest.w = v.w * s;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_scale_as(const vec4 v, const f32 s) {
    f32 norm;

    norm = rm_vec4_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec4_zero() : rm_vec4_scale(v, s / norm);
}
RM_INLINE vec4 rm_vec4_scale_aniso(const vec4 v, const f32 x, const f32 y, const f32 z, const f32 w) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_mul(rmm_load(v.raw), rmm_set(x, y, z, w)));
#else
    dest.x = v.x * x;
    dest.y = v.y * y;
    dest.z = v.z * z;
    dest.w = v.w * w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_div(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_div(rmm_load(a.raw), rmm_load(b.raw)));
#else
    dest.x = a.x / b.x;
    dest.y = a.y / b.y;
    dest.z = a.z / b.z;
    dest.w = a.w / b.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_divs(const vec4 v, const f32 s) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_mul(rmm_load(v.raw), rmm_set1(1.0F / s)));
#else
    dest = rm_vec4_scale(v, 1.0F / s);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_negate(const vec4 v) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_neg(rmm_load(v.raw)));
#else
    dest.x = -v.x;
    dest.y = -v.y;
    dest.z = -v.z;
    dest.w = -v.w;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_normalize(const vec4 v) {
    f32 norm;

    norm = rm_vec4_norm(v);

    return (rm_f32_eq(norm, 0)) ? rm_vec4_zero() : rm_vec4_scale(v, 1.0F / norm);
}
RM_INLINE f32 rm_vec4_distance2(const vec4 a, const vec4 b) {
#if RM_SIMD
    RM_VEC x0;

    x0 = rmm_sub(rmm_load(a.raw), rmm_load(b.raw));

    return rmm_hadd(rmm_mul(x0, x0));
#else
    return rm_f32_pow2(a.x - b.x) + rm_f32_pow2(a.y - b.y) + rm_f32_pow2(a.z - b.z) + rm_f32_pow2(a.w - b.w);
#endif /* RM_SIMD */
}
RM_INLINE f32 rm_vec4_distance(const vec4 a, const vec4 b) {
    return rm_f32_sqrt(rm_vec4_distance2(a, b));
}
RM_INLINE vec4 rm_vec4_clamp(const vec4 v, const f32 min, const f32 max) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_min(rmm_max(rmm_load(v.raw), rmm_set1(min)), rmm_set1(max)));
#else
    dest.x = rm_f32_clamp(v.x, min, max);
    dest.y = rm_f32_clamp(v.y, min, max);
    dest.z = rm_f32_clamp(v.z, min, max);
    dest.w = rm_f32_clamp(v.w, min, max);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_wrap(const vec4 v, const f32 min, const f32 max) {
    vec4 dest;
#if RM_SIMD
    RM_VEC x0, x1;

    x0 = rmm_set1(min);
    x1 = rmm_set1(max - min);

    rmm_store(dest.raw, rmm_add(x0, rmm_fmod(rmm_add(x1, rmm_fmod(rmm_sub(rmm_load(v.raw), x0), x1)), x1)));
#else
    dest.x = rm_f32_wrap(v.x , min, max);
    dest.y = rm_f32_wrap(v.y , min, max);
    dest.z = rm_f32_wrap(v.z , min, max);
    dest.w = rm_f32_wrap(v.w , min, max);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_vec4_center(const vec4 a, const vec4 b) {
    vec4 dest;
#if RM_SIMD
    rmm_store(dest.raw, rmm_mul(rmm_add(rmm_load(a.raw), rmm_load(b.raw)), rmm_set1(0.5F)));
#else
    dest = rm_vec4_scale(rm_vec4_add(a, b), 0.5F);
#endif /* RM_SIMD */
    return dest;
}

RM_INLINE mat2 rm_mat2_copy(const mat2 m) {
    mat2 dest;
#if RM_SIMD
    rmm_store(dest.rawv, rmm_load(m.rawv));
#else
    dest.cols[0] = rm_vec2_copy(m.cols[0]);
    dest.cols[1] = rm_vec2_copy(m.cols[1]);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE mat2 rm_mat2_identity(void) {
    return RM_MAT2_IDENTITY;
}
RM_INLINE void rm_mat2_identity_array(mat2* m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat2_identity();
    }
}
RM_INLINE mat2 rm_mat2_zero(void) {
    mat2 dest;

    dest = RM_MAT2_FILL(0);

    return dest;
}
RM_INLINE mat2 rm_mat2_mul(const mat2 a, const mat2 b) {
    mat2 dest;
#if RM_SIMD
    RM_VEC x0, x1, x2;

    x0 = rmm_load(a.rawv);
    x1 = rmm_load(b.rawv);

    x2 = rmm_shuffle(x1, 0, 0, 2, 2);
    x1 = rmm_shuffle(x1, 1, 1, 3, 3);

    rmm_store(dest.rawv, rmm_fmadd(rmm_unpack_lo(x0, x0), x2, rmm_mul(rmm_unpack_hi(x0, x0), x1)));
#else
    dest.cols[0] = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[0].x), rm_vec2_scale(a.cols[1], b.cols[0].y));
    dest.cols[1] = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[1].x), rm_vec2_scale(a.cols[1], b.cols[1].y));
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec2 rm_mat2_mul_vec2(const mat2 m, const vec2 v) {
    return rm_vec2_add(rm_vec2_scale(m.cols[0], v.x), rm_vec2_scale(m.cols[1], v.y));
}
RM_INLINE mat2 rm_mat2_scale(const mat2 m, const f32 s) {
    mat2 dest;
#if RM_SIMD
    rmm_store(dest.rawv, rmm_mul(rmm_load(m.rawv), rmm_set1(s)));
#else
    dest.cols[0] = rm_vec2_scale(m.cols[0], s);
    dest.cols[1] = rm_vec2_scale(m.cols[1], s);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE mat2 rm_mat2_transpose(const mat2 m) {
    mat2 dest;
#if RM_SIMD
    rmm_store(dest.rawv, rmm_shuffle(rmm_load(m.rawv), 0, 2, 1, 3));
#else
    dest.cols[0].x = m.cols[0].x;
    dest.cols[0].y = m.cols[1].x;
    dest.cols[1].x = m.cols[0].y;
    dest.cols[1].y = m.cols[1].y;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE f32 rm_mat2_trace(const mat2 m) {
    return m.cols[0].x + m.cols[1].y;
}

RM_INLINE f32 rm_mat2_det(const mat2 m) {
    return m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x;
}
RM_INLINE mat2 rm_mat2_inv(const mat2 m) {
    f32 det;
    mat2 dest;

    det = 1.0 / (m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x);
#if RM_SIMD
    rmm_store(dest.rawv, rmm_mul(rmm_shuffle(rmm_load(m.rawv), 3, 1, 2, 0), rmm_set(det, -det, -det, det)));
#else
    dest.cols[0].x =  m.rawv[3] * det;
    dest.cols[0].y = -m.rawv[1] * det;

    dest.cols[1].x = -m.rawv[2] * det;
    dest.cols[1].y =  m.rawv[0] * det;
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE mat2 rm_mat2_swap_col(const mat2 m, const u32 col1, const u32 col2) {
    mat2 dest;

    dest = rm_mat2_copy(m);

    dest.cols[col1] = rm_vec2_copy(m.cols[col2]);
    dest.cols[col2] = rm_vec2_copy(m.cols[col1]);

    return dest;
}
RM_INLINE mat2 rm_mat2_swap_row(const mat2 m, const u32 row1, const u32 row2) {
    mat2 dest;

    dest = rm_mat2_copy(m);

    dest.raw[0][row1] = m.raw[0][row2];
    dest.raw[0][row2] = m.raw[0][row1];

    dest.raw[1][row1] = m.raw[1][row2];
    dest.raw[1][row2] = m.raw[1][row1];

    return dest;
}
RM_INLINE f32 rm_mat2_rmc(const vec2 r, const mat2 m, const vec2 c) {
    return rm_vec2_dot(r, rm_mat2_mul_vec2(m, c));
}

RM_INLINE mat3 rm_mat3_copy(const mat3 m) {
    mat3 dest;

    dest.cols[0] = rm_vec3_copy(m.cols[0]);
    dest.cols[1] = rm_vec3_copy(m.cols[1]);
    dest.cols[2] = rm_vec3_copy(m.cols[2]);

    return dest;
}
RM_INLINE mat3 rm_mat3_identity(void) {
    return RM_MAT3_IDENTITY;
}
RM_INLINE void rm_mat3_identity_array(mat3* m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat3_identity();
    }
}
RM_INLINE mat3 rm_mat3_zero(void) {
    mat3 dest;

    dest = RM_MAT3_FILL(0);

    return dest;
}
RM_INLINE mat3 rm_mat3_mul(const mat3 a, const mat3 b) {
    vec3 tmp;
    mat3 dest;

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[0].x), rm_vec3_scale(a.cols[1], b.cols[0].y));
    dest.cols[0] = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[0].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[1].x), rm_vec3_scale(a.cols[1], b.cols[1].y));
    dest.cols[1] = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[1].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[2].x), rm_vec3_scale(a.cols[1], b.cols[2].y));
    dest.cols[2] = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[2].z));

    return dest;
}
RM_INLINE vec3 rm_mat3_mul_vec3(const mat3 m, const vec3 v) {
    vec3 tmp;
    tmp = rm_vec3_add(rm_vec3_scale(m.cols[0], v.x), rm_vec3_scale(m.cols[1], v.y));

    return rm_vec3_add(tmp, rm_vec3_scale(m.cols[2], v.z));
}
RM_INLINE mat3 rm_mat3_scale(const mat3 m, const f32 s) {
    mat3 dest;

    dest.cols[0] = rm_vec3_scale(m.cols[0], s);
    dest.cols[1] = rm_vec3_scale(m.cols[1], s);
    dest.cols[2] = rm_vec3_scale(m.cols[2], s);

    return dest;
}
RM_INLINE mat3 rm_mat3_transpose(const mat3 m) {
    mat3 dest;

    dest.cols[0].x = m.cols[0].x;
    dest.cols[0].y = m.cols[1].x;
    dest.cols[0].z = m.cols[2].x;

    dest.cols[1].x = m.cols[0].y;
    dest.cols[1].y = m.cols[1].y;
    dest.cols[1].z = m.cols[2].y;

    dest.cols[2].x = m.cols[0].z;
    dest.cols[2].y = m.cols[1].z;
    dest.cols[2].z = m.cols[2].z;

    return dest;
}
RM_INLINE f32 rm_mat3_trace(const mat3 m) {
    return m.cols[0].x + m.cols[1].y + m.cols[2].z;
}

RM_INLINE f32 rm_mat3_det(const mat3 m) {
    vec3 tmp;

    tmp.x = m.cols[0].x * (m.cols[1].y * m.cols[2].z - m.cols[2].y * m.cols[1].z);
    tmp.y = -(m.cols[1].x * (m.cols[0].y * m.cols[2].z - m.cols[2].y * m.cols[0].z));
    tmp.z = m.cols[2].x * (m.cols[0].y * m.cols[1].z - m.cols[1].y * m.cols[0].z);

    return rm_vec3_hadd(tmp);
}
RM_INLINE mat3 rm_mat3_inv(const mat3 m) {
    f32 det;
    vec3 tmp;
    mat3 dest;

    dest.cols[0].x = m.cols[1].y * m.cols[2].z - m.cols[2].y * m.cols[1].z;
    dest.cols[0].y = -(m.cols[0].y * m.cols[2].z - m.cols[2].y * m.cols[0].z);
    dest.cols[0].z = m.cols[0].y * m.cols[1].z - m.cols[1].y * m.cols[0].z;

    dest.cols[1].x = -(m.cols[1].x * m.cols[2].z - m.cols[2].x * m.cols[1].z);
    dest.cols[1].y = m.cols[0].x * m.cols[2].z - m.cols[2].x * m.cols[0].z;
    dest.cols[1].z = -(m.cols[0].x * m.cols[1].z - m.cols[1].x * m.cols[0].z);

    dest.cols[2].x = m.cols[1].x * m.cols[2].y - m.cols[2].x * m.cols[1].y;
    dest.cols[2].y = -(m.cols[0].x * m.cols[2].y - m.cols[2].x * m.cols[0].y);
    dest.cols[2].z = m.cols[0].x * m.cols[1].y - m.cols[1].x * m.cols[0].y;

    tmp = rm_vec3_scale_aniso(m.cols[0], dest.cols[0].x, dest.cols[1].x, dest.cols[2].x);

    det = 1.0F / rm_vec3_hadd(tmp);

    return rm_mat3_scale(dest, det);
}
RM_INLINE mat3 rm_mat3_swap_col(const mat3 m, const u32 col1, const u32 col2) {
    mat3 dest;

    dest = rm_mat3_copy(m);

    dest.cols[col1] = rm_vec3_copy(m.cols[col2]);
    dest.cols[col2] = rm_vec3_copy(m.cols[col1]);

    return dest;
}
RM_INLINE mat3 rm_mat3_swap_row(const mat3 m, const u32 row1, const u32 row2) {
    mat3 dest;

    dest = rm_mat3_copy(m);

    dest.raw[0][row1] = m.raw[0][row2];
    dest.raw[1][row1] = m.raw[1][row2];
    dest.raw[2][row1] = m.raw[2][row2];

    dest.raw[0][row2] = m.raw[0][row1];
    dest.raw[1][row2] = m.raw[1][row1];
    dest.raw[2][row2] = m.raw[2][row1];

    return dest;
}
RM_INLINE f32 rm_mat3_rmc(const vec3 r, const mat3 m, const vec3 c) {
    return rm_vec3_dot(r, rm_mat3_mul_vec3(m, c));
}

RM_INLINE mat4 rm_mat4_copy(const mat4 m) {
    mat4 dest;
#if RM_SIMD
    rmm_store(dest.raw[0], rmm_load(m.raw[0]));
    rmm_store(dest.raw[1], rmm_load(m.raw[1]));
    rmm_store(dest.raw[2], rmm_load(m.raw[2]));
    rmm_store(dest.raw[3], rmm_load(m.raw[3]));
#else
    dest.cols[0] = rm_vec4_copy(m.cols[0]);
    dest.cols[1] = rm_vec4_copy(m.cols[1]);
    dest.cols[2] = rm_vec4_copy(m.cols[2]);
    dest.cols[3] = rm_vec4_copy(m.cols[3]);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE mat4 rm_mat4_identity(void) {
    return RM_MAT4_IDENTITY;
}
RM_INLINE void rm_mat4_identity_array(mat4* m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat4_identity();
    }
}
RM_INLINE mat4 rm_mat4_zero(void) {
    mat4 dest;

    dest = RM_MAT4_FILL(0);

    return dest;
}
RM_INLINE mat3 rm_mat4_pick3(const mat4 m) {
    mat3 dest;

    dest.cols[0] = rm_vec4_copy3(m.cols[0]);
    dest.cols[1] = rm_vec4_copy3(m.cols[1]);
    dest.cols[2] = rm_vec4_copy3(m.cols[2]);

    return dest;
}
RM_INLINE mat3 rm_mat4_pick3t(const mat4 m) {
    mat3 dest;

    dest.cols[0].x = m.cols[0].x;
    dest.cols[0].y = m.cols[1].x;
    dest.cols[0].z = m.cols[2].x;

    dest.cols[1].x = m.cols[0].y;
    dest.cols[1].y = m.cols[1].y;
    dest.cols[1].z = m.cols[2].y;

    dest.cols[2].x = m.cols[0].z;
    dest.cols[2].y = m.cols[1].z;
    dest.cols[2].z = m.cols[2].z;

    return dest;
}
RM_INLINE void rm_mat4_insert_mat3(const mat3 a, mat4 b) {
    b.cols[0] = rm_vec4_make(a.cols[0], b.cols[0].w);
    b.cols[1] = rm_vec4_make(a.cols[1], b.cols[1].w);
    b.cols[2] = rm_vec4_make(a.cols[2], b.cols[2].w);
}
RM_INLINE mat4 rm_mat4_mul(const mat4 a, const mat4 b) {
    mat4 dest;
#if RM_SIMD
    RM_VEC x0, x1, x2, x3, x4, x5;

    x0 = rmm_load(a.raw[0]);
    x1 = rmm_load(a.raw[1]);
    x2 = rmm_load(a.raw[2]);
    x3 = rmm_load(a.raw[3]);

    x4 = rmm_add(rmm_mul(x0, rmm_set1(b.cols[0].x)), rmm_mul(x1, rmm_set1(b.cols[0].y)));
    x5 = rmm_add(rmm_mul(x2, rmm_set1(b.cols[0].z)), rmm_mul(x3, rmm_set1(b.cols[0].w)));
    rmm_store(dest.raw[0], rmm_add(x4, x5));

    x4 = rmm_add(rmm_mul(x0, rmm_set1(b.cols[1].x)), rmm_mul(x1, rmm_set1(b.cols[1].y)));
    x5 = rmm_add(rmm_mul(x2, rmm_set1(b.cols[1].z)), rmm_mul(x3, rmm_set1(b.cols[1].w)));
    rmm_store(dest.raw[1], rmm_add(x4, x5));

    x4 = rmm_add(rmm_mul(x0, rmm_set1(b.cols[2].x)), rmm_mul(x1, rmm_set1(b.cols[2].y)));
    x5 = rmm_add(rmm_mul(x2, rmm_set1(b.cols[2].z)), rmm_mul(x3, rmm_set1(b.cols[2].w)));
    rmm_store(dest.raw[2], rmm_add(x4, x5));

    x4 = rmm_add(rmm_mul(x0, rmm_set1(b.cols[3].x)), rmm_mul(x1, rmm_set1(b.cols[3].y)));
    x5 = rmm_add(rmm_mul(x2, rmm_set1(b.cols[3].z)), rmm_mul(x3, rmm_set1(b.cols[3].w)));
    rmm_store(dest.raw[3], rmm_add(x4, x5));
#else
    vec4 tmp1, tmp2;

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[0].x), rm_vec4_scale(a.cols[1], b.cols[0].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[0].z), rm_vec4_scale(a.cols[3], b.cols[0].w));
    dest.cols[0] = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[1].x), rm_vec4_scale(a.cols[1], b.cols[1].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[1].z), rm_vec4_scale(a.cols[3], b.cols[1].w));
    dest.cols[1] = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[2].x), rm_vec4_scale(a.cols[1], b.cols[2].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[2].z), rm_vec4_scale(a.cols[3], b.cols[2].w));
    dest.cols[2] = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[3].x), rm_vec4_scale(a.cols[1], b.cols[3].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[3].z), rm_vec4_scale(a.cols[3], b.cols[3].w));
    dest.cols[3] = rm_vec4_add(tmp1, tmp2);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_mat4_mul_vec4(const mat4 m, const vec4 v) {
    vec4 dest;
#if RM_SIMD
    RM_VEC x0, x1;

    x0 = rmm_add(rmm_mul(rmm_load(m.raw[0]), rmm_set1(v.x)), rmm_mul(rmm_load(m.raw[1]), rmm_set1(v.y)));
    x1 = rmm_add(rmm_mul(rmm_load(m.raw[2]), rmm_set1(v.z)), rmm_mul(rmm_load(m.raw[3]), rmm_set1(v.w)));

    rmm_store(dest.raw, rmm_add(x0, x1));
#else
    vec4 tmp1, tmp2;

    tmp1 = rm_vec4_add(rm_vec4_scale(m.cols[0], v.x), rm_vec4_scale(m.cols[1], v.y));
    tmp2 = rm_vec4_add(rm_vec4_scale(m.cols[2], v.z), rm_vec4_scale(m.cols[3], v.w));

    dest = rm_vec4_add(tmp1, tmp2);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec3 rm_mat4_mul_vec3(const mat4 m, const vec3 v, const f32 last) {
    return rm_vec4_copy3(rm_mat4_mul_vec4(m, rm_vec4_make(v, last)));
}
RM_INLINE mat4 rm_mat4_scale(const mat4 m, const f32 s) {
    mat4 dest;
#if RM_SIMD
    RM_VEC x0;

    x0 = rmm_set1(s);

    rmm_store(dest.raw[0], rmm_mul(rmm_load(m.raw[0]), x0));
    rmm_store(dest.raw[1], rmm_mul(rmm_load(m.raw[1]), x0));
    rmm_store(dest.raw[2], rmm_mul(rmm_load(m.raw[2]), x0));
    rmm_store(dest.raw[3], rmm_mul(rmm_load(m.raw[3]), x0));
#else
    dest.cols[0] = rm_vec4_scale(m.cols[0], s);
    dest.cols[1] = rm_vec4_scale(m.cols[1], s);
    dest.cols[2] = rm_vec4_scale(m.cols[2], s);
    dest.cols[3] = rm_vec4_scale(m.cols[3], s);
#endif /* RM_SIMD */
    return dest;
}
RM_INLINE mat4 rm_mat4_scale_aniso(const mat4 m, const f32 x, const f32 y, const f32 z) {
    mat4 dest;
#if RM_SIMD
    rmm_store(dest.raw[0], rmm_mul(rmm_load(m.raw[0]), rmm_set1(x)));
    rmm_store(dest.raw[1], rmm_mul(rmm_load(m.raw[1]), rmm_set1(y)));
    rmm_store(dest.raw[2], rmm_mul(rmm_load(m.raw[2]), rmm_set1(z)));
    rmm_store(dest.raw[3], rmm_load(m.raw[3]));
#else
    dest.cols[0] = rm_vec4_scale(m.cols[0], x);
    dest.cols[1] = rm_vec4_scale(m.cols[1], y);
    dest.cols[2] = rm_vec4_scale(m.cols[2], z);
    dest.cols[3] = rm_vec4_copy(m.cols[3]);
#endif /* RM_SIMD */
    return dest;
}

RM_INLINE mat4 rm_mat4_transpose(const mat4 m) {
    mat4 dest;

    dest.cols[0].x = m.cols[0].x;
    dest.cols[0].y = m.cols[1].x;
    dest.cols[0].z = m.cols[2].x;
    dest.cols[0].w = m.cols[3].x;

    dest.cols[1].x = m.cols[0].y;
    dest.cols[1].y = m.cols[1].y;
    dest.cols[1].z = m.cols[2].y;
    dest.cols[1].w = m.cols[3].y;

    dest.cols[2].x = m.cols[0].z;
    dest.cols[2].y = m.cols[1].z;
    dest.cols[2].z = m.cols[2].z;
    dest.cols[2].w = m.cols[3].z;

    dest.cols[3].x = m.cols[0].w;
    dest.cols[3].y = m.cols[1].w;
    dest.cols[3].z = m.cols[2].w;
    dest.cols[3].w = m.cols[3].w;

    return dest;
}
RM_INLINE mat4 rm_mat4_translate(const f32 x, const f32 y, const f32 z) {
    mat4 dest;

    dest = rm_mat4_identity();
    dest.cols[3] = rm_vec4_set(x, y, z, dest.cols[3].w);

    return dest;
}
RM_INLINE mat4 rm_mat4_translate_vec3(const vec3 v) {
    mat4 dest;

    dest = rm_mat4_identity();
    dest.cols[3] = rm_vec4_make(v, dest.cols[3].w);

    return dest;
}
RM_INLINE f32 rm_mat4_trace(const mat4 m) {
    return m.raw[0][0] + m.raw[1][1] + m.raw[2][2] + m.raw[3][3];
}
RM_INLINE f32 rm_mat4_trace3(const mat4 m) {
    return m.raw[0][0] + m.raw[1][1] + m.raw[2][2];
}
RM_INLINE f32 rm_mat4_det(const mat4 m) {
    f32 t[6];
    vec4 v;

    t[0] = m.cols[2].z * m.cols[3].w - m.cols[3].z * m.cols[2].w;
    t[1] = m.cols[2].y * m.cols[3].w - m.cols[3].y * m.cols[2].w;
    t[2] = m.cols[2].y * m.cols[3].z - m.cols[3].y * m.cols[2].z;
    t[3] = m.cols[2].x * m.cols[3].w - m.cols[3].x * m.cols[2].w;
    t[4] = m.cols[2].x * m.cols[3].z - m.cols[3].x * m.cols[2].z;
    t[5] = m.cols[2].x * m.cols[3].y - m.cols[3].x * m.cols[2].y;

    v.x = m.cols[0].x * (m.cols[1].y * t[0] - m.cols[1].z * t[1] + m.cols[1].w * t[2]);
    v.y = -(m.cols[0].y * (m.cols[1].x * t[0] - m.cols[1].z * t[3] + m.cols[1].w * t[4]));
    v.z = m.cols[0].z * (m.cols[1].x * t[1] - m.cols[1].y * t[3] + m.cols[1].w * t[5]);
    v.w = -(m.cols[0].w * (m.cols[1].x * t[2] - m.cols[1].y * t[4] + m.cols[1].z * t[5]));

    return rm_vec4_hadd(v);
}
RM_INLINE mat4 rm_mat4_inv(const mat4 m) {
    f32 det, q[6];
    vec4 m0, m1, m2, m3, v;
    mat4 dest;

    m0 = rm_vec4_copy(m.cols[0]);
    m1 = rm_vec4_copy(m.cols[1]);
    m2 = rm_vec4_copy(m.cols[2]);
    m3 = rm_vec4_copy(m.cols[3]);

    q[0] = m2.z * m3.w - m3.z * m2.w;
    q[1] = m2.y * m3.w - m3.y * m2.w;
    q[2] = m2.y * m3.z - m3.y * m2.z;
    q[3] = m2.x * m3.w - m3.x * m2.w;
    q[4] = m2.x * m3.z - m3.x * m2.z;
    q[5] = m2.x * m3.y - m3.x * m2.y;

    dest.cols[0].x = m1.y * q[0] - m1.z * q[1] + m1.w * q[2];
    dest.cols[1].x = -(m1.x * q[0] - m1.z * q[3] + m1.w * q[4]);
    dest.cols[2].x = m1.x * q[1] - m1.y * q[3] + m1.w * q[5];
    dest.cols[3].x = -(m1.x * q[2] - m1.y * q[4] + m1.z * q[5]);

    dest.cols[0].y = -(m0.y * q[0] - m0.z * q[1] + m0.w * q[2]);
    dest.cols[1].y = m0.x * q[0] - m0.z * q[3] + m0.w * q[4];
    dest.cols[2].y = -(m0.x * q[1] - m0.y * q[3] + m0.w * q[5]);
    dest.cols[3].y = m0.x * q[2] - m0.y * q[4] + m0.z * q[5];

    q[0] = m1.z * m3.w - m3.z * m1.w;
    q[1] = m1.y * m3.w - m3.y * m1.w;
    q[2] = m1.y * m3.z - m3.y * m1.z;
    q[3] = m1.x * m3.w - m3.x * m1.w;
    q[4] = m1.x * m3.z - m3.x * m1.z;
    q[5] = m1.x * m3.y - m3.x * m1.y;

    dest.cols[0].z = m0.y * q[0] - m0.z * q[1] + m0.w * q[2];
    dest.cols[1].z = -(m0.x * q[0] - m0.z * q[3] + m0.w * q[4]);
    dest.cols[2].z = m0.x * q[1] - m0.y * q[3] + m0.w * q[5];
    dest.cols[3].z = -(m0.x * q[2] - m0.y * q[4] + m0.z * q[5]);

    q[0] = m1.z * m2.w - m1.w * m2.z;
    q[1] = m1.y * m2.w - m1.w * m2.y;
    q[2] = m1.y * m2.z - m1.z * m2.y;
    q[3] = m1.x * m2.w - m1.w * m2.x;
    q[4] = m1.x * m2.z - m1.z * m2.x;
    q[5] = m1.x * m2.y - m1.y * m2.x;

    dest.cols[0].w = -(m0.y * q[0] - m0.z * q[1] + m0.w * q[2]);
    dest.cols[1].w = m0.x * q[0] - m0.z * q[3] + m0.w * q[4];
    dest.cols[2].w = -(m0.x * q[1] - m0.y * q[3] + m0.w * q[5]);
    dest.cols[3].w = m0.x * q[2] - m0.y * q[4] + m0.z * q[5];

    v = rm_vec4_scale_aniso(m.cols[0], dest.cols[0].x, dest.cols[1].x, dest.cols[2].x, dest.cols[3].x);

    det = 1.0F / rm_vec4_hadd(v);

    return rm_mat4_scale(dest, det);
}
RM_INLINE mat4 rm_mat4_swap_col(const mat4 m, const u32 col1, const u32 col2) {
    mat4 dest;

    dest = rm_mat4_copy(m);

    dest.cols[col1] = rm_vec4_copy(m.cols[col2]);
    dest.cols[col2] = rm_vec4_copy(m.cols[col1]);

    return dest;
}
RM_INLINE mat4 rm_mat4_swap_row(const mat4 m, const u32 row1, const u32 row2) {
    mat4 dest;

    dest = rm_mat4_copy(m);

    dest.raw[0][row1] = m.raw[0][row2];
    dest.raw[1][row1] = m.raw[1][row2];
    dest.raw[2][row1] = m.raw[2][row2];
    dest.raw[3][row1] = m.raw[3][row2];

    dest.raw[0][row2] = m.raw[0][row1];
    dest.raw[1][row2] = m.raw[1][row1];
    dest.raw[2][row2] = m.raw[2][row1];
    dest.raw[3][row2] = m.raw[3][row1];

    return dest;
}
RM_INLINE f32 rm_mat4_rmc(const vec4 r, const mat4 m, const vec4 c) {
    return rm_vec4_dot(r, rm_mat4_mul_vec4(m, c));
}
RM_INLINE mat4 rm_mat4_ortho(const f32 l, const f32 r, const f32 b, const f32 t, const f32 n, const f32 f) {
    f32 rl, tb, fn;
    mat4 dest;

    rl = 1 / (r - l);
    tb = 1 / (t - b);
    fn = 1 / (f - n);

    dest.cols[0]   = rm_vec4_zero();
    dest.cols[0].x = 2 * rl;

    dest.cols[1]   = rm_vec4_zero();
    dest.cols[1].y = 2 * tb;

    dest.cols[2]   = rm_vec4_zero();
    dest.cols[2].z = -2 * fn;

    dest.cols[3].x = -(r + l) * rl;
    dest.cols[3].y = -(t + b) * tb;
    dest.cols[3].z = -(f + n) * fn;
    dest.cols[3].w = 1;

    return dest;
}
RM_INLINE mat4 rm_mat4_frustum(const f32 l, const f32 r, const f32 b, const f32 t, const f32 n, const f32 f) {
    f32 rl, tb, fn, nv;
    mat4 dest;

    rl = 1 / (r - l);
    tb = 1 / (t - b);
    fn = 1 / (f - n);
    nv = 2 * n;

    dest.cols[0]   = rm_vec4_zero();
    dest.cols[0].x = nv * rl;

    dest.cols[1]   = rm_vec4_zero();
    dest.cols[1].y = nv * tb;

    dest.cols[2].x = (r + l) * rl;
    dest.cols[2].y = (t + b) * tb;
    dest.cols[2].z = -(f + n) * fn;
    dest.cols[2].w = -1;

    dest.cols[3]   = rm_vec4_zero();
    dest.cols[3].z = -f * nv * fn;

    return dest;
}
RM_INLINE mat4 rm_mat4_perspective(const f32 fov, const f32 aspect, const f32 n, const f32 f) {
    f32 fv, fn;
    mat4 dest;

    fv = 1 / rm_f32_tan(fov * 0.5F);
    fn = 1 / (n - f);

    dest.cols[0]   = rm_vec4_zero();
    dest.cols[0].x = fv / aspect;

    dest.cols[1]   = rm_vec4_zero();
    dest.cols[1].y = fv;

    dest.cols[2]   = rm_vec4_zero();
    dest.cols[2].z = (n + f) * fn;
    dest.cols[2].w = -1;

    dest.cols[3]   = rm_vec4_zero();
    dest.cols[3].z = 2 * n * f * fn;

    return dest;
}

#ifdef __cplusplus
//}
#endif /* __cplusplus */
#endif /* RANMATH_IMPLEMENTATION */
