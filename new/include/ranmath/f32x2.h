#ifndef _RANMATH_F32X2_H_
#define _RANMATH_F32X2_H_

#include "types.h"
#include "f32.h"

typedef struct f32x2_t f32x2;

struct f32x2_t {
    union {
        struct {
            f32 x, y;
        };
        struct {
            f32 z, w;
        };
        struct {
            f32 r, g;
        };
        struct {
            f32 b, a;
        };
        struct {
            f32 u, v;
        };

        f32 raw[2];
    };
};

#define rm_f32x2(_x, _y) ((f32x2) {.x = (_x), .y = (_y)})
#define rm_f32x2s(_s)    ((f32x2) {.x = (_s), .y = (_s)})

RM_INLINE f32x2
rm_abs_f32x2(const f32x2 v) {
    return rm_f32x2(rm_abs_f32(v.x), rm_abs_f32(v.y));
}
RM_INLINE f32x2
rm_min_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_min_f32(a.x, b.x), rm_min_f32(a.y, b.y));
}
RM_INLINE f32x2
rm_mins_f32x2(const f32x2 v, const f32 s) {
    return rm_min_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32
rm_minv_f32x2(const f32x2 v) {
    return rm_min_f32(v.x, v.y);
}
RM_INLINE f32x2
rm_max_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_max_f32(a.x, b.x), rm_max_f32(a.y, b.y));
}
RM_INLINE f32x2
rm_maxs_f32x2(const f32x2 v, const f32 s) {
    return rm_max_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32
rm_maxv_f32x2(const f32x2 v) {
    return rm_max_f32(v.x, v.y);
}
RM_INLINE f32
rm_hadd_f32x2(const f32x2 v) {
    return v.x + v.y;
}
RM_INLINE f32x2
rm_add_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x + b.x, a.y + b.y);
}
RM_INLINE f32x2
rm_adds_f32x2(const f32x2 v, const f32 s) {
    return rm_add_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2
rm_sub_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x - b.x, a.y - b.y);
}
RM_INLINE f32x2
rm_subs_f32x2(const f32x2 v, const f32 s) {
    return rm_sub_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2
rm_ssub_f32x2(const f32 s, const f32x2 v) {
    return rm_sub_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x2
rm_mul_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x * b.x, a.y * b.y);
}
RM_INLINE f32x2
rm_muls_f32x2(const f32x2 v, const f32 s) {
    return rm_mul_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2
rm_div_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x / b.x, a.y / b.y);
}
RM_INLINE f32x2
rm_divs_f32x2(const f32x2 v, const f32 s) {
    return rm_muls_f32x2(v, 1.0f / s);
}
RM_INLINE f32x2
rm_sdiv_f32x2(const f32 s, const f32x2 v) {
    return rm_div_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x2
rm_mod_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_mod_f32(a.x, b.x), rm_mod_f32(a.y, b.y));
}
RM_INLINE f32x2
rm_mods_f32x2(const f32x2 v, const f32 s) {
    return rm_mod_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2
rm_smod_f32x2(const f32 s, const f32x2 v) {
    return rm_mod_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x2
rm_wrap_f32x2(const f32x2 val, const f32x2 min, const f32x2 max) {
    return rm_f32x2(rm_wrap_f32(val.x, min.x, max.x),
                    rm_wrap_f32(val.y, min.y, max.y));
}
RM_INLINE f32x2
rm_wraps_f32x2(const f32x2 val, const f32 min, const f32 max) {
    return rm_wrap_f32x2(val, rm_f32x2s(min), rm_f32x2s(max));
}
RM_INLINE f32x2
rm_clamp_f32x2(const f32x2 v, const f32x2 min, const f32x2 max) {
    return rm_f32x2(rm_clamp_f32(v.x, min.x, max.x),
                    rm_clamp_f32(v.y, min.y, max.y));
}
RM_INLINE f32x2
rm_clamps_f32x2(const f32x2 v, f32 min, f32 max) {
    return rm_clamp_f32x2(v, rm_f32x2s(min), rm_f32x2s(max));
}
RM_INLINE f32x2
rm_sign_f32x2(const f32x2 v) {
    return rm_f32x2(rm_sign_f32(v.x), rm_sign_f32(v.y));
}
RM_INLINE f32x2
rm_copysign_f32x2(const f32x2 v, const f32x2 s) {
    return rm_f32x2(rm_copysign_f32(v.x, s.x), rm_copysign_f32(v.y, s.y));
}
RM_INLINE f32x2
rm_copysigns_f32x2(const f32x2 v, const f32 s) {
    return rm_copysign_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2
rm_fma_f32x2(const f32x2 a, const f32x2 b, const f32x2 c) {
    return rm_add_f32x2(rm_mul_f32x2(a, b), c);
}
RM_INLINE f32x2
rm_fmas_f32x2(const f32x2 a, const f32x2 b, const f32 c) {
    return rm_adds_f32x2(rm_mul_f32x2(a, b), c);
}
RM_INLINE f32x2
rm_fmass_f32x2(const f32x2 a, const f32 b, const f32 c) {
    return rm_adds_f32x2(rm_muls_f32x2(a, b), c);
}
RM_INLINE f32x2
rm_floor_f32x2(const f32x2 v) {
    return rm_f32x2(rm_floor_f32(v.x), rm_floor_f32(v.y));
}
RM_INLINE f32x2
rm_ceil_f32x2(const f32x2 v) {
    return rm_f32x2(rm_ceil_f32(v.x), rm_ceil_f32(v.y));
}
RM_INLINE f32x2
rm_round_f32x2(const f32x2 v) {
    return rm_f32x2(rm_round_f32(v.x), rm_round_f32(v.y));
}
RM_INLINE f32x2
rm_trunc_f32x2(const f32x2 v) {
    return rm_f32x2(rm_trunc_f32(v.x), rm_trunc_f32(v.y));
}
RM_INLINE f32x2
rm_fract_f32x2(const f32x2 v) {
    return rm_f32x2(rm_fract_f32(v.x), rm_fract_f32(v.y));
}
RM_INLINE f32x2
rm_copy_f32x2(const f32x2 v) {
    return rm_f32x2(v.x, v.y);
}
RM_INLINE f32x2
rm_zero_f32x2(void) {
    return rm_f32x2s(0);
}
RM_INLINE f32x2
rm_one_f32x2(void) {
    return rm_f32x2s(1);
}
RM_INLINE f32
rm_dot_f32x2(const f32x2 a, const f32x2 b) {
    return a.x * b.x + a.y * b.y;
}
RM_INLINE f32
rm_norm2_f32x2(const f32x2 v) {
    return rm_dot_f32x2(v, v);
}
RM_INLINE f32
rm_norm_f32x2(const f32x2 v) {
    return rm_sqrt_f32(rm_norm2_f32x2(v));
}
RM_INLINE f32
rm_norm_one_f32x2(const f32x2 v) {
    return rm_hadd_f32x2(rm_abs_f32x2(v));
}
RM_INLINE f32
rm_norm_inf_f32x2(const f32x2 v) {
    return rm_maxv_f32x2(rm_abs_f32x2(v));
}
RM_INLINE f32x2
rm_normalize_f32x2(const f32x2 v) {
    f32 norm;

    norm = rm_norm_f32x2(v);

    if (norm == 0.0f) { return rm_zero_f32x2(); }

    return rm_muls_f32x2(v, 1.0f / norm);
}
RM_INLINE f32
rm_cross_f32x2(const f32x2 a, const f32x2 b) {
    return a.x * b.y - a.y * b.x;
}
RM_INLINE f32
rm_distance2_f32x2(const f32x2 a, const f32x2 b) {
    return rm_pow2_f32(a.x - b.x) + rm_pow2_f32(a.y - b.y);
}
RM_INLINE f32
rm_distance_f32x2(const f32x2 a, const f32x2 b) {
    return rm_sqrt_f32(rm_distance2_f32x2(a, b));
}
RM_INLINE f32x2
rm_rotate_origin_f32x2(const f32x2 v, const f32 a) {
    f32x2 tmp, tmp1;

    tmp  = rm_muls_f32x2(v, rm_cos_f32(a));
    tmp1 = rm_muls_f32x2(v, rm_sin_f32(a));

    return rm_f32x2(tmp.x - tmp1.y, tmp1.x + tmp.y);
}
RM_INLINE f32x2
rm_rotate_point_f32x2(const f32x2 v, const f32x2 p, const f32 a) {
    f32x2 tmp, tmp1, tmp2;

    tmp = rm_f32x2(v.x - p.x, p.y - v.y);

    tmp1 = rm_muls_f32x2(tmp, rm_cos_f32(a));
    tmp2 = rm_muls_f32x2(tmp, rm_sin_f32(a));

    return rm_f32x2(p.x + (tmp1.x - tmp2.y), p.y - (tmp2.x + tmp1.y));
}

#endif /* _RANMATH_F32X2_H_ */
