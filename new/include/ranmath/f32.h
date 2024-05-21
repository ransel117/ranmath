#ifndef _RANMATH_F32_H_
#define _RANMATH_F32_H_

#include "types.h"
#include "util.h"

RM_INLINE f32
rm_abs_f32(const f32 x) {
    return RM_ABS(x);
}
RM_INLINE f32
rm_min_f32(const f32 a, const f32 b) {
    return RM_MIN(a, b);
}
RM_INLINE f32
rm_max_f32(const f32 a, const f32 b) {
    return RM_MAX(a, b);
}
RM_INLINE f32
rm_pow2_f32(const f32 x) {
    return RM_POW2(x);
}
RM_INLINE f32
rm_trunc_f32(const f32 x) {
    return (i32)x;
}
RM_INLINE f32
rm_mod_f32(const f32 a, const f32 b) {
    return a - (rm_trunc_f32(a / b) * b);
}
RM_INLINE f32
rm_clamp_f32(const f32 val, const f32 min, const f32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32
rm_wrap_f32(const f32 val, const f32 min, const f32 max) {
    f32 tmax;

    tmax = max - min;

    return min + rm_mod_f32(tmax + rm_mod_f32(val - min, tmax), tmax);
}
RM_INLINE f32
rm_sign_f32(const f32 x) {
    return RM_SIGN(x);
}
RM_INLINE f32
rm_copysign_f32(const f32 x, const f32 s) {
    return rm_abs_f32(x) * rm_sign_f32(s);
}
RM_INLINE f32
rm_floor_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x - 1) : rm_trunc_f32(x);
}
RM_INLINE f32
rm_ceil_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x) : rm_trunc_f32(x + 1);
}
RM_INLINE f32
rm_round_f32(const f32 x) {
    f32 t;

    if (x < 0) {
        t = rm_floor_f32(-x);
        return ((t + x) <= -0.5F) ? -(t + 1) : -t;
    }

    t = rm_floor_f32(x);
    return ((t - x) <= -0.5F) ? (t + 1) : t;
}
RM_INLINE f32
rm_fract_f32(const f32 x) {
    return x - rm_floor_f32(x);
}
RM_INLINE f32
rm_sqrt_f32(const f32 x) {
    return sqrtf(x);
}
RM_INLINE f32
rm_cos_f32(const f32 x) {
    return cosf(x);
}
RM_INLINE f32
rm_sin_f32(const f32 x) {
    return sinf(x);
}

#endif /* _RANMATH_F32_H_ */
