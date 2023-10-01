scalar_unsigned = ["u8", "u16", "u32", "u64"]
scalar_signed   = ["i8", "i16", "i32", "i64"]
scalar_floating = ["f32", "f64"]

scalar_types    = scalar_unsigned + scalar_signed + scalar_floating

scalar_abs = """RM_INLINE {T} rm_abs_{T}({T} x) {{
    return RM_ABS(x);
}}"""

scalar_min = """RM_INLINE {T} rm_min_{T}({T} x) {{
    return RM_MIN(x);
}}
"""
scalar_max = """RM_INLINE {T} rm_max_{T}({T} x) {{
    return RM_MAX(x);
}}
"""
scalar_clamp = """RM_INLINE {T} rm_clamp_{T}({T} val, {T} min, {T} max) {{
    return RM_CLAMP(val, min, max);
}}"""

scalar_trunc_floating = """RM_INLINE {T} rm_trunc_{T}({T} x) {{
    return ({TI})x;
}}"""

scalar_mod_integers = """RM_INLINE {T} rm_mod_{T}({T} a, {T} b) {{
    return a % b;
}}"""
scalar_mod_floating = """RM_INLINE {T} rm_mod_{T}({T} a, {T} b) {{
    return a - (rm_trunc_{T}(a / b) * b);
}}"""

scalar_sign = """RM_INLINE {T} rm_sign_{T}({T} x) {{
    return RM_SIGN(x);
}}
"""
scalar_copysign = """RM_INLINE rm_copysign_{T}({T} x, {T} s) {{
    return rm_abs_{T}(x) * rm_sign_{T}(s);
}}"""



scalar_functions = []
for type in scalar_types:
    if type in scalar_signed + scalar_floating:
        scalar_functions.append(scalar_abs.format(T=type))
    scalar_functions.append((scalar_min + scalar_max + scalar_clamp).format(T=type))

    if type == "f32":
        scalar_functions.append(scalar_trunc_floating.format(T=type, TI="i32"))
    if type == "f64":
        scalar_functions.append(scalar_trunc_floating.format(T=type, TI="i64"))

    if type in scalar_unsigned + scalar_signed:
        scalar_functions.append(scalar_mod_integers.format(T=type))
    if type in scalar_floating:
        scalar_functions.append(scalar_mod_floating.format(T=type))

    if type in scalar_signed + scalar_floating:
        scalar_functions.append((scalar_sign + scalar_copysign).format(T=type))

for scalar_function in scalar_functions:
    print(scalar_function)

test = """{T}_test, {TC}_TEST"""
print(test.format(T="f32", TC="f32".upper()))
