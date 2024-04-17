import re

file = open("test.txt", "w")

bools     = ["bool"]
unsigneds = ["u8", "u16", "u32", "u64"]
signeds   = ["i8", "i16", "i32", "i64"]
floating  = ["f32", "f64"]
scalars   = unsigneds + signeds + floating
types     = bools + scalars

comps = ["2", "3", "4"]
vectors = []
for type in types:
    for comp in comps:
        vectors.append(type+"x"+comp)

matrices = []
for vector in vectors:
    for comp in comps:
        matrices.append(vector+"x"+comp)

<<<<<<< HEAD
=======
inline = "#define RM_INLINE static inline\n"
file.write(inline)

>>>>>>> 45db7e32c7f35abfa413764092ec1f1d8e87f7a9
"""
------------------------------------FUNCTIONS-----------------------------------
"""
"""
-------------------------------------SCALARS------------------------------------
"""
constants = """
#define RM_HUGE_F32    u32_as_f32(0x7f7fffff)
#define RM_HUGE_F64    u64_as_f64(0x7fefffffffffffff)
#define RM_INF_F32     u32_as_f32(0x7f800000)
#define RM_INF_F64     u64_as_f64(0x7ff0000000000000)
/* THE MINIMUM TO BECOME NAN */
#define RM_NAN_F32     u32_as_f32(0x7fc00000)
#define RM_NAN_F64     u64_as_f64(0x7ff8000000000000)

#define RM_PI_F32      u32_as_f32(0x40490fdb)
#define RM_PI_F64      u64_as_f64(0x400921fb54442d18)
#define RM_2PI_F32     u32_as_f32(0x40c90fdb)
#define RM_2PI_F64     u64_as_f64(0x401921fb54442d18)
#define RM_PISQ_F32    u32_as_f32(0x411de9e7)
#define RM_PISQ_F64    u64_as_f64(0x4023bd3cc9be45de)
#define RM_SQRTPI_F32  u32_as_f32(0x3fe2dfc5)
#define RM_SQRTPI_F64  u64_as_f64(0x3ffc5bf891b4ef6a)
#define RM_RSQRTPI_F32 u32_as_f32(0x3f106eba)
#define RM_RSQRTPI_F64 u64_as_f64(0x3fe20dd750429b6d)
#define RM_PIO2_F32    u32_as_f32(0x3fc90fdb)
#define RM_PIO2_F64    u64_as_f64(0x3ff921fb54442d18)
#define RM_1OPI_F32    u32_as_f32(0x3ea2f983)
#define RM_1OPI_F64    u64_as_f64(0x3fd45f306dc9c883)
#define RM_2OPI_F32    u32_as_f32(0x3f22f983)
#define RM_2OPI_F64    u64_as_f64(0x3fe45f306dc9c883)
#define RM_DEG2RAD_F32 u32_as_f32(0x3c8efa35)
#define RM_DEG2RAD_F64 u64_as_f64(0x3f91df46a2529d39)
#define RM_RAD2DEG_F32 u32_as_f32(0x42652ee0)
#define RM_RAD2DEG_F64 u64_as_f64(0x404ca5dc1a63c1f8)
"""
#file.write(constants)

utils = """#define RM_ABS(_x) (((_x) < 0) ? -(_x) : (_x))
#define RM_MIN(_a, _b) (((_a) < (_b)) ? (_a) : (_b))
#define RM_MAX(_a, _b) (((_a) > (_b)) ? (_a) : (_b))
#define RM_CLAMP(_val, _min, _max) (RM_MIN(RM_MAX((_val), (_min)), (_max)))

"""
#file.write(utils)

sabs = """RM_INLINE {T} rm_abs_{T}(const {T} x) {{
    return RM_ABS(x);
}}
"""
smin = """RM_INLINE {T} rm_min_{T}(const {T} a, const {T} b) {{
    return RM_MIN(a, b);
}}
"""
smax = """RM_INLINE {T} rm_max_{T}(const {T} a, const {T} b) {{
    return RM_MAX(a, b);
}}
"""
sclamp = """RM_INLINE {T} rm_clamp_{T}(const {T} val, const {T} min, const {T} max) {{
    return RM_CLAMP(val, min, max);
}}
"""
smod = """RM_INLINE {T} rm_mod_{T}(const {T} a, const {T} b) {{
    return a % b;
}}
"""
strunc32 = """RM_INLINE f32 rm_trunc_f32(const f32 x) {
    return (i32)x;
}
"""
strunc64 = """RM_INLINE f64 rm_trunc_f64(const f64 x) {
    return (i64)x;
}
"""
smod32 = """RM_INLINE f32 rm_mod_f32(const f32 a, const f32 b) {
    return a - (rm_trunc_f32(a / b) * b);
}
"""
smod64 = """RM_INLINE f64 rm_mod_f64(const f64 a, const f64 b) {
    return a - (rm_trunc_f64(a / b) * b);
}
"""
ssign = """RM_INLINE {T} rm_sign_{T}(const {T} x) {{
    return (x > 0) - (x < 0);
}}
"""
scopysign = """RM_INLINE {T} rm_copysign_{T}(const {T} x, const {T} s) {{
    return rm_abs_{T}(x) * rm_sign_{T}(s);
}}
"""
sfloor32 = """RM_INLINE f32 rm_floor_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x - 1) : rm_trunc_f32(x);
}
"""
sfloor64 = """RM_INLINE f64 rm_floor_f64(const f64 x) {
    return (x < 0) ? rm_trunc_f64(x - 1) : rm_trunc_f64(x);
}
"""
sceil32 = """RM_INLINE f32 rm_ceil_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x) : rm_trunc_f32(x + 1);
}
"""
sceil64 = """RM_INLINE f64 rm_ceil_f64(const f64 x) {
    return (x < 0) ? rm_trunc_f64(x) : rm_trunc_f64(x + 1);
}
"""
sround32 = """RM_INLINE f32 rm_round_f32(const f32 x) {
    f32 t;

    if (x < 0) {
        t = rm_floor_f32(-x);
        return ((t + x) <= -0.5F) ? -(t + 1) : -t;
    }

    t = rm_floor_f32(x);
    return ((t - x) <= -0.5F) ? (t + 1) : t;
}
"""
sround64 = """RM_INLINE f64 rm_round_f64(const f64 x) {
    f64 t;

    if (x < 0) {
        t = rm_floor_f64(-x);
        return ((t + x) <= -0.5) ? -(t + 1) : -t;
    }

    t = rm_floor_f64(x);
    return ((t - x) <= -0.5) ? (t + 1) : t;
}
"""
sfract32 = """RM_INLINE f32 rm_fract_f32(const f32 x) {
    return x - rm_floor_f32(x);
}
"""
sfract64 = """RM_INLINE f64 rm_fract_f64(const f64 x) {
    return x - rm_floor_f64(x);
}
"""
sdeg2rad32 = """RM_INLINE f32 rm_deg2rad_f32(const f32 x) {
    return x * RM_DEG2RAD_F32;
}
"""
sdeg2rad64 = """RM_INLINE f64 rm_deg2rad_f64(const f64 x) {
    return x * RM_DEG2RAD_F64;
}
"""

srad2deg32 = """RM_INLINE f32 rm_rad2deg_f32(const f32 x) {
    return x * RM_RAD2DEG_F32;
}
"""
srad2deg64 = """RM_INLINE f64 rm_rad2deg_f64(const f64 x) {
    return x * RM_RAD2DEG_F64;
}
"""

sfuncs = []
for type in scalars:
    if type in signeds + floating:
        sfuncs.append(sabs.format(T=type))
    sfuncs.append((smin+smax+sclamp).format(T=type))
    if type == "f32":
        sfuncs.append(strunc32)
    if type == "f64":
        sfuncs.append(strunc64)

    if type in unsigneds + signeds:
        sfuncs.append(smod.format(T=type))
    if type == "f32":
        sfuncs.append(smod32)
    if type == "f64":
        sfuncs.append(smod64)
    if type in signeds + floating:
        sfuncs.append((ssign+scopysign).format(T=type))

sfuncs.append(sfloor32+sfloor64+sceil32+sceil64+sround32+sround64+sfract32+sfract64+sdeg2rad32+sdeg2rad64+srad2deg32+srad2deg64)

file.writelines(sfuncs)
"""
-------------------------------------VECTOR-------------------------------------
"""
vfuncs = """RM_INLINE {T}x{N} rm_{FN}s_{T}x{N}(const {T}x{N} v, const {T} s) {{
    return rm_{FN}_{T}x{N}(v, rm_{T}x{N}s(s));
}}
"""
vsfuncs = """RM_INLINE {T}x{N} rm_s{FN}_{T}x{N}(const {T} s, const {T}x{N} v) {{
    return rm_{FN}_{T}x{N}(rm_{T}x{N}s(s), v);
}}
"""
vbfuncs = """RM_INLINE boolx{N} rm_{FN}s_{T}x{N}(const {T}x{N} v, const {T} s) {{
    return rm_{FN}_{T}x{N}(v, rm_{T}x{N}s(s));
}}
"""
"""
------------------------------------BOOLEANS------------------------------------
"""
vanyx2 = """RM_INLINE bool rm_any_{T}x2(const {T}x2 v) {{
    return v.x || v.y;
}}
"""
vanyx3 = """RM_INLINE bool rm_any_{T}x3(const {T}x2 v) {{
    return (v.x || v.y) || v.z;
}}
"""
vanyx4 = """RM_INLINE bool rm_any_{T}x4(const {T}x2 v) {{
    return (v.x || v.y) || (v.z || v.w);
}}
"""

vallx2 = """RM_INLINE bool rm_all_{T}x2(const {T}x2 v) {{
    return v.x && v.y;
}}
"""
vallx3 = """RM_INLINE bool rm_all_{T}x3(const {T}x2 v) {{
    return (v.x && v.y) && v.z;
}}
"""
vallx4 = """RM_INLINE bool rm_all_{T}x4(const {T}x2 v) {{
    return (v.x && v.y) && (v.z && v.w);
}}
"""

vnotx2 = """RM_INLINE boolx2 rm_not_{T}x2(const {T}x2 v) {{
    return rm_boolx2(!v.x, !v.y);
}}
"""
vnotx3 = """RM_INLINE boolx3 rm_not_{T}x3(const {T}x3 v) {{
    return rm_boolx3(!v.x, !v.y, !v.z);
}}
"""
vnotx4 = """RM_INLINE boolx4 rm_not_{T}x4(const {T}x4 v) {{
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}}
"""

veqx2 = """RM_INLINE boolx2 rm_eq_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x == b.x, a.y == b.y);
}}
"""
veqx3 = """RM_INLINE boolx3 rm_eq_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}}
"""
veqx4 = """RM_INLINE boolx4 rm_eq_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}}
"""

vneqx2 = """RM_INLINE boolx2 rm_neq_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x != b.x, a.y != b.y);
}}
"""
vneqx3 = """RM_INLINE boolx3 rm_neq_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}}
"""
vneqx4 = """RM_INLINE boolx4 rm_neq_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}}
"""

vltx2 = """RM_INLINE boolx2 rm_lt_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x < b.x, a.y < b.y);
}}
"""
vltx3 = """RM_INLINE boolx3 rm_lt_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}}
"""
vltx4 = """RM_INLINE boolx4 rm_lt_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}}
"""

vlteqx2 = """RM_INLINE boolx2 rm_lteq_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}}
"""
vlteqx3 = """RM_INLINE boolx3 rm_lteq_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}}
"""
vlteqx4 = """RM_INLINE boolx4 rm_lteq_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}}
"""

vgtx2 = """RM_INLINE boolx2 rm_gt_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x > b.x, a.y > b.y);
}}
"""
vgtx3 = """RM_INLINE boolx3 rm_gt_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}}
"""
vgtx4 = """RM_INLINE boolx4 rm_gt_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}}
"""

vgteqx2 = """RM_INLINE boolx2 rm_gteq_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}}
"""
vgteqx3 = """RM_INLINE boolx3 rm_gteq_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}}
"""
vgteqx4 = """RM_INLINE boolx4 rm_gteq_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}}
"""

vany  = vanyx2  + vanyx3  + vanyx4
vall  = vallx2  + vallx3  + vallx4
vnot  = vnotx2  + vnotx3  + vnotx4
veq   = veqx2   + veqx3   + veqx4
vneq  = vneqx2  + vneqx3  + vneqx4
vlt   = vltx2   + vltx3   + vltx4
vlteq = vlteqx2 + vlteqx3 + vlteqx4
vgt   = vgtx2   + vgtx3   + vgtx4
vgteq = vgteqx2 + vgteqx3 + vgteqx4

boolfunc = vany + vall + vnot + veq + vneq + vlt + vlteq + vgt + vgteq

boolfunclist = ["eq", "neq", "lt", "lteq", "gt", "gteq"]

boolfuncs = []
for type in scalars:
    boolfuncs.append(boolfunc.format(T=type))
    for func in boolfunclist:
        for comp in comps:
            boolfuncs.append(vbfuncs.format(T=type, N=comp, FN=func))
file.writelines(boolfuncs)

"""
--------------------------------- ARITHMETIC------------------------------------
"""
vnegx2 = """RM_INLINE {T}x2 rm_neg_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(-v.x, -v.y);
}}
"""
vnegx3 = """RM_INLINE {T}x3 rm_neg_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(-v.x, -v.y, -v.z);
}}
"""
vnegx4 = """RM_INLINE {T}x4 rm_neg_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(-v.x, -v.y, -v.z, -v.w);
}}
"""
vabsx2 = """RM_INLINE {T}x2 rm_abs_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_abs_{T}(v.x), rm_abs_{T}(v.y));
}}
"""
vabsx3 = """RM_INLINE {T}x3 rm_abs_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_abs_{T}(v.x), rm_abs_{T}(v.y), rm_abs_{T}(v.z));
}}
"""
vabsx4 = """RM_INLINE {T}x4 rm_abs_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_abs_{T}(v.x), rm_abs_{T}(v.y), rm_abs_{T}(v.z), rm_abs_{T}(v.w));
}}
"""
vminx2 = """RM_INLINE {T}x2 rm_min_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(rm_min_{T}(a.x, b.x), rm_min_{T}(a.y, b.y));
}}
"""
vminx3 = """RM_INLINE {T}x3 rm_min_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(rm_min_{T}(a.x, b.x), rm_min_{T}(a.y, b.y),
                    rm_min_{T}(a.z, b.z));
}}
"""
vminx4 = """RM_INLINE {T}x4 rm_min_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(rm_min_{T}(a.x, b.x), rm_min_{T}(a.y, b.y),
                    rm_min_{T}(a.z, b.z), rm_min_{T}(a.w, b.w));
}}
"""
vmaxx2 = """RM_INLINE {T}x2 rm_max_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(rm_max_{T}(a.x, b.x), rm_max_{T}(a.y, b.y));
}}
"""
vmaxx3 = """RM_INLINE {T}x3 rm_max_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(rm_max_{T}(a.x, b.x), rm_max_{T}(a.y, b.y),
                    rm_max_{T}(a.z, b.z));
}}
"""
vmaxx4 = """RM_INLINE {T}x4 rm_max_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(rm_max_{T}(a.x, b.x), rm_max_{T}(a.y, b.y),
                    rm_max_{T}(a.z, b.z), rm_max_{T}(a.w, b.w));
}}
"""
vaddx2 = """RM_INLINE {T}x2 rm_add_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(a.x + b.x, a.y + b.y);
}}
"""
vaddx3 = """RM_INLINE {T}x3 rm_add_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(a.x + b.x, a.y + b.y, a.z + b.z);
}}
"""
vaddx4 = """RM_INLINE {T}x4 rm_add_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}}
"""
vsubx2 = """RM_INLINE {T}x2 rm_sub_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(a.x - b.x, a.y - b.y);
}}
"""
vsubx3 = """RM_INLINE {T}x3 rm_sub_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(a.x - b.x, a.y - b.y, a.z - b.z);
}}
"""
vsubx4 = """RM_INLINE {T}x4 rm_sub_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}}
"""
vmulx2 = """RM_INLINE {T}x2 rm_mul_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(a.x * b.x, a.y * b.y);
}}
"""
vmulx3 = """RM_INLINE {T}x3 rm_mul_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(a.x * b.x, a.y * b.y, a.z * b.z);
}}
"""
vmulx4 = """RM_INLINE {T}x4 rm_mul_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}}
"""
vdivx2 = """RM_INLINE {T}x2 rm_div_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(a.x / b.x, a.y / b.y);
}}
"""
vdivx3 = """RM_INLINE {T}x3 rm_div_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(a.x / b.x, a.y / b.y, a.z / b.z);
}}
"""
vdivx4 = """RM_INLINE {T}x4 rm_div_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}}
"""
vmodx2 = """RM_INLINE {T}x2 rm_mod_{T}x2(const {T}x2 a, const {T}x2 b) {{
    return rm_{T}x2(rm_mod_{T}(a.x, b.x), rm_mod_{T}(a.y, b.y));
}}
"""
vmodx3 = """RM_INLINE {T}x3 rm_mod_{T}x3(const {T}x3 a, const {T}x3 b) {{
    return rm_{T}x3(rm_mod_{T}(a.x, b.x), rm_mod_{T}(a.y, b.y),
                    rm_mod_{T}(a.z, b.z));
}}
"""
vmodx4 = """RM_INLINE {T}x4 rm_mod_{T}x4(const {T}x4 a, const {T}x4 b) {{
    return rm_{T}x4(rm_mod_{T}(a.x, b.x), rm_mod_{T}(a.y, b.y),
                    rm_mod_{T}(a.z, b.z), rm_mod_{T}(a.w, b.w));
}}
"""
vclampx2 = """RM_INLINE {T}x2 rm_clamp_{T}x2(const {T}x2 v, const {T}x2 min, const {T}x2 max) {{
    return rm_{T}x2(rm_clamp_{T}(v.x, min.x, max.x), rm_clamp_{T}(v.y, min.y, max.y));
}}
"""
vclampx3 = """RM_INLINE {T}x3 rm_clamp_{T}x3(const {T}x3 v, const {T}x3 min, const {T}x3 max) {{
    return rm_{T}x3(rm_clamp_{T}(v.x, min.x, max.x), rm_clamp_{T}(v.y, min.y, max.y),
                    rm_clamp_{T}(v.z, min.z, max.z));
}}
"""
vclampx4 = """RM_INLINE {T}x4 rm_clamp_{T}x4(const {T}x4 v, const {T}x4 min, const {T}x4 max) {{
    return rm_{T}x4(rm_clamp_{T}(v.x, min.x, max.x), rm_clamp_{T}(v.y, min.y, max.y),
                    rm_clamp_{T}(v.z, min.z, max.z), rm_clamp_{T}(v.w, min.w, max.w));
}}
"""
vclamps = """RM_INLINE {T}x{N} rm_clamps_{T}x{N}(const {T}x{N} v, {T} min, {T} max) {{
    return rm_clamp_{T}x{N}(v, rm_{T}x{N}s(min), rm_{T}x{N}s(max));
}}
"""
vsignx2 = """RM_INLINE {T}x2 rm_sign_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_sign_{T}(v.x), rm_sign_{T}(v.y));
}}
"""
vsignx3 = """RM_INLINE {T}x3 rm_sign_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_sign_{T}(v.x), rm_sign_{T}(v.y),
                    rm_sign_{T}(v.z));
}}
"""
vsignx4 = """RM_INLINE {T}x4 rm_sign_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_sign_{T}(v.x), rm_sign_{T}(v.y),
                    rm_sign_{T}(v.z), rm_sign_{T}(v.w));
}}
"""
vcopysignx2 = """RM_INLINE {T}x2 rm_copysign_{T}x2(const {T}x2 v, const {T}x2 s) {{
    return rm_{T}x2(rm_copysign_{T}(v.x, s.x), rm_copysign_{T}(v.y, s.y));
}}
"""
vcopysignx3 = """RM_INLINE {T}x3 rm_copysign_{T}x3(const {T}x3 v, const {T}x3 s) {{
    return rm_{T}x3(rm_copysign_{T}(v.x, s.x), rm_copysign_{T}(v.y, s.y),
                    rm_copysign_{T}(v.z, s.z));
}}
"""
vcopysignx4 = """RM_INLINE {T}x4 rm_copysign_{T}x4(const {T}x4 v, const {T}x4 s) {{
    return rm_{T}x4(rm_copysign_{T}(v.x, s.x), rm_copysign_{T}(v.y, s.y),
                    rm_copysign_{T}(v.z, s.z), rm_copysign_{T}(v.w, s.w));
}}
"""
vfma = """RM_INLINE {T}x{N} rm_fma_{T}x{N}(const {T}x{N} a, const {T}x{N} b, const {T}x{N} c) {{
    return rm_add_{T}x{N}(rm_mul_{T}x{N}(a, b), c);
}}
"""
vfmas = """RM_INLINE {T}x{N} rm_fmas_{T}x{N}(const {T}x{N} a, const {T}x{N} b, const {T} c) {{
    return rm_adds_{T}x{N}(rm_mul_{T}x{N}(a, b), c);
}}
"""
vfmass = """RM_INLINE {T}x{N} rm_fmass_{T}x{N}(const {T}x{N} a, const {T} b, const {T} c) {{
    return rm_adds_{T}x{N}(rm_muls_{T}x{N}(a, b), c);
}}
"""

vfloorx2 = """RM_INLINE {T}x2 rm_floor_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_floor_{T}(v.x), rm_floor_{T}(v.y));
}}
"""
vfloorx3 = """RM_INLINE {T}x3 rm_floor_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_floor_{T}(v.x), rm_floor_{T}(v.y),
                    rm_floor_{T}(v.z));
}}
"""
vfloorx4 = """RM_INLINE {T}x4 rm_floor_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_floor_{T}(v.x), rm_floor_{T}(v.y),
                    rm_floor_{T}(v.z), rm_floor_{T}(v.w));
}}
"""
vceilx2 = """RM_INLINE {T}x2 rm_ceil_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_ceil_{T}(v.x), rm_ceil_{T}(v.y));
}}
"""
vceilx3 = """RM_INLINE {T}x3 rm_ceil_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_ceil_{T}(v.x), rm_ceil_{T}(v.y),
                    rm_ceil_{T}(v.z));
}}
"""
vceilx4 = """RM_INLINE {T}x4 rm_ceil_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_ceil_{T}(v.x), rm_ceil_{T}(v.y),
                    rm_ceil_{T}(v.z), rm_ceil_{T}(v.w));
}}
"""
vroundx2 = """RM_INLINE {T}x2 rm_round_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_round_{T}(v.x), rm_round_{T}(v.y));
}}
"""
vroundx3 = """RM_INLINE {T}x3 rm_round_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_round_{T}(v.x), rm_round_{T}(v.y),
                    rm_round_{T}(v.z));
}}
"""
vroundx4 = """RM_INLINE {T}x4 rm_round_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_round_{T}(v.x), rm_round_{T}(v.y),
                    rm_round_{T}(v.z), rm_round_{T}(v.w));
}}
"""

vtruncx2 = """RM_INLINE {T}x2 rm_trunc_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_trunc_{T}(v.x), rm_trunc_{T}(v.y));
}}
"""
vtruncx3 = """RM_INLINE {T}x3 rm_trunc_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_trunc_{T}(v.x), rm_trunc_{T}(v.y),
                    rm_trunc_{T}(v.z));
}}
"""
vtruncx4 = """RM_INLINE {T}x4 rm_trunc_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_trunc_{T}(v.x), rm_trunc_{T}(v.y),
                    rm_trunc_{T}(v.z), rm_trunc_{T}(v.w));
}}
"""

vfractx2 = """RM_INLINE {T}x2 rm_fract_{T}x2(const {T}x2 v) {{
    return rm_{T}x2(rm_fract_{T}(v.x), rm_fract_{T}(v.y));
}}
"""
vfractx3 = """RM_INLINE {T}x3 rm_fract_{T}x3(const {T}x3 v) {{
    return rm_{T}x3(rm_fract_{T}(v.x), rm_fract_{T}(v.y),
                    rm_fract_{T}(v.z));
}}
"""
vfractx4 = """RM_INLINE {T}x4 rm_fract_{T}x4(const {T}x4 v) {{
    return rm_{T}x4(rm_fract_{T}(v.x), rm_fract_{T}(v.y),
                    rm_fract_{T}(v.z), rm_fract_{T}(v.w));
}}
"""

vneg      = vnegx2      + vnegx3      + vnegx4
vabs      = vabsx2      + vabsx3      + vabsx4

vmin      = vminx2      + vminx3      + vminx4
vmax      = vmaxx2      + vmaxx3      + vmaxx4
vadd      = vaddx2      + vaddx3      + vaddx4
vsub      = vsubx2      + vsubx3      + vsubx4
vmul      = vmulx2      + vmulx3      + vmulx4
vdiv      = vdivx2      + vdivx3      + vdivx4
vmod      = vmodx2      + vmodx3      + vmodx4
vclamp    = vclampx2    + vclampx3    + vclampx4

vsign     = vsignx2     + vsignx3     + vsignx4
vcopysign = vcopysignx2 + vcopysignx3 + vcopysignx4

vfloor    = vfloorx2    + vfloorx3    + vfloorx4
vceil     = vceilx2     + vceilx3     + vceilx4
vround    = vroundx2    + vroundx3    + vroundx4
vtrunc    = vtruncx2    + vtruncx3    + vtruncx4
vfract    = vfractx2    + vfractx3    + vfractx4

arithmetics = []
for type in signeds + floating:
    arithmetics.append((vneg+vabs).format(T=type))

vt = vmin + vmax + vadd + vsub + vmul + vdiv + vmod + vclamp

vfunclist = ["min", "max", "add", "sub", "mul", "div", "mod"]

for type in scalars:
    arithmetics.append(vt.format(T=type))
    if re.search("[fi]", type):
        arithmetics.append((vsign+vcopysign).format(T=type))
    for comp in comps:
        arithmetics.append(vfma.format(T=type, N=comp))
    for vfunc in vfunclist:
        for comp in comps:
            arithmetics.append(vfuncs.format(T=type, N=comp, FN=vfunc))
            if vfunc in ("min", "max", "add", "mul"):
                continue
            arithmetics.append(vsfuncs.format(T=type, N=comp, FN=vfunc))
    for comp in comps:
        arithmetics.append(vclamps.format(T=type, N=comp))
        if re.search("[fi]", type):
            arithmetics.append(vfuncs.format(T=type, N=comp, FN="copysign"))
        arithmetics.append((vfmas+vfmass).format(T=type, N=comp))

for type in floating:
    arithmetics.append((vfloor+vceil+vround+vtrunc+vfract).format(T=type))

#file.writelines(arithmetics)
