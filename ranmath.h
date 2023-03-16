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
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
#include <stddef.h>

#if !defined(__bool_true_false_are_defined)
#define bool _Bool
#define true 1
#define false 0

#define __bool_true_false_are_defined 1
#endif /* Check if user has included stdbool.h */

#define RM_CC 0
#define RM_CL 1

#ifndef RM_SSE_ENABLE
#if defined(__SSE2__) || defined(_M_X64) || defined(_M_AMD64) || defined(_M_IX86_FP)
#define RM_SSE_ENABLE 1
#define RM_VEC __m128
#else
#define RM_SSE_ENABLE 0
#endif /* Check for sse2 intrinsics*/
#endif /* Check if already defined */

#ifndef RM_NEON_ENABLE
#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#define RM_NEON_ENABLE 1
#define RM_VEC float32x4_t
#else
#define RM_NEON_ENABLE 0
#endif /* Check for neon intrinsics */
#endif /* Check if already defined */

#if RM_SSE_ENABLE || RM_NEON_ENABLE
#define RM_SIMD 1
#else
#define RM_SIMD 0
#endif /* Check for simd */

#if defined(__GNUC__) || defined(__clang__) || defined(__PCC__)
/* GCC-compatible compiler (gcc, clang) */
#define RM_COMPILER RM_CC
#define RM_INLINE   static inline __attribute__((always_inline))
#define RM_ALIGN(x) __attribute__((aligned(x)))
#elif defined(_MSC_VER)
/* Microsoft cl */
#define RM_COMPILER RM_CL
#define RM_INLINE   static inline __forceinline
#define RM_ALIGN(x) __declspec(align(x))
#else
/* Unknown */
#define RM_COMPILER RM_CC /* Temporary, might change */
#define RM_INLINE   static inline
#define RM_ALIGN(x)
#endif /* Check compiler for alignment of vectors */

/* ---------------- TYPES ---------------- */
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

typedef union  RM_ALIGN(4) f32_cvt f32_cvt;
typedef union  RM_ALIGN(8) f64_cvt f64_cvt;

typedef struct RM_ALIGN(4) vec2 vec2;
typedef struct RM_ALIGN(4) vec3 vec3;
typedef struct RM_ALIGN(4) vec4 vec4;
typedef union  RM_ALIGN(4) vec2_cvt vec2_cvt;
typedef union  RM_ALIGN(4) vec3_cvt vec3_cvt;
typedef union  RM_ALIGN(4) vec4_cvt vec4_cvt;

typedef union RM_ALIGN(16) mat2 mat2;
typedef union RM_ALIGN(16) mat3 mat3;
typedef union RM_ALIGN(16) mat4 mat4;

union RM_ALIGN(4) f32_cvt {
    f32 f;
    i32 i;
    u32 u;
};
union RM_ALIGN(8) f64_cvt {
    f64 f;
    i64 i;
    u64 u;
};
struct RM_ALIGN(4) vec2 {
    f32 x;
    f32 y;
};
struct RM_ALIGN(4) vec3 {
    f32 x;
    f32 y;
    f32 z;
};
struct RM_ALIGN(4) vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};
union RM_ALIGN(16) mat2 {
    vec2 RM_ALIGN(16) cols[2];
    vec4 RM_ALIGN(16) v;
    f32  RM_ALIGN(16) raw[2][2];
    f32  RM_ALIGN(16) rawv[4];
};
union RM_ALIGN(16) mat3 {
    vec3 RM_ALIGN(16) cols[3];
    f32  RM_ALIGN(16) raw[3][3];
};
union RM_ALIGN(16) mat4 {
    vec4 RM_ALIGN(16) cols[4];
    f32  RM_ALIGN(16) raw[4][4];
};
union RM_ALIGN(4) vec2_cvt {
    vec2 RM_ALIGN(4) v;
    f32  RM_ALIGN(4) raw[2];
};
union RM_ALIGN(4) vec3_cvt {
    vec3 RM_ALIGN(4) v;
    f32  RM_ALIGN(4) raw[3];
};
union RM_ALIGN(4) vec4_cvt {
    vec4 RM_ALIGN(4) v;
    mat2 RM_ALIGN(4) m;
    f32  RM_ALIGN(4) raw[4];
};

/* ---------------- CONSTANTS ---------------- */
#define RM_E           2.7182818284590452353602874713526624977572470936999595749669676277
#define RM_E_F         (f32)RM_E
#define RM_LOG2E       1.4426950408889634073599246810018921374266459541529859341354494069
#define RM_LOG2E_F     (f32)RM_LOG2E
#define RM_LOG10E      0.4342944819032518276511289189166050822943970058036665661144537831
#define RM_LOG10E_F    (f32)RM_LOG10E
#define RM_LN2         0.6931471805599453094172321214581765680755001343602552541206800094
#define RM_LN2_F       (f32)RM_LN2
#define RM_LN10        2.3025850929940456840179914546843642076011014886287729760333279009
#define RM_LN10_F      (f32)RM_LN10
#define RM_PI          3.1415926535897932384626433832795028841971693993751058209749445923
#define RM_PI_F        (f32)RM_PI
#define RM_PI_2        1.5707963267948966192313216916397514420985846996875529104874722961
#define RM_PI_2_F      (f32)RM_PI_2
#define RM_2PI         6.2831853071795864769252867665590057683943387987502116419498891846
#define RM_2PI_F       (f32)RM_2PI
#define RM_PI2         9.8696044010893586188344909998761511353136994072407906264133493762
#define RM_PI2_F       (f32)RM_PI2
#define RM_PI3         31.006276680299820175476315067101395202225288565885107694144538103
#define RM_PI3_F       (f32)RM_PI3
#define RM_PI4         97.409091034002437236440332688705111249727585672685421691467859389
#define RM_PI4_F       (f32)RM_PI4
#define RM_1_PI        0.3183098861837906715377675267450287240689192914809128974953346881
#define RM_1_PI_F      (f32)RM_1_PI
#define RM_1_2PI       0.1591549430918953357688837633725143620344596457404564487476673440
#define RM_1_2PI_F     (f32)RM_1_2PI
#define RM_SQRTPI      1.7724538509055160272981674833411451827975494561223871282138077898
#define RM_SQRTPI_F    (f32)RM_SQRTPI
#define RM_1_SQRTPI    0.5641895835477562869480794515607725858440506293289988568440857217
#define RM_1_SQRTPI_F  (f32)RM_1_SQRTPI
#define RM_2_SQRTPI    1.1283791670955125738961589031215451716881012586579977136881714434
#define RM_2_SQRTPI_F  (f32)RM_2_SQRTPI
#define RM_SQRT2       1.4142135623730950488016887242096980785696718753769480731766797379
#define RM_SQRT2_F     (f32)RM_SQRT2
#define RM_1_SQRT2     0.7071067811865475244008443621048490392848359376884740365883398689
#define RM_1_SQRT2_F   (f32)RM_1_SQRT2
#define RM_MAKE_DEG    57.295779513082320876798154814105170332405472466564321549160243861
#define RM_MAKE_DEG_F  (f32)RM_MAKE_DEG
#define RM_MAKE_RAD    0.0174532925199432957692369076848861271344287188854172545609719144
#define RM_MAKE_RAD_F  (f32)RM_MAKE_RAD
#define RM_FLT_EPSILON 1.19210000093517010100185871124267578125E-7
#define RM_DBL_EPSILON 2.220446049250313080847263336181640625000000000000E-16
#define RM_NAN         (f64_cvt){.u = 0x7FFFFFFFFFFFFFFF}.f
#define RM_NAN_F       (f32_cvt){.u = 0x7FFFFFFF}.f
#define RM_INF         (f64_cvt){.u = 0x7FF0000000000000}.f
#define RM_INF_F       (f32_cvt){.u = 0x7F800000}.f

/* ----------------- METHODS ----------------- */
RM_INLINE bool rm_eqf(const f32, const f32);
RM_INLINE bool rm_eqd(const f64, const f64);
RM_INLINE bool rm_eq_epsf(const f32, const f32);
RM_INLINE bool rm_eq_epsd(const f64, const f64);
RM_INLINE i32 rm_facti(const i32);
RM_INLINE i64 rm_factl(const i64);
RM_INLINE i32 rm_powi(const i32, const i32);
RM_INLINE i64 rm_powl(const i64, const i64);
RM_INLINE i32 rm_pow2i(const i32);
RM_INLINE i64 rm_pow2l(const i64);
RM_INLINE f32 rm_pow2f(const f32);
RM_INLINE f64 rm_pow2d(const f64);
RM_INLINE f32 rm_rsqrtf(const f32);
RM_INLINE f64 rm_rsqrtd(const f64);
RM_INLINE f32 rm_sqrtf(const f32);
RM_INLINE f64 rm_sqrtd(const f64);
RM_INLINE i32 rm_absi(const i32);
RM_INLINE i64 rm_absl(const i64);
RM_INLINE f32 rm_absf(const f32);
RM_INLINE f64 rm_absd(const f64);
RM_INLINE i32 rm_mini(const i32, const i32);
RM_INLINE i64 rm_minl(const i64, const i64);
RM_INLINE f32 rm_minf(const f32, const f32);
RM_INLINE f64 rm_mind(const f64, const f64);
RM_INLINE i32 rm_mini(const i32, const i32);
RM_INLINE i64 rm_minl(const i64, const i64);
RM_INLINE f32 rm_maxf(const f32, const f32);
RM_INLINE f64 rm_maxd(const f64, const f64);
RM_INLINE i32 rm_clampi(const i32, const i32, const i32);
RM_INLINE i64 rm_clampl(const i64, const i64, const i64);
RM_INLINE f32 rm_clampf(const f32, const f32, const f32);
RM_INLINE f64 rm_clampd(const f64, const f64, const f64);
RM_INLINE f32 rm_truncf(const f32);
RM_INLINE f64 rm_truncd(const f64);
RM_INLINE f32 rm_floorf(const f32);
RM_INLINE f64 rm_floord(const f64);
RM_INLINE f32 rm_ceilf(const f32);
RM_INLINE f64 rm_ceild(const f64);
RM_INLINE f32 rm_roundf(const f32);
RM_INLINE f64 rm_roundd(const f64);
RM_INLINE f32 rm_wrap_maxf(const f32, const f32);
RM_INLINE f64 rm_wrap_maxd(const f64, const f64);
RM_INLINE f32 rm_wrapf(const f32, const f32, const f32);
RM_INLINE f64 rm_wrapd(const f64, const f64, const f64);
RM_INLINE f32 rm_cosf(const f32);
RM_INLINE f64 rm_cosd(const f64);
RM_INLINE f32 rm_sinf(const f32);
RM_INLINE f64 rm_sind(const f64);
RM_INLINE f32 rm_tanf(const f32);
RM_INLINE f64 rm_tand(const f64);
RM_INLINE f32 rm_cotf(const f32);
RM_INLINE f64 rm_cotd(const f64);
RM_INLINE f32 rm_secf(const f32);
RM_INLINE f64 rm_secd(const f64);
RM_INLINE f32 rm_cscf(const f32);
RM_INLINE f64 rm_cscd(const f64);
/* OBS!! inverse trig functions are not implemented yet */
RM_INLINE f32 rm_acosf(const f32);
RM_INLINE f64 rm_acosd(const f64);
RM_INLINE f32 rm_asinf(const f32);
RM_INLINE f64 rm_asind(const f64);
RM_INLINE f32 rm_atanf(const f32);
RM_INLINE f64 rm_atand(const f64);
RM_INLINE f32 rm_rad2degf(const f32);
RM_INLINE f64 rm_rad2degd(const f64);
RM_INLINE f32 rm_deg2radf(const f32);
RM_INLINE f64 rm_deg2radd(const f64);

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
RM_INLINE mat2 rm_mat2_transpose(const mat2);
RM_INLINE vec2 rm_mat2_mulv(const mat2, const vec2);
RM_INLINE f32  rm_mat2_trace(const mat2);
RM_INLINE mat2 rm_mat2_scale(const mat2, const f32);
RM_INLINE f32  rm_mat2_det(const mat2);
RM_INLINE mat2 rm_mat2_inv(const mat2);
RM_INLINE void rm_mat2_swap_col(mat2, const u32, const u32);
RM_INLINE void rm_mat2_swap_row(mat2, const u32, const u32);
RM_INLINE f32  rm_mat2_rmc(const vec2, const mat2, const vec2);

RM_INLINE mat3 rm_mat3_copy(const mat3);
RM_INLINE mat3 rm_mat3_identity(void);
RM_INLINE void rm_mat3_identity_array(mat3*, const usize);
RM_INLINE mat3 rm_mat3_zero(void);
RM_INLINE mat3 rm_mat3_mul(const mat3, const mat3);
RM_INLINE mat3 rm_mat3_transpose(const mat3);
RM_INLINE vec3 rm_mat3_mulv(const mat3, const vec3);
RM_INLINE f32  rm_mat3_trace(const mat3);
RM_INLINE mat3 rm_mat3_scale(const mat3, const f32);
RM_INLINE f32  rm_mat3_det(const mat3);
RM_INLINE mat3 rm_mat3_inv(const mat3);
RM_INLINE void rm_mat3_swap_col(mat3, const u32, const u32);
RM_INLINE void rm_mat3_swap_row(mat3, const u32, const u32);
RM_INLINE f32  rm_mat3_rmc(const vec3, const mat3, const vec3);

RM_INLINE mat4 rm_mat4_copy(const mat4);
RM_INLINE mat4 rm_mat4_identity(void);
RM_INLINE void rm_mat4_identity_array(mat4*, const usize);
RM_INLINE mat4 rm_mat4_zero(void);
RM_INLINE mat3 rm_mat4_pick3(const mat4);
RM_INLINE mat3 rm_mat4_pick3t(const mat4);
RM_INLINE void rm_mat4_ins3(const mat3, const mat4);
RM_INLINE mat4 rm_mat4_mul(const mat4, const mat4);
RM_INLINE vec4 rm_mat4_mulv(const mat4, const vec4);
RM_INLINE vec3 rm_mat4_mulv3(const mat4, const vec3, const f32);
RM_INLINE f32  rm_mat4_trace(const mat4);
RM_INLINE f32  rm_mat4_trace3(const mat4);
RM_INLINE mat4 rm_mat4_transpose(const mat4);
RM_INLINE mat4 rm_mat4_translate(const f32, const f32, const f32);
RM_INLINE mat4 rm_mat4_translatev3(const vec3);
RM_INLINE mat4 rm_mat4_scale(const mat4, const f32);
RM_INLINE mat4 rm_mat4_scale_aniso(const mat4, const f32, const f32, const f32);
RM_INLINE f32  rm_mat4_det(const mat4);
RM_INLINE mat4 rm_mat4_inv(const mat4);
RM_INLINE void rm_mat4_swap_col(mat4, const u32, const u32);
RM_INLINE void rm_mat4_swap_row(mat4, const u32, const u32);
RM_INLINE f32  rm_mat4_rmc(const vec4, const mat4, const vec4);
RM_INLINE mat4 rm_mat4_ortho(const f32, const f32, const f32, const f32, const f32, const f32);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RANMATH_H */

#ifdef RANMATH_IMPLEMENTATION
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if RM_SIMD
#define _MM_SHUFFLE(x, y, z, w) (((w) << 6) | ((z) << 4) | ((y) << 2) | ((x)))

#if RM_SSE_ENABLE
#include <emmintrin.h>

#define rmm_load(v) _mm_load_ps((v))
#define rmm_store(v, a) _mm_store_ps((v), (a))
#define rmm_set(x, y, z, w) _mm_set_ps((w), (z), (y), (x))
#define rmm_set1(x) _mm_set_ps1((x))
#define rmm_unpack_lo(a, b) _mm_unpacklo_ps((a), (b))
#define rmm_unpack_hi(a, b) _mm_unpackhi_ps((a), (b))
#define rmm_add(a, b) _mm_add_ps((a), (b))
#define rmm_sub(a, b) _mm_sub_ps((a), (b))
#define rmm_mul(a, b) _mm_mul_ps((a), (b))
#define rmm_div(a, b) _mm_div_ps((a), (b))
#define rmm_min(a, b) _mm_min_ps((a), (b))
#define rmm_max(a, b) _mm_max_ps((a), (b))
#define rmm_abs(x) _mm_and_ps(_mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)), (x))
#define rmm_neg(x) rmm_sub(rmm_set1(0.0F), (x))
#define rmm_cvts32_f32(x) _mm_cvtepi32_ps((x))
#define rmm_cvtf32_s32(x) _mm_cvtps_epi32((x))
#define rmm_cvttf32_s32(x) _mm_cvttps_epi32((x))
#define rmm_shuffle(v, x, y, z, w) _mm_shuffle_ps((v), (v), _MM_SHUFFLE((w), (z), (y), (x)))
#define rmm_shuffle2(v, u, x, y, z, w) _mm_shuffle_ps((v), (u), _MM_SHUFFLE((w), (z), (y), (x)))
#endif /* RM_SSE_ENABLE */

#if RM_NEON_ENABLE
#include <arm_neon.h>

#define rmm_load(v) vld1q_f32((v))
#define rmm_store(v, a) vst1q_f32((v), (a))
#define rmm_set(x, y, z, w) ((RM_VEC){(x), (y), (z), (w)})
#define rmm_set1(x) vdupq_n_f32((x))
#if defined(__aarch64__)
#define rmm_unpack_lo(a, b) vzip1q_f32((a), (b))
#define rmm_unpack_hi(a, b) vzip2q_f32((a), (b))
#else
#define rmm_unpack_lo(a, b) do {                         \
    float32x2x2_t res;                                   \
                                                         \
    res = vzip_f32(vget_low_f32(a), vget_low_f32(b));    \
                                                         \
    return vcombine_f32(res.val[0], res.val[1]);         \
} while(0);
#define rmm_unpack_hi(a, b) do {                           \
    float32x2x2_t res;                                     \
                                                           \
    res = vzip_f32(vget_high_f32(a), vget_high_f32(b));    \
                                                           \
    return vcombine_f32(res.val[0], res.val[1]);           \
} while(0);
#endif /* __aarch64__ */
#define rmm_add(a, b) vaddq_f32((a), (b))
#define rmm_sub(a, b) vsubq_f32((a), (b))
#define rmm_mul(a, b) vmulq_f32((a), (b))
#define rmm_div(a, b) vdivq_f32((a), (b))
#define rmm_min(a, b) vminq_f32((a), (b))
#define rmm_max(a, b) vmaxq_f32((a), (b))
#define rmm_abs(x) vabsq_f32((x))
#define rmm_neg(x) vnegq_f32((x))
#define rmm_cvts32_f32(x) vcvtq_f32_s32((x))
#define rmm_cvtf32_s32(x) vcvtnq_s32_f32((x))
#define rmm_cvttf32_s32(x) vcvtq_s32_f32((x))
/* OBS!! this may not work and has not been tested: */
#if 0
#define rmm_shuffle(v, x, y, z, w) do {
    u32 control_element[4];
    uint8x8_t rl, rh;
    uint32x2_t idx;
    int8x8x2_t tbl;

    control_element[0] = 0x03020100; /* RM_SWIZZLE_X */
    control_element[1] = 0x07060504; /* RM_SWIZZLE_Y */
    control_element[2] = 0x0B0A0908; /* RM_SWIZZLE_Z */
    control_element[3] = 0x0F0E0D0C; /* RM_SWIZZLE_W */


    tbl.val[0] = vget_low_f32(v);
    tbl.val[1] = vget_high_f32(v);

    idx = vcreate_u32(((u64)control_element[x]) | (((u64)control_element[y]) << 32));
    rl = vtbl2_u8(tbl, idx);

    idx = vcreate_u32(((u64)control_element[z]) | (((u64)control_element[w]) << 32));
    rh = vtbl2_u8(tbl, idx);

    return vcombine_f32(rl, rh);
} while(0);
#endif
#endif /* RM_NEON_ENABLE */

RM_INLINE f32 rmm_hadd(RM_VEC x) {
    #if RM_COMPILER == RM_CL
    return x.m128_f32[0] + x.m128_f32[1] + x.m128_f32[2] + x.m128_f32[3];
    #elif RM_NEON_ENABLE && defined(__aarch64__)
    return vaddvq_f32(x);
    #else
    return x[0] + x[1] + x[2] + x[3];
    #endif /* Microsoft */
}
RM_INLINE RM_VEC rmm_hadd4(RM_VEC a, RM_VEC b, RM_VEC c, RM_VEC d) {
    RM_VEC s1, s2;

    /* [a0+a2 c0+c2 a1+a3 c1+c3] */
    s1 = rmm_add(rmm_unpack_lo(a, c), rmm_unpack_hi(a, c));
    /* [b0+b2 d0+d2 b1+b3 d1+d3] */
    s2 = rmm_add(rmm_unpack_lo(b, d), rmm_unpack_hi(b, d));
    /* [a0+a2 b0+b2 c0+c2 d0+d2] + [a1+a3 b1+b3 c1+c3 d1+d3] */

    return rmm_add(rmm_unpack_lo(s1, s2), rmm_unpack_hi(s1, s2));
}

#define rmm_trunc(x) rmm_cvts32_f32(rmm_cvttf32_s32((x)))
#define rmm_mod(a, b) rmm_sub((a), rmm_mul(rmm_trunc(rmm_div((a), (b))), (b)))
#define rmm_fmadd(a, b, c) rmm_add(rmm_mul((a), (b)), (c))
#endif /* RM_SIMD */

#define RM_ABS(x) (((x) < 0) ? -(x) : (x))
#define RM_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define RM_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define RM_CLAMP(val, min, max) (RM_MIN(RM_MAX((val), (min)), (max)))
#define RM_POW2(x) ((x) * (x))
#define RM_POW4(x) (RM_POW2(RM_POW2((x))))

#define RM_VEC2_FILL(x) (vec2){(x), (x)}
#define RM_VEC3_FILL(x) (vec3){(x), (x), (x)}
#define RM_VEC4_FILL(x) (vec4){(x), (x), (x), (x)}

#define RM_MAT2_FILL(x) (mat2){{RM_VEC2_FILL((x)), RM_VEC2_FILL((x))}}
#define RM_MAT3_FILL(x) (mat3){{RM_VEC3_FILL((x)), RM_VEC3_FILL((x)), RM_VEC3_FILL((x))}}
#define RM_MAT4_FILL(x) (mat4){{RM_VEC4_FILL((x)), RM_VEC4_FILL((x)), RM_VEC4_FILL((x)), RM_VEC4_FILL((x))}}

#define RM_MAT2_IDENTITY (mat2){{{1, 0}, {0, 1}}}
#define RM_MAT3_IDENTITY (mat3){{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}
#define RM_MAT4_IDENTITY (mat4){{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}}

/* Stolen from: https://math.stackexchange.com/questions/3886552/bhaskara-approximation-of-cosx,
* Claude Leibovici's answer (precalculated)
*/
#define RM_COS_APPR_A -0.132995644812022330410032839099700470577487194965079816065230286
#define RM_COS_APPR_B  0.0032172781382535624048708288689972016965839213439467243797038973
#define RM_COS_APPR_C  0.0336709157304375144254000370104015622020879871979042486728981326
#define RM_COS_APPR_D  0.0004962828018660570906955733487210649504998482691550479603258607

RM_INLINE bool rm_eqf(const f32 a, const f32 b) {
    return RM_ABS(RM_MAX(a, b) - RM_MIN(a, b)) <= (f32_cvt){.u = 0x1A000019}.f;
}
RM_INLINE bool rm_eqd(const f64 a, const f64 b) {
    return RM_ABS(RM_MAX(a, b) - RM_MIN(a, b)) <= (f64_cvt){.u = 0x1E58000000000000}.f;
}
RM_INLINE bool rm_eq_epsf(const f32 a, const f32 b) {
    return RM_ABS(RM_MAX(a, b) - RM_MIN(a, b)) <= RM_FLT_EPSILON;
}
RM_INLINE bool rm_eq_epsd(const f64 a, const f64 b) {
    return RM_ABS(RM_MAX(a, b) - RM_MIN(a, b)) <= RM_DBL_EPSILON;
}
RM_INLINE i32 rm_facti(const i32 x) {
    if (x < 0) return -1; /* ERROR */
    i32 i, d;

    d = 1;
    for (i = 1; i <= x; ++i) {
        d *= i;
    }

    return d;
}
RM_INLINE i64 rm_factl(const i64 x) {
    if (x < 0) return -1; /* ERROR */
    i64 i, d;

    d = 1;
    for (i = 1; i <= x; ++i) {
        d *= i;
    }

    return d;
}
RM_INLINE i32 rm_powi(const i32 x, const i32 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;
    i32 i, val, x2, p2;

    val = 1;
    x2 = (x < 0) ? 1 / x : x;
    p2 = rm_absi(p);
    for (i = 0; i < p2; ++i) {
        val *= x2;
    }

    return val;
}
RM_INLINE i64 rm_powl(const i64 x, const i64 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;
    i64 i, val, x2, p2;

    val = 1;
    x2 = (x < 0) ? 1 / x : x;
    p2 = rm_absl(p);
    for (i = 0; i < p2; ++i) {
        val *= x2;
    }

    return val;
}
RM_INLINE i32 rm_pow2i(const i32 x) {
    return RM_POW2(x);
}
RM_INLINE i64 rm_pow2l(const i64 x) {
    return RM_POW2(x);
}
RM_INLINE f32 rm_pow2f(const f32 x) {
    return RM_POW2(x);
}
RM_INLINE f64 rm_pow2d(const f64 x) {
    return RM_POW2(x);
}
RM_INLINE f32 rm_rsqrtf(const f32 x) {
    if (x < 0) return RM_NAN_F;
    if (rm_eqf(x, 0)) return RM_INF_F;
    f32_cvt c;
    f32 xh;

    c.f = x;
    xh = 0.5F * x;

    c.u = 0x5F375A86 - (c.u >> 1);

    /* Newton-Raphson iterations for accuracy */
    c.f *= 1.5F - (RM_POW2(c.f) * xh);
    c.f *= 1.5F - (RM_POW2(c.f) * xh);
    c.f *= 1.5F - (RM_POW2(c.f) * xh);

    return c.f;
}
RM_INLINE f64 rm_rsqrtd(const f64 x) {
    if (x < 0) return RM_NAN;
    if (rm_eqd(x, 0)) return RM_INF;
    f64_cvt c;
    f64 xh;

    c.f = x;
    xh = 0.5 * x;

    c.u = 0x5FE6EB50C7B537A9 - (c.u >> 1);

    /* Newton-Raphson iterations for accuracy */
    c.f *= 1.5 - (RM_POW2(c.f) * xh);
    c.f *= 1.5 - (RM_POW2(c.f) * xh);
    c.f *= 1.5 - (RM_POW2(c.f) * xh);
    c.f *= 1.5 - (RM_POW2(c.f) * xh);

    return c.f;
}
RM_INLINE f32 rm_sqrtf(const f32 x) {
    if (x < 0) return RM_NAN_F;
    if (x == 0 || x == 1) return x;

    /* sqrt(x) = x * 1/sqrt(x) */
    return x * rm_rsqrtf(x);
}
RM_INLINE f64 rm_sqrtd(const f64 x) {
    if (x < 0) return RM_NAN;
    if (x == 0 || x == 1) return x;

    /* sqrt(x) = x * 1/sqrt(x) */
    return x * rm_rsqrtd(x);
}
RM_INLINE i32 rm_absi(const i32 x) {
    return RM_ABS(x);
}
RM_INLINE i64 rm_absl(const i64 x) {
    return RM_ABS(x);
}
RM_INLINE f32 rm_absf(const f32 x) {
    return RM_ABS(x);
}
RM_INLINE f64 rm_absd(const f64 x) {
    return RM_ABS(x);
}
RM_INLINE i32 rm_mini(const i32 a, const i32 b) {
    return RM_MIN(a, b);
}
RM_INLINE i64 rm_minl(const i64 a, const i64 b) {
    return RM_MIN(a, b);
}
RM_INLINE f32 rm_minf(const f32 a, const f32 b) {
    return RM_MIN(a, b);
}
RM_INLINE f64 rm_mind(const f64 a, const f64 b) {
    return RM_MIN(a, b);
}
RM_INLINE i32 rm_maxi(const i32 a, const i32 b) {
    return RM_MAX(a, b);
}
RM_INLINE i64 rm_maxl(const i64 a, const i64 b) {
    return RM_MAX(a,b);
}
RM_INLINE f32 rm_maxf(const f32 a, const f32 b) {
    return RM_MAX(a, b);
}
RM_INLINE f64 rm_maxd(const f64 a, const f64 b) {
    return RM_MAX(a, b);
}
RM_INLINE i32 rm_clampi(const i32 val, const i32 min, const i32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i64 rm_clampl(const i64 val, const i64 min, const i64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32 rm_clampf(const f32 val, const f32 min, const f32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f64 rm_clampd(const f64 val, const f64 min, const f64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32 rm_truncf(const f32 x) {
    return (i32)x;
}
RM_INLINE f64 rm_truncd(const f64 x) {
    return (i64)x;
}
RM_INLINE f32 rm_modf(const f32 a, const f32 b) {
    return a - rm_truncf(a / b) * b;
}
RM_INLINE f64 rm_modd(const f64 a, const f64 b) {
    return a - rm_truncd(a / b) * b;
}
RM_INLINE f32 rm_floorf(const f32 x) {
    if (x == 0) return x;
    i32 ix ,inx;

    ix = rm_truncf(x);
    inx = ix - 1;

    return (x < 0) ? inx : ix;
}
RM_INLINE f64 rm_floord(const f64 x) {
    if (x == 0) return x;
    i64 ix, inx;

    ix = rm_truncd(x);
    inx = ix - 1;

    return (x < 0) ? inx : ix;
}
RM_INLINE f32 rm_ceilf(const f32 x) {
    if (x == 0) return x;
    i32 ix;

    ix = rm_truncf(x);

    return (x < 0) ? ix : ix + 1;
}
RM_INLINE f64 rm_ceild(const f64 x) {
    if (x == 0) return x;
    i64 ix;

    ix = rm_truncd(x);

    return (x < 0) ? ix : ix + 1;
}
RM_INLINE f32 rm_roundf(const f32 x) {
    bool c1, c2;
    f32 floor, ceil;

    c1 = (rm_absf(x) - rm_absi(rm_truncf(x))) < 0.5F;
    c2 = x < 0;
    floor = rm_floorf(x);
    ceil = rm_ceilf(x);

    return (c1) ? ((c2) ? ceil : floor) : ((c2) ? floor : ceil);
}
RM_INLINE f64 rm_roundd(const f64 x) {
    bool c1, c2;
    f64 floor, ceil;

    c1 = (rm_absd(x) - rm_absl(rm_truncd(x))) < 0.5;
    c2 = x < 0;
    floor = rm_floord(x);
    ceil = rm_ceild(x);

    return (c1) ? ((c2) ? ceil : floor) : ((c2) ? floor : ceil);
}
RM_INLINE f32 rm_wrap_maxf(const f32 val, const f32 max) {
    return rm_modf(max + rm_modf(val, max), max);
}
RM_INLINE f64 rm_wrap_maxd(const f64 val, const f64 max) {
    return rm_modd(max + rm_modd(val, max), max);
}
RM_INLINE f32 rm_wrapf(const f32 val, const f32 min, const f32 max) {
    f32 tmax;

    tmax = max - min;

    return min + rm_modf(tmax + rm_modf(val - min, tmax), tmax);
}
RM_INLINE f64 rm_wrapd(const f64 val, const f64 min, const f64 max) {
    f64 tmax;

    tmax = max - min;

    return min + rm_modd(tmax + rm_modd(val - min, tmax), tmax);
}
RM_INLINE f32 rm_cosf(const f32 x) {
    f32 i, i2, i4;
    f64 val;

    i = RM_PI_2 - rm_absd(rm_wrap_maxd(x, RM_2PI) - RM_PI);
    i2 = rm_pow2f(i);
    i4 = rm_pow2f(i2);

    val = 1.0 + (RM_COS_APPR_A * i2) + (RM_COS_APPR_B * i4);
    val /= 1.0 + (RM_COS_APPR_C * i2) + (RM_COS_APPR_D * i4);
    val *= i;

    return -val;
}
RM_INLINE f64 rm_cosd(const f64 x) {
    f64 i, i2, i4, val;

    i = RM_PI_2 - rm_absd(rm_wrap_maxd(x, RM_2PI) - RM_PI);
    i2 = rm_pow2d(i);
    i4 = rm_pow2d(i2);

    val = 1.0 + (RM_COS_APPR_A * i2) + (RM_COS_APPR_B * i4);
    val /= 1.0 + (RM_COS_APPR_C * i2) + (RM_COS_APPR_D * i4);
    val *= i;

    return -val;
}
RM_INLINE f32 rm_sinf(const f32 x) {
    return -rm_cosf(x + RM_PI_2);
}
RM_INLINE f64 rm_sind(const f64 x) {
    return -rm_cosd(x + RM_PI_2);
}
RM_INLINE f32 rm_tanf(const f32 x) {
    return rm_sinf(x) / rm_cosf(x);
}
RM_INLINE f64 rm_tand(const f64 x) {
    return rm_sind(x) / rm_cosd(x);
}
RM_INLINE f32 rm_cotf(const f32 x) {
    return rm_cosf(x) / rm_sinf(x);
}
RM_INLINE f64 rm_cotd(const f64 x) {
    return rm_cosd(x) / rm_sind(x);
}
RM_INLINE f32 rm_secf(const f32 x) {
    return 1.0F / rm_cosf(x);
}
RM_INLINE f64 rm_secd(const f64 x) {
    return 1.0 / rm_cosd(x);
}
RM_INLINE f32 rm_cscf(const f32 x) {
    return 1.0F / rm_sinf(x);
}
RM_INLINE f64 rm_cscd(const f64 x) {
    return 1.0 / rm_sind(x);
}
/* UNIMPLEMENTED: DON'T USE */
RM_INLINE f32 rm_acosf(const f32 x) {
    return 0;
}
RM_INLINE f64 rm_acosd(const f64 x) {
    return 0;
}
RM_INLINE f32 rm_asinf(const f32 x) {
    return 0;
}
RM_INLINE f64 rm_asind(const f64 x) {
    return 0;
}
RM_INLINE f32 rm_atanf(const f32 x) {
    return 0;
}
RM_INLINE f64 rm_atand(const f64 x) {
    return 0;
}
/* END UNIMPLEMENTED */
RM_INLINE f32 rm_rad2degf(const f32 x) {
    return RM_MAKE_DEG * x;
}
RM_INLINE f64 rm_rad2degd(const f64 x) {
    return RM_MAKE_DEG * x;
}
RM_INLINE f32 rm_deg2radf(const f32 x) {
    return RM_MAKE_RAD * x;
}
RM_INLINE f64 rm_deg2radd(const f64 x) {
    return RM_MAKE_RAD * x;
}

RM_INLINE vec2 rm_vec2_copy(const vec2 v) {
    vec2 dest;

    dest = v;

    return dest;
}
RM_INLINE vec2 rm_vec2_abs(const vec2 v) {
    vec2 dest;

    dest = (vec2){rm_absf(v.x), rm_absf(v.y)};

    return dest;
}
RM_INLINE f32 rm_vec2_max(const vec2 v) {
    return rm_maxf(v.x, v.y);
}
RM_INLINE f32 rm_vec2_min(const vec2 v) {
    return rm_minf(v.x, v.y);
}
RM_INLINE vec2 rm_vec2_maxv(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){rm_maxf(a.x, b.x), rm_maxf(a.y, b.y)};

    return dest;
}
RM_INLINE vec2 rm_vec2_minv(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){rm_minf(a.x, b.x), rm_minf(a.y, b.y)};

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

    dest = (vec2){x, y};

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
    return rm_sqrtf(rm_vec2_norm2(v));
}
RM_INLINE f32 rm_vec2_norm_one(const vec2 v) {
    return rm_vec2_hadd(rm_vec2_abs(v));
}
RM_INLINE f32 rm_vec2_norm_inf(const vec2 v) {
    return rm_vec2_max(rm_vec2_abs(v));
}
RM_INLINE vec2 rm_vec2_add(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){a.x + b.x, a.y + b.y};

    return dest;
}
RM_INLINE vec2 rm_vec2_adds(const vec2 v, const f32 s) {
    vec2 dest;

    dest = (vec2){v.x + s, v.y + s};

    return dest;
}
RM_INLINE vec2 rm_vec2_sub(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){a.x - b.x, a.y - b.y};

    return dest;
}
RM_INLINE vec2 rm_vec2_subs(const vec2 v, const f32 s) {
    vec2 dest;

    dest = (vec2){v.x - s, v.y - s};

    return dest;
}
RM_INLINE vec2 rm_vec2_mul(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){a.x * b.x, a.y * b.y};

    return dest;
}
RM_INLINE vec2 rm_vec2_scale(const vec2 v, const f32 s) {
    vec2 dest;

    dest = (vec2){v.x * s, v.y * s};

    return dest;
}
RM_INLINE vec2 rm_vec2_scale_as(const vec2 v, const f32 s) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (rm_eqf(norm, 0.0F)) ? rm_vec2_zero() : rm_vec2_scale(v, s / norm);
}
RM_INLINE vec2 rm_vec2_scale_aniso(const vec2 v, const f32 x, const f32 y) {
    vec2 dest;

    dest = (vec2){v.x * x, v.y * y};

    return dest;
}
RM_INLINE vec2 rm_vec2_div(const vec2 a, const vec2 b) {
    vec2 dest;

    dest = (vec2){a.x / b.x, a.y / b.y};

    return dest;
}
RM_INLINE vec2 rm_vec2_divs(const vec2 v, const f32 s) {
    vec2 dest;

    dest = rm_vec2_scale(v, 1.0F / s);

    return dest;
}
RM_INLINE vec2 rm_vec2_negate(const vec2 v) {
    vec2 dest;

    dest = (vec2){-v.x, -v.y};

    return dest;
}
RM_INLINE vec2 rm_vec2_normalize(const vec2 v) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (rm_eqf(norm, 0.0F)) ? rm_vec2_zero() : rm_vec2_scale(v, 1.0F / norm);
}
RM_INLINE vec2 rm_vec2_rotate(const vec2 v, const f32 a) {
    f32 c, s;
    vec2 dest;

    c = rm_cosf(a);
    s = rm_sinf(a);

    dest = (vec2){c * v.x - s * v.y, s * v.x + c * v.y};

    return dest;
}
RM_INLINE f32 rm_vec2_distance2(const vec2 a, const vec2 b) {
    return rm_pow2f(b.x - a.x) + rm_pow2f(b.y - a.y);
}
RM_INLINE f32 rm_vec2_distance(const vec2 a, const vec2 b) {
    return rm_sqrtf(rm_vec2_distance2(a, b));
}
RM_INLINE vec2 rm_vec2_clamp(const vec2 v, const f32 min, const f32 max) {
    vec2 dest;

    dest = (vec2){rm_clampf(v.x, min, max), rm_clampf(v.y, min, max)};

    return dest;
}
RM_INLINE vec2 rm_vec2_wrap(const vec2 v, const f32 min, const f32 max) {
    vec2 dest;

    dest = (vec2){rm_wrapf(v.x, min, max), rm_wrapf(v.y, min, max)};

    return dest;
}
RM_INLINE vec2 rm_vec2_center(const vec2 a, const vec2 b) {
    return rm_vec2_scale(rm_vec2_add(a, b), 0.5F);
}

RM_INLINE vec3 rm_vec3_copy(const vec3 v) {
    vec3 dest;

    dest = v;

    return dest;
}
RM_INLINE vec2 rm_vec3_copy2(const vec3 v) {
    vec2 dest;

    dest = (vec2){v.x, v.y};

    return dest;
}
RM_INLINE vec3 rm_vec3_abs(const vec3 v) {
    vec3 dest;

    dest = (vec3){rm_absf(v.x), rm_absf(v.y), rm_absf(v.z)};

    return dest;
}
RM_INLINE f32 rm_vec3_max(const vec3 v) {
    return rm_maxf(rm_maxf(v.x, v.y), v.z);
}
RM_INLINE f32 rm_vec3_min(const vec3 v) {
    return rm_minf(rm_minf(v.x, v.y), v.z);
}
RM_INLINE vec3 rm_vec3_maxv(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){rm_maxf(a.x, b.x), rm_maxf(a.y, b.y), rm_maxf(a.z, b.z)};

    return dest;
}
RM_INLINE vec3 rm_vec3_minv(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){rm_minf(a.x, b.x), rm_minf(a.y, b.y), rm_minf(a.z, b.z)};

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

    dest = (vec3){x, y, z};

    return dest;
}
RM_INLINE vec3 rm_vec3_fill(const f32 x) {
    vec3 dest;

    dest = RM_VEC3_FILL(x);

    return dest;
}
RM_INLINE vec3 rm_vec3_make(const vec2 v, const f32 last) {
    vec3 dest;

    dest = (vec3){v.x, v.y, last};

    return dest;
}
RM_INLINE f32 rm_vec3_dot(const vec3 a, const vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
RM_INLINE vec3 rm_vec3_cross(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};

    return dest;
}
RM_INLINE vec3 rm_vec3_crossn(const vec3 a, const vec3 b) {
    return rm_vec3_normalize(rm_vec3_cross(a, b));
}
RM_INLINE f32 rm_vec3_norm2(const vec3 v) {
    return rm_vec3_dot(v, v);
}
RM_INLINE f32 rm_vec3_norm(const vec3 v) {
    return rm_sqrtf(rm_vec3_norm2(v));
}
RM_INLINE f32 rm_vec3_norm_one(const vec3 v) {
    return rm_vec3_hadd(rm_vec3_abs(v));
}
RM_INLINE f32 rm_vec3_norm_inf(const vec3 v) {
    return rm_vec3_max(rm_vec3_abs(v));
}
RM_INLINE vec3 rm_vec3_add(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){a.x + b.x, a.y + b.y, a.z + b.z};

    return dest;
}
RM_INLINE vec3 rm_vec3_adds(const vec3 v, const f32 s) {
    vec3 dest;

    dest = (vec3){v.x + s, v.y + s, v.z + s};

    return dest;
}
RM_INLINE vec3 rm_vec3_sub(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){a.x - b.x, a.y - b.y, a.z - b.z};

    return dest;
}
RM_INLINE vec3 rm_vec3_subs(const vec3 v, const f32 s) {
    vec3 dest;

    dest = (vec3){v.x - s, v.y - s, v.z - s};

    return dest;
}
RM_INLINE vec3 rm_vec3_mul(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){a.x * b.x, a.y * b.y, a.z * b.z};

    return dest;
}
RM_INLINE vec3 rm_vec3_scale(const vec3 v, const f32 s) {
    vec3 dest;

    dest = (vec3){v.x * s, v.y * s, v.z * s};

    return dest;
}
RM_INLINE vec3 rm_vec3_scale_as(const vec3 v, const f32 s) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (rm_eqf(norm, 0.0F)) ? rm_vec3_zero() : rm_vec3_scale(v, s / norm);
}
RM_INLINE vec3 rm_vec3_scale_aniso(const vec3 v, const f32 x, const f32 y, const f32 z) {
    vec3 dest;

    dest = (vec3){v.x * x, v.y * y, v.z * z};

    return dest;
}
RM_INLINE vec3 rm_vec3_div(const vec3 a, const vec3 b) {
    vec3 dest;

    dest = (vec3){a.x / b.x, a.y / b.y, a.z / b.z};

    return dest;
}
RM_INLINE vec3 rm_vec3_divs(const vec3 v, const f32 s) {
    vec3 dest;

    dest = rm_vec3_scale(v, 1.0F / s);

    return dest;
}
RM_INLINE vec3 rm_vec3_negate(const vec3 v) {
    vec3 dest;

    dest = (vec3){-v.x, -v.y, -v.z};

    return dest;
}
RM_INLINE vec3 rm_vec3_normalize(const vec3 v) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (rm_eqf(norm, 0.0F)) ? rm_vec3_zero() : rm_vec3_scale(v, 1.0F / norm);
}
RM_INLINE vec3 rm_vec3_rotate(const vec3 v, const f32 a, const vec3 axis) {
    f32 c, s;
    vec3 v1, v2, k, dest;

    c = rm_cosf(a);
    s = rm_sinf(a);

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
    return rm_pow2f(a.x - b.x) + rm_pow2f(a.y - b.y) + rm_pow2f(a.z - b.z);
}
RM_INLINE f32 rm_vec3_distance(const vec3 a, const vec3 b) {
    return rm_sqrtf(rm_vec3_distance2(a, b));
}
RM_INLINE vec3 rm_vec3_clamp(const vec3 v, const f32 min, const f32 max) {
    vec3 dest;

    dest = (vec3){rm_clampf(v.x, min, max), rm_clampf(v.y, min, max), rm_clampf(v.z, min, max)};

    return dest;

}
RM_INLINE vec3 rm_vec3_wrap(const vec3 v, const f32 min, const f32 max) {
    vec3 dest;

    dest = (vec3){rm_wrapf(v.x, min, max), rm_wrapf(v.y, min, max), rm_wrapf(v.z, min, max)};

    return dest;
}
RM_INLINE vec3 rm_vec3_center(const vec3 a, const vec3 b) {
    return rm_vec3_scale(rm_vec3_add(a, b), 0.5F);
}

RM_INLINE vec4 rm_vec4_copy(const vec4 v) {
    vec4 dest;

    dest = v;

    return dest;
}
RM_INLINE vec3 rm_vec4_copy3(const vec4 v) {
    vec3 dest;

    dest = (vec3){v.x, v.y, v.z};

    return dest;
}
RM_INLINE vec4 rm_vec4_abs(const vec4 v) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_abs(rmm_load(dest.raw)));
    #else
    dest.v = (vec4){rm_absf(v.x), rm_absf(v.y), rm_absf(v.z), rm_absf(v.w)};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE f32 rm_vec4_max(const vec4 v) {
    return rm_maxf(rm_maxf(rm_maxf(v.x, v.y), v.z), v.w);
}
RM_INLINE f32 rm_vec4_min(const vec4 v) {
    return rm_minf(rm_minf(rm_minf(v.x, v.y), v.z), v.w);
}
RM_INLINE vec4 rm_vec4_maxv(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_max(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){rm_maxf(a.x, b.x), rm_maxf(a.y, b.y), rm_maxf(a.z, b.z), rm_maxf(a.w, b.w)};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_minv(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_min(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){rm_minf(a.x, b.x), rm_minf(a.y, b.y), rm_minf(a.z, b.z), rm_minf(a.w, b.w)};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE f32 rm_vec4_hadd(const vec4 v) {
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(v);

    return rmm_hadd(rmm_load(v0.raw));
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

    dest = (vec4){x, y, z, w};

    return dest;
}
RM_INLINE vec4 rm_vec4_fill(const f32 x) {
    vec4 dest;

    dest = RM_VEC4_FILL(x);

    return dest;
}
RM_INLINE vec4 rm_vec4_make(const vec3 v, const f32 last) {
    vec4 dest;

    dest = (vec4){v.x, v.y, v.z, last};

    return dest;
}
RM_INLINE f32 rm_vec4_dot(const vec4 a, const vec4 b) {
    #if RM_SIMD
    vec4_cvt v0, v1;

    v0.v = rm_vec4_copy(a);
    v1.v = rm_vec4_copy(b);

    return rmm_hadd(rmm_mul(rmm_load(v0.raw), rmm_load(v1.raw)));
    #else
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    #endif /* RM_SIMD */
}
RM_INLINE f32 rm_vec4_norm2(const vec4 v) {
    return rm_vec4_dot(v, v);
}
RM_INLINE f32 rm_vec4_norm(const vec4 v) {
    return rm_sqrtf(rm_vec4_norm2(v));
}
RM_INLINE f32 rm_vec4_norm_one(const vec4 v) {
    return rm_vec4_hadd(rm_vec4_abs(v));
}
RM_INLINE f32 rm_vec4_norm_inf(const vec4 v) {
    return rm_vec4_max(rm_vec4_abs(v));
}
RM_INLINE vec4 rm_vec4_add(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_add(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_adds(const vec4 v, const f32 s) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_add(rmm_load(dest.raw), rmm_set1(s)));
    #else
    dest.v = (vec4){v.x + s, v.y + s, v.z + s, v.w + s};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_sub(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_sub(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_subs(const vec4 v, const f32 s) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_sub(rmm_load(dest.raw), rmm_set1(s)));
    #else
    dest.v = (vec4){v.x - s, v.y - s, v.z - s, v.w - s};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_mul(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_mul(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_scale(const vec4 v, const f32 s) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_mul(rmm_load(dest.raw), rmm_set1(s)));
    #else
    dest.v = (vec4){v.x * s, v.y * s, v.z * s, v.w * s};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_scale_as(const vec4 v, const f32 s) {
    f32 norm;

    norm = rm_vec4_norm(v);

    return (rm_eqf(norm, 0)) ? rm_vec4_zero() : rm_vec4_scale(v, s / norm);
}
RM_INLINE vec4 rm_vec4_scale_aniso(const vec4 v, const f32 x, const f32 y, const f32 z, const f32 w) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_mul(rmm_load(dest.raw), rmm_set(x, y, z, w)));
    #else
    dest.v = (vec4){v.x * x, v.y * y, v.z * z, v.w * w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_div(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_div(rmm_load(v0.raw), rmm_load(dest.raw)));
    #else
    dest.v = (vec4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_divs(const vec4 v, const f32 s) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_mul(rmm_load(dest.raw), rmm_set1(1.0F / s)));
    #else
    f32 x;

    x = 1.0F / s;

    dest.v = rm_vec4_scale(v, x);
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_negate(const vec4 v) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_neg(rmm_load(dest.raw)));
    #else
    dest.v = (vec4){-v.x, -v.y, -v.z, -v.w};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_normalize(const vec4 v) {
    f32 norm;

    norm = rm_vec4_norm(v);

    return (rm_eqf(norm, 0)) ? rm_vec4_zero() : rm_vec4_scale(v, 1.0F / norm);
}
RM_INLINE f32 rm_vec4_distance2(const vec4 a, const vec4 b) {
    #if RM_SIMD
    RM_VEC x0;
    vec4_cvt v0, v1;

    v0.v = rm_vec4_copy(a);
    v1.v = rm_vec4_copy(b);
    x0 = rmm_sub(rmm_load(v0.raw), rmm_load(v1.raw));

    return rmm_hadd(rmm_mul(x0, x0));
    #else
    return rm_pow2f(a.x - b.x) + rm_pow2f(a.y - b.y) + rm_pow2f(a.z - b.z) + rm_pow2f(a.w - b.w);
    #endif /* RM_SIMD */
}
RM_INLINE f32 rm_vec4_distance(const vec4 a, const vec4 b) {
    return rm_sqrtf(rm_vec4_distance2(a, b));
}
RM_INLINE vec4 rm_vec4_clamp(const vec4 v, const f32 min, const f32 max) {
    vec4_cvt dest;
    #if RM_SIMD
    dest.v = rm_vec4_copy(v);

    rmm_store(dest.raw, rmm_min(rmm_max(rmm_load(dest.raw), rmm_set1(min)), rmm_set1(max)));
    #else
    f32 cx, cy, cz, cw;

    cx = rm_clampf(v.x, min, max);
    cy = rm_clampf(v.y, min, max);
    cz = rm_clampf(v.z, min, max);
    cw = rm_clampf(v.w, min, max);

    dest.v = (vec4){cx, cy, cz, cw};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_wrap(const vec4 v, const f32 min, const f32 max) {
    vec4_cvt dest;
    #if RM_SIMD
    RM_VEC x0, x1;

    dest.v = rm_vec4_copy(v);

    x0 = rmm_set1(min);
    x1 = rmm_set1(max - min);

    rmm_store(dest.raw, rmm_add(x0, rmm_mod(rmm_add(x1, rmm_mod(rmm_sub(rmm_load(dest.raw), x0), x1)), x1)));
    #else
    f32 wx, wy, wz, ww;

    wx = rm_wrapf(v.x , min, max);
    wy = rm_wrapf(v.y , min, max);
    wz = rm_wrapf(v.z , min, max);
    ww = rm_wrapf(v.w , min, max);

    dest.v = (vec4){wx, wy, wz, ww};
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec4 rm_vec4_center(const vec4 a, const vec4 b) {
    vec4_cvt dest;
    #if RM_SIMD
    vec4_cvt v0;

    v0.v = rm_vec4_copy(a);
    dest.v = rm_vec4_copy(b);

    rmm_store(dest.raw, rmm_mul(rmm_sub(rmm_load(v0.raw), rmm_load(dest.raw)), rmm_set1(0.5F)));
    #else
    dest.v = rm_vec4_scale(rm_vec4_add(a, b), 0.5F);
    #endif /* RM_SIMD */
    return dest.v;
}

RM_INLINE mat2 rm_mat2_copy(const mat2 m) {
    mat2 dest;

    dest = m;

    return dest;
}
RM_INLINE mat2 rm_mat2_identity(void) {
    return RM_MAT2_IDENTITY;
}
RM_INLINE void rm_mat2_identity_array(mat2 *m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat2_identity();
    }
}
RM_INLINE mat2 rm_mat2_zero(void) {
    return RM_MAT2_FILL(0);
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
    vec2 c1, c2;

    c1 = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[0].x), rm_vec2_scale(a.cols[1], b.cols[0].y));
    c2 = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[1].x), rm_vec2_scale(a.cols[1], b.cols[1].y));

    dest = (mat2){{c1, c2}};
    #endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec2 rm_mat2_mulv(const mat2 m, const vec2 v) {
    return rm_vec2_add(rm_vec2_scale(m.cols[0], v.x), rm_vec2_scale(m.cols[1], v.y));
}
RM_INLINE mat2 rm_mat2_transpose(const mat2 m) {
    mat2 dest;
    #if RM_SIMD
    rmm_store(dest.rawv, rmm_shuffle(rmm_load(m.rawv), 0, 2, 1, 3));
    #else
    vec2 c1, c2;

    c1 = (vec2){m.cols[0].x, m.cols[1].x};
    c2 = (vec2){m.cols[0].y, m.cols[1].y};

    dest = (mat2){{c1, c2}};
    #endif /* RM_SIMD */
    return dest;
}
RM_INLINE f32 rm_mat2_trace(const mat2 m) {
    return m.cols[0].x + m.cols[1].y;
}
RM_INLINE mat2 rm_mat2_scale(const mat2 m, const f32 s) {
    mat2 dest;
    #if RM_SIMD
    rmm_store(dest.rawv, rmm_mul(rmm_load(m.rawv), rmm_set1(s)));
    #else
    vec2 c1, c2;

    c1 = rm_vec2_scale(m.cols[0], s);
    c2 = rm_vec2_scale(m.cols[1], s);

    dest = (mat2){{c1, c2}};
    #endif /* RM_SIMD */
    return dest;
}
RM_INLINE f32 rm_mat2_det(const mat2 m) {
    return m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x;
}
RM_INLINE mat2 rm_mat2_inv(const mat2 m) {
    f32 det;
    mat2 dest;

    det = 1.0F / (m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x);
    #if RM_SIMD
    rmm_store(dest.rawv, rmm_mul(rmm_shuffle(rmm_load(m.rawv), 3, 1, 2, 0), rmm_set(det, -det, -det, det)));
    #else
    vec2 c1, c2;

    c1 = (vec2){ m.rawv[3] * det, -m.rawv[1] * det};
    c2 = (vec2){-m.rawv[2] * det,  m.rawv[0] * det};

    dest = (mat2){{c1, c2}};
    #endif /* RM_SIMD */
    return dest;
}
RM_INLINE void rm_mat2_swap_col(mat2 m, const u32 col1, const u32 col2) {
    vec2 tmp;

    tmp = rm_vec2_copy(m.cols[col1]);

    m.cols[col1] = rm_vec2_copy(m.cols[col2]);
    m.cols[col2] = rm_vec2_copy(tmp);
}
RM_INLINE void rm_mat2_swap_row(mat2 m, const u32 row1, const u32 row2) {
    vec2 tmp;

    tmp = (vec2){m.raw[0][row1], m.raw[1][row1]};

    m.raw[0][row1] = m.raw[0][row2];
    m.raw[1][row1] = m.raw[1][row2];

    m.raw[0][row2] = tmp.x;
    m.raw[1][row2] = tmp.y;
}
RM_INLINE f32 rm_mat2_rmc(const vec2 r, const mat2 m, const vec2 c) {
    return rm_vec2_dot(r, rm_mat2_mulv(m, c));
}

RM_INLINE mat3 rm_mat3_copy(const mat3 m) {
    mat3 dest;

    dest = m;

    return dest;
}
RM_INLINE mat3 rm_mat3_identity(void) {
    return RM_MAT3_IDENTITY;
}
RM_INLINE void rm_mat3_identity_array(mat3 *m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat3_identity();
    }
}
RM_INLINE mat3 rm_mat3_zero(void) {
    return RM_MAT3_FILL(0);
}
RM_INLINE mat3 rm_mat3_mul(const mat3 a, const mat3 b) {
    vec3 c1, c2, c3, tmp;
    mat3 dest;

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[0].x), rm_vec3_scale(a.cols[1], b.cols[0].y));
    c1 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[0].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[1].x), rm_vec3_scale(a.cols[1], b.cols[1].y));
    c2 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[1].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[2].x), rm_vec3_scale(a.cols[1], b.cols[2].y));
    c3 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[2].z));

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RM_INLINE vec3 rm_mat3_mulv(const mat3 m, const vec3 v) {
    vec3 tmp;
    tmp = rm_vec3_add(rm_vec3_scale(m.cols[0], v.x), rm_vec3_scale(m.cols[1], v.y));

    return rm_vec3_add(tmp, rm_vec3_scale(m.cols[2], v.z));
}
RM_INLINE mat3 rm_mat3_transpose(const mat3 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = (vec3){m.cols[0].x, m.cols[1].x, m.cols[2].x};
    c2 = (vec3){m.cols[0].y, m.cols[1].y, m.cols[2].y};
    c3 = (vec3){m.cols[0].z, m.cols[1].z, m.cols[2].z};

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RM_INLINE f32 rm_mat3_trace(const mat3 m) {
    return m.cols[0].x + m.cols[1].y + m.cols[2].z;
}
RM_INLINE mat3 rm_mat3_scale(const mat3 m, const f32 s) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = rm_vec3_scale(m.cols[0], s);
    c2 = rm_vec3_scale(m.cols[1], s);
    c3 = rm_vec3_scale(m.cols[2], s);

    dest = (mat3){{c1, c2, c3}};

    return dest;
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
RM_INLINE void rm_mat3_swap_col(mat3 m, const u32 col1, const u32 col2) {
    vec3 tmp;

    tmp = rm_vec3_copy(m.cols[col1]);

    m.cols[col1] = rm_vec3_copy(m.cols[col2]);
    m.cols[col2] = rm_vec3_copy(tmp);
}
RM_INLINE void rm_mat3_swap_row(mat3 m, const u32 row1, const u32 row2) {
    vec3 tmp;

    tmp = (vec3){m.raw[0][row1], m.raw[1][row1], m.raw[2][row1]};

    m.raw[0][row1] = m.raw[0][row2];
    m.raw[1][row1] = m.raw[1][row2];
    m.raw[2][row1] = m.raw[2][row2];

    m.raw[0][row2] = tmp.x;
    m.raw[1][row2] = tmp.y;
    m.raw[2][row2] = tmp.z;
}
RM_INLINE f32 rm_mat3_rmc(const vec3 r, const mat3 m, const vec3 c) {
    return rm_vec3_dot(r, rm_mat3_mulv(m, c));
}

RM_INLINE mat4 rm_mat4_copy(const mat4 m) {
    mat4 dest;

    dest = m;

    return dest;
}
RM_INLINE mat4 rm_mat4_identity(void) {
    return RM_MAT4_IDENTITY;
}
RM_INLINE void rm_mat4_identity_array(mat4 *m, const usize count) {
    usize i;

    for (i = 0; i < count; ++i) {
        m[i] = rm_mat4_identity();
    }
}
RM_INLINE mat4 rm_mat4_zero(void) {
    return RM_MAT4_FILL(0);
}
RM_INLINE mat3 rm_mat4_pick3(const mat4 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = rm_vec4_copy3(m.cols[0]);
    c2 = rm_vec4_copy3(m.cols[1]);
    c3 = rm_vec4_copy3(m.cols[2]);

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RM_INLINE mat3 rm_mat4_pick3t(const mat4 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = (vec3){m.cols[0].x, m.cols[1].x, m.cols[2].x};
    c2 = (vec3){m.cols[0].y, m.cols[1].y, m.cols[2].y};
    c3 = (vec3){m.cols[0].z, m.cols[1].z, m.cols[2].z};

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RM_INLINE void rm_mat4_ins3(const mat3 a, mat4 b) {
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
    vec4 c1, c2, c3, c4, tmp1, tmp2;

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[0].x), rm_vec4_scale(a.cols[1], b.cols[0].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[0].z), rm_vec4_scale(a.cols[3], b.cols[0].w));
    c1 = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[1].x), rm_vec4_scale(a.cols[1], b.cols[1].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[1].z), rm_vec4_scale(a.cols[3], b.cols[1].w));
    c2 = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[2].x), rm_vec4_scale(a.cols[1], b.cols[2].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[2].z), rm_vec4_scale(a.cols[3], b.cols[2].w));
    c3 = rm_vec4_add(tmp1, tmp2);

    tmp1 = rm_vec4_add(rm_vec4_scale(a.cols[0], b.cols[3].x), rm_vec4_scale(a.cols[1], b.cols[3].y));
    tmp2 = rm_vec4_add(rm_vec4_scale(a.cols[2], b.cols[3].z), rm_vec4_scale(a.cols[3], b.cols[3].w));
    c4 = rm_vec4_add(tmp1, tmp2);

    dest = (mat4){{c1, c2, c3, c4}};
    #endif /* RM_SIMD */
    return dest;
}
RM_INLINE vec4 rm_mat4_mulv(const mat4 m, const vec4 v) {
    vec4_cvt dest;
    #if RM_SIMD
    RM_VEC x0, x1;

    x0 = rmm_add(rmm_mul(rmm_load(m.raw[0]), rmm_set1(v.x)), rmm_mul(rmm_load(m.raw[1]), rmm_set1(v.y)));
    x1 = rmm_add(rmm_mul(rmm_load(m.raw[2]), rmm_set1(v.z)), rmm_mul(rmm_load(m.raw[3]), rmm_set1(v.w)));

    rmm_store(dest.raw, rmm_add(x0, x1));
    #else
    vec4 tmp1, tmp2;

    tmp1 = rm_vec4_add(rm_vec4_scale(m.cols[0], v.x), rm_vec4_scale(m.cols[1], v.y));
    tmp2 = rm_vec4_add(rm_vec4_scale(m.cols[2], v.z), rm_vec4_scale(m.cols[3], v.w));

    dest.v = rm_vec4_add(tmp1, tmp2);
    #endif /* RM_SIMD */
    return dest.v;
}
RM_INLINE vec3 rm_mat4_mulv3(const mat4 m, const vec3 v, const f32 last) {
    return rm_vec4_copy3(rm_mat4_mulv(m, rm_vec4_make(v, last)));
}
RM_INLINE f32 rm_mat4_trace(const mat4 m) {
    return m.raw[0][0] + m.raw[1][1] + m.raw[2][2] + m.raw[3][3];
}
RM_INLINE f32 rm_mat4_trace3(const mat4 m) {
    return m.raw[0][0] + m.raw[1][1] + m.raw[2][2];
}
RM_INLINE mat4 rm_mat4_transpose(const mat4 m) {
    vec4 c1, c2, c3, c4;
    mat4 dest;

    c1 = (vec4){m.cols[0].x, m.cols[1].x, m.cols[2].x, m.cols[3].x};
    c2 = (vec4){m.cols[0].y, m.cols[1].y, m.cols[2].y, m.cols[3].y};
    c3 = (vec4){m.cols[0].z, m.cols[1].z, m.cols[2].z, m.cols[3].z};
    c4 = (vec4){m.cols[0].w, m.cols[1].w, m.cols[2].w, m.cols[3].w};

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}
RM_INLINE mat4 rm_mat4_translate(const f32 x, const f32 y, const f32 z) {
    mat4 dest;

    dest = rm_mat4_identity();
    dest.cols[3] = rm_vec4_set(x, y, z, dest.cols[3].w);

    return dest;
}
RM_INLINE mat4 rm_mat4_translatev3(const vec3 v) {
    mat4 dest;

    dest = rm_mat4_identity();
    dest.cols[3] = rm_vec4_make(v, dest.cols[3].w);

    return dest;
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
    vec4 c1, c2, c3, c4;

    c1 = rm_vec4_scale(m.cols[0], s);
    c2 = rm_vec4_scale(m.cols[1], s);
    c3 = rm_vec4_scale(m.cols[2], s);
    c4 = rm_vec4_scale(m.cols[3], s);

    dest = (mat4){{c1, c2, c3, c4}};
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
    vec4 c1, c2, c3, c4;

    c1 = rm_vec4_scale(m.cols[0], x);
    c2 = rm_vec4_scale(m.cols[1], y);
    c3 = rm_vec4_scale(m.cols[2], z);
    c4 = rm_vec4_copy(m.cols[3]);

    dest = (mat4){{c1, c2, c3, c4}};
    #endif /* RM_SIMD */
    return dest;
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
RM_INLINE void rm_mat4_swap_col(mat4 m, const u32 col1, const u32 col2) {
    vec4 tmp;

    tmp = rm_vec4_copy(m.cols[col1]);

    m.cols[col1] = rm_vec4_copy(m.cols[col2]);
    m.cols[col2] = rm_vec4_copy(tmp);
}
RM_INLINE void rm_mat4_swap_row(mat4 m, const u32 row1, const u32 row2) {
    vec4 tmp;

    tmp = (vec4){m.raw[0][row1], m.raw[1][row1], m.raw[2][row1], m.raw[3][row1]};

    m.raw[0][row1] = m.raw[0][row2];
    m.raw[1][row1] = m.raw[1][row2];
    m.raw[2][row1] = m.raw[2][row2];
    m.raw[3][row1] = m.raw[3][row2];

    m.raw[0][row2] = tmp.x;
    m.raw[1][row2] = tmp.y;
    m.raw[2][row2] = tmp.z;
    m.raw[3][row2] = tmp.w;
}
RM_INLINE f32 rm_mat4_rmc(const vec4 r, const mat4 m, const vec4 c) {
    return rm_vec4_dot(r, rm_mat4_mulv(m, c));
}
RM_INLINE mat4 rm_mat4_ortho(const f32 l, const f32 r, const f32 b, const f32 t, const f32 n, const f32 f) {
    f32 rl, tb, fn;
    vec4 c1, c2, c3, c4;
    mat4 dest;

    rl = r - l;
    tb = t - b;
    fn = f - n;

    c1 = (vec4){2 / rl, 0, 0, 0};
    c2 = (vec4){0, 2 / tb, 0, 0};
    c3 = (vec4){0, 0, -2 / fn, 0};
    c4 = (vec4){-(r + l) / rl, -(t + b) / tb, -(f + n) / fn, 1};

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* RANMATH_IMPLEMENTATION */
