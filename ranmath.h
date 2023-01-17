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


/* ----------------------------Types---------------------------- */
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

typedef const u8  u8k;
typedef const u16 u16k;
typedef const u32 u32k;
typedef const u64 u64k;

typedef const i8  i8k;
typedef const i16 i16k;
typedef const i32 i32k;
typedef const i64 i64k;

typedef const f32 f32k;
typedef const f64 f64k;

typedef const vec2 vec2k;
typedef const vec3 vec3k;
typedef const vec4 vec4k;

#define RM_FLT_EPSILON 1.19209290E-7F
#define RM_PI          3.14159265359F
#define RM_MAKE_RAD    1.74532925E-2F
#define RM_MAKE_DEG    5.72957795E1F

/* PS: the s and v functions requires dest to be initialized, such as rm_vec2_adds or rm_vec2_divv.
* The others do not need dest to be initialized.
*/

i32 rm_pow2i(i32k x);
f32 rm_powi(i32k  x, i32k val);
i32 rm_absi(i32k  x);
i32 rm_maxi(i32k  a, i32k b);
i32 rm_mini(i32k  a, i32k b);
i32 rm_clampi(i32k val, i32k minval, i32k maxval);

f32 rm_pow2f(f32k x);                                 /* Returns the square of x */
f32 rm_powf(f32k  x, f32k val);                       /* Returns x to the power of val */
f32 rm_powfi(f32k x, i32k val);                       /* Returns x to the power of integer val */
f32 rm_sqrtf(f32k x);                                 /*  */
f32 rm_cosf(f32k  a);                                 /*  */
f32 rm_sinf(f32k  a);                                 /*  */
f32 rm_acosf(f32k a);                                 /*  */
f32 rm_asinf(f32k a);                                 /*  */
f32 rm_cosf_deg(f32k a);                              /*  */
f32 rm_sinf_deg(f32k a);                              /*  */
f32 rm_acosf_deg(f32k a);                             /*  */
f32 rm_asinf_deg(f32k a);                             /*  */
f32 rm_absf(f32k x);                                  /*  */
f32 rm_maxf(f32k a, f32k b);                          /*  */
f32 rm_minf(f32k a, f32k b);                          /*  */
f32 rm_clampf(f32k val, f32k minval, f32k maxval);    /* Clamps the value between minval and maxval */

/* ----------------------------Vec2---------------------------- */
void rm_vec2_print(vec2k v);                           /* Prints x and y values of v */
void rm_vec2_copy(vec2k  v, vec2 dest);                /* Copies the values of v into dest */
void rm_vec2_set(f32k x, f32k y, vec2 dest);           /* Sets x and y values of dest */
void rm_vec2_fill(f32k val, vec2 v);                   /* Fills v with val */
void rm_vec2_zero(vec2 v);                             /* Fills v with zero */
void rm_vec2_one(vec2  v);                             /* Files v with one */
f32  rm_vec2_dot(vec2k a, vec2k b);                    /* Returns dot product of a and b */
f32  rm_vec2_norm2(vec2k v);                           /* Returns squared norm (magnitude) of v (L2 squared or (L²)², could be called L4 or L⁴) */
f32  rm_vec2_norm(vec2k v);                            /* Returns norm (magnitude) of v (L2 or L²) */
f32  rm_vec2_norm_one(vec2k v);                        /* Returns norm (magnitude) of v (L1 or L¹) */
f32  rm_vec2_norm_inf(vec2k v);                        /* Returns norm (magnitude) of v (infinity norm or max norm) */
f32  rm_vec2_cross(vec2k a, vec2k b);                  /* Returns the cross product of a and b */
f32  rm_vec2_max(vec2k v);
f32  rm_vec2_min(vec2k v);
void rm_vec2_abs(vec2k v, vec2 dest);
void rm_vec2_maxv(vec2k a, vec2k b, vec2 dest);
void rm_vec2_minv(vec2k a, vec2k b, vec2 dest);
void rm_vec2_clamp(vec2k v,f32k minval, f32k maxval, vec2 dest);
void rm_vec2_adds(f32k s, vec2 dest);                  /* Adds s to dest */
void rm_vec2_subs(f32k s, vec2 dest);                  /* Subtracts s from dest */
void rm_vec2_muls(f32k s, vec2 dest);                  /* Multiplies dest with s */
void rm_vec2_divs(f32k s, vec2 dest);                  /* Divides dest by s */
void rm_vec2_addss(vec2k v, f32k s, vec2 dest);        /* Adds s to v and stores it in dest */
void rm_vec2_subss(vec2k v, f32k s, vec2 dest);        /* Subtracts s from v and stores it in dest */
void rm_vec2_mulss(vec2k v, f32k s, vec2 dest);        /* Multiplies v with s and stores it in dest */
void rm_vec2_divss(vec2k v, f32k s, vec2 dest);        /* Divides v by s and stores it in dest */
void rm_vec2_adds_add(vec2k v, f32k s, vec2 dest);     /* Adds s to v and the sum to dest */
void rm_vec2_subs_add(vec2k v, f32k s, vec2 dest);     /* Subtracts s from v and adds the sum to dest */
void rm_vec2_muls_add(vec2k v, f32k s, vec2 dest);     /* Multiplies v with s and adds the product to dest */
void rm_vec2_divs_add(vec2k v, f32k s, vec2 dest);     /* Divides v by s and adds the quotient to dest */
void rm_vec2_adds_sub(vec2k v, f32k s, vec2 dest);     /* Adds s to v and subracts the sum from dest */
void rm_vec2_subs_sub(vec2k v, f32k s, vec2 dest);     /* Subtracts s from v and the difference from dest */
void rm_vec2_muls_sub(vec2k v, f32k s, vec2 dest);     /* Multiplies v with s and subtracts the difference from dest */
void rm_vec2_divs_sub(vec2k v, f32k s, vec2 dest);     /* Divides v by s and subtracts the quotient from dest */
void rm_vec2_adds_mul(vec2k v, f32k s, vec2 dest);     /* Adds s to v and multiplies dest with the sum */
void rm_vec2_subs_mul(vec2k v, f32k s, vec2 dest);     /* Subtracts s from v and multiplies dest with the difference */
void rm_vec2_muls_mul(vec2k v, f32k s, vec2 dest);     /* Multiplies v with s and dest with the product */
void rm_vec2_divs_mul(vec2k v, f32k s, vec2 dest);     /* Divides v by s and multiplies dest with the quotient */
void rm_vec2_adds_div(vec2k v, f32k s, vec2 dest);     /* Adds s to v and divides dest by the sum */
void rm_vec2_subs_div(vec2k v, f32k s, vec2 dest);     /* Subtracts s from v and divides dest by the difference */
void rm_vec2_muls_div(vec2k v, f32k s, vec2 dest);     /* Multiplies v with s and divides dest by the product */
void rm_vec2_divs_div(vec2k v, f32k s, vec2 dest);     /* Divides v by s and dest by the quotient */
void rm_vec2_addv(vec2k v, vec2 dest);                 /* Adds v to dest */
void rm_vec2_subv(vec2k v, vec2 dest);                 /* Subtracts v from dest */
void rm_vec2_mulv(vec2k v, vec2 dest);                 /* Multiplies dest with v */
void rm_vec2_divv(vec2k v, vec2 dest);                 /* Divides dest by v */
void rm_vec2_addsv(vec2k a, vec2k b, vec2 dest);       /* Adds b to a and stores it in dest */
void rm_vec2_subsv(vec2k a, vec2k b, vec2 dest);       /* Subtracts b from a and stores it in dest */
void rm_vec2_mulsv(vec2k a, vec2k b, vec2 dest);       /* Multiplies a with b and stores it in dest */
void rm_vec2_divsv(vec2k a, vec2k b, vec2 dest);       /* Divides a by b and stores it in dest */
void rm_vec2_addv_add(vec2k a, vec2k b, vec2 dest);    /* Adds b to a and the sum to dest */
void rm_vec2_subv_add(vec2k a, vec2k b, vec2 dest);    /* Subtracts b from a and adds the difference to dest */
void rm_vec2_mulv_add(vec2k a, vec2k b, vec2 dest);    /* Multiplies a with b and adds the product to dest */
void rm_vec2_divv_add(vec2k a, vec2k b, vec2 dest);    /* Divides a by b and adds the quotient to dest */
void rm_vec2_divv_add(vec2k a, vec2k b, vec2 dest);    /* Divides a by b and adds the quotient to dest */
void rm_vec2_addv_sub(vec2k a, vec2k b, vec2 dest);    /* Adds b to a and subtracts the sum from dest */
void rm_vec2_subv_sub(vec2k a, vec2k b, vec2 dest);    /* Subtracts b from a and the difference from dest */
void rm_vec2_mulv_sub(vec2k a, vec2k b, vec2 dest);    /* Multiplies a with b and subtracts the product from dest */
void rm_vec2_divv_sub(vec2k a, vec2k b, vec2 dest);    /* Divides a by b and subracts the quotient from dest*/
void rm_vec2_addv_mul(vec2k a, vec2k b, vec2 dest);    /* Adds b to a and multiplies dest with the sum */
void rm_vec2_subv_mul(vec2k a, vec2k b, vec2 dest);    /* Subtracts b from a and multiplies dest with the difference */
void rm_vec2_mulv_mul(vec2k a, vec2k b, vec2 dest);    /* Multiplies a with b and dest with the product */
void rm_vec2_divv_mul(vec2k a, vec2k b, vec2 dest);    /* Divides a by b and multiplies dest with the quotient */
void rm_vec2_addv_div(vec2k a, vec2k b, vec2 dest);    /* Adds b to a and divides dest by the sum */
void rm_vec2_subv_div(vec2k a, vec2k b, vec2 dest);    /* Subtracts b from a and divides dest by the difference */
void rm_vec2_mulv_div(vec2k a, vec2k b, vec2 dest);    /* Multiplies a with b and divides dest by the product */
void rm_vec2_divv_div(vec2k a, vec2k b, vec2 dest);    /* Divides a by b and dest by the quotient */
void rm_vec2_negate_to(vec2k v, vec2 dest);
void rm_vec2_negate(vec2 v);
void rm_vec2_normalize_to(vec2k v, vec2 dest);
void rm_vec2_normalize(vec2 v);
f32  rm_vec2_distance2(vec2k a, vec2k b);
f32  rm_vec2_distance(vec2k  a, vec2k b);
f32  rm_vec2_angle(vec2k a, vec2k b);
f32  rm_vec2_angle_deg(vec2k a, vec2k b);
void rm_vec2_rotate_origin(vec2k v, f32k a, vec2 dest);
void rm_vec2_rotate_point(vec2k  v, vec2k point, f32k a, vec2 dest);
void rm_vec2_rotate_origin_deg(vec2k v, f32k a, vec2 dest);
void rm_vec2_rotate_point_deg(vec2k  v, vec2k point, f32k a, vec2 dest);

// TODO: Vec3 and Vec4
/* ----------------------------Vec3---------------------------- */
/* ----------------------------Vec4---------------------------- */

#endif /* RANMATH_H */
