#ifndef RANMATH_H
#define RANMATH_H

#include <stdint.h>
#include <stdbool.h>

#ifndef RANMATH_SSE_ENABLE
#if defined(__SSE2__) || defined(__SSE__)
#define RANMATH_SSE_ENABLE 1
#else
#define RANMATH_SSE_ENABLE 0
#endif /* Check for sse2 */
#endif /* Check if already defined */

#if RANMATH_SSE_ENABLE
#include <emmintrin.h>
#endif /* RANMATH_SSE_ENABLE */

#if defined(__GNUC__)
/* GCC-compatible compiler (gcc, clang) */
#define RANMATH_ALIGN(x) __attribute((aligned(x)))
#define RANMATH_INLINE static inline __attribute((always_inline))
#elif defined(_MSC_VER)
/* Microsoft */
#define RANMATH_ALIGN(x) __declspec((align(x)))
#define RANMATH_INLINE static inline __forceinline
#else
/* Unknown */
#define RANMATH_ALIGN(x)
#define RANMATH_INLINE static inline
#endif /* Check compiler */

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

typedef RANMATH_ALIGN(4) struct {
    f32 x;
    f32 y;
} vec2;
typedef RANMATH_ALIGN(4) struct {
    f32 x;
    f32 y;
    f32 z;
} vec3;
typedef RANMATH_ALIGN(4) struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} vec4;
typedef RANMATH_ALIGN(16) struct {
    vec2 cols[2];
} mat2;
typedef RANMATH_ALIGN(16) struct {
    vec3 cols[3];
} mat3;
typedef RANMATH_ALIGN(16) struct {
    vec4 cols[4];
} mat4;

/* ---------------- CONSTANTS ---------------- */
#define RM_E           2.7182818284590452353602874713526624977572470936999595749669676277
#define RM_LOG2E       1.4426950408889634073599246810018921374266459541529859341354494069
#define Rm_LOG10E      0.4342944819032518276511289189166050822943970058036665661144537831
#define RM_LN2         0.6931471805599453094172321214581765680755001343602552541206800094
#define RM_LN10        2.3025850929940456840179914546843642076011014886287729760333279009
#define RM_PI          3.1415926535897932384626433832795028841971693993751058209749445923
#define RM_PI_2        1.5707963267948966192313216916397514420985846996875529104874722961
#define RM_2PI         6.2831853071795864769252867665590057683943387987502116419498891846
#define RM_PI2         9.8696044010893586188344909998761511353136994072407906264133493762
#define RM_PI3         31.006276680299820175476315067101395202225288565885107694144538103
#define RM_PI4         97.409091034002437236440332688705111249727585672685421691467859389
#define RM_1_PI        0.3183098861837906715377675267450287240689192914809128974953346881
#define RM_1_2PI       0.1591549430918953357688837633725143620344596457404564487476673440
#define RM_SQRTPI      1.7724538509055160272981674833411451827975494561223871282138077898
#define RM_1_SQRTPI    0.5641895835477562869480794515607725858440506293289988568440857217
#define RM_2_SQRTPI    1.1283791670955125738961589031215451716881012586579977136881714434
#define RM_SQRT2       1.4142135623730950488016887242096980785696718753769480731766797379
#define RM_1_SQRT2     0.7071067811865475244008443621048490392848359376884740365883398689
#define RM_MAKE_DEG    57.295779513082320876798154814105170332405472466564321549160243861
#define RM_MAKE_RAD    0.0174532925199432957692369076848861271344287188854172545609719144

/* ----------------- METHODS ----------------- */
#define RM_F32_CVT union {f32 f; u32 i;}
#define RM_F64_CVT union {f64 f; u64 i;}

#define RM_VEC_CVT(v) ((f32*)&v)

#define RM_VEC2_CVT union {vec2 v; RANMATH_ALIGN(8) f32 gl[2];}
#define RM_VEC3_CVT union {vec3 v; f32 gl[3];}
#define RM_VEC4_CVT union {vec4 v; RANMATH_ALIGN(16) f32 gl[4];}

#define RM_MAT2_CVT union {mat2 m; RANMATH_ALIGN(16) f32 gl[2][2];}
#define RM_MAT3_CVT union {mat3 m; RANMATH_ALIGN(16) f32 gl[3][3];}
#define RM_MAT4_CVT union {mat4 m; RANMATH_ALIGN(16) f32 gl[4][4];}

RANMATH_INLINE i32 rm_facti(i32);
RANMATH_INLINE i64 rm_factl(i64);
RANMATH_INLINE i32 rm_powi(i32, i32);
RANMATH_INLINE i64 rm_powl(i64, i64);
RANMATH_INLINE i32 rm_pow2i(i32);
RANMATH_INLINE i64 rm_pow2l(i64);
RANMATH_INLINE f32 rm_pow2f(f32);
RANMATH_INLINE f64 rm_pow2d(f64);
RANMATH_INLINE f32 rm_rsqrtf(f32);
RANMATH_INLINE f64 rm_rsqrtd(f64);
RANMATH_INLINE f32 rm_sqrtf(f32);
RANMATH_INLINE f64 rm_sqrtd(f64);
RANMATH_INLINE i32 rm_absi(i32);
RANMATH_INLINE i64 rm_absl(i64);
RANMATH_INLINE f32 rm_absf(f32);
RANMATH_INLINE f64 rm_absd(f64);
RANMATH_INLINE i32 rm_mini(i32, i32);
RANMATH_INLINE i64 rm_minl(i64, i64);
RANMATH_INLINE f32 rm_minf(f32, f32);
RANMATH_INLINE f64 rm_mind(f64, f64);
RANMATH_INLINE i32 rm_mini(i32, i32);
RANMATH_INLINE i64 rm_minl(i64, i64);
RANMATH_INLINE f32 rm_maxf(f32, f32);
RANMATH_INLINE f64 rm_maxd(f64, f64);
RANMATH_INLINE i32 rm_clampi(i32, i32, i32);
RANMATH_INLINE i64 rm_clampl(i64, i64, i64);
RANMATH_INLINE f32 rm_clampf(f32, f32, f32);
RANMATH_INLINE f64 rm_clampd(f64, f64, f64);
RANMATH_INLINE f32 rm_truncf(f32);
RANMATH_INLINE f64 rm_truncd(f64);
RANMATH_INLINE f32 rm_floorf(f32);
RANMATH_INLINE f64 rm_floord(f64);
RANMATH_INLINE f32 rm_ceilf(f32);
RANMATH_INLINE f64 rm_ceild(f64);
RANMATH_INLINE f32 rm_roundf(f32);
RANMATH_INLINE f64 rm_roundd(f64);
RANMATH_INLINE f32 rm_wrap_maxf(f32, f32);
RANMATH_INLINE f64 rm_wrap_maxd(f64, f64);
RANMATH_INLINE f32 rm_wrapf(f32, f32, f32);
RANMATH_INLINE f64 rm_wrapd(f64, f64, f64);
RANMATH_INLINE f32 rm_cosf(f32);
RANMATH_INLINE f64 rm_cosd(f64);
RANMATH_INLINE f32 rm_sinf(f32);
RANMATH_INLINE f64 rm_sind(f64);
RANMATH_INLINE f32 rm_tanf(f32);
RANMATH_INLINE f64 rm_tand(f64);
RANMATH_INLINE f32 rm_cotf(f32);
RANMATH_INLINE f64 rm_cotd(f64);
RANMATH_INLINE f32 rm_secf(f32);
RANMATH_INLINE f64 rm_secd(f64);
RANMATH_INLINE f32 rm_cscf(f32);
RANMATH_INLINE f64 rm_cscd(f64);
RANMATH_INLINE f32 rm_rad2degf(f32);
RANMATH_INLINE f64 rm_rad2degd(f64);
RANMATH_INLINE f32 rm_deg2radf(f32);
RANMATH_INLINE f64 rm_deg2radd(f64);

RANMATH_INLINE vec2 rm_vec2_copy(vec2);
RANMATH_INLINE vec2 rm_vec2_abs(vec2);
RANMATH_INLINE f32  rm_vec2_max(vec2);
RANMATH_INLINE f32  rm_vec2_min(vec2);
RANMATH_INLINE vec2 rm_vec2_maxv(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_minv(vec2, vec2);
RANMATH_INLINE f32  rm_vec2_hadd(vec2);
RANMATH_INLINE vec2 rm_vec2_zero(void);
RANMATH_INLINE vec2 rm_vec2_one(void);
RANMATH_INLINE vec2 rm_vec2_set(f32, f32);
RANMATH_INLINE vec2 rm_vec2_fill(f32);
RANMATH_INLINE f32  rm_vec2_dot(vec2, vec2);
RANMATH_INLINE f32  rm_vec2_cross(vec2, vec2);
RANMATH_INLINE f32  rm_vec2_norm2(vec2);
RANMATH_INLINE f32  rm_vec2_norm(vec2);
RANMATH_INLINE f32  rm_vec2_norm_one(vec2);
RANMATH_INLINE f32  rm_vec2_norm_inf(vec2);
RANMATH_INLINE vec2 rm_vec2_add(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_adds(vec2, f32);
RANMATH_INLINE vec2 rm_vec2_sub(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_subs(vec2, f32);
RANMATH_INLINE vec2 rm_vec2_mul(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_scale(vec2, f32);
RANMATH_INLINE vec2 rm_vec2_scale_as(vec2, f32);
RANMATH_INLINE vec2 rm_vec2_scale_aniso(vec2, f32, f32);
RANMATH_INLINE vec2 rm_vec2_div(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_divs(vec2, f32);
RANMATH_INLINE vec2 rm_vec2_negate(vec2);
RANMATH_INLINE vec2 rm_vec2_normalize(vec2);
RANMATH_INLINE vec2 rm_vec2_rotate(vec2, f32);
RANMATH_INLINE f32  rm_vec2_distance2(vec2, vec2);
RANMATH_INLINE f32  rm_vec2_distance(vec2, vec2);
RANMATH_INLINE vec2 rm_vec2_clamp(vec2, f32, f32);
RANMATH_INLINE vec2 rm_vec2_wrap(vec2, f32, f32);
RANMATH_INLINE vec2 rm_vec2_center(vec2, vec2);

RANMATH_INLINE vec3 rm_vec3_copy(vec3);
RANMATH_INLINE vec2 rm_vec3_copy2(vec3);
RANMATH_INLINE vec3 rm_vec3_abs(vec3);
RANMATH_INLINE f32  rm_vec3_max(vec3);
RANMATH_INLINE f32  rm_vec3_min(vec3);
RANMATH_INLINE vec3 rm_vec3_maxv(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_minv(vec3, vec3);
RANMATH_INLINE f32  rm_vec3_hadd(vec3);
RANMATH_INLINE vec3 rm_vec3_zero(void);
RANMATH_INLINE vec3 rm_vec3_one(void);
RANMATH_INLINE vec3 rm_vec3_set(f32, f32, f32);
RANMATH_INLINE vec3 rm_vec3_fill(f32);
RANMATH_INLINE vec3 rm_make_vec3(vec2, f32);
RANMATH_INLINE f32  rm_vec3_dot(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_cross(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_crossn(vec3, vec3);
RANMATH_INLINE f32  rm_vec3_norm2(vec3);
RANMATH_INLINE f32  rm_vec3_norm(vec3);
RANMATH_INLINE f32  rm_vec3_norm_one(vec3);
RANMATH_INLINE f32  rm_vec3_norm_inf(vec3);
RANMATH_INLINE vec3 rm_vec3_add(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_adds(vec3, f32);
RANMATH_INLINE vec3 rm_vec3_sub(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_subs(vec3, f32);
RANMATH_INLINE vec3 rm_vec3_mul(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_scale(vec3, f32);
RANMATH_INLINE vec3 rm_vec3_scale_as(vec3, f32);
RANMATH_INLINE vec3 rm_vec3_scale_aniso(vec3, f32, f32, f32);
RANMATH_INLINE vec3 rm_vec3_div(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_divs(vec3, f32);
RANMATH_INLINE vec3 rm_vec3_negate(vec3);
RANMATH_INLINE vec3 rm_vec3_normalize(vec3);
RANMATH_INLINE vec3 rm_vec3_rotate(vec3, f32, vec3);
RANMATH_INLINE f32  rm_vec3_distance2(vec3, vec3);
RANMATH_INLINE f32  rm_vec3_distance(vec3, vec3);
RANMATH_INLINE vec3 rm_vec3_clamp(vec3, f32, f32);
RANMATH_INLINE vec3 rm_vec3_wrap(vec3, f32, f32);
RANMATH_INLINE vec3 rm_vec3_center(vec3, vec3);

RANMATH_INLINE vec4 rm_vec4_copy(vec4);
RANMATH_INLINE vec3 rm_vec4_copy3(vec4);
RANMATH_INLINE vec4 rm_vec4_abs(vec4);
RANMATH_INLINE f32  rm_vec4_max(vec4);
RANMATH_INLINE f32  rm_vec4_min(vec4);
RANMATH_INLINE vec4 rm_vec4_maxv(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_minv(vec4, vec4);
RANMATH_INLINE f32  rm_vec4_hadd(vec4);
RANMATH_INLINE vec4 rm_vec4_zero(void);
RANMATH_INLINE vec4 rm_vec4_one(void);
RANMATH_INLINE vec4 rm_vec4_set(f32, f32, f32, f32);
RANMATH_INLINE vec4 rm_vec4_fill(f32);
RANMATH_INLINE vec4 rm_make_vec4(vec3, f32);
RANMATH_INLINE f32  rm_vec4_dot(vec4, vec4);
RANMATH_INLINE f32  rm_vec4_norm2(vec4);
RANMATH_INLINE f32  rm_vec4_norm(vec4);
RANMATH_INLINE f32  rm_vec4_norm_one(vec4);
RANMATH_INLINE f32  rm_vec4_norm_inf(vec4);
RANMATH_INLINE vec4 rm_vec4_add(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_adds(vec4, f32);
RANMATH_INLINE vec4 rm_vec4_sub(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_subs(vec4, f32);
RANMATH_INLINE vec4 rm_vec4_mul(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_scale(vec4, f32);
RANMATH_INLINE vec4 rm_vec4_scale_as(vec4, f32);
RANMATH_INLINE vec4 rm_vec4_div(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_divs(vec4, f32);
RANMATH_INLINE vec4 rm_vec4_negate(vec4);
RANMATH_INLINE vec4 rm_vec4_normalize(vec4);
RANMATH_INLINE f32  rm_vec4_distance2(vec4, vec4);
RANMATH_INLINE f32  rm_vec4_distance(vec4, vec4);
RANMATH_INLINE vec4 rm_vec4_clamp(vec4, f32, f32);
RANMATH_INLINE vec4 rm_vec4_wrap(vec4, f32, f32);
RANMATH_INLINE vec4 rm_vec4_center(vec4, vec4);

RANMATH_INLINE mat2 rm_mat2_copy(mat2);
RANMATH_INLINE mat2 rm_mat2_identity(void);
RANMATH_INLINE void rm_mat2_identity_array(mat2 *, size_t);
RANMATH_INLINE mat2 rm_mat2_zero(void);
RANMATH_INLINE mat2 rm_mat2_mul(mat2, mat2);
RANMATH_INLINE mat2 rm_mat2_transpose(mat2);
RANMATH_INLINE vec2 rm_mat2_mulv(mat2, vec2);
RANMATH_INLINE f32  rm_mat2_trace(mat2);
RANMATH_INLINE mat2 rm_mat2_scale(mat2, f32);
RANMATH_INLINE f32  rm_mat2_det(mat2);
RANMATH_INLINE mat2 rm_mat2_inv(mat2);
RANMATH_INLINE void rm_mat2_swap_col(mat2, u32, u32);
RANMATH_INLINE void rm_mat2_swap_row(mat2, u32, u32);
RANMATH_INLINE f32  rm_mat2_rmc(vec2, mat2, vec2);

RANMATH_INLINE mat3 rm_mat3_copy(mat3);
RANMATH_INLINE mat3 rm_mat3_identity(void);
RANMATH_INLINE void rm_mat3_identity_array(mat3 *, size_t);
RANMATH_INLINE mat3 rm_mat3_zero(void);
RANMATH_INLINE mat3 rm_mat3_mul(mat3, mat3);
RANMATH_INLINE mat3 rm_mat3_transpose(mat3);
RANMATH_INLINE vec3 rm_mat3_mulv(mat3, vec3);
RANMATH_INLINE f32  rm_mat3_trace(mat3);
RANMATH_INLINE mat3 rm_mat3_scale(mat3, f32);
RANMATH_INLINE f32  rm_mat3_det(mat3);
RANMATH_INLINE mat3 rm_mat3_inv(mat3);
RANMATH_INLINE void rm_mat3_swap_col(mat3, u32, u32);
RANMATH_INLINE void rm_mat3_swap_row(mat3, u32, u32);
RANMATH_INLINE f32  rm_mat3_rmc(vec3, mat3, vec3);

RANMATH_INLINE mat4 rm_mat4_copy(mat4);
RANMATH_INLINE mat4 rm_mat4_identity(void);
RANMATH_INLINE void rm_mat4_identity_array(mat4 *, size_t);
RANMATH_INLINE mat4 rm_mat4_zero(void);
RANMATH_INLINE mat3 rm_mat4_pick3(mat4);
RANMATH_INLINE mat3 rm_mat4_pick3t(mat4);
RANMATH_INLINE void rm_mat4_ins3(mat3, mat4);
RANMATH_INLINE mat4 rm_mat4_mul(mat4, mat4);
RANMATH_INLINE vec4 rm_mat4_mulv(mat4, vec4);
RANMATH_INLINE vec3 rm_mat4_mulv3(mat4, vec3, f32);
RANMATH_INLINE f32  rm_mat4_trace(mat4);
RANMATH_INLINE f32  rm_mat4_trace3(mat4);
RANMATH_INLINE mat4 rm_mat4_transpose(mat4);
RANMATH_INLINE mat4 rm_mat4_translate(f32, f32, f32);
RANMATH_INLINE mat4 rm_mat4_scale(mat4, f32);
RANMATH_INLINE mat4 rm_mat4_scale_aniso(mat4, f32, f32, f32);
RANMATH_INLINE f32  rm_mat4_det(mat4);
RANMATH_INLINE mat4 rm_mat4_inv(mat4);
RANMATH_INLINE void rm_mat4_swap_col(mat4, u32, u32);
RANMATH_INLINE void rm_mat4_swap_row(mat4, u32, u32);
RANMATH_INLINE f32  rm_mat4_rmc(vec4, mat4, vec4);
RANMATH_INLINE mat4 rm_mat4_ortho(f32, f32, f32, f32, f32, f32);
#endif /* RANMATH_H */

#ifdef RANMATH_IMPLEMENTATION
#if RANMATH_SSE_ENABLE
#define rmm_load(v) _mm_load_ps(RM_VEC_CVT(v))
#define rmm_store(v, a) _mm_store_ps(RM_VEC_CVT(v), a)
#define rmm_set(x, y, z, w) _mm_set_ps(w, z, y, x)
#define rmm_set1(x) _mm_set_ps1(x)
RANMATH_INLINE f32 rmm_hadd(__m128 x) {
    return x[0] + x[1] + x[2] + x[3];
}
RANMATH_INLINE __m128 rmm_hadd4(__m128 a, __m128 b, __m128 c, __m128 d) {
    /* [a0+a2 c0+c2 a1+a3 c1+c3 */
    __m128 s1 = _mm_add_ps(_mm_unpacklo_ps(a,c),_mm_unpackhi_ps(a,c));
    /* [b0+b2 d0+d2 b1+b3 d1+d3 */
    __m128 s2 = _mm_add_ps(_mm_unpacklo_ps(b,d),_mm_unpackhi_ps(b,d));
    /* [a0+a2 b0+b2 c0+c2 d0+d2]+
    [a1+a3 b1+b3 c1+c3 d1+d3] */
    return _mm_add_ps(_mm_unpacklo_ps(s1,s2),_mm_unpackhi_ps(s1,s2));
}
#endif /* RANMATH_SSE_ENABLE */

#define RANMATH_ABS(x) ((x < 0) ? -x : x)
#define RANMATH_MIN(a, b) ((a < b) ? a : b)
#define RANMATH_MAX(a, b) ((a > b) ? a : b)
#define RANMATH_CLAMP(val, min, max) (RANMATH_MIN(RANMATH_MAX(val, min), max))
#define RANMATH_POW2(x) (x * x)

#define RM_VEC2_FILL(x) (vec2){x, x}
#define RM_VEC3_FILL(x) (vec3){x, x, x}
#define RM_VEC4_FILL(x) (vec4){x, x, x}

#define RM_MAT2_IDENTITY (mat2){{    \
{1, 0},                              \
{0, 1},                              \
}}
#define RM_MAT2_FILL(x) (mat2){{    \
RM_VEC2_FILL(x),                    \
RM_VEC2_FILL(x),                    \
}}
#define RM_MAT3_IDENTITY (mat3){{    \
{1, 0, 0},                           \
{0, 1, 0},                           \
{0, 0, 1},                           \
}}
#define RM_MAT3_FILL(x) (mat3){{    \
RM_VEC3_FILL(x),                    \
RM_VEC3_FILL(x),                    \
RM_VEC3_FILL(x),                    \
}}
#define RM_MAT4_IDENTITY (mat4){{    \
{1, 0, 0, 0},                        \
{0, 1, 0, 0},                        \
{0, 0, 1, 0},                        \
{0, 0, 0, 1},                        \
}}
#define RM_MAT4_FILL(x) (mat4){{    \
RM_VEC4_FILL(x),                    \
RM_VEC4_FILL(x),                    \
RM_VEC4_FILL(x),                    \
RM_VEC4_FILL(x),                    \
}}

RANMATH_INLINE i32 rm_facti(i32 x) {
    if (x < 0) return -1;

    i32 i, d;

    d = 1;
    for (i = 1; i <= x; ++i) {
        d *= i;
    }

    return d;
}
RANMATH_INLINE i64 rm_factl(i64 x) {
    if (x < 0) return -1;

    i64 i, d;

    d = 1;
    for (i = 1; i <= x; ++i) {
        d *= i;
    }

    return d;
}
RANMATH_INLINE i32 rm_powi(i32 x, i32 p) {
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
RANMATH_INLINE i64 rm_powl(i64 x, i64 p) {
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
RANMATH_INLINE i32 rm_pow2i(i32 x) {
    return RANMATH_POW2(x);
}
RANMATH_INLINE i64 rm_pow2l(i64 x) {
    return RANMATH_POW2(x);
}
RANMATH_INLINE f32 rm_pow2f(f32 x) {
    return RANMATH_POW2(x);
}
RANMATH_INLINE f64 rm_pow2d(f64 x) {
    return RANMATH_POW2(x);
}
RANMATH_INLINE f32 rm_rsqrtf(f32 x) {
    f32 xh;
    RM_F32_CVT c = {x};

    xh = 0.5 * x;

    c.i = 0x5F375A86 - (c.i >> 1);

    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));
    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));
    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));

    return c.f;
}
RANMATH_INLINE f64 rm_rsqrtd(f64 x) {
    f64 xh;
    RM_F64_CVT c = {x};

    xh = 0.5 * x;

    c.i = 0x5FE6EB50C7B537A9 - (c.i >> 1);

    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));
    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));
    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));
    c.f *= 1.5 - (xh * RANMATH_POW2(c.f));

    return c.f;
}
RANMATH_INLINE f32 rm_sqrtf(f32 x) {
    return x * rm_rsqrtf(x);
}
RANMATH_INLINE f64 rm_sqrtd(f64 x) {
    return x * rm_rsqrtd(x);
}
RANMATH_INLINE i32 rm_absi(i32 x) {
    return RANMATH_ABS(x);
}
RANMATH_INLINE i64 rm_absl(i64 x) {
    return RANMATH_ABS(x);
}
RANMATH_INLINE f32 rm_absf(f32 x) {
    return RANMATH_ABS(x);
}
RANMATH_INLINE f64 rm_absd(f64 x) {
    return RANMATH_ABS(x);
}
RANMATH_INLINE i32 rm_mini(i32 a, i32 b) {
    return RANMATH_MIN(a, b);
}
RANMATH_INLINE i64 rm_minl(i64 a, i64 b) {
    return RANMATH_MIN(a, b);
}
RANMATH_INLINE f32 rm_minf(f32 a, f32 b) {
    return RANMATH_MIN(a, b);
}
RANMATH_INLINE f64 rm_mind(f64 a, f64 b) {
    return RANMATH_MIN(a, b);
}
RANMATH_INLINE i32 rm_maxi(i32 a, i32 b) {
    return RANMATH_MAX(a, b);
}
RANMATH_INLINE i64 rm_maxl(i64 a, i64 b) {
    return RANMATH_MAX(a,b);
}
RANMATH_INLINE f32 rm_maxf(f32 a, f32 b) {
    return RANMATH_MAX(a, b);
}
RANMATH_INLINE f64 rm_maxd(f64 a, f64 b) {
    return RANMATH_MAX(a, b);
}
RANMATH_INLINE i32 rm_clampi(i32 val, i32 minval, i32 maxval) {
    return RANMATH_CLAMP(val, minval, maxval);
}
RANMATH_INLINE i64 rm_clampl(i64 val, i64 minval, i64 maxval) {
    return RANMATH_CLAMP(val, minval, maxval);
}
RANMATH_INLINE f32 rm_clampf(f32 val, f32 minval, f32 maxval) {
    return RANMATH_CLAMP(val, minval, maxval);
}
RANMATH_INLINE f64 rm_clampd(f64 val, f64 minval, f64 maxval) {
    return RANMATH_CLAMP(val, minval, maxval);
}
RANMATH_INLINE f32 rm_truncf(f32 x) {
    return (i32)x;
}
RANMATH_INLINE f64 rm_truncd(f64 x) {
    return (i64)x;
}
RANMATH_INLINE f32 rm_modf(f32 a, f32 b) {
    return a - rm_truncf(a / b) * b;
}
RANMATH_INLINE f64 rm_modd(f64 a, f64 b) {
    return a - rm_truncd(a / b) * b;
}
RANMATH_INLINE f32 rm_floorf(f32 x) {
    if (x == 0) return x;
    i32 inx;

    inx = (i32)x -1;

    return (x < 0) ? (inx == 0 ? -0.0 : inx) : (i32)x;
}
RANMATH_INLINE f64 rm_floord(f64 x) {
    if (x == 0) return x;
    i64 inx;

    inx = (i64)x -1;

    return (x < 0) ? (inx == 0 ? -0.0 : inx) : (i64)x;
}
RANMATH_INLINE f32 rm_ceilf(f32 x) {
    if (x == 0) return x;
    i32 ix;

    ix = (i32)x;

    return (x < 0) ? (ix == 0 ? -0.0 : ix) : (i32)x + 1;
}
RANMATH_INLINE f64 rm_ceild(f64 x) {
    if (x == 0) return x;
    i64 ix;

    ix = (i64)x;

    return (x < 0) ? (ix == 0 ? -0.0 : ix) : (i64)x + 1;
}
RANMATH_INLINE f32 rm_roundf(f32 x) {
    bool c1, c2;

    c1 = (rm_absf(x) - rm_absi((i32)x)) < 0.5;
    c2 = x < 0;

    return (c1) ? ((c2) ? rm_ceilf(x) : rm_floorf(x)) : ((c2) ? rm_floorf(x) : rm_ceilf(x));
}
RANMATH_INLINE f64 rm_roundd(f64 x) {
    bool c1, c2;

    c1 = (rm_absd(x) - rm_absl((i64)x)) < 0.5;
    c2 = x < 0;

    return (c1) ? ((c2) ? rm_ceild(x) : rm_floord(x)) : ((c2) ? rm_floord(x) : rm_ceild(x));
}
RANMATH_INLINE f32 rm_wrap_maxf(f32 val, f32 maxval) {
    return rm_modf(maxval + rm_modf(val, maxval), maxval);
}
RANMATH_INLINE f64 rm_wrap_maxd(f64 val, f64 maxval) {
    return rm_modd(maxval + rm_modd(val, maxval), maxval);
}
RANMATH_INLINE f32 rm_wrapf(f32 val, f32 minval, f32 maxval) {
    f32 tmaxval;

    tmaxval = maxval - minval;

    return minval + rm_modf(tmaxval + rm_modf(val - minval, tmaxval), tmaxval);
}
RANMATH_INLINE f64 rm_wrapd(f64 val, f64 minval, f64 maxval) {
    f64 tmaxval;

    tmaxval = maxval - minval;

    return minval + rm_modd(tmaxval + rm_modd(val - minval, tmaxval), tmaxval);
}
RANMATH_INLINE f32 rm_cosf(f32 x) {
    f32 i, i2, i4;
    f64 a, b, c, d, val, val2;

    i = RM_PI_2 - rm_absd(rm_wrap_maxd(x, RM_2PI) - RM_PI);
    i2 = rm_pow2f(i);
    i4 = rm_pow2f(i2);

    a = -0.132995644812022330410032839099700470577487194965079816065230286;
    b = 0.0032172781382535624048708288689972016965839213439467243797038973;
    c = 0.0336709157304375144254000370104015622020879871979042486728981326;
    d = 0.0004962828018660570906955733487210649504998482691550479603258607;

    val = 1 + a * i2 + b * i4;
    val2 = 1 / (1 + c * i2 + d * i4);

    return (f32)-i * val * val2;
}
RANMATH_INLINE f64 rm_cosd(f64 x) {
    f64 i, i2, i4, a, b, c, d, val, val2;

    i = RM_PI_2 - rm_absd(rm_wrap_maxd(x, RM_2PI) - RM_PI);
    i2 = rm_pow2d(i);
    i4 = rm_pow2d(i2);

    a = -0.132995644812022330410032839099700470577487194965079816065230286;
    b = 0.0032172781382535624048708288689972016965839213439467243797038973;
    c = 0.0336709157304375144254000370104015622020879871979042486728981326;
    d = 0.0004962828018660570906955733487210649504998482691550479603258607;

    val = 1 + a * i2 + b * i4;
    val2 = 1 / (1 + c * i2 + d * i4);

    return -i * val * val2;
}
RANMATH_INLINE f32 rm_sinf(f32 x) {
    return -rm_cosf(x + RM_PI_2);
}
RANMATH_INLINE f64 rm_sind(f64 x) {
    return -rm_cosd(x + RM_PI_2);
}
RANMATH_INLINE f32 rm_tanf(f32 x) {
    return rm_sinf(x) / rm_cosf(x);
}
RANMATH_INLINE f64 rm_tand(f64 x) {
    return rm_sind(x) / rm_cosd(x);
}
RANMATH_INLINE f32 rm_cotf(f32 x) {
    return rm_cosf(x) / rm_sinf(x);
}
RANMATH_INLINE f64 rm_cotd(f64 x) {
    return rm_cosd(x) / rm_sind(x);
}
RANMATH_INLINE f32 rm_secf(f32 x) {
    return 1 / rm_cosf(x);
}
RANMATH_INLINE f64 rm_secd(f64 x) {
    return 1 / rm_cosd(x);
}
RANMATH_INLINE f32 rm_cscf(f32 x) {
    return 1 / rm_sinf(x);
}
RANMATH_INLINE f64 rm_cscd(f64 x) {
    return 1 / rm_sind(x);
}
RANMATH_INLINE f32 rm_rad2degf(f32 x) {
    return RM_MAKE_DEG * x;
}
RANMATH_INLINE f64 rm_rad2degd(f64 x) {
    return RM_MAKE_DEG * x;
}
RANMATH_INLINE f32 rm_deg2radf(f32 x) {
    return RM_MAKE_RAD * x;
}
RANMATH_INLINE f64 rm_deg2radd(f64 x) {
    return RM_MAKE_RAD * x;
}


RANMATH_INLINE vec2 rm_vec2_copy(vec2 v) {
    return v;
}
RANMATH_INLINE vec2 rm_vec2_abs(vec2 v) {
    return (vec2){rm_absf(v.x), rm_absf(v.y)};
}
RANMATH_INLINE f32 rm_vec2_max(vec2 v) {
    return rm_maxf(v.x, v.y);
}
RANMATH_INLINE f32 rm_vec2_min(vec2 v) {
    return rm_minf(v.x, v.y);
}
RANMATH_INLINE vec2 rm_vec2_maxv(vec2 a, vec2 b) {
    return (vec2){rm_maxf(a.x, b.x), rm_maxf(a.y, b.y)};
}
RANMATH_INLINE vec2 rm_vec2_minv(vec2 a, vec2 b) {
    return (vec2){rm_minf(a.x, b.x), rm_minf(a.y, b.y)};
}
RANMATH_INLINE f32 rm_vec2_hadd(vec2 v) {
    return v.x + v.y;
}
RANMATH_INLINE vec2 rm_vec2_zero(void) {
    return RM_VEC2_FILL(0);
}
RANMATH_INLINE vec2 rm_vec2_one(void) {
    return RM_VEC2_FILL(1);
}
RANMATH_INLINE vec2 rm_vec2_set(f32 x, f32 y) {
    return (vec2){x, y};
}
RANMATH_INLINE vec2 rm_vec2_fill(f32 x) {
    return RM_VEC2_FILL(x);
}
RANMATH_INLINE f32 rm_vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}
RANMATH_INLINE f32 rm_vec2_cross(vec2 a, vec2 b) {
    return a.x * b.y - b.x * a.y;
}
RANMATH_INLINE f32 rm_vec2_norm2(vec2 v) {
    return rm_vec2_dot(v, v);
}
RANMATH_INLINE f32 rm_vec2_norm(vec2 v) {
    return rm_sqrtf(rm_vec2_norm2(v));
}
RANMATH_INLINE f32 rm_vec2_norm_one(vec2 v) {
    return rm_vec2_hadd(rm_vec2_abs(v));
}
RANMATH_INLINE f32 rm_vec2_norm_inf(vec2 v) {
    return rm_vec2_max(rm_vec2_abs(v));
}
RANMATH_INLINE vec2 rm_vec2_add(vec2 a, vec2 b) {
    return (vec2){a.x + b.x, a.y + b.y};
}
RANMATH_INLINE vec2 rm_vec2_adds(vec2 v, f32 s) {
    return (vec2){v.x + s, v.y + s};
}
RANMATH_INLINE vec2 rm_vec2_sub(vec2 a, vec2 b) {
    return (vec2){a.x - b.x, a.y - b.y};
}
RANMATH_INLINE vec2 rm_vec2_subs(vec2 v, f32 s) {
    return (vec2){v.x - s, v.y - s};
}
RANMATH_INLINE vec2 rm_vec2_mul(vec2 a, vec2 b) {
    return (vec2){a.x * b.x, a.y * b.y};
}
RANMATH_INLINE vec2 rm_vec2_scale(vec2 v, f32 s) {
    return (vec2){v.x * s, v.y * s};
}
RANMATH_INLINE vec2 rm_vec2_scale_as(vec2 v, f32 s) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (norm == 0) ? rm_vec2_zero() : rm_vec2_scale(v, s / norm);
}
RANMATH_INLINE vec2 rm_vec2_scale_aniso(vec2 v, f32 x, f32 y) {
    return (vec2){v.x * x, v.y * y};
}
RANMATH_INLINE vec2 rm_vec2_div(vec2 a, vec2 b) {
    return (vec2){a.x / b.x, a.y / b.y};
}
RANMATH_INLINE vec2 rm_vec2_divs(vec2 v, f32 s) {
    return (vec2){v.x / s, v.y / s};
}
RANMATH_INLINE vec2 rm_vec2_negate(vec2 v) {
    return (vec2){-v.x, -v.y};
}
RANMATH_INLINE vec2 rm_vec2_normalize(vec2 v) {
    f32 norm;

    norm = rm_vec2_norm(v);

    return (norm == 0) ? rm_vec2_zero() : rm_vec2_scale(v, 1 / norm);
}
RANMATH_INLINE vec2 rm_vec2_rotate(vec2 v, f32 a) {
    f32 c, s;

    c = rm_cosf(a);
    s = rm_sinf(a);

    return (vec2){c * v.x - s * v.y, s * v.x + c * v.y};
}
RANMATH_INLINE f32 rm_vec2_distance2(vec2 a, vec2 b) {
    return rm_pow2f(b.x - a.x) + rm_pow2f(b.y - a.y);
}
RANMATH_INLINE f32 rm_vec2_distance(vec2 a, vec2 b) {
    return rm_sqrtf(rm_vec2_distance2(a, b));
}
RANMATH_INLINE vec2 rm_vec2_clamp(vec2 v, f32 minval, f32 maxval) {
    return (vec2){rm_clampf(v.x, minval, maxval), rm_clampf(v.y, minval, maxval)};
}
RANMATH_INLINE vec2 rm_vec2_wrap(vec2 v, f32 minval, f32 maxval) {
    return (vec2){rm_wrapf(v.x, minval, maxval), rm_wrapf(v.y, minval, maxval)};
}
RANMATH_INLINE vec2 rm_vec2_center(vec2 a, vec2 b) {
    return rm_vec2_scale(rm_vec2_add(a, b), 0.5);
}

RANMATH_INLINE vec3 rm_vec3_copy(vec3 v) {
    return v;
}
RANMATH_INLINE vec2 rm_vec3_copy2(vec3 v) {
    return (vec2){v.x, v.y};
}
RANMATH_INLINE vec3 rm_vec3_abs(vec3 v) {
    return (vec3){rm_absf(v.x), rm_absf(v.y), rm_absf(v.z)};
}
RANMATH_INLINE f32 rm_vec3_max(vec3 v) {
    return rm_maxf(rm_maxf(v.x, v.y), v.z);
}
RANMATH_INLINE f32 rm_vec3_min(vec3 v) {
    return rm_minf(rm_minf(v.x, v.y), v.z);
}
RANMATH_INLINE vec3 rm_vec3_maxv(vec3 a, vec3 b) {
    return (vec3){rm_maxf(a.x, b.x), rm_maxf(a.y, b.y), rm_maxf(a.z, b.z)};
}
RANMATH_INLINE vec3 rm_vec3_minv(vec3 a, vec3 b) {
    return (vec3){rm_minf(a.x, b.x), rm_minf(a.y, b.y), rm_minf(a.z, b.z)};
}
RANMATH_INLINE f32 rm_vec3_hadd(vec3 v) {
    return v.x + v.y + v.z;
}
RANMATH_INLINE vec3 rm_vec3_zero(void) {
    return RM_VEC3_FILL(0);
}
RANMATH_INLINE vec3 rm_vec3_one(void) {
    return RM_VEC3_FILL(1);
}
RANMATH_INLINE vec3 rm_vec3_set(f32 x, f32 y, f32 z) {
    return (vec3){x, y, z};
}
RANMATH_INLINE vec3 rm_vec3_fill(f32 x) {
    return RM_VEC3_FILL(x);
}
RANMATH_INLINE vec3 rm_make_vec3(vec2 v, f32 last) {
    return (vec3){v.x, v.y, last};
}
RANMATH_INLINE f32 rm_vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
RANMATH_INLINE vec3 rm_vec3_cross(vec3 a, vec3 b) {
    return (vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
RANMATH_INLINE vec3 rm_vec3_crossn(vec3 a, vec3 b) {
    return rm_vec3_normalize(rm_vec3_cross(a, b));
}
RANMATH_INLINE f32 rm_vec3_norm2(vec3 v) {
    return rm_vec3_dot(v, v);
}
RANMATH_INLINE f32 rm_vec3_norm(vec3 v) {
    return rm_sqrtf(rm_vec3_norm2(v));
}
RANMATH_INLINE f32 rm_vec3_norm_one(vec3 v) {
    return rm_vec3_hadd(rm_vec3_abs(v));
}
RANMATH_INLINE f32 rm_vec3_norm_inf(vec3 v) {
    return rm_vec3_max(rm_vec3_abs(v));
}
RANMATH_INLINE vec3 rm_vec3_add(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}
RANMATH_INLINE vec3 rm_vec3_adds(vec3 v, f32 s) {
    return (vec3){v.x + s, v.y + s, v.z + s};
}
RANMATH_INLINE vec3 rm_vec3_sub(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}
RANMATH_INLINE vec3 rm_vec3_subs(vec3 v, f32 s) {
    return (vec3){v.x - s, v.y - s, v.z - s};
}
RANMATH_INLINE vec3 rm_vec3_mul(vec3 a, vec3 b) {
    return (vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}
RANMATH_INLINE vec3 rm_vec3_scale(vec3 v, f32 s) {
    return (vec3){v.x * s, v.y * s, v.z * s};
}
RANMATH_INLINE vec3 rm_vec3_scale_as(vec3 v, f32 s) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (norm == 0) ? rm_vec3_zero() : rm_vec3_scale(v, s / norm);
}
RANMATH_INLINE vec3 rm_vec3_scale_aniso(vec3 v, f32 x, f32 y, f32 z) {
    return (vec3){v.x * x, v.y * y, v.z * z};
}
RANMATH_INLINE vec3 rm_vec3_div(vec3 a, vec3 b) {
    return (vec3){a.x / b.x, a.y / b.y, a.z / b.z};
}
RANMATH_INLINE vec3 rm_vec3_divs(vec3 v, f32 s) {
    return (vec3){v.x / s, v.y / s, v.z / s};
}
RANMATH_INLINE vec3 rm_vec3_negate(vec3 v) {
    return (vec3){-v.x, -v.y, -v.z};
}
RANMATH_INLINE vec3 rm_vec3_normalize(vec3 v) {
    f32 norm;

    norm = rm_vec3_norm(v);

    return (norm == 0) ? rm_vec3_zero() : rm_vec3_scale(v, 1 / norm);
}
RANMATH_INLINE vec3 rm_vec3_rotate(vec3 v, f32 a, vec3 axis) {
    f32 c, s;
    vec3 v1, v2, k;

    c = rm_cosf(a);
    s = rm_sinf(a);

    k = rm_vec3_normalize(axis);

    v1 = rm_vec3_scale(v, c);

    v2 = rm_vec3_cross(k, v);
    v2 = rm_vec3_scale(v2, s);

    v1 = rm_vec3_add(v1, v2);

    v2 = rm_vec3_scale(k, rm_vec3_dot(k, v) * (1.0f - c));

    return rm_vec3_add(v1, v2);
}
RANMATH_INLINE f32 rm_vec3_distance2(vec3 a, vec3 b) {
    return rm_pow2f(a.x - b.x) + rm_pow2f(a.y - b.y) + rm_pow2f(a.z - b.z);
}
RANMATH_INLINE f32 rm_vec3_distance(vec3 a, vec3 b) {
    return rm_sqrtf(rm_vec3_distance2(a, b));
}
RANMATH_INLINE vec3 rm_vec3_clamp(vec3 v, f32 minval, f32 maxval) {
    return (vec3){
        rm_clampf(v.x, minval, maxval),
        rm_clampf(v.y, minval, maxval),
        rm_clampf(v.z, minval, maxval)
    };
}
RANMATH_INLINE vec3 rm_vec3_wrap(vec3 v, f32 minval, f32 maxval) {
    return (vec3){
        rm_wrapf(v.x, minval, maxval),
        rm_wrapf(v.y, minval, maxval),
        rm_wrapf(v.z, minval, maxval)
    };
}
RANMATH_INLINE vec3 rm_vec3_center(vec3 a, vec3 b) {
    return rm_vec3_scale(rm_vec3_add(a, b), 0.5);
}

RANMATH_INLINE vec4 rm_vec4_copy(vec4 v) {
    return v;
}
RANMATH_INLINE vec3 rm_vec4_copy3(vec4 v) {
    return (vec3){v.x, v.y, v.z};
}
RANMATH_INLINE vec4 rm_vec4_abs(vec4 v) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, mask;
    vec4 dest;

    mask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
    x0 = rmm_load(v);
    x0 = _mm_and_ps(mask, x0);

    rmm_store(dest, x0);

    return dest;
    #else
    return (vec4){rm_absf(v.x), rm_absf(v.y), rm_absf(v.z), rm_absf(v.w)};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE f32 rm_vec4_max(vec4 v) {
    return rm_maxf(rm_maxf(rm_maxf(v.x, v.y), v.z), v.w);
}
RANMATH_INLINE f32 rm_vec4_min(vec4 v) {
    return rm_minf(rm_minf(rm_minf(v.x, v.y), v.z), v.w);
}
RANMATH_INLINE vec4 rm_vec4_maxv(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0,x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_max_ps(x0, x1));

    return dest;
    #else
    return (vec4){
        rm_maxf(a.x, b.x),
        rm_maxf(a.y, b.y),
        rm_maxf(a.z, b.z),
        rm_maxf(a.w, b.w)
    };
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_minv(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0,x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_min_ps(x0, x1));

    return dest;
    #else
    return (vec4){
        rm_minf(a.x, b.x),
        rm_minf(a.y, b.y),
        rm_minf(a.z, b.z),
        rm_minf(a.w, b.w)
    };
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE f32 rm_vec4_hadd(vec4 v) {
    #if RANMATH_SSE_ENABLE
    return rmm_hadd(rmm_load(v));
    #else
    return v.x + v.y + v.z + v.w;
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_zero(void) {
    #if RANMATH_SSE_ENABLE
    vec4 dest;

    rmm_store(dest, _mm_setzero_ps());

    return dest;
    #else
    return RM_VEC4_FILL(0);
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_one(void) {
    #if RANMATH_SSE_ENABLE
    vec4 dest;

    rmm_store(dest, rmm_set1(1));

    return dest;
    #else
    return RM_VEC4_FILL(1);
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_set(f32 x, f32 y, f32 z, f32 w) {
    #if RANMATH_SSE_ENABLE
    vec4 dest;

    rmm_store(dest, rmm_set(x, y, z, w));

    return dest;
    #else
    return (vec4){x, y, z, w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_fill(f32 x) {
    #if RANMATH_SSE_ENABLE
    vec4 dest;

    rmm_store(dest, rmm_set1(x));

    return dest;
    #else
    return RM_VEC4_FILL(x);
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_make_vec4(vec3 v, f32 last) {
    #if RANMATH_SSE_ENABLE
    __m128 x0;
    vec4 dest;

    x0 = rmm_load(v);
    x0[3] = last;

    rmm_store(dest, x0);

    return dest;
    #else
    return (vec4){v.x, v.y, v.z, last};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE f32 rm_vec4_dot(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    return rmm_hadd(_mm_mul_ps(x0, x1));
    #else
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE f32 rm_vec4_norm2(vec4 v) {
    return rm_vec4_dot(v, v);
}
RANMATH_INLINE f32 rm_vec4_norm(vec4 v) {
    return rm_sqrtf(rm_vec4_norm2(v));
}
RANMATH_INLINE f32 rm_vec4_norm_one(vec4 v) {
    return rm_vec4_hadd(rm_vec4_abs(v));
}
RANMATH_INLINE f32 rm_vec4_norm_inf(vec4 v) {
    return rm_vec4_max(rm_vec4_abs(v));
}
RANMATH_INLINE vec4 rm_vec4_add(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_add_ps(x0, x1));

    return dest;
    #else
    return (vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_adds(vec4 v, f32 s) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set1(s);

    rmm_store(dest, _mm_add_ps(x0, x1));

    return dest;
    #else
    return (vec4){v.x + s, v.y + s, v.z + s, v.w + s};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_sub(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_sub_ps(x0, x1));

    return dest;
    #else
    return (vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_subs(vec4 v, f32 s) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set1(s);

    rmm_store(dest, _mm_sub_ps(x0, x1));

    return dest;
    #else
    return (vec4){v.x - s, v.y - s, v.z - s, v.w - s};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_mul(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_mul_ps(x0, x1));

    return dest;
    #else
    return (vec4){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_scale(vec4 v, f32 s) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set1(s);

    rmm_store(dest, _mm_mul_ps(x0, x1));

    return dest;
    #else
    return (vec4){v.x * s, v.y * s, v.z * s, v.w * s};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_scale_as(vec4 v, f32 s) {
    f32 norm;
    norm = rm_vec4_norm(v);
    return (norm == 0) ? rm_vec4_zero() : rm_vec4_scale(v, s / norm);
}
RANMATH_INLINE vec4 rm_vec4_scale_aniso(vec4 v, f32 x, f32 y, f32 z, f32 w) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set(x, y, z, w);

    rmm_store(dest, _mm_mul_ps(x0, x1));

    return dest;
    #else
    return (vec4){v.x * x, v.y * y, v.z * z, v.w * w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_div(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);

    rmm_store(dest, _mm_div_ps(x0, x1));

    return dest;
    #else
    return (vec4){a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_divs(vec4 v, f32 s) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set1(s);

    rmm_store(dest, _mm_div_ps(x0, x1));

    return dest;
    #else
    return (vec4){v.x / s, v.y / s, v.z / s, v.w / s};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_negate(vec4 v) {
    #if RANMATH_SSE_ENABLE
    __m128 x0;
    vec4 dest;

    x0 = rmm_load(v);

    rmm_store(dest, _mm_mul_ps(x0, rmm_set1(-1)));

    return dest;
    #else
    return (vec4){-v.x, -v.y, -v.z, -v.w};
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE vec4 rm_vec4_normalize(vec4 v) {
    f32 norm;
    norm = rm_vec4_norm(v);

    return (norm == 0) ? rm_vec4_zero() : rm_vec4_scale(v, 1 / norm);
}
RANMATH_INLINE f32 rm_vec4_distance2(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1, x2;

    x0 = rmm_load(a);
    x1 = rmm_load(b);
    x2 = _mm_mul_ps(x0, x1);
    x2 = _mm_mul_ps(x2, x2);

    return rmm_hadd(x2);
    #else
    return rm_pow2f(a.x - b.x) + rm_pow2f(a.y - b.y) + rm_pow2f(a.z - b.z) + rm_pow2f(a.w - b.w);
    #endif /* RANMATH_SSE_ENABLE */
}
RANMATH_INLINE f32 rm_vec4_distance(vec4 a, vec4 b) {
    return rm_sqrtf(rm_vec4_distance2(a, b));
}
RANMATH_INLINE vec4 rm_vec4_clamp(vec4 v, f32 minval, f32 maxval) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1, x2;
    vec4 dest;

    x0 = rmm_load(v);
    x1 = rmm_set1(minval);
    x2 = rmm_set1(maxval);

    rmm_store(dest, _mm_min_ps(_mm_max_ps(x0, x1), x2));

    return dest;
    #else
    return (vec4){
        rm_clampf(v.x, minval, maxval),
        rm_clampf(v.y, minval, maxval),
        rm_clampf(v.z, minval, maxval),
        rm_clampf(v.w, minval, maxval)
    };
    #endif /* RANMATH_SSE_ENABLE */
}
/* TODO: SIMD representation? */
RANMATH_INLINE vec4 rm_vec4_wrap(vec4 v, f32 minval, f32 maxval) {
    return (vec4){
        rm_wrapf(v.x , minval, maxval),
        rm_wrapf(v.y , minval, maxval),
        rm_wrapf(v.z , minval, maxval),
        rm_wrapf(v.w , minval, maxval),
    };
}
RANMATH_INLINE vec4 rm_vec4_center(vec4 a, vec4 b) {
    #if RANMATH_SSE_ENABLE
    __m128 x0, x1, x2;
    vec4 dest;

    x0 = rmm_load(a);
    x1 = rmm_load(b);
    x2 = rmm_set1(0.5);

    rmm_store(dest, _mm_mul_ps(_mm_sub_ps(x0, x1), x2));

    return dest;
    #else
    return rm_vec4_scale(rm_vec4_add(a, b), 0.5);
    #endif /* RANMATH_SSE_ENABLE */
}

RANMATH_INLINE mat2 rm_mat2_copy(mat2 m) {
    return m;
}
RANMATH_INLINE mat2 rm_mat2_identity(void) {
    return RM_MAT2_IDENTITY;
}
RANMATH_INLINE void rm_mat2_identity_array(mat2 *m, size_t count) {
    size_t i;

    for (i = 0; i < count; i++) {
        m[i] = rm_mat2_identity();
    }
}
RANMATH_INLINE mat2 rm_mat2_zero(void) {
    return RM_MAT2_FILL(0);
}
RANMATH_INLINE mat2 rm_mat2_mul(mat2 a, mat2 b) {
    vec2 c1, c2;
    mat2 dest;

    c1 = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[0].x), rm_vec2_scale(a.cols[1], b.cols[0].y));
    c2 = rm_vec2_add(rm_vec2_scale(a.cols[0], b.cols[1].x), rm_vec2_scale(a.cols[1], b.cols[1].y));

    dest = (mat2){{c1, c2}};

    return dest;
}
RANMATH_INLINE vec2 rm_mat2_mulv(mat2 m, vec2 v) {
    return rm_vec2_add(rm_vec2_scale(m.cols[0], v.x), rm_vec2_scale(m.cols[1], v.y));
}
RANMATH_INLINE mat2 rm_mat2_transpose(mat2 m) {
    vec2 c1, c2;
    mat2 dest;

    c1 = (vec2){m.cols[0].x, m.cols[1].x};
    c2 = (vec2){m.cols[0].y, m.cols[1].y};

    dest = (mat2){{c1, c2}};

    return dest;
}
RANMATH_INLINE f32 rm_mat2_trace(mat2 m) {
    return m.cols[0].x + m.cols[1].y;
}
RANMATH_INLINE mat2 rm_mat2_scale(mat2 m, f32 s) {
    vec2 c1, c2;
    mat2 dest;

    c1 = rm_vec2_scale(m.cols[0], s);
    c2 = rm_vec2_scale(m.cols[1], s);

    dest = (mat2){{c1, c2}};

    return dest;
}
RANMATH_INLINE f32 rm_mat2_det(mat2 m) {
    return m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x;
}
RANMATH_INLINE mat2 rm_mat2_inv(mat2 m) {
    f32 det;
    vec2 c1, c2, tmp;
    mat2 dest;

    det = (f32)1 / m.cols[0].x * m.cols[1].y - m.cols[0].y * m.cols[1].x;

    c1 = rm_vec2_scale(m.cols[0], det);
    c2 = rm_vec2_scale(m.cols[1], det);

    tmp = rm_vec2_copy(c1);

    c1 = (vec2){c2.y, -tmp.y};
    c2 = (vec2){-c2.x, tmp.x};

    dest = (mat2){{c1, c2}};

    return dest;
}
RANMATH_INLINE void rm_mat2_swap_col(mat2 m, u32 col1, u32 col2) {
    vec2 tmp;

    tmp = rm_vec2_copy(m.cols[col1]);

    m.cols[col1] = rm_vec2_copy(m.cols[col2]);
    m.cols[col2] = rm_vec2_copy(tmp);
}
RANMATH_INLINE void rm_mat2_swap_row(mat2 m, u32 row1, u32 row2) {
    f32 a, b;
    RM_MAT2_CVT c;

    c.m = rm_mat2_copy(m);

    a = c.gl[0][row1];
    b = c.gl[1][row1];

    c.gl[0][row1] = c.gl[0][row2];
    c.gl[1][row1] = c.gl[1][row2];

    c.gl[0][row2] = a;
    c.gl[1][row2] = b;

    m = rm_mat2_copy(c.m);
}
RANMATH_INLINE f32 rm_mat2_rmc(vec2 r, mat2 m, vec2 c) {
    return rm_vec2_dot(r, rm_mat2_mulv(m, c));
}

RANMATH_INLINE mat3 rm_mat3_copy(mat3 m) {
    return m;
}
RANMATH_INLINE mat3 rm_mat3_identity(void) {
    return RM_MAT3_IDENTITY;
}
RANMATH_INLINE void rm_mat3_identity_array(mat3 *m, size_t count) {
    size_t i;

    for (i = 0; i < count; i++) {
        m[i] = rm_mat3_identity();
    }
}
RANMATH_INLINE mat3 rm_mat3_zero(void) {
    return RM_MAT3_FILL(0);
}
RANMATH_INLINE mat3 rm_mat3_mul(mat3 a, mat3 b) {
    vec3 c1, c2, c3, tmp;
    mat3 dest;

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[0].x), rm_vec3_scale(a.cols[1], b.cols[0].y));
    c1 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[0].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[1].x), rm_vec3_scale(a.cols[1], b.cols[1].y));
    c1 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[1].z));

    tmp = rm_vec3_add(rm_vec3_scale(a.cols[0], b.cols[2].x), rm_vec3_scale(a.cols[1], b.cols[2].y));
    c3 = rm_vec3_add(tmp, rm_vec3_scale(a.cols[2], b.cols[2].z));

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RANMATH_INLINE vec3 rm_mat3_mulv(mat3 m, vec3 v) {
    vec3 tmp;
    tmp = rm_vec3_add(rm_vec3_scale(m.cols[0], v.x), rm_vec3_scale(m.cols[1], v.y));

    return rm_vec3_add(tmp, rm_vec3_scale(m.cols[2], v.z));
}
RANMATH_INLINE mat3 rm_mat3_transpose(mat3 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = (vec3){m.cols[0].x, m.cols[1].x, m.cols[2].x};
    c2 = (vec3){m.cols[0].y, m.cols[1].y, m.cols[2].y};
    c3 = (vec3){m.cols[0].z, m.cols[1].z, m.cols[2].z};

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RANMATH_INLINE f32 rm_mat3_trace(mat3 m) {
    return m.cols[0].x + m.cols[1].y + m.cols[2].z;
}
RANMATH_INLINE mat3 rm_mat3_scale(mat3 m, f32 s) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = rm_vec3_scale(m.cols[0], s);
    c2 = rm_vec3_scale(m.cols[1], s);
    c3 = rm_vec3_scale(m.cols[2], s);

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RANMATH_INLINE f32 rm_mat3_det(mat3 m) {
    vec3 tmp;

    tmp.x = m.cols[0].x * (m.cols[1].y * m.cols[2].z - m.cols[1].z * m.cols[2].y);
    tmp.y = -(m.cols[1].x * (m.cols[0].y * m.cols[2].z - m.cols[0].z * m.cols[2].y));
    tmp.z = m.cols[2].x * (m.cols[0].y * m.cols[1].z - m.cols[0].z * m.cols[1].y);

    return rm_vec3_hadd(tmp);
}
RANMATH_INLINE mat3 rm_mat3_inv(mat3 m) {
    float det;
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

    det = (f32)1 / rm_vec3_hadd(tmp);

    return rm_mat3_scale(dest, det);
}

RANMATH_INLINE void rm_mat3_swap_col(mat3 m, u32 col1, u32 col2) {
    vec3 tmp;

    tmp = rm_vec3_copy(m.cols[col1]);

    m.cols[col1] = rm_vec3_copy(m.cols[col2]);
    m.cols[col2] = rm_vec3_copy(tmp);
}
RANMATH_INLINE void rm_mat3_swap_row(mat3 m, u32 row1, u32 row2) {
    vec3 tmp;
    RM_MAT3_CVT c;

    c.m = rm_mat3_copy(m);

    tmp.x = c.gl[0][row1];
    tmp.y = c.gl[1][row1];
    tmp.z = c.gl[2][row1];

    c.gl[0][row1] = c.gl[0][row2];
    c.gl[1][row1] = c.gl[1][row2];
    c.gl[2][row1] = c.gl[2][row2];

    c.gl[0][row2] = tmp.x;
    c.gl[1][row2] = tmp.y;
    c.gl[2][row2] = tmp.z;

    m = rm_mat3_copy(c.m);
}
RANMATH_INLINE f32 rm_mat3_rmc(vec3 r, mat3 m, vec3 c) {
    return rm_vec3_dot(r, rm_mat3_mulv(m, c));
}
RANMATH_INLINE mat4 rm_mat4_copy(mat4 m) {
    return m;
}
RANMATH_INLINE mat4 rm_mat4_identity(void) {
    return RM_MAT4_IDENTITY;
}
RANMATH_INLINE void rm_mat4_identity_array(mat4 *m, size_t count) {
    size_t i;

    for (i = 0; i < count; i++) {
        m[i] = rm_mat4_identity();
    }
}
RANMATH_INLINE mat4 rm_mat4_zero(void) {
    return RM_MAT4_FILL(0);
}
RANMATH_INLINE mat3 rm_mat4_pick3(mat4 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = rm_vec4_copy3(m.cols[0]);
    c2 = rm_vec4_copy3(m.cols[1]);
    c3 = rm_vec4_copy3(m.cols[2]);

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RANMATH_INLINE mat3 rm_mat4_pick3t(mat4 m) {
    vec3 c1, c2, c3;
    mat3 dest;

    c1 = (vec3){m.cols[0].x, m.cols[1].x, m.cols[2].x};
    c2 = (vec3){m.cols[0].y, m.cols[1].y, m.cols[2].y};
    c3 = (vec3){m.cols[0].z, m.cols[1].z, m.cols[2].z};

    dest = (mat3){{c1, c2, c3}};

    return dest;
}
RANMATH_INLINE void rm_mat4_ins3(mat3 a, mat4 b) {
    b.cols[0] = rm_make_vec4(a.cols[0], b.cols[0].w);
    b.cols[1] = rm_make_vec4(a.cols[1], b.cols[1].w);
    b.cols[2] = rm_make_vec4(a.cols[2], b.cols[2].w);
}
RANMATH_INLINE mat4 rm_mat4_mul(mat4 a, mat4 b) {
    vec4 c1, c2, c3, c4, tmp1, tmp2;
    mat4 dest;

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

    return dest;
}
RANMATH_INLINE vec4 rm_mat4_mulv(mat4 m, vec4 v) {
    vec4 tmp1, tmp2, dest;

    tmp1 = rm_vec4_add(rm_vec4_scale(m.cols[0], v.x), rm_vec4_scale(m.cols[1], v.y));
    tmp2 = rm_vec4_add(rm_vec4_scale(m.cols[2], v.z), rm_vec4_scale(m.cols[3], v.w));

    dest = rm_vec4_add(tmp1, tmp2);

    return dest;
}
RANMATH_INLINE vec3 rm_mat4_mulv3(mat4 m, vec3 v, f32 last) {
    vec4 dest;

    dest = rm_make_vec4(v, last);
    dest = rm_mat4_mulv(m, dest);

    return rm_vec4_copy3(dest);
}
RANMATH_INLINE f32 rm_mat4_trace(mat4 m) {
    return m.cols[0].x + m.cols[1].y + m.cols[2].z + m.cols[3].w;
}
RANMATH_INLINE f32 rm_mat4_trace3(mat4 m) {
    return m.cols[0].x + m.cols[1].y + m.cols[2].z;
}
RANMATH_INLINE mat4 rm_mat4_transpose(mat4 m) {
    vec4 c1, c2, c3, c4;
    mat4 dest;

    c1 = (vec4){m.cols[0].x, m.cols[1].x, m.cols[2].x, m.cols[3].x};
    c2 = (vec4){m.cols[0].y, m.cols[1].y, m.cols[2].y, m.cols[3].y};
    c3 = (vec4){m.cols[0].z, m.cols[1].z, m.cols[2].z, m.cols[3].z};
    c4 = (vec4){m.cols[0].w, m.cols[1].w, m.cols[2].w, m.cols[3].w};

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}
RANMATH_INLINE mat4 rm_mat4_translate(f32 x, f32 y, f32 z) {
    mat4 dest;

    dest = rm_mat4_identity();
    dest.cols[3].x = x;
    dest.cols[3].y = y;
    dest.cols[3].z = z;

    return dest;
}
RANMATH_INLINE mat4 rm_mat4_scale(mat4 m, f32 s) {
    vec4 c1, c2, c3, c4;
    mat4 dest;

    c1 = rm_vec4_scale(m.cols[0], s);
    c2 = rm_vec4_scale(m.cols[1], s);
    c3 = rm_vec4_scale(m.cols[2], s);
    c4 = rm_vec4_scale(m.cols[3], s);

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}
RANMATH_INLINE mat4 rm_mat4_scale_aniso(mat4 m, f32 x, f32 y, f32 z) {
    vec4 c1, c2, c3, c4;
    mat4 dest;

    c1 = rm_vec4_scale(m.cols[0], x);
    c2 = rm_vec4_scale(m.cols[1], y);
    c3 = rm_vec4_scale(m.cols[2], z);
    c4 = rm_vec4_copy(m.cols[3]);

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}
RANMATH_INLINE f32 rm_mat4_det(mat4 m) {
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
RANMATH_INLINE mat4 rm_mat4_inv(mat4 m) {
    f32 det;
    f32 t[6];
    vec4 v;
    mat4 dest;

    t[0] = m.cols[2].z * m.cols[3].w - m.cols[3].z * m.cols[2].w;
    t[1] = m.cols[2].y * m.cols[3].w - m.cols[3].y * m.cols[2].w;
    t[2] = m.cols[2].y * m.cols[3].z - m.cols[3].y * m.cols[2].z;
    t[3] = m.cols[2].x * m.cols[3].w - m.cols[3].x * m.cols[2].w;
    t[4] = m.cols[2].x * m.cols[3].z - m.cols[3].x * m.cols[2].z;
    t[5] = m.cols[2].x * m.cols[3].y - m.cols[3].x * m.cols[2].y;

    dest.cols[0].x = m.cols[1].y * t[0] - m.cols[1].z * t[1] + m.cols[1].w * t[2];
    dest.cols[1].x = -(m.cols[1].x * t[0] - m.cols[1].z * t[3] + m.cols[1].w * t[4]);
    dest.cols[2].x = m.cols[1].x * t[1] - m.cols[1].y * t[3] + m.cols[1].w * t[5];
    dest.cols[3].x = -(m.cols[1].x * t[2] - m.cols[1].y * t[4] + m.cols[1].z * t[5]);

    dest.cols[0].y = -(m.cols[0].y * t[0] - m.cols[0].z * t[1] + m.cols[0].w * t[2]);
    dest.cols[1].y = m.cols[0].x * t[0] - m.cols[0].z * t[3] + m.cols[0].w * t[4];
    dest.cols[2].y = -(m.cols[0].x * t[1] - m.cols[0].y * t[3] + m.cols[0].w * t[5]);
    dest.cols[3].y = m.cols[0].x * t[2] - m.cols[0].y * t[4] + m.cols[0].z * t[5];

    t[0] = m.cols[1].z * m.cols[3].w - m.cols[3].z * m.cols[1].w;
    t[1] = m.cols[1].y * m.cols[3].w - m.cols[3].y * m.cols[1].w;
    t[2] = m.cols[1].y * m.cols[3].z - m.cols[3].y * m.cols[1].z;
    t[3] = m.cols[1].x * m.cols[3].w - m.cols[3].x * m.cols[1].w;
    t[4] = m.cols[1].x * m.cols[3].z - m.cols[3].x * m.cols[1].z;
    t[5] = m.cols[1].x * m.cols[3].y - m.cols[3].x * m.cols[1].y;

    dest.cols[0].z = m.cols[0].y * t[0] - m.cols[0].z * t[1] + m.cols[0].w * t[2];
    dest.cols[1].z = -(m.cols[0].x * t[0] - m.cols[0].z * t[3] + m.cols[0].w * t[4]);
    dest.cols[2].z = m.cols[0].x * t[1] - m.cols[0].y * t[3] + m.cols[0].w * t[5];
    dest.cols[3].z = -(m.cols[0].x * t[2] - m.cols[0].y * t[4] + m.cols[0].z * t[5]);

    t[0] = m.cols[1].z * m.cols[2].w - m.cols[2].z * m.cols[1].w;
    t[1] = m.cols[1].y * m.cols[2].w - m.cols[2].y * m.cols[1].w;
    t[2] = m.cols[1].y * m.cols[2].z - m.cols[2].y * m.cols[1].z;
    t[3] = m.cols[1].x * m.cols[2].w - m.cols[2].x * m.cols[1].w;
    t[4] = m.cols[1].x * m.cols[2].z - m.cols[2].x * m.cols[1].z;
    t[5] = m.cols[1].x * m.cols[2].y - m.cols[2].x * m.cols[1].y;

    dest.cols[0].w = -(m.cols[0].y * t[0] - m.cols[0].z * t[1] + m.cols[0].w * t[2]);
    dest.cols[1].w = m.cols[0].x * t[0] - m.cols[0].z * t[3] + m.cols[0].w * t[4];
    dest.cols[2].w = -(m.cols[0].x * t[1] - m.cols[0].y * t[3] + m.cols[0].w * t[5]);
    dest.cols[3].w = m.cols[0].x * t[2] - m.cols[0].y * t[4] + m.cols[0].z * t[5];

    v = rm_vec4_scale_aniso(m.cols[0], dest.cols[0].x, dest.cols[1].x, dest.cols[2].x, dest.cols[3].x);

    det = (f32)1 / rm_vec4_hadd(v);

    return rm_mat4_scale(dest, det);
}
RANMATH_INLINE void rm_mat4_swap_col(mat4 m, u32 col1, u32 col2) {
    vec4 tmp;

    tmp = rm_vec4_copy(m.cols[col1]);

    m.cols[col1] = rm_vec4_copy(m.cols[col2]);
    m.cols[col2] = rm_vec4_copy(tmp);
}
RANMATH_INLINE void rm_mat4_swap_row(mat4 m, u32 row1, u32 row2) {
    vec4 tmp;
    RM_MAT4_CVT c;

    c.m = rm_mat4_copy(m);

    tmp.x = c.gl[0][row1];
    tmp.y = c.gl[1][row1];
    tmp.z = c.gl[2][row1];
    tmp.w = c.gl[3][row1];

    c.gl[0][row1] = c.gl[0][row2];
    c.gl[1][row1] = c.gl[1][row2];
    c.gl[2][row1] = c.gl[2][row2];
    c.gl[3][row1] = c.gl[3][row2];

    c.gl[0][row2] = tmp.x;
    c.gl[1][row2] = tmp.y;
    c.gl[2][row2] = tmp.z;
    c.gl[3][row2] = tmp.w;

    m = rm_mat4_copy(c.m);
}
RANMATH_INLINE f32 rm_mat4_rmc(vec4 r, mat4 m, vec4 c) {
    return rm_vec4_dot(r, rm_mat4_mulv(m, c));
}
RANMATH_INLINE mat4 rm_mat4_ortho(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f) {
    f32 rl, tb, fn;
    vec4 c1, c2, c3, c4;
    mat4 dest;

    rl = r - l;
    tb = t - b;
    fn = f - n;

    c1 = (vec4){2 / (rl), 0, 0, 0};
    c2 = (vec4){0, 2 / (tb), 0, 0};
    c3 = (vec4){0, 0, -2 / (fn), 0};
    c4 = (vec4){-(r + l) / (rl), -(t + b) / (tb), -(f + n) / (fn), 1};

    dest = (mat4){{c1, c2, c3, c4}};

    return dest;
}

#endif /* RANMATH_IMPLEMENTATION */
