/* MIT License
*
* Copyright (c) 2022 Ransel117
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

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define bool _Bool
#define true 1
#define false 0

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float_t  f32;
typedef double_t f64;

typedef f32 vec2[2];
typedef f32 vec3[3];
typedef f32 vec4[3];

#if defined(__GNUC__) /* GCC-compatible compiler */
#define RANMATH_INLINE static inline __attribute((always_inline))
#elif defined(_MSC_VER) /* Microsoft */
#define RANMATH_INLINE static __forceinline
#else /* Some other */
#define RANMATH_INLINE static inline
#endif

#define RM_FLT_EPSILON 1.19209290E-7F
#define RM_PI          3.14159265359F
#define RM_MAKE_RAD    1.74532925E-2F
#define RM_MAKE_DEG    5.72957795E1F

/* PS: the s and v functions requires dest to be initialized, such as rm_vec2_adds or rm_vec2_divv.
* The others do not need dest to be initialized.
*/

/* Declarations */
/* Integer */
RANMATH_INLINE i32 rm_pow2i(i32 x);

/* Floating point */
RANMATH_INLINE f32 rm_pow2f(f32 x);
RANMATH_INLINE f32 rm_powf(f32  x, f32 p);
RANMATH_INLINE f32 rm_sqrtf(f32 x);
RANMATH_INLINE f32 rm_cosf(f32  a);
RANMATH_INLINE f32 rm_sinf(f32  a);
RANMATH_INLINE f32 rm_acosf(f32 a);
RANMATH_INLINE f32 rm_asinf(f32 a);
RANMATH_INLINE f32 rm_cosf_deg(f32  a);
RANMATH_INLINE f32 rm_sinf_deg(f32  a);
RANMATH_INLINE f32 rm_acosf_deg(f32 a);
RANMATH_INLINE f32 rm_asinf_deg(f32 a);
RANMATH_INLINE f32 rm_absf(f32 x);
RANMATH_INLINE f32 rm_maxf(f32 a, f32 b);
RANMATH_INLINE f32 rm_minf(f32 a, f32 b);
RANMATH_INLINE f32 rm_clampf(f32 val, f32 minval, f32 maxval);

/* Vec2: */
RANMATH_INLINE void rm_vec2_print(const vec2 v);                                /* Prints x and y values of v */
RANMATH_INLINE void rm_vec2_copy(const vec2 v, vec2 dest);                      /* Copies the values of v into dest */
RANMATH_INLINE void rm_vec2_set(const f32 x, const f32 y, vec2 dest);           /* Sets x and y values of dest */
RANMATH_INLINE void rm_vec2_fill(const f32 val, vec2 dest);                     /* Fills dest with val */
RANMATH_INLINE void rm_vec2_zero(vec2 v);                                       /* Fills dest with zero */
RANMATH_INLINE void rm_vec2_one(vec2 v);                                        /* Files dest with one */
RANMATH_INLINE f32  rm_vec2_dot(const vec2 a, const vec2 b);                    /* Returns dot product of a and b */
RANMATH_INLINE f32  rm_vec2_norm2(const vec2 v);                                /* Returns squared norm (magnitude) of v (L2 squared or (L²)², could be called L4 or L⁴) */
RANMATH_INLINE f32  rm_vec2_norm(const vec2 v);                                 /* Returns norm (magnitude) of v (L2 or L²) */
RANMATH_INLINE f32  rm_vec2_norm_one(const vec2 v);                             /* Returns norm (magnitude) of v (L1 or L¹) */
RANMATH_INLINE f32  rm_vec2_norm_inf(const vec2 v);                             /* Returns norm (magnitude) of v (infinity norm or max norm) */
RANMATH_INLINE f32  rm_vec2_cross(const vec2 a, const vec2 b);                  /* Returns the cross product of a and b */
RANMATH_INLINE f32  rm_vec2_max(const vec2 v);
RANMATH_INLINE f32  rm_vec2_min(const vec2 v);
RANMATH_INLINE void rm_vec2_abs(const vec2 v, vec2 dest);
RANMATH_INLINE void rm_vec2_maxv(const vec2 a, const vec2 b, vec2 dest);
RANMATH_INLINE void rm_vec2_minv(const vec2 a, const vec2 b, vec2 dest);
RANMATH_INLINE void rm_vec2_clamp(const vec2 v, const f32 minval, const f32 maxval, vec2 dest);
/* Vector operations: */
/* Scalar on vector */
RANMATH_INLINE void rm_vec2_adds(const f32   s, vec2 dest);                     /* Adds s to dest */
RANMATH_INLINE void rm_vec2_subs(const f32   s, vec2 dest);                     /* Subtracts s from dest */
RANMATH_INLINE void rm_vec2_muls(const f32   s, vec2 dest);                     /* Multiplies dest with s */
RANMATH_INLINE void rm_vec2_divs(const f32   s, vec2 dest);                     /* Divides dest by s */
RANMATH_INLINE void rm_vec2_addss(const vec2 v, const f32 s, vec2 dest);        /* Adds s to v and stores it in dest */
RANMATH_INLINE void rm_vec2_subss(const vec2 v, const f32 s, vec2 dest);        /* Subtracts s from v and stores it in dest */
RANMATH_INLINE void rm_vec2_mulss(const vec2 v, const f32 s, vec2 dest);        /* Multiplies v with s and stores it in dest */
RANMATH_INLINE void rm_vec2_divss(const vec2 v, const f32 s, vec2 dest);        /* Divides v by s and stores it in dest */
RANMATH_INLINE void rm_vec2_adds_add(const vec2 v, const f32 s, vec2 dest);     /* Adds s to v and the sum to dest */
RANMATH_INLINE void rm_vec2_subs_add(const vec2 v, const f32 s, vec2 dest);     /* Subtracts s from v and adds the sum to dest */
RANMATH_INLINE void rm_vec2_muls_add(const vec2 v, const f32 s, vec2 dest);     /* Multiplies v with s and adds the product to dest */
RANMATH_INLINE void rm_vec2_divs_add(const vec2 v, const f32 s, vec2 dest);     /* Divides v by s and adds the quotient to dest */
RANMATH_INLINE void rm_vec2_adds_sub(const vec2 v, const f32 s, vec2 dest);     /* Adds s to v and subracts the sum from dest */
RANMATH_INLINE void rm_vec2_subs_sub(const vec2 v, const f32 s, vec2 dest);     /* Subtracts s from v and the difference from dest */
RANMATH_INLINE void rm_vec2_muls_sub(const vec2 v, const f32 s, vec2 dest);     /* Multiplies v with s and subtracts the difference from dest */
RANMATH_INLINE void rm_vec2_divs_sub(const vec2 v, const f32 s, vec2 dest);     /* Divides v by s and subtracts the quotient from dest */
RANMATH_INLINE void rm_vec2_adds_mul(const vec2 v, const f32 s, vec2 dest);     /* Adds s to v and multiplies dest with the sum */
RANMATH_INLINE void rm_vec2_subs_mul(const vec2 v, const f32 s, vec2 dest);     /* Subtracts s from v and multiplies dest with the difference */
RANMATH_INLINE void rm_vec2_muls_mul(const vec2 v, const f32 s, vec2 dest);     /* Multiplies v with s and dest with the product */
RANMATH_INLINE void rm_vec2_divs_mul(const vec2 v, const f32 s, vec2 dest);     /* Divides v by s and multiplies dest with the quotient */
RANMATH_INLINE void rm_vec2_adds_div(const vec2 v, const f32 s, vec2 dest);     /* Adds s to v and divides dest by the sum */
RANMATH_INLINE void rm_vec2_subs_div(const vec2 v, const f32 s, vec2 dest);     /* Subtracts s from v and divides dest by the difference */
RANMATH_INLINE void rm_vec2_muls_div(const vec2 v, const f32 s, vec2 dest);     /* Multiplies v with s and divides dest by the product */
RANMATH_INLINE void rm_vec2_divs_div(const vec2 v, const f32 s, vec2 dest);     /* Divides v by s and dest by the quotient */
/* Vector on vector */
RANMATH_INLINE void rm_vec2_addv(const vec2  v, vec2 dest);                     /* Adds v to dest */
RANMATH_INLINE void rm_vec2_subv(const vec2  v, vec2 dest);                     /* Subtracts v from dest */
RANMATH_INLINE void rm_vec2_mulv(const vec2  v, vec2 dest);                     /* Multiplies dest with v */
RANMATH_INLINE void rm_vec2_divv(const vec2  v, vec2 dest);                     /* Divides dest by v */
RANMATH_INLINE void rm_vec2_addsv(const vec2 a, const vec2 b, vec2 dest);       /* Adds b to a and stores it in dest */
RANMATH_INLINE void rm_vec2_subsv(const vec2 a, const vec2 b, vec2 dest);       /* Subtracts b from a and stores it in dest */
RANMATH_INLINE void rm_vec2_mulsv(const vec2 a, const vec2 b, vec2 dest);       /* Multiplies a with b and stores it in dest */
RANMATH_INLINE void rm_vec2_divsv(const vec2 a, const vec2 b, vec2 dest);       /* Divides a by b and stores it in dest */
RANMATH_INLINE void rm_vec2_addv_add(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and the sum to dest */
RANMATH_INLINE void rm_vec2_subv_add(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and adds the difference to dest */
RANMATH_INLINE void rm_vec2_mulv_add(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and adds the product to dest */
RANMATH_INLINE void rm_vec2_divv_add(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and adds the quotient to dest */

RANMATH_INLINE void rm_vec2_divv_add(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and adds the quotient to dest */
RANMATH_INLINE void rm_vec2_addv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and subtracts the sum from dest */
RANMATH_INLINE void rm_vec2_subv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and the difference from dest */
RANMATH_INLINE void rm_vec2_mulv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and subtracts the product from dest */
RANMATH_INLINE void rm_vec2_divv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and subracts the quotient from dest*/
RANMATH_INLINE void rm_vec2_addv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and multiplies dest with the sum */
RANMATH_INLINE void rm_vec2_subv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and multiplies dest with the difference */
RANMATH_INLINE void rm_vec2_mulv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and dest with the product */
RANMATH_INLINE void rm_vec2_divv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and multiplies dest with the quotient */
RANMATH_INLINE void rm_vec2_addv_div(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and divides dest by the sum */
RANMATH_INLINE void rm_vec2_subv_div(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and divides dest by the difference */
RANMATH_INLINE void rm_vec2_mulv_div(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and divides dest by the product */
RANMATH_INLINE void rm_vec2_divv_div(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and dest by the quotient */

RANMATH_INLINE void rm_vec2_negate_to(const vec2 v, vec2 dest);
RANMATH_INLINE void rm_vec2_negate(vec2 v);
RANMATH_INLINE void rm_vec2_normalize_to(const vec2 v, vec2 dest);
RANMATH_INLINE void rm_vec2_normalize(vec2 v);
RANMATH_INLINE f32  rm_vec2_distance2(const vec2 a, const vec2 b);
RANMATH_INLINE f32  rm_vec2_distance(const vec2 a, const vec2 b);
RANMATH_INLINE f32  rm_vec2_angle(const vec2 a, const vec2 b);
RANMATH_INLINE f32  rm_vec2_angle_deg(const vec2 a, const vec2 b);
RANMATH_INLINE void rm_vec2_rotate_origin(const vec2 v, const f32 a, vec2 dest);
RANMATH_INLINE void rm_vec2_rotate_point(const vec2 v, const vec2 point, const f32 a, vec2 dest);
RANMATH_INLINE void rm_vec2_rotate_origin_deg(const vec2 v, const f32 a, vec2 dest);
RANMATH_INLINE void rm_vec2_rotate_point_deg(const vec2 v, const vec2 point, const f32 a, vec2 dest);


/* Definitions */
/* Integer */
RANMATH_INLINE i32 rm_pow2i(i32 x) { return x* x; }
RANMATH_INLINE i32 rm_absi(i32  x) { return x < 0 ? -x : x; }
RANMATH_INLINE i32 rm_maxi(i32 a, i32 b) { return a > b ? a : b; }
RANMATH_INLINE i32 rm_mini(i32 a, i32 b) { return a < b ? a : b; }
/* Floating point */
RANMATH_INLINE f32 rm_pow2f(f32 x) { return x * x; }
RANMATH_INLINE f32 rm_powf(f32  x, f32 p) { return powf(x, p); } /* TODO: implement own pow */
RANMATH_INLINE f32 rm_sqrtf(f32 x) { return sqrtf(x); } /* TODO: implement own sqrt */
RANMATH_INLINE f32 rm_cosf(f32 a) { return cosf(a); }   /* TODO: implement own cos and inverse */
RANMATH_INLINE f32 rm_sinf(f32 a) { return sinf(a); }   /* TODO: implement own sin and inverse */
RANMATH_INLINE f32 rm_acosf(f32 a) { return acosf(a); }
RANMATH_INLINE f32 rm_asinf(f32 a) { return asinf(a); }
RANMATH_INLINE f32 rm_cosf_deg(f32 a) { return rm_cosf(RM_MAKE_RAD * a); }
RANMATH_INLINE f32 rm_sinf_deg(f32 a) { return rm_sinf(RM_MAKE_RAD * a); }
RANMATH_INLINE f32 rm_acosf_deg(f32 a) { return RM_MAKE_DEG * rm_acosf(a); }
RANMATH_INLINE f32 rm_asinf_deg(f32 a) { return RM_MAKE_DEG * rm_asinf(a); }
RANMATH_INLINE f32 rm_absf(f32 x) { return x < 0.0F ? -x : x; }
RANMATH_INLINE f32 rm_maxf(f32 a, f32 b) {
    return a > b ? a : b;

    /* Alt implementation */
    //return (a > b) * a + (b > a) * b;
}
RANMATH_INLINE f32 rm_minf(f32 a, f32 b) {
    return a < b ? a : b;

    /* Alt implementation */
    //return (a < b) * a + (b < a) * b;
}
RANMATH_INLINE f32 rm_clampf(f32 val, f32 minval, f32 maxval) { return rm_minf(rm_maxf(val,minval),maxval); }



/* Vec2: */
RANMATH_INLINE void rm_vec2_print(const vec2 v) { printf("<x: %f, y: %f>\n", v[0], v[1]); }
RANMATH_INLINE void rm_vec2_copy(const vec2 v, vec2 dest) {
    dest[0] = v[0];
    dest[1] = v[1];
}
RANMATH_INLINE void rm_vec2_set(const f32 x, const f32 y, vec2 dest) {
    dest[0] = x;
    dest[1] = y;
}
RANMATH_INLINE void rm_vec2_fill(const f32 val, vec2 dest) { dest[0] = dest[1] = val; }
RANMATH_INLINE void rm_vec2_zero(vec2 v) { v[0] = v[1] = 0.0F; }
RANMATH_INLINE void rm_vec2_one(vec2 v) { v[0] = v[1] = 1.0F; }
RANMATH_INLINE f32 rm_vec2_dot(const vec2 a, const vec2 b) { return a[0] * b[0] + a[1] * b[1]; }
RANMATH_INLINE f32 rm_vec2_norm2(const vec2 v) { return rm_vec2_dot(v, v); }
RANMATH_INLINE f32 rm_vec2_norm(const vec2 v) { return rm_sqrtf(rm_vec2_norm2(v)); }
RANMATH_INLINE f32 rm_vec2_norm_one(const vec2 v) { return rm_absf(v[0]) + rm_absf(v[1]); }
RANMATH_INLINE f32 rm_vec2_norm_inf(const vec2 v) { return rm_maxf(rm_absf(v[0]), rm_absf(v[1])); }
RANMATH_INLINE f32 rm_vec2_cross(const vec2 a, const vec2 b) { return a[0] * b[0] - a[1] * b[1]; }
RANMATH_INLINE f32 rm_vec2_max(const vec2 v) { return rm_maxf(v[0], v[1]); }
RANMATH_INLINE f32 rm_vec2_min(const vec2 v) { return rm_minf(v[0], v[1]); }
RANMATH_INLINE void rm_vec2_abs(const vec2 v, vec2 dest) {
    dest[0] = rm_absf(v[0]);
    dest[1] = rm_absf(v[1]);
}
RANMATH_INLINE void rm_vec2_maxv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = rm_maxf(a[0], b[0]);
    dest[1] = rm_maxf(a[1], b[1]);
}
RANMATH_INLINE void rm_vec2_minv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = rm_minf(a[0], b[0]);
    dest[1] = rm_minf(a[1], b[1]);
}
RANMATH_INLINE void rm_vec2_clamp(const vec2 v, const f32 minval, const f32 maxval, vec2 dest) {
    dest[0] = rm_clampf(v[0], minval, maxval);
    dest[1] = rm_clampf(v[1], minval, maxval);
}

/* Vector operations: */
/* Scalar on vector */
RANMATH_INLINE void rm_vec2_adds(const f32 s, vec2 dest) {
    dest[0] += s;
    dest[1] += s;
}
RANMATH_INLINE void rm_vec2_subs(const f32 s, vec2 dest) {
    dest[0] -= s;
    dest[1] -= s;
}
RANMATH_INLINE void rm_vec2_muls(const f32 s, vec2 dest) {
    dest[0] *= s;
    dest[1] *= s;
}
RANMATH_INLINE void rm_vec2_divs(const f32 s, vec2 dest) {
    dest[0] /= s;
    dest[1] /= s;
}
RANMATH_INLINE void rm_vec2_addss(const vec2 v, const f32 s, vec2 dest) {
    dest[0] = v[0] + s;
    dest[1] = v[1] + s;
}
RANMATH_INLINE void rm_vec2_subss(const vec2 v, const f32 s, vec2 dest) {
    dest[0] = v[0] - s;
    dest[1] = v[1] - s;
}
RANMATH_INLINE void rm_vec2_mulss(const vec2 v, const f32 s, vec2 dest) {
    dest[0] = v[0] * s;
    dest[1] = v[1] * s;
}
RANMATH_INLINE void rm_vec2_divss(const vec2 v, const f32 s, vec2 dest) {
    dest[0] = v[0] / s;
    dest[1] = v[1] / s;
}
RANMATH_INLINE void rm_vec2_adds_add(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subs_add(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_muls_add(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divs_add(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_adds_sub(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subs_sub(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_muls_sub(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divs_sub(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_adds_mul(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subs_mul(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_muls_mul(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divs_mul(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_adds_div(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subs_div(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_muls_div(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divs_div(const vec2 v, const f32 s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
/* Vector on vector */
RANMATH_INLINE void rm_vec2_addv(const vec2 v, vec2 dest) {
    dest[0] += v[0];
    dest[1] += v[1];
}
RANMATH_INLINE void rm_vec2_subv(const vec2 v, vec2 dest) {
    dest[0] -= v[0];
    dest[1] -= v[1];
}
RANMATH_INLINE void rm_vec2_mulv(const vec2 v, vec2 dest) {
    dest[0] *= v[0];
    dest[1] *= v[1];
}
RANMATH_INLINE void rm_vec2_divv(const vec2 v, vec2 dest) {
    dest[0] /= v[0];
    dest[1] /= v[1];
}
RANMATH_INLINE void rm_vec2_addsv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
}
RANMATH_INLINE void rm_vec2_subsv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
}
RANMATH_INLINE void rm_vec2_mulsv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
}
RANMATH_INLINE void rm_vec2_divsv(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] / b[0];
    dest[1] = a[1] / b[1];
}
RANMATH_INLINE void rm_vec2_addv_add(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subv_add(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_mulv_add(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divv_add(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_addv_sub(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subv_sub(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_mulv_sub(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divv_sub(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_addv_mul(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subv_mul(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_mulv_mul(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divv_mul(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_addv_div(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_subv_div(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_mulv_div(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
RANMATH_INLINE void rm_vec2_divv_div(const vec2 a, const vec2 b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}

RANMATH_INLINE void rm_vec2_negate_to(const vec2 v, vec2 dest) {
    dest[0] = -v[0];
    dest[1] = -v[1];
}
RANMATH_INLINE void rm_vec2_negate(vec2 v) {
    v[0] = -v[0];
    v[1] = -v[1];
}
RANMATH_INLINE void rm_vec2_normalize_to(const vec2 v, vec2 dest) {
    f32 norm = rm_vec2_norm(v);

    (rm_absf(norm) <= RM_FLT_EPSILON) ? rm_vec2_zero(dest) : rm_vec2_mulss(v, 1.0F / norm, dest);
}
RANMATH_INLINE void rm_vec2_normalize(vec2 v) {
    f32 norm = rm_vec2_norm(v);

    (rm_absf(norm) <= RM_FLT_EPSILON) ? rm_vec2_zero(v) : rm_vec2_muls(1.0F / norm, v);
}
RANMATH_INLINE f32 rm_vec2_distance2(const vec2 a, const vec2 b) { return rm_pow2f(a[0] - b[0]) + rm_pow2f(a[1] - b[1]); }
RANMATH_INLINE f32 rm_vec2_distance(const vec2 a, const vec2 b) { return rm_sqrtf(rm_vec2_distance2(a, b)); }
RANMATH_INLINE f32 rm_vec2_angle(const vec2 a, const vec2 b) {
    f32 dot  = rm_vec2_dot(a, b) / (rm_vec2_norm(a) * rm_vec2_norm(b));

    return (dot > 1.0F) ? 0.0F : (dot < -1.0F) ? RM_PI : rm_acosf(dot);
    /* Alt implementation */
    // bool lessn1 = dot < -1.0F;
    // return lessn1 * RM_PI + (dot < 1.0F && !lessn1) * rm_acosf(dot);
}
RANMATH_INLINE f32 rm_vec2_angle_deg(const vec2 a, const vec2 b) {
    f32 dot  = rm_vec2_dot(a, b) / (rm_vec2_norm(a) * rm_vec2_norm(b));

    return (dot > 1.0F) ? 0.0F : (dot < -1.0F) ? 180.0F : rm_acosf_deg(dot);
    /* Alt implementation */
    // bool lessn1 = dot < -1.0F;
    // return lessn1 * 180.0F + (dot < 1.0F && !lessn1) * rm_acosf_deg(dot);
}
RANMATH_INLINE void rm_vec2_rotate_origin(const vec2 v, const f32 a, vec2 dest) {
    f32 c = rm_cosf(a);
    f32 s = rm_sinf(a);

    dest[0] = v[0] * c - v[1] * s;
    dest[1] = v[0] * s + v[1] * c;
}
RANMATH_INLINE void rm_vec2_rotate_point(const vec2 v, const vec2 point, const f32 a, vec2 dest) {
    f32 c = rm_cosf(a);
    f32 s = rm_sinf(a);
    f32 ndotx = v[0] - point[0];
    f32 ndoty = v[1] - point[1];

    dest[0] = ndotx * c - ndoty * s + point[0];
    dest[1] = ndotx * s + ndoty * c + point[1];
}
RANMATH_INLINE void rm_vec2_rotate_origin_deg(const vec2 v, const f32 a, vec2 dest) {
    f32 c = rm_cosf_deg(a);
    f32 s = rm_sinf_deg(a);

    dest[0] = v[0] * c - v[1] * s;
    dest[1] = v[0] * s + v[1] * c;
}
RANMATH_INLINE void rm_vec2_rotate_point_deg(const vec2 v, const vec2 point, const f32 a, vec2 dest) {
    f32 c = rm_cosf_deg(a);
    f32 s = rm_sinf_deg(a);
    f32 ndotx = v[0] - point[0];
    f32 ndoty = v[1] - point[1];

    dest[0] = ndotx * c - ndoty * s + point[0];
    dest[1] = ndotx * s + ndoty * c + point[1];
}
RANMATH_INLINE void rm_vec2_center(const vec2 a, const vec2 b, vec2 dest) {
    rm_vec2_addsv(a, b, dest);
    rm_vec2_muls(0.5F,  dest);
}


#endif /* RANMATH_H */
