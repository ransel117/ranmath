#include "ranmath.h"

i32 rm_pow2i(i32k x) {
    return x * x;
}
f32 rm_powi(i32k x, i32k val) {
    if (x == 0 || x == 1) return x;
    if (x == -1 && val % 2 == 0) return -x;
    if (x == -1) return x;

    f32 dest = 1.0F;
    f32 power = (val < 0) ? (f32)1 / x : (f32)x;

    for (u32 i = 0; i < val; ++i) {
        dest *= power;
    }

    return dest;
}
i32 rm_absi(i32k x) {
    return x < 0 ? -x : x;
}
i32 rm_maxi(i32k a, i32k b) {
    return a > b ? a : b;
}
i32 rm_mini(i32k a, i32k b) {
    return a < b ? a : b;
}
i32 rm_clampi(i32k val, i32k minval, i32k maxval) {
    return rm_mini(rm_maxi(val, minval), maxval);
}

f32 rm_pow2f(f32k x) {
    return x * x;
}
/* TODO: implement own pow */
f32 rm_powf(f32k x, f32k val) {
    return powf(x, val);
}
f32 rm_powfi(f32k x, i32k val) {
    if (x == 0 || x == 1.0F) return x;
    if (x == -1.0F && val % 2 == 0) return -x;
    if (x == -1.0F) return x;

    f32 dest = 1.0F;
    f32 power = (val < 0) ? 1 / x : x;

    for (u32 i = 0; i < val; ++i) {
        dest *= power;
    }

    return dest;
}
/* TODO: implement own sqrt */
/* TODO: implement own cos and inverse */
/* TODO: implement own sin and inverse */
f32 rm_sqrtf(f32 x) {
    return sqrtf(x);
}
f32 rm_cosf(f32k  a) {
    return cosf(a);
}
f32 rm_sinf(f32k a) {
    return sinf(a);
}
f32 rm_acosf(f32k a) {
    return acosf(a);
}
f32 rm_asinf(f32k a) {
    return asinf(a);
}
f32 rm_cosf_deg(f32k a) {
    return rm_cosf(RM_MAKE_RAD * a);
}
f32 rm_sinf_deg(f32k a) {
    return rm_sinf(RM_MAKE_RAD * a);
}
f32 rm_acosf_deg(f32k a) {
    return RM_MAKE_DEG * rm_acosf(a);
}
f32 rm_asinf_deg(f32k a) {
    return RM_MAKE_DEG * rm_asinf(a);
}
f32 rm_absf(f32k x) {
    return x < 0.0F ? -x : x;
}
f32 rm_maxf(f32k a, f32k b) {
    return a > b ? a : b;

    /* Alt implementation */
    //return (a > b) * a + (b > a) * b;
}
f32 rm_minf(f32k a, f32k b) {
    return a < b ? a : b;

    /* Alt implementation */
    //return (a < b) * a + (b < a) * b;
}
f32 rm_clampf(f32k val, f32k minval, f32k maxval) {
    return rm_minf(rm_maxf(val, minval), maxval);
}



/* ----------------------------Vec2---------------------------- */
void rm_vec2_print(vec2k v) {
    printf("<x: %f, y: %f>\n", v[0], v[1]);
}
void rm_vec2_copy(vec2k v, vec2 dest) {
    dest[0] = v[0];
    dest[1] = v[1];
}
void rm_vec2_set(f32k x, f32k y, vec2 dest) {
    dest[0] = x;
    dest[1] = y;
}
void rm_vec2_fill(f32k val, vec2 v) {
    v[0] = v[1] = val;
}
void rm_vec2_zero(vec2 v) {
    v[0] = v[1] = 0.0F;
}
void rm_vec2_one(vec2 v) {
    v[0] = v[1] = 1.0F;
}
f32 rm_vec2_dot(vec2k a, vec2k b) {
    return a[0] * b[0] + a[1] * b[1];
}
f32 rm_vec2_norm2(vec2k v) {
    return rm_vec2_dot(v, v);
}
f32 rm_vec2_norm(vec2k v) {
    return rm_sqrtf(rm_vec2_norm2(v));
}
f32 rm_vec2_norm_one(vec2k v) {
    return rm_absf(v[0]) + rm_absf(v[1]);
}
f32 rm_vec2_norm_inf(vec2k v) {
    return rm_maxf(rm_absf(v[0]), rm_absf(v[1]));
}
f32 rm_vec2_cross(vec2k a, vec2k b) {
    return a[0] * b[0] - a[1] * b[1];
}
f32 rm_vec2_max(vec2k v) {
    return rm_maxf(v[0], v[1]);
}
f32 rm_vec2_min(vec2k v) {
    return rm_minf(v[0], v[1]);
}
void rm_vec2_abs(vec2k v, vec2 dest) {
    dest[0] = rm_absf(v[0]);
    dest[1] = rm_absf(v[1]);
}
void rm_vec2_maxv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = rm_maxf(a[0], b[0]);
    dest[1] = rm_maxf(a[1], b[1]);
}
void rm_vec2_minv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = rm_minf(a[0], b[0]);
    dest[1] = rm_minf(a[1], b[1]);
}
void rm_vec2_clamp(vec2k v, f32k minval, f32k maxval, vec2 dest) {
    dest[0] = rm_clampf(v[0], minval, maxval);
    dest[1] = rm_clampf(v[1], minval, maxval);
}
void rm_vec2_adds(f32k s, vec2 dest) {
    dest[0] += s;
    dest[1] += s;
}
void rm_vec2_subs(f32k s, vec2 dest) {
    dest[0] -= s;
    dest[1] -= s;
}
void rm_vec2_muls(f32k s, vec2 dest) {
    dest[0] *= s;
    dest[1] *= s;
}
void rm_vec2_divs(f32k s, vec2 dest) {
    f32 num = 1.0F / s;
    dest[0] *= num;
    dest[1] *= num;
}
void rm_vec2_addss(vec2k v, f32k s, vec2 dest) {
    dest[0] = v[0] + s;
    dest[1] = v[1] + s;
}
void rm_vec2_subss(vec2k v, f32k s, vec2 dest) {
    dest[0] = v[0] - s;
    dest[1] = v[1] - s;
}
void rm_vec2_mulss(vec2k v, f32k s, vec2 dest) {
    dest[0] = v[0] * s;
    dest[1] = v[1] * s;
}
void rm_vec2_divss(vec2k v, f32k s, vec2 dest) {
    f32 num = 1.0F / s;
    dest[0] = v[0] * num;
    dest[1] = v[1] * num;
}
void rm_vec2_adds_add(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_subs_add(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_muls_add(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_divs_add(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_adds_sub(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_subs_sub(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_muls_sub(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_divs_sub(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_adds_mul(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_subs_mul(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_muls_mul(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_divs_mul(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_adds_div(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_addss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_subs_div(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_subss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_muls_div(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_divs_div(vec2k v, f32k s, vec2 dest) {
    vec2 tmp;
    rm_vec2_divss(v, s, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_addv(vec2k v, vec2 dest) {
    dest[0] += v[0];
    dest[1] += v[1];
}
void rm_vec2_subv(vec2k v, vec2 dest) {
    dest[0] -= v[0];
    dest[1] -= v[1];
}
void rm_vec2_mulv(vec2k v, vec2 dest) {
    dest[0] *= v[0];
    dest[1] *= v[1];
}
void rm_vec2_divv(vec2k v, vec2 dest) {
    dest[0] /= v[0];
    dest[1] /= v[1];
}
void rm_vec2_addsv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
}
void rm_vec2_subsv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
}
void rm_vec2_mulsv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
}
void rm_vec2_divsv(vec2k a, vec2k b, vec2 dest) {
    dest[0] = a[0] / b[0];
    dest[1] = a[1] / b[1];
}
void rm_vec2_addv_add(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_subv_add(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_mulv_add(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_divv_add(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_addv(tmp,  dest);
}
void rm_vec2_addv_sub(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_subv_sub(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_mulv_sub(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_divv_sub(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_subv(tmp,  dest);
}
void rm_vec2_addv_mul(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_subv_mul(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_mulv_mul(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_divv_mul(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_mulv(tmp,  dest);
}
void rm_vec2_addv_div(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_addsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_subv_div(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_subsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_mulv_div(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_mulsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_divv_div(vec2k a, vec2k b, vec2 dest) {
    vec2 tmp;
    rm_vec2_divsv(a, b, tmp);
    rm_vec2_divv(tmp,  dest);
}
void rm_vec2_negate_to(vec2k v, vec2 dest) {
    dest[0] = -v[0];
    dest[1] = -v[1];
}
void rm_vec2_negate(vec2 v) {
    v[0] = -v[0];
    v[1] = -v[1];
}
void rm_vec2_normalize_to(vec2k v, vec2 dest) {
    f32 norm = rm_vec2_norm(v);

    (rm_absf(norm) <= RM_FLT_EPSILON) ? rm_vec2_zero(dest) : rm_vec2_mulss(v, 1.0F / norm, dest);
}
void rm_vec2_normalize(vec2 v) {
    f32 norm = rm_vec2_norm(v);

    (rm_absf(norm) <= RM_FLT_EPSILON) ? rm_vec2_zero(v) : rm_vec2_muls(1.0F / norm, v);
}
f32 rm_vec2_distance2(vec2k a, vec2k b) {
    return rm_pow2f(a[0] - b[0]) + rm_pow2f(a[1] - b[1]);
}
f32 rm_vec2_distance(vec2k a, vec2k b) {
    return rm_sqrtf(rm_vec2_distance2(a, b));
}
f32 rm_vec2_angle(vec2k a, vec2k b) {
    f32 dot  = rm_vec2_dot(a, b) / (rm_vec2_norm(a) * rm_vec2_norm(b));

    return (dot > 1.0F) ? 0.0F : (dot < -1.0F) ? RM_PI : rm_acosf(dot);
    /* Alt implementation */
    // bool lessn1 = dot < -1.0F;
    // return lessn1 * RM_PI + (dot < 1.0F && !lessn1) * rm_acosf(dot);
}
f32 rm_vec2_angle_deg(vec2k a, vec2k b) {
    f32 dot  = rm_vec2_dot(a, b) / (rm_vec2_norm(a) * rm_vec2_norm(b));

    return (dot > 1.0F) ? 0.0F : (dot < -1.0F) ? 180.0F : rm_acosf_deg(dot);
    /* Alt implementation */
    // bool lessn1 = dot < -1.0F;
    // return lessn1 * 180.0F + (dot < 1.0F && !lessn1) * rm_acosf_deg(dot);
}
void rm_vec2_rotate_origin(vec2k v, f32k a, vec2 dest) {
    f32 c = rm_cosf(a);
    f32 s = rm_sinf(a);

    dest[0] = v[0] * c - v[1] * s;
    dest[1] = v[0] * s + v[1] * c;
}
void rm_vec2_rotate_point(vec2k v, vec2k point, f32k a, vec2 dest) {
    f32 c = rm_cosf(a);
    f32 s = rm_sinf(a);
    vec2 tv = { v[0] - point[0], v[1] - point[1] }; /* Translate v to origin */


    dest[0] = tv[0] * c - tv[1] * s + point[0];
    dest[1] = tv[0] * s + tv[1] * c + point[1];
}
void rm_vec2_rotate_origin_deg(vec2k v, f32k a, vec2 dest) {
    f32 c = rm_cosf_deg(a);
    f32 s = rm_sinf_deg(a);

    dest[0] = v[0] * c - v[1] * s;
    dest[1] = v[0] * s + v[1] * c;
}
void rm_vec2_rotate_point_deg(vec2k v, vec2k point, f32k a, vec2 dest) {
    f32 c = rm_cosf_deg(a);
    f32 s = rm_sinf_deg(a);
    vec2 tv = { v[0] - point[0], v[1] - point[1] }; /* Translate v to origin */

    dest[0] = tv[0] * c - tv[1] * s + point[0];
    dest[1] = tv[0] * s + tv[1] * c + point[1];
}
void rm_vec2_center(vec2k a, vec2k b, vec2 dest) {
    rm_vec2_addsv(a, b, dest);
    rm_vec2_muls(0.5F,  dest);
}
