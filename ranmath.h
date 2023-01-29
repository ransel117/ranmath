#ifndef RANMATH_H
#define RANMATH_H

#define RANMATH_INLINE static inline

/* ---------------- TYPES ---------------- */
typedef _Bool bool;
#define true  1
#define false 0

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  u64;
typedef signed char    i8;
typedef signed short   i16;
typedef signed int     i32;
typedef signed long    i64;
typedef float          f32;
typedef double         f64;

/* Debating whether to use structs or arrays */
typedef struct {
    f32 x;
    f32 y;
} vec2;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} vec3;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} vec4;

/* ---------------- CONSTANTS ---------------- */
#define RAN_E           2.7182818284590452353602874713526624977572470936999595749669676277
#define RAN_LOG2E       1.4426950408889634073599246810018921374266459541529859341354494069
#define RAN_LOG10E      0.4342944819032518276511289189166050822943970058036665661144537831
#define RAN_LN2         0.6931471805599453094172321214581765680755001343602552541206800094
#define RAN_LN10        2.3025850929940456840179914546843642076011014886287729760333279009
#define RAN_PI          3.1415926535897932384626433832795028841971693993751058209749445923
#define RAN_PI_2        1.5707963267948966192313216916397514420985846996875529104874722961
#define RAN_2PI         6.2831853071795864769252867665590057683943387987502116419498891846
#define RAN_PI2         9.8696044010893586188344909998761511353136994072407906264133493762
#define RAN_PI3         31.006276680299820175476315067101395202225288565885107694144538103
#define RAN_PI4         97.409091034002437236440332688705111249727585672685421691467859389
#define RAN_1_PI        0.3183098861837906715377675267450287240689192914809128974953346881
#define RAN_1_2PI       0.1591549430918953357688837633725143620344596457404564487476673440
#define RAN_SQRTPI      1.7724538509055160272981674833411451827975494561223871282138077898
#define RAN_1_SQRTPI    0.5641895835477562869480794515607725858440506293289988568440857217
#define RAN_2_SQRTPI    1.1283791670955125738961589031215451716881012586579977136881714434
#define RAN_SQRT2       1.4142135623730950488016887242096980785696718753769480731766797379
#define RAN_1_SQRT2     0.7071067811865475244008443621048490392848359376884740365883398689
#define RAN_MAKE_DEG    57.295779513082320876798154814105170332405472466564321549160243861
#define RAN_MAKE_RAD    0.0174532925199432957692369076848861271344287188854172545609719144

/* ---------------- FUNCTIONS ---------------- */
RANMATH_INLINE i32 ran_powi(i32, i32);
RANMATH_INLINE i64 ran_powl(i64, i64);

RANMATH_INLINE i32 ran_pow2i(i32);
RANMATH_INLINE i64 ran_pow2l(i64);
RANMATH_INLINE f32 ran_pow2f(f32);
RANMATH_INLINE f64 ran_pow2d(f64);

RANMATH_INLINE f32 ran_rsqrtf(f32);
RANMATH_INLINE f64 ran_rsqrtd(f64);

RANMATH_INLINE f32 ran_sqrtf(f32);
RANMATH_INLINE f64 ran_sqrtd(f64);

RANMATH_INLINE i32 ran_absi(i32);
RANMATH_INLINE i64 ran_absl(i64);
RANMATH_INLINE f32 ran_absf(f32);
RANMATH_INLINE f64 ran_absd(f64);

RANMATH_INLINE f32 ran_floorf(f32);
RANMATH_INLINE f64 ran_floord(f64);

RANMATH_INLINE f32 ran_ceilf(f32);
RANMATH_INLINE f64 ran_ceild(f64);

RANMATH_INLINE f32 ran_roundf(f32);
RANMATH_INLINE f64 ran_roundd(f64);

RANMATH_INLINE f32 ran_cosf(f32);
RANMATH_INLINE f64 ran_cosd(f64);

RANMATH_INLINE f32 ran_sinf(f32);
RANMATH_INLINE f64 ran_sind(f64);

RANMATH_INLINE f32 ran_tanf(f32);
RANMATH_INLINE f64 ran_tand(f64);

RANMATH_INLINE f32 ran_cotf(f32);
RANMATH_INLINE f64 ran_cotd(f64);

RANMATH_INLINE f32 ran_rad2degf(f32);
RANMATH_INLINE f64 ran_rad2degd(f64);

RANMATH_INLINE f32 ran_deg2radf(f32);
RANMATH_INLINE f64 ran_deg2radd(f64);

#endif /* RANMATH_H */

#ifdef RANMATH_IMPLEMENTATION

RANMATH_INLINE i32 ran_powi(i32 x, i32 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;

    i32 val = 1;
    i32 x2 = (x < 0) ? 1 / x : x;
    i32 i, p2 = ran_absi(p);
    for (i = 0; i < p2; ++i) {
        val *= x2;
    }

    return val;
}
RANMATH_INLINE i64 ran_powl(i64 x, i64 p) {
    if (x == 0 || x == 1) return x;
    if (p == 0) return 1;

    i64 val = 1;
    i64 x2 = (x < 0) ? 1 / x : x;
    i64 i, p2 = ran_absl(p);
    for (i = 0; i < p2; ++i) {
        val *= x2;
    }

    return val;
}

RANMATH_INLINE i32 ran_pow2i(i32 x) {
    return x * x;
}
RANMATH_INLINE i64 ran_pow2l(i64 x) {
    return x * x;
}
RANMATH_INLINE f32 ran_pow2f(f32 x) {
    return x * x;
}
RANMATH_INLINE f64 ran_pow2d(f64 x) {
    return x * x;
}

RANMATH_INLINE f32 ran_rsqrtf(f32 x) {
    union { f32 f; u32 i; } c = {x};

    f32 xh = 0.5 * x;

    c.i = 0x5F375A86 - (c.i >> 1);

    c.f *= 1.5 - (xh * c.f * c.f);
    c.f *= 1.5 - (xh * c.f * c.f);
    c.f *= 1.5 - (xh * c.f * c.f);

    return c.f;
}
RANMATH_INLINE f64 ran_rsqrtd(f64 x) {
    union { f64 f; u64 i; } c = {x};

    f64 xh = 0.5 * x;

    c.i = 0x5FE6EB50C7B537A9 - (c.i >> 1);

    c.f *= 1.5 - (xh * c.f * c.f);
    c.f *= 1.5 - (xh * c.f * c.f);
    c.f *= 1.5 - (xh * c.f * c.f);
    c.f *= 1.5 - (xh * c.f * c.f);

    return c.f;
}

RANMATH_INLINE f32 ran_sqrtf(f32 x) {
    return x * ran_rsqrtf(x);
}
RANMATH_INLINE f64 ran_sqrtd(f64 x) {
    return x * ran_rsqrtd(x);
}

RANMATH_INLINE i32 ran_absi(i32 x) {
    return (x < 0) ? -x : x;
}
RANMATH_INLINE i64 ran_absl(i64 x) {
    return (x < 0) ? -x : x;
}
RANMATH_INLINE f32 ran_absf(f32 x) {
    return (x < 0) ? -x : x;
}
RANMATH_INLINE f64 ran_absd(f64 x) {
    return (x < 0) ? -x : x;
}

RANMATH_INLINE f32 ran_floorf(f32 x) {
    if (x == 0) return x;
    i32 inx = (i32)x -1;
    return (x < 0) ? (inx == 0 ? -0.0 : inx) : (i32)x;
}
RANMATH_INLINE f64 ran_floord(f64 x) {
    if (x == 0) return x;
    i64 inx = (i64)x -1;
    return (x < 0) ? (inx == 0 ? -0.0 : inx) : (i64)x;
}

RANMATH_INLINE f32 ran_ceilf(f32 x) {
    if (x == 0) return x;
    i32 ix  = (i32)x;
    return (x < 0) ? (ix == 0 ? -0.0 : ix) : (i32)x + 1;
}
RANMATH_INLINE f64 ran_ceild(f64 x) {
    if (x == 0) return x;
    i64 ix  = (i64)x;
    return (x < 0) ? (ix == 0 ? -0.0 : ix) : (i64)x + 1;
}

RANMATH_INLINE f32 ran_roundf(f32 x) {
    bool c1 = (ran_absf(x) - ran_absi((i32)x)) < 0.5;
    bool c2 = x < 0;

    /*
    * if (c1) {
    *     if (c2) {
    *         return ran_ceilf(x);
    *     }
    *     return ran_floorf(x);
    * }
    * if (c2) {
    *     return ran_floorf(x);
    * }
    * return ran_ceilf(x);
    */

    return (c1) ? ((c2) ? ran_ceilf(x) : ran_floorf(x)) : ((c2) ? ran_floorf(x) : ran_ceilf(x));
}
RANMATH_INLINE f64 ran_roundd(f64 x) {
    bool c1 = (ran_absd(x) - ran_absl((i64)x)) < 0.5;
    bool c2 = x < 0;

    /*
    * if (c1) {
    *     if (c2) {
    *         return ran_ceild(x);
    *     }
    *     return ran_floord(x);
    * }
    * if (c2) {
    *     return ran_floord(x);
    * }
    * return ran_ceild(x);
    */

    return (c1) ? ((c2) ? ran_ceild(x) : ran_floord(x)) : ((c2) ? ran_floord(x) : ran_ceild(x));
}

RANMATH_INLINE f32 ran_cosf(f32 x) {
    const f32 i = RAN_PI_2 - ran_absf((x - RAN_2PI * ran_floorf(x * RAN_1_2PI)) - RAN_PI);
    const f64 i2 = i * i;
    const f64 i4 = i2 * i2;
    const f64 a = -0.132995644812022330410032839099700470577487194965079816065230286;
    const f64 b = 0.0032172781382535624048708288689972016965839213439467243797038973;
    const f64 c = 0.0336709157304375144254000370104015622020879871979042486728981326;
    const f64 d = 0.0004962828018660570906955733487210649504998482691550479603258607;

    const f64 val = 1 + a * i2 + b * i4;
    const f64 val2 = 1 / (1 + c * i2 + d * i4);

    return (f32)-i * val * val2;
}
RANMATH_INLINE f64 ran_cosd(f64 x) {
    const f64 i = RAN_PI_2 - ran_absd((x - RAN_2PI * ran_floord(x * RAN_1_2PI)) - RAN_PI);
    const f64 i2 = i * i;
    const f64 i4 = i2 * i2;
    const f64 a = -0.132995644812022330410032839099700470577487194965079816065230286;
    const f64 b = 0.0032172781382535624048708288689972016965839213439467243797038973;
    const f64 c = 0.0336709157304375144254000370104015622020879871979042486728981326;
    const f64 d = 0.0004962828018660570906955733487210649504998482691550479603258607;

    const f64 val = 1 + a * i2 + b * i4;
    const f64 val2 = 1 / (1 + c * i2 + d * i4);

    return -i * val * val2;
}

RANMATH_INLINE f32 ran_sinf(f32 x) {
    return -ran_cosf(x + RAN_PI_2);
}
RANMATH_INLINE f64 ran_sind(f64 x) {
    return -ran_cosd(x + RAN_PI_2);
}

RANMATH_INLINE f32 ran_tanf(f32 x) {
    return ran_sinf(x) / ran_cosf(x);
}
RANMATH_INLINE f64 ran_tand(f64 x) {
    return ran_sind(x) / ran_cosd(x);
}

RANMATH_INLINE f32 ran_cotf(f32 x) {
    return ran_cosf(x) / ran_sinf(x);
}
RANMATH_INLINE f64 ran_cotd(f64 x) {
    return ran_cosd(x) / ran_sind(x);
}

RANMATH_INLINE f32 ran_rad2degf(f32 x) {
    return RAN_MAKE_DEG * x;
}
RANMATH_INLINE f64 ran_rad2degd(f64 x) {
    return RAN_MAKE_DEG * x;
}

RANMATH_INLINE f32 ran_deg2radf(f32 x) {
    return RAN_MAKE_RAD * x;
}
RANMATH_INLINE f64 ran_deg2radd(f64 x) {
    return RAN_MAKE_RAD * x;
}

#endif /* RANMATH_IMPLEMENTATION */
