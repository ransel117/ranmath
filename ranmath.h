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
#define RM_MAKE_RAD    1.74532925E-2F
#define RM_MAKE_DEG    5.72957795E1F

/* Declarations */
RANMATH_INLINE void rm_vec2_print(const vec2 v);                                /* Prints x and y values of v */
RANMATH_INLINE void rm_vec2_set(const f32 x, const f32 y, vec2 dest);           /* Sets x and y values of dest */
RANMATH_INLINE void rm_vec2_fill(const f32 val, vec2 dest);                     /* Fills dest with val */
RANMATH_INLINE void rm_vec2_zero(vec2 v);                                       /* Fills dest with zero */
RANMATH_INLINE void rm_vec2_one(vec2 v);                                        /* Files dest with one */
RANMATH_INLINE f32  rm_vec2_dot(const vec2 a, const vec2 b);                    /* Returns dot product of a and b */
RANMATH_INLINE f32  rm_vec2_norm2(const vec2 v);                                /* Returns squared norm (magnitude) of v (L2 squared or (L²)²) */
RANMATH_INLINE f32  rm_vec2_norm(const vec2 v);                                 /* Returns norm (magnitude) of v (L2 or L²) */
RANMATH_INLINE f32  rm_vec2_norm_one(const vec2 v);                             /* Returns norm (magnitude) of v (L1 or L¹) */
RANMATH_INLINE f32  rm_vec2_inf(const vec2 v);                                  /* Returns norm (magnitude) of v (infinity norm or max norm) */
RANMATH_INLINE f32  rm_vec2_cross(const vec2 a, const vec2 b);                  /* Returns the cross product of a and b */
RANMATH_INLINE void rm_vec2_addv(const vec2 v, vec2 dest);                      /* Adds v to dest */
RANMATH_INLINE void rm_vec2_subv(const vec2 v, vec2 dest);                      /* Subtracts v from dest */
RANMATH_INLINE void rm_vec2_mulv(const vec2 v, vec2 dest);                      /* Multiplies dest with v */
RANMATH_INLINE void rm_vec2_divv(const vec2 v, vec2 dest);                      /* Divides dest by v */
RANMATH_INLINE void rm_vec2_adds(const f32  s, vec2 dest);                      /* Adds s to dest */
RANMATH_INLINE void rm_vec2_subs(const f32  s, vec2 dest);                      /* Subtracts s from dest */
RANMATH_INLINE void rm_vec2_muls(const f32  s, vec2 dest);                      /* Multiplies dest with s */
RANMATH_INLINE void rm_vec2_divs(const f32  s, vec2 dest);                      /* Divides dest by s */
RANMATH_INLINE void rm_vec2_addsv(const vec2 a, const vec2 b, vec2 dest);       /* Adds b to a and stores it in dest */
RANMATH_INLINE void rm_vec2_subsv(const vec2 a, const vec2 b, vec2 dest);       /* Subtracts b from a and stores it in dest */
RANMATH_INLINE void rm_vec2_mulsv(const vec2 a, const vec2 b, vec2 dest);       /* Multiplies a with b and stores it in dest */
RANMATH_INLINE void rm_vec2_divsv(const vec2 a, const vec2 b, vec2 dest);       /* Divides a by b and stores it in dest */
RANMATH_INLINE void rm_vec2_addss(const vec2 v, const f32  s, vec2 dest);       /* Adds s to v and stores it in dest */
RANMATH_INLINE void rm_vec2_subss(const vec2 v, const f32  s, vec2 dest);       /* Subtracts s from v and stores it in dest */
RANMATH_INLINE void rm_vec2_mulss(const vec2 v, const f32  s, vec2 dest);       /* Multiplies v with s and stores it in dest */
RANMATH_INLINE void rm_vec2_divss(const vec2 v, const f32  s, vec2 dest);       /* Divides v by s and stores it in dest */
RANMATH_INLINE void rm_vec2_addv_add(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and the sum to dest */
RANMATH_INLINE void rm_vec2_subv_add(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and adds the difference to dest */
RANMATH_INLINE void rm_vec2_mulv_add(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and adds the product to dest */
RANMATH_INLINE void rm_vec2_divv_add(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and adds the quotient to dest */
RANMATH_INLINE void rm_vec2_adds_add(const vec2 v, const f32  s, vec2 dest);    /* Adds s to v and the sum to dest */
RANMATH_INLINE void rm_vec2_subs_add(const vec2 v, const f32  s, vec2 dest);    /* Subtracts s from v and adds the sum to dest */
RANMATH_INLINE void rm_vec2_muls_add(const vec2 v, const f32  s, vec2 dest);    /* Multiplies v with s and adds the product to dest */
RANMATH_INLINE void rm_vec2_divs_add(const vec2 v, const f32  s, vec2 dest);    /* Divides v by s and adds the quotient to dest */
RANMATH_INLINE void rm_vec2_addv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and subtracts the sum from dest */
RANMATH_INLINE void rm_vec2_subv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and the difference from dest */
RANMATH_INLINE void rm_vec2_mulv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and subtracts the product from dest */
RANMATH_INLINE void rm_vec2_divv_sub(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and subracts the quotient from dest*/
RANMATH_INLINE void rm_vec2_adds_sub(const vec2 v, const f32  s, vec2 dest);    /* Adds s to v and subracts the sum from dest */
RANMATH_INLINE void rm_vec2_subs_sub(const vec2 v, const f32  s, vec2 dest);    /* Subtracts s from v and the difference from dest */
RANMATH_INLINE void rm_vec2_muls_sub(const vec2 v, const f32  s, vec2 dest);    /* Multiplies v with s and subtracts the difference from dest */
RANMATH_INLINE void rm_vec2_divs_sub(const vec2 v, const f32  s, vec2 dest);    /* Divides v by s and subtracts the quotient from dest */
RANMATH_INLINE void rm_vec2_addv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and multiplies dest with the sum */
RANMATH_INLINE void rm_vec2_subv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and multiplies dest with the difference */
RANMATH_INLINE void rm_vec2_mulv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and dest with the product */
RANMATH_INLINE void rm_vec2_divv_mul(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and multiplies dest with the quotient */
RANMATH_INLINE void rm_vec2_adds_mul(const vec2 v, const f32  s, vec2 dest);    /* Adds s to v and multiplies dest with the sum */
RANMATH_INLINE void rm_vec2_subs_mul(const vec2 v, const f32  s, vec2 dest);    /* Subtracts s from v and multiplies dest with the difference */
RANMATH_INLINE void rm_vec2_muls_mul(const vec2 v, const f32  s, vec2 dest);    /* Multiplies v with s and dest with the product */
RANMATH_INLINE void rm_vec2_divs_mul(const vec2 v, const f32  s, vec2 dest);    /* Divides v by s and multiplies dest with the quotient */
RANMATH_INLINE void rm_vec2_addv_div(const vec2 a, const vec2 b, vec2 dest);    /* Adds b to a and divides dest by the sum */
RANMATH_INLINE void rm_vec2_subv_div(const vec2 a, const vec2 b, vec2 dest);    /* Subtracts b from a and divides dest by the difference */
RANMATH_INLINE void rm_vec2_mulv_div(const vec2 a, const vec2 b, vec2 dest);    /* Multiplies a with b and divides dest by the product */
RANMATH_INLINE void rm_vec2_divv_div(const vec2 a, const vec2 b, vec2 dest);    /* Divides a by b and dest by the quotient */
RANMATH_INLINE void rm_vec2_adds_div(const vec2 v, const f32  s, vec2 dest);    /* Adds s to v and divides dest by the sum */
RANMATH_INLINE void rm_vec2_subs_div(const vec2 v, const f32  s, vec2 dest);    /* Subtracts s from v and divides dest by the difference */
RANMATH_INLINE void rm_vec2_muls_div(const vec2 v, const f32  s, vec2 dest);    /* Multiplies v with s and divides dest by the product */
RANMATH_INLINE void rm_vec2_divs_div(const vec2 v, const f32  s, vec2 dest);    /* Divides v by s and dest by the quotient */




/* Definitions */
RANMATH_INLINE void rm_vec2_print(const vec2 v) {
  printf("<x: %f, y: %f>\n", v[0], v[1]);
}

RANMATH_INLINE void rm_vec2_set(const f32 x, const f32 y, vec2 dest) {
  dest[0] = x;
  dest[1] = y;
}

RANMATH_INLINE void rm_vec2_fill(const f32 val, vec2 dest) {
  dest[0] = dest[1] = val;
}

RANMATH_INLINE void rm_vec2_zero(vec2 v) {
  v[0] = v[1] = 0.0F;
}

RANMATH_INLINE void rm_vec2_one(vec2 v) {
  v[0] = v[1] = 1.0F;
}

RANMATH_INLINE f32 rm_vec2_dot(const vec2 a, const vec2 b) {
  return a[0] * b[0] + a[1] * b[1];
}

RANMATH_INLINE f32 rm_vec2_norm2(const vec2 v) {
  return rm_vec2_dot(v, v);
}

RANMATH_INLINE f32 rm_vec2_norm(const vec2 v) {
  return sqrtf(rm_vec2_norm2(v));
}

RANMATH_INLINE f32 rm_vec2_norm_one(const vec2 v) {
  return fabsf(v[0]) + fabsf(v[1]);
}

RANMATH_INLINE f32 rm_vec2_inf(const vec2 v) {
  return fmaxf(fabsf(v[0]), fabsf(v[1]));
}

RANMATH_INLINE f32 rm_vec2_cross(const vec2 a, const vec2 b) {
  return a[0] * b[0] - a[1] * b[1];
}

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



#endif /* RANMATH_H */
