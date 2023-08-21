/*
* MIT License
*
* Copyright (c) 2023 Ransel117
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

#define RM_PLATFORM_LINUX           0x1
#define RM_PLATFORM_WINDOWS         0x2

#if defined(__linux__)
#define RM_PLATFORM RM_PLATFORM_LINUX
#elif defined(_MSC_VER)
#define RM_PLATFORM RM_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#else
#error unsupported platform
#endif /* CHECK PLATFORM */

#define RM_ARCH_X86                 (1 << 0)
/* 32-bit arm and 64-bit arm, RM_ARCH_ARM is for either */
#define RM_ARCH_AARCH32             (1 << 0)
#define RM_ARCH_AARCH64             (1 << 1)
#if defined(__x86_64__)    || defined(_M_X64)      ||    \
    defined(__amd64__)     || defined(_M_AMD64)    ||    \
    defined(__i386__)      || defined(_M_IX86)
#define RM_ARCH RM_ARCH_X86
#elif defined(__aarch64__) || defined(_M_ARM64)
#define RM_ARCH_ARM RM_ARCH_AARCH64 | RM_ARCH_AARCH32
#define RM_ARCH     RM_ARCH_ARM
#elif defined(__arm__)     || defined(_M_ARM)
#define RM_ARCH_ARM RM_ARCH_AARCH32
#define RM_ARCH     RM_ARCH_ARM
#else
#error unsupported architecture
#endif /* CHECK ARCHITECTURE */

#define RM_BYTE_ORDER_BIG_ENDIAN    4321
#define RM_BYTE_ORDER_LITTLE_ENDIAN 1234
#if RM_PLATFORM == RM_PLATFORM_LINUX

#if defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define RM_BYTE_ORDER RM_BYTE_ORDER_BIG_ENDIAN
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define RM_BYTE_ORDER RM_BYTE_ORDER_LITTLE_ENDIAN
#else
#error unsupported byte order
#endif /* __BYTE_ORDER__ */
#endif

/*
 * according to https://en.wikipedia.org/wiki/Endianness#Newer_architectures
 * x86 is little-endian and arm/aarch64 are bi-endian to some degree.
 *
 * according to
 * https://developer.arm.com/documentation/dui0472/m/Compiler-specific-Features/Predefined-macros
 * and
 * https://developer.arm.com/documentation/101754/0620/armclang-Reference/Other-Compiler-specific-Features/Predefined-macros
 * the compilers should specify if the target is big-endian.
 */
#elif RM_ARCH == RM_ARCH_X86
#define RM_BYTE_ORDER RM_BYTE_ORDER_LITTLE_ENDIAN

#elif RM_ARCH == RM_ARCH_ARM
#if defined(__BIG_ENDIAN) || defined(__ARM_BIG_ENDIAN)
#define RM_BYTE_ORDER RM_BYTE_ORDER_BIG_ENDIAN
#else
#define RM_BYTE_ORDER RM_BYTE_ORDER_LITTLE_ENDIAN
#endif
#endif /* CHECK BYTE ORDER */

#if !defined(RM_NO_INTRINSICS)

#if RM_ARCH == RM_ARCH_X86
/* fallthroughs for windows since it only checks for SSE/SSE2 and AVX/AVX2 */
#if defined(__AVX2__)
#if !defined(RM_AVX2)
#define RM_AVX2 (1 << 7)
#endif
#endif /* AVX2 INTRINSICS */

#if defined(__AVX__) || defined(RM_AVX2)
#if !defined(RM_AVX)
#define RM_AVX (1 << 6)
#endif
#endif /* AVX INTRINSICS */

#if defined(__SSE4_2__) || defined(RM_AVX)
#if !defined(RM_SSE4_2)
#define RM_SSE4_2 (1 << 5)
#endif
#endif /* SSE4.2 INTRINSICS */

#if defined(__SSE4_1__) || defined(RM_SSE4_2)
#if !defined(RM_SSE4_1)
#define RM_SSE4_1 (1 << 4)
#endif
#endif /* SSE4.1 INTRINSICS */

#if defined(__SSSE3__) || defined(RM_SSE4_1)
#if !defined(RM_SSSE3)
#define RM_SSSE3 (1 << 3)
#endif
#endif /* SSSE3 INTRINSICS */

#if defined(__SSE3__) || defined(RM_SSSE3)
#if !defined(RM_SSE3)
#define RM_SSE3 (1 << 2)
#endif
#endif /* SSE3 INTRINSICS */

#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP == 2) ||    \
    defined(RM_SSE3)
#if !defined(RM_SSE2)
#define RM_SSE2 (1 << 1)
#endif
#endif /* SSE2 INTRINSICS */

#if defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP == 1) ||     \
    defined(RM_SSE2)
#if !defined(RM_SSE)
#define RM_SSE (1 << 0)
#endif
#endif /* SSE1 INTRINSICS */
#define RM_SIMD RM_AVX2  | RM_AVX  | RM_SSE4_2 | RM_SSE4_1 |    \
                RM_SSSE3 | RM_SSE3 | RM_SSE2   | RM_SSE
#endif /* X86 SIMD INTRINSICS */

#if RM_ARCH == RM_ARCH_ARM
#if (defined(__ARM_NEON__)    || defined(__ARM_NEON)) &&       \
    (defined(__ARM_NEON_FP__) || defined(__ARM_NEON_FP))
#if !defined(RM_NEON)
#define RM_NEON (1 << 0)
#endif
#endif /* NEON INTRINSICS */
#define RM_SIMD RM_NEON
#endif /* ARM SIMD INTRINSICS */
#endif /* NO INTRINSICS */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* TEMPORARY, WILL STAY UNTIL EVERYTHING ELSE IS IMPLEMENTED */
#include <math.h>

#if !defined(RM_NO_INTRINSICS)
#if RM_ARCH == RM_ARCH_X86
#if defined(RM_AVX2) || defined(RM_AVX)
#include <immintrin.h>
#endif

#if defined(RM_SSE4_2)
#include <nmmintrin.h>
#endif

#if defined(RM_SSE4_1)
#include <smmintrin.h>
#endif

#if defined(RM_SSSE3)
#include <tmmintrin.h>
#endif

#if defined(RM_SSE3)
#include <pmmintrin.h>
#endif

#if defined(RM_SSE2)
#include <emmintrin.h>
#endif

#if defined(RM_SSE)
#include <xmmintrin.h>
#endif
#endif /* X86 INTRINSICS */

#if RM_ARCH == RM_ARCH_ARM
#if defined(RM_NEON)
#include <arm_neon.h>
#endif
#endif /* ARM INTRINSICS */
#endif /* NO INTRINSICS */

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
typedef size_t   usize;

typedef struct f32_cvt_t  f32_cvt;
typedef struct f64_cvt_t  f64_cvt;
typedef struct boolx2_t   boolx2;
typedef struct boolx3_t   boolx3;
typedef struct boolx4_t   boolx4;
typedef struct u8x2_t     u8x2;
typedef struct u8x3_t     u8x3;
typedef struct u8x4_t     u8x4;
typedef struct u16x2_t    u16x2;
typedef struct u16x3_t    u16x3;
typedef struct u16x4_t    u16x4;
typedef struct u32x2_t    u32x2;
typedef struct u32x3_t    u32x3;
typedef struct u32x4_t    u32x4;
typedef struct u64x2_t    u64x2;
typedef struct u64x3_t    u64x3;
typedef struct u64x4_t    u64x4;
typedef struct i8x2_t     i8x2;
typedef struct i8x3_t     i8x3;
typedef struct i8x4_t     i8x4;
typedef struct i16x2_t    i16x2;
typedef struct i16x3_t    i16x3;
typedef struct i16x4_t    i16x4;
typedef struct i32x2_t    i32x2;
typedef struct i32x3_t    i32x3;
typedef struct i32x4_t    i32x4;
typedef struct i64x2_t    i64x2;
typedef struct i64x3_t    i64x3;
typedef struct i64x4_t    i64x4;
typedef struct f32x2_t    f32x2;
typedef struct f32x3_t    f32x3;
typedef struct f32x4_t    f32x4;
typedef struct f64x2_t    f64x2;
typedef struct f64x3_t    f64x3;
typedef struct f64x4_t    f64x4;
typedef struct boolx2x2_t boolx2x2;
typedef struct boolx2x3_t boolx2x3;
typedef struct boolx2x4_t boolx2x4;
typedef struct boolx3x2_t boolx3x2;
typedef struct boolx3x3_t boolx3x3;
typedef struct boolx3x4_t boolx3x4;
typedef struct boolx4x2_t boolx4x2;
typedef struct boolx4x3_t boolx4x3;
typedef struct boolx4x4_t boolx4x4;
typedef struct u8x2x2_t   u8x2x2;
typedef struct u8x2x3_t   u8x2x3;
typedef struct u8x2x4_t   u8x2x4;
typedef struct u8x3x2_t   u8x3x2;
typedef struct u8x3x3_t   u8x3x3;
typedef struct u8x3x4_t   u8x3x4;
typedef struct u8x4x2_t   u8x4x2;
typedef struct u8x4x3_t   u8x4x3;
typedef struct u8x4x4_t   u8x4x4;
typedef struct u16x2x2_t  u16x2x2;
typedef struct u16x2x3_t  u16x2x3;
typedef struct u16x2x4_t  u16x2x4;
typedef struct u16x3x2_t  u16x3x2;
typedef struct u16x3x3_t  u16x3x3;
typedef struct u16x3x4_t  u16x3x4;
typedef struct u16x4x2_t  u16x4x2;
typedef struct u16x4x3_t  u16x4x3;
typedef struct u16x4x4_t  u16x4x4;
typedef struct u32x2x2_t  u32x2x2;
typedef struct u32x2x3_t  u32x2x3;
typedef struct u32x2x4_t  u32x2x4;
typedef struct u32x3x2_t  u32x3x2;
typedef struct u32x3x3_t  u32x3x3;
typedef struct u32x3x4_t  u32x3x4;
typedef struct u32x4x2_t  u32x4x2;
typedef struct u32x4x3_t  u32x4x3;
typedef struct u32x4x4_t  u32x4x4;
typedef struct u64x2x2_t  u64x2x2;
typedef struct u64x2x3_t  u64x2x3;
typedef struct u64x2x4_t  u64x2x4;
typedef struct u64x3x2_t  u64x3x2;
typedef struct u64x3x3_t  u64x3x3;
typedef struct u64x3x4_t  u64x3x4;
typedef struct u64x4x2_t  u64x4x2;
typedef struct u64x4x3_t  u64x4x3;
typedef struct u64x4x4_t  u64x4x4;
typedef struct i8x2x2_t   i8x2x2;
typedef struct i8x2x3_t   i8x2x3;
typedef struct i8x2x4_t   i8x2x4;
typedef struct i8x3x2_t   i8x3x2;
typedef struct i8x3x3_t   i8x3x3;
typedef struct i8x3x4_t   i8x3x4;
typedef struct i8x4x2_t   i8x4x2;
typedef struct i8x4x3_t   i8x4x3;
typedef struct i8x4x4_t   i8x4x4;
typedef struct i16x2x2_t  i16x2x2;
typedef struct i16x2x3_t  i16x2x3;
typedef struct i16x2x4_t  i16x2x4;
typedef struct i16x3x2_t  i16x3x2;
typedef struct i16x3x3_t  i16x3x3;
typedef struct i16x3x4_t  i16x3x4;
typedef struct i16x4x2_t  i16x4x2;
typedef struct i16x4x3_t  i16x4x3;
typedef struct i16x4x4_t  i16x4x4;
typedef struct i32x2x2_t  i32x2x2;
typedef struct i32x2x3_t  i32x2x3;
typedef struct i32x2x4_t  i32x2x4;
typedef struct i32x3x2_t  i32x3x2;
typedef struct i32x3x3_t  i32x3x3;
typedef struct i32x3x4_t  i32x3x4;
typedef struct i32x4x2_t  i32x4x2;
typedef struct i32x4x3_t  i32x4x3;
typedef struct i32x4x4_t  i32x4x4;
typedef struct i64x2x2_t  i64x2x2;
typedef struct i64x2x3_t  i64x2x3;
typedef struct i64x2x4_t  i64x2x4;
typedef struct i64x3x2_t  i64x3x2;
typedef struct i64x3x3_t  i64x3x3;
typedef struct i64x3x4_t  i64x3x4;
typedef struct i64x4x2_t  i64x4x2;
typedef struct i64x4x3_t  i64x4x3;
typedef struct i64x4x4_t  i64x4x4;
typedef struct f32x2x2_t  f32x2x2;
typedef struct f32x2x3_t  f32x2x3;
typedef struct f32x2x4_t  f32x2x4;
typedef struct f32x3x2_t  f32x3x2;
typedef struct f32x3x3_t  f32x3x3;
typedef struct f32x3x4_t  f32x3x4;
typedef struct f32x4x2_t  f32x4x2;
typedef struct f32x4x3_t  f32x4x3;
typedef struct f32x4x4_t  f32x4x4;
typedef struct f64x2x2_t  f64x2x2;
typedef struct f64x2x3_t  f64x2x3;
typedef struct f64x2x4_t  f64x2x4;
typedef struct f64x3x2_t  f64x3x2;
typedef struct f64x3x3_t  f64x3x3;
typedef struct f64x3x4_t  f64x3x4;
typedef struct f64x4x2_t  f64x4x2;
typedef struct f64x4x3_t  f64x4x3;
typedef struct f64x4x4_t  f64x4x4;

struct f32_cvt_t {
    union {
        f32 f;
        u32 u;
        i32 i;
    };
};
struct f64_cvt_t {
    union {
        f64 f;
        u64 u;
        i64 i;
/* [ui]0 is msw */
#if RM_BYTE_ORDER == RM_BYTE_ORDER_BIG_ENDIAN
        struct {u32 u0, u1;};
        struct {i32 i0, i1;};
#elif RM_BYTE_ORDER == RM_BYTE_ORDER_LITTLE_ENDIAN
        struct {u32 u1, u0;};
        struct {i32 i1, i0;};
#endif /* RM_BYTE_ORDER */
    };
};
struct boolx2_t {
    union {
        struct {bool x, y;};
        struct {bool z, w;};
        struct {bool r, g;};
        struct {bool b, a;};
        struct {bool u, v;};

        bool   raw[2];
    };
};
struct boolx3_t {
    union {
        struct {bool x, y, z;};
        struct {bool r, g, b;};

        struct {boolx2 xy; bool   _0;};
        struct {bool   _1; boolx2 yz;};

        struct {boolx2 rg; bool   _2;};
        struct {bool   _3; boolx2 gb;};

        bool   raw[3];
    };
};
struct boolx4_t {
    union {
        struct {bool x, y, z, w;};
        struct {bool r, g, b, a;};

        struct {boolx2 xy,  zw;};
        struct {boolx2 rg,  ba;};

        struct {boolx3 xyz; bool   _0;};
        struct {bool   _1;  boolx3 yzw;};

        struct {boolx3 rgb; bool   _2;};
        struct {bool   _3;  boolx3 gba;};

        struct {bool   _4;  boolx2 yz; bool _5;};
        struct {bool   _6;  boolx2 gb; bool _7;};

        bool   raw[4];
    };
};
struct u8x2_t {
    union {
        struct {u8 x, y;};
        struct {u8 z, w;};
        struct {u8 r, g;};
        struct {u8 b, a;};
        struct {u8 u, v;};

        u8     raw[2];
    };
};
struct u8x3_t {
    union {
        struct {u8 x, y, z;};
        struct {u8 r, g, b;};

        struct {u8x2 xy; u8   _0;};
        struct {u8   _1; u8x2 yz;};

        struct {u8x2 rg; u8   _2;};
        struct {u8   _3; u8x2 gb;};

        u8     raw[3];
    };
};
struct u8x4_t {
    union {
        struct {u8 x, y, z, w;};
        struct {u8 r, g, b, a;};

        struct {u8x2 xy,  zw;};
        struct {u8x2 rg,  ba;};

        struct {u8x3 xyz; u8   _0;};
        struct {u8   _1;  u8x3 yzw;};

        struct {u8x3 rgb; u8   _2;};
        struct {u8   _3;  u8x3 gba;};

        struct {u8   _4;  u8x2 yz; u8 _5;};
        struct {u8   _6;  u8x2 gb; u8 _7;};

        u8     raw[4];
    };
};
struct u16x2_t {
    union {
        struct {u16 x, y;};
        struct {u16 z, w;};
        struct {u16 r, g;};
        struct {u16 b, a;};
        struct {u16 u, v;};

        u16    raw[2];
    };
};
struct u16x3_t {
    union {
        struct {u16 x, y, z;};
        struct {u16 r, g, b;};

        struct {u16x2 xy; u16   _0;};
        struct {u16   _1; u16x2 yz;};

        struct {u16x2 rg; u16   _2;};
        struct {u16   _3; u16x2 gb;};

        u16    raw[3];
    };
};
struct u16x4_t {
    union {
        struct {u16 x, y, z, w;};
        struct {u16 r, g, b, a;};

        struct {u16x2 xy,  zw;};
        struct {u16x2 rg,  ba;};

        struct {u16x3 xyz; u16   _0;};
        struct {u16   _1;  u16x3 yzw;};

        struct {u16x3 rgb; u16   _2;};
        struct {u16   _3;  u16x3 gba;};

        struct {u16   _4;  u16x2 yz; u16 _5;};
        struct {u16   _6;  u16x2 gb; u16 _7;};

        u16    raw[4];
    };
};
struct u32x2_t {
    union {
        struct {u32 x, y;};
        struct {u32 z, w;};
        struct {u32 r, g;};
        struct {u32 b, a;};
        struct {u32 u, v;};

        u32    raw[2];
    };
};
struct u32x3_t {
    union {
        struct {u32 x, y, z;};
        struct {u32 r, g, b;};

        struct {u32x2 xy; u32   _0;};
        struct {u32   _1; u32x2 yz;};

        struct {u32x2 rg; u32   _2;};
        struct {u32   _3; u32x2 gb;};

        u32    raw[3];
    };
};
struct u32x4_t {
    union {
        struct {u32 x, y, z, w;};
        struct {u32 r, g, b, a;};

        struct {u32x2 xy,  zw;};
        struct {u32x2 rg,  ba;};

        struct {u32x3 xyz; u32   _0;};
        struct {u32   _1;  u32x3 yzw;};

        struct {u32x3 rgb; u32   _2;};
        struct {u32   _3;  u32x3 gba;};

        struct {u32   _4;  u32x2 yz; u32 _5;};
        struct {u32   _6;  u32x2 gb; u32 _7;};

        u32    raw[4];
    };
};
struct u64x2_t {
    union {
        struct {u64 x, y;};
        struct {u64 z, w;};
        struct {u64 r, g;};
        struct {u64 b, a;};
        struct {u64 u, v;};

        u64    raw[2];
    };
};
struct u64x3_t {
    union {
        struct {u64 x, y, z;};
        struct {u64 r, g, b;};

        struct {u64x2 xy; u64   _0;};
        struct {u64   _1; u64x2 yz;};

        struct {u64x2 rg; u64   _2;};
        struct {u64   _3; u64x2 gb;};

        u64    raw[3];
    };
};
struct u64x4_t {
    union {
        struct {u64 x, y, z, w;};
        struct {u64 r, g, b, a;};

        struct {u64x2 xy,  zw;};
        struct {u64x2 rg,  ba;};

        struct {u64x3 xyz; u64   _0;};
        struct {u64   _1;  u64x3 yzw;};

        struct {u64x3 rgb; u64   _2;};
        struct {u64   _3;  u64x3 gba;};

        struct {u64   _4;  u64x2 yz; u64 _5;};
        struct {u64   _6;  u64x2 gb; u64 _7;};

        u64    raw[4];
    };
};
struct i8x2_t {
    union {
        struct {i8 x, y;};
        struct {i8 z, w;};
        struct {i8 r, g;};
        struct {i8 b, a;};
        struct {i8 u, v;};

        i8     raw[2];
    };
};
struct i8x3_t {
    union {
        struct {i8 x, y, z;};
        struct {i8 r, g, b;};

        struct {i8x2 xy; i8   _0;};
        struct {i8   _1; i8x2 yz;};

        struct {i8x2 rg; i8   _2;};
        struct {i8   _3; i8x2 gb;};

        i8     raw[3];
    };
};
struct i8x4_t {
    union {
        struct {i8 x, y, z, w;};
        struct {i8 r, g, b, a;};

        struct {i8x2 xy,  zw;};
        struct {i8x2 rg,  ba;};

        struct {i8x3 xyz; i8   _0;};
        struct {i8   _1;  i8x3 yzw;};

        struct {i8x3 rgb; i8   _2;};
        struct {i8   _3;  i8x3 gba;};

        struct {i8   _4;  i8x2 yz; i8 _5;};
        struct {i8   _6;  i8x2 gb; i8 _7;};

        i8     raw[4];
    };
};
struct i16x2_t {
    union {
        struct {i16 x, y;};
        struct {i16 z, w;};
        struct {i16 r, g;};
        struct {i16 b, a;};
        struct {i16 u, v;};

        i16    raw[2];
    };
};
struct i16x3_t {
    union {
        struct {i16 x, y, z;};
        struct {i16 r, g, b;};

        struct {i16x2 xy; i16   _0;};
        struct {i16   _1; i16x2 yz;};

        struct {i16x2 rg; i16   _2;};
        struct {i16   _3; i16x2 gb;};

        i16    raw[3];
    };
};
struct i16x4_t {
    union {
        struct {i16 x, y, z, w;};
        struct {i16 r, g, b, a;};

        struct {i16x2 xy,  zw;};
        struct {i16x2 rg,  ba;};

        struct {i16x3 xyz; i16   _0;};
        struct {i16   _1;  i16x3 yzw;};

        struct {i16x3 rgb; i16   _2;};
        struct {i16   _3;  i16x3 gba;};

        struct {i16   _4;  i16x2 yz; i16 _5;};
        struct {i16   _6;  i16x2 gb; i16 _7;};

        i16    raw[4];
    };
};
struct i32x2_t {
    union {
        struct {i32 x, y;};
        struct {i32 z, w;};
        struct {i32 r, g;};
        struct {i32 b, a;};
        struct {i32 u, v;};

        i32    raw[2];
    };
};
struct i32x3_t {
    union {
        struct {i32 x, y, z;};
        struct {i32 r, g, b;};

        struct {i32x2 xy; i32   _0;};
        struct {i32   _1; i32x2 yz;};

        struct {i32x2 rg; i32   _2;};
        struct {i32   _3; i32x2 gb;};

        i32    raw[3];
    };
};
struct i32x4_t {
    union {
        struct {i32 x, y, z, w;};
        struct {i32 r, g, b, a;};

        struct {i32x2 xy,  zw;};
        struct {i32x2 rg,  ba;};

        struct {i32x3 xyz; i32   _0;};
        struct {i32   _1;  i32x3 yzw;};

        struct {i32x3 rgb; i32   _2;};
        struct {i32   _3;  i32x3 gba;};

        struct {i32   _4;  i32x2 yz; i32 _5;};
        struct {i32   _6;  i32x2 gb; i32 _7;};

        i32    raw[4];
    };
};
struct i64x2_t {
    union {
        struct {i64 x, y;};
        struct {i64 z, w;};
        struct {i64 r, g;};
        struct {i64 b, a;};
        struct {i64 u, v;};

        i64    raw[2];
    };
};
struct i64x3_t {
    union {
        struct {i64 x, y, z;};
        struct {i64 r, g, b;};

        struct {i64x2 xy; i64   _0;};
        struct {i64   _1; i64x2 yz;};

        struct {i64x2 rg; i64   _2;};
        struct {i64   _3; i64x2 gb;};

        i64    raw[3];
    };
};
struct i64x4_t {
    union {
        struct {i64 x, y, z, w;};
        struct {i64 r, g, b, a;};

        struct {i64x2 xy,  zw;};
        struct {i64x2 rg,  ba;};

        struct {i64x3 xyz; i64   _0;};
        struct {i64   _1;  i64x3 yzw;};

        struct {i64x3 rgb; i64   _2;};
        struct {i64   _3;  i64x3 gba;};

        struct {i64   _4;  i64x2 yz; i64 _5;};
        struct {i64   _6;  i64x2 gb; i64 _7;};

        i64    raw[4];
    };
};
struct f32x2_t {
    union {
        struct {f32 x, y;};
        struct {f32 z, w;};
        struct {f32 r, g;};
        struct {f32 b, a;};
        struct {f32 u, v;};

        f32    raw[2];
    };
};
struct f32x3_t {
    union {
        struct {f32 x, y, z;};
        struct {f32 r, g, b;};

        struct {f32x2 xy; f32   _0;};
        struct {f32   _1; f32x2 yz;};

        struct {f32x2 rg; f32   _2;};
        struct {f32   _3; f32x2 gb;};

        f32    raw[3];
    };
};
struct f32x4_t {
    union {
        struct {f32 x, y, z, w;};
        struct {f32 r, g, b, a;};

        struct {f32x2 xy,  zw;};
        struct {f32x2 rg,  ba;};

        struct {f32x3 xyz; f32   _0;};
        struct {f32   _1;  f32x3 yzw;};

        struct {f32x3 rgb; f32   _2;};
        struct {f32   _3;  f32x3 gba;};

        struct {f32   _4;  f32x2 yz; f32 _5;};
        struct {f32   _6;  f32x2 gb; f32 _7;};

        f32    raw[4];
    };
};
struct f64x2_t {
    union {
        struct {f64 x, y;};
        struct {f64 z, w;};
        struct {f64 r, g;};
        struct {f64 b, a;};
        struct {f64 u, v;};

        f64    raw[2];
    };
};
struct f64x3_t {
    union {
        struct {f64 x, y, z;};
        struct {f64 r, g, b;};

        struct {f64x2 xy; f64   _0;};
        struct {f64   _1; f64x2 yz;};

        struct {f64x2 rg; f64   _2;};
        struct {f64   _3; f64x2 gb;};

        f64    raw[3];
    };
};
struct f64x4_t {
    union {
        struct {f64 x, y, z, w;};
        struct {f64 r, g, b, a;};

        struct {f64x2 xy,  zw;};
        struct {f64x2 rg,  ba;};

        struct {f64x3 xyz; f64   _0;};
        struct {f64   _1;  f64x3 yzw;};

        struct {f64x3 rgb; f64   _2;};
        struct {f64   _3;  f64x3 gba;};

        struct {f64   _4;  f64x2 yz; f64 _5;};
        struct {f64   _6;  f64x2 gb; f64 _7;};

        f64    raw[4];
    };
};
struct boolx2x2_t {
    union {
        boolx2 cols[2];
        bool   raw[2][2];
    };
};
struct boolx2x3_t {
    union {
        boolx2 cols[3];
        bool   raw[3][2];
    };
};
struct boolx2x4_t {
    union {
        boolx2 cols[4];
        bool   raw[4][2];
    };
};
struct boolx3x2_t {
    union {
        boolx3 cols[2];
        bool   raw[2][3];
    };
};
struct boolx3x3_t {
    union {
        boolx3 cols[3];
        bool   raw[3][3];
    };
};
struct boolx3x4_t {
    union {
        boolx3 cols[4];
        bool   raw[4][3];
    };
};
struct boolx4x2_t {
    union {
        boolx4 cols[2];
        bool   raw[2][4];
    };
};
struct boolx4x3_t {
    union {
        boolx4 cols[3];
        bool   raw[3][4];
    };
};
struct boolx4x4_t {
    union {
        boolx4 cols[4];
        bool   raw[4][4];
    };
};
struct u8x2x2_t {
    union {
        u8x2 cols[2];
        u8   raw[2][2];
    };
};
struct u8x2x3_t {
    union {
        u8x2 cols[3];
        u8   raw[3][2];
    };
};
struct u8x2x4_t {
    union {
        u8x2 cols[4];
        u8   raw[4][2];
    };
};
struct u8x3x2_t {
    union {
        u8x3 cols[2];
        u8   raw[2][3];
    };
};
struct u8x3x3_t {
    union {
        u8x3 cols[3];
        u8   raw[3][3];
    };
};
struct u8x3x4_t {
    union {
        u8x3 cols[4];
        u8   raw[4][3];
    };
};
struct u8x4x2_t {
    union {
        u8x4 cols[2];
        u8   raw[2][4];
    };
};
struct u8x4x3_t {
    union {
        u8x4 cols[3];
        u8   raw[3][4];
    };
};
struct u8x4x4_t {
    union {
        u8x4 cols[4];
        u8   raw[4][4];
    };
};
struct u16x2x2_t {
    union {
        u16x2 cols[2];
        u16   raw[2][2];
    };
};
struct u16x2x3_t {
    union {
        u16x2 cols[3];
        u16   raw[3][2];
    };
};
struct u16x2x4_t {
    union {
        u16x2 cols[4];
        u16   raw[4][2];
    };
};
struct u16x3x2_t {
    union {
        u16x3 cols[2];
        u16   raw[2][3];
    };
};
struct u16x3x3_t {
    union {
        u16x3 cols[3];
        u16   raw[3][3];
    };
};
struct u16x3x4_t {
    union {
        u16x3 cols[4];
        u16   raw[4][3];
    };
};
struct u16x4x2_t {
    union {
        u16x4 cols[2];
        u16   raw[2][4];
    };
};
struct u16x4x3_t {
    union {
        u16x4 cols[3];
        u16   raw[3][4];
    };
};
struct u16x4x4_t {
    union {
        u16x4 cols[4];
        u16   raw[4][4];
    };
};
struct u32x2x2_t {
    union {
        u32x2 cols[2];
        u32   raw[2][2];
    };
};
struct u32x2x3_t {
    union {
        u32x2 cols[3];
        u32   raw[3][2];
    };
};
struct u32x2x4_t {
    union {
        u32x2 cols[4];
        u32   raw[4][2];
    };
};
struct u32x3x2_t {
    union {
        u32x3 cols[2];
        u32   raw[2][3];
    };
};
struct u32x3x3_t {
    union {
        u32x3 cols[3];
        u32   raw[3][3];
    };
};
struct u32x3x4_t {
    union {
        u32x3 cols[4];
        u32   raw[4][3];
    };
};
struct u32x4x2_t {
    union {
        u32x4 cols[2];
        u32   raw[2][4];
    };
};
struct u32x4x3_t {
    union {
        u32x4 cols[3];
        u32   raw[3][4];
    };
};
struct u32x4x4_t {
    union {
        u32x4 cols[4];
        u32   raw[4][4];
    };
};
struct u64x2x2_t {
    union {
        u64x2 cols[2];
        u64   raw[2][2];
    };
};
struct u64x2x3_t {
    union {
        u64x2 cols[3];
        u64   raw[3][2];
    };
};
struct u64x2x4_t {
    union {
        u64x2 cols[4];
        u64   raw[4][2];
    };
};
struct u64x3x2_t {
    union {
        u64x3 cols[2];
        u64   raw[2][3];
    };
};
struct u64x3x3_t {
    union {
        u64x3 cols[3];
        u64   raw[3][3];
    };
};
struct u64x3x4_t {
    union {
        u64x3 cols[4];
        u64   raw[4][3];
    };
};
struct u64x4x2_t {
    union {
        u64x4 cols[2];
        u64   raw[2][4];
    };
};
struct u64x4x3_t {
    union {
        u64x4 cols[3];
        u64   raw[3][4];
    };
};
struct u64x4x4_t {
    union {
        u64x4 cols[4];
        u64   raw[4][4];
    };
};
struct i8x2x2_t {
    union {
        i8x2 cols[2];
        i8   raw[2][2];
    };
};
struct i8x2x3_t {
    union {
        i8x2 cols[3];
        i8   raw[3][2];
    };
};
struct i8x2x4_t {
    union {
        i8x2 cols[4];
        i8   raw[4][2];
    };
};
struct i8x3x2_t {
    union {
        i8x3 cols[2];
        i8   raw[2][3];
    };
};
struct i8x3x3_t {
    union {
        i8x3 cols[3];
        i8   raw[3][3];
    };
};
struct i8x3x4_t {
    union {
        i8x3 cols[4];
        i8   raw[4][3];
    };
};
struct i8x4x2_t {
    union {
        i8x4 cols[2];
        i8   raw[2][4];
    };
};
struct i8x4x3_t {
    union {
        i8x4 cols[3];
        i8   raw[3][4];
    };
};
struct i8x4x4_t {
    union {
        i8x4 cols[4];
        i8   raw[4][4];
    };
};
struct i16x2x2_t {
    union {
        i16x2 cols[2];
        i16   raw[2][2];
    };
};
struct i16x2x3_t {
    union {
        i16x2 cols[3];
        i16   raw[3][2];
    };
};
struct i16x2x4_t {
    union {
        i16x2 cols[4];
        i16   raw[4][2];
    };
};
struct i16x3x2_t {
    union {
        i16x3 cols[2];
        i16   raw[2][3];
    };
};
struct i16x3x3_t {
    union {
        i16x3 cols[3];
        i16   raw[3][3];
    };
};
struct i16x3x4_t {
    union {
        i16x3 cols[4];
        i16   raw[4][3];
    };
};
struct i16x4x2_t {
    union {
        i16x4 cols[2];
        i16   raw[2][4];
    };
};
struct i16x4x3_t {
    union {
        i16x4 cols[3];
        i16   raw[3][4];
    };
};
struct i16x4x4_t {
    union {
        i16x4 cols[4];
        i16   raw[4][4];
    };
};
struct i32x2x2_t {
    union {
        i32x2 cols[2];
        i32   raw[2][2];
    };
};
struct i32x2x3_t {
    union {
        i32x2 cols[3];
        i32   raw[3][2];
    };
};
struct i32x2x4_t {
    union {
        i32x2 cols[4];
        i32   raw[4][2];
    };
};
struct i32x3x2_t {
    union {
        i32x3 cols[2];
        i32   raw[2][3];
    };
};
struct i32x3x3_t {
    union {
        i32x3 cols[3];
        i32   raw[3][3];
    };
};
struct i32x3x4_t {
    union {
        i32x3 cols[4];
        i32   raw[4][3];
    };
};
struct i32x4x2_t {
    union {
        i32x4 cols[2];
        i32   raw[2][4];
    };
};
struct i32x4x3_t {
    union {
        i32x4 cols[3];
        i32   raw[3][4];
    };
};
struct i32x4x4_t {
    union {
        i32x4 cols[4];
        i32   raw[4][4];
    };
};
struct i64x2x2_t {
    union {
        i64x2 cols[2];
        i64   raw[2][2];
    };
};
struct i64x2x3_t {
    union {
        i64x2 cols[3];
        i64   raw[3][2];
    };
};
struct i64x2x4_t {
    union {
        i64x2 cols[4];
        i64   raw[4][2];
    };
};
struct i64x3x2_t {
    union {
        i64x3 cols[2];
        i64   raw[2][3];
    };
};
struct i64x3x3_t {
    union {
        i64x3 cols[3];
        i64   raw[3][3];
    };
};
struct i64x3x4_t {
    union {
        i64x3 cols[4];
        i64   raw[4][3];
    };
};
struct i64x4x2_t {
    union {
        i64x4 cols[2];
        i64   raw[2][4];
    };
};
struct i64x4x3_t {
    union {
        i64x4 cols[3];
        i64   raw[3][4];
    };
};
struct i64x4x4_t {
    union {
        i64x4 cols[4];
        i64   raw[4][4];
    };
};
struct f32x2x2_t {
    union {
        f32x2 cols[2];
        f32   raw[2][2];
    };
};
struct f32x2x3_t {
    union {
        f32x2 cols[3];
        f32   raw[3][2];
    };
};
struct f32x2x4_t {
    union {
        f32x2 cols[4];
        f32   raw[4][2];
    };
};
struct f32x3x2_t {
    union {
        f32x3 cols[2];
        f32   raw[2][3];
    };
};
struct f32x3x3_t {
    union {
        f32x3 cols[3];
        f32   raw[3][3];
    };
};
struct f32x3x4_t {
    union {
        f32x3 cols[4];
        f32   raw[4][3];
    };
};
struct f32x4x2_t {
    union {
        f32x4 cols[2];
        f32   raw[2][4];
    };
};
struct f32x4x3_t {
    union {
        f32x4 cols[3];
        f32   raw[3][4];
    };
};
struct f32x4x4_t {
    union {
        f32x4 cols[4];
        f32   raw[4][4];
    };
};
struct f64x2x2_t {
    union {
        f64x2 cols[2];
        f64   raw[2][2];
    };
};
struct f64x2x3_t {
    union {
        f64x2 cols[3];
        f64   raw[3][2];
    };
};
struct f64x2x4_t {
    union {
        f64x2 cols[4];
        f64   raw[4][2];
    };
};
struct f64x3x2_t {
    union {
        f64x3 cols[2];
        f64   raw[2][3];
    };
};
struct f64x3x3_t {
    union {
        f64x3 cols[3];
        f64   raw[3][3];
    };
};
struct f64x3x4_t {
    union {
        f64x3 cols[4];
        f64   raw[4][3];
    };
};
struct f64x4x2_t {
    union {
        f64x4 cols[2];
        f64   raw[2][4];
    };
};
struct f64x4x3_t {
    union {
        f64x4 cols[3];
        f64   raw[3][4];
    };
};
struct f64x4x4_t {
    union {
        f64x4 cols[4];
        f64   raw[4][4];
    };
};

#define f32_as_u32(_x)                (((f32_cvt){.f = (_x)}).u)
#define f64_as_u64(_x)                (((f64_cvt){.f = (_x)}).u)
#define u32_as_f32(_x)                (((f32_cvt){.u = (_x)}).f)
#define u64_as_f64(_x)                (((f64_cvt){.u = (_x)}).f)
#define u32_as_f64(_x0, _x1)          (((f64_cvt){.u0 = (_x0), .u1 = (_x1)}).f)

#define rm_boolx2(_x, _y)         ((boolx2){.x = (_x),   .y = (_y)})

#define rm_boolx2s(_s)            ((boolx2){.x = (_s),   .y = (_s)})

#define rm_boolx3(_x, _y, _z)     ((boolx3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_boolx3s(_s)            ((boolx3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_boolx3sv2(_x, _v)      ((boolx3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_boolx3v2s(_v, _z)      ((boolx3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_boolx4(_x, _y, _z, _w) ((boolx4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_boolx4s(_s)            ((boolx4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_boolx4sv2(_x, _y, _v)  ((boolx4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_boolx4v2s(_v, _z, _w)  ((boolx4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_boolx4sv2s(_x, _v, _w) ((boolx4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_boolx4sv3(_x, _v)      ((boolx4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_boolx4v3s(_v, _w)      ((boolx4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_u8x2(_x, _y)           ((u8x2){.x = (_x),   .y = (_y)})

#define rm_u8x2s(_s)              ((u8x2){.x = (_s),   .y = (_s)})

#define rm_u8x3(_x, _y, _z)       ((u8x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_u8x3s(_s)              ((u8x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_u8x3sv2(_x, _v)        ((u8x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_u8x3v2s(_v, _z)        ((u8x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_u8x4(_x, _y, _z, _w)   ((u8x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_u8x4s(_s)              ((u8x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_u8x4sv2(_x, _y, _v)    ((u8x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_u8x4v2s(_v, _z, _w)    ((u8x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_u8x4sv2s(_x, _v, _w)   ((u8x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_u8x4sv3(_x, _v)        ((u8x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_u8x4v3s(_v, _w)        ((u8x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_u16x2(_x, _y)          ((u16x2){.x = (_x),   .y = (_y)})

#define rm_u16x2s(_s)             ((u16x2){.x = (_s),   .y = (_s)})

#define rm_u16x3(_x, _y, _z)      ((u16x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_u16x3s(_s)             ((u16x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_u16x3sv2(_x, _v)       ((u16x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_u16x3v2s(_v, _z)       ((u16x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_u16x4(_x, _y, _z, _w)  ((u16x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_u16x4s(_s)             ((u16x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_u16x4sv2(_x, _y, _v)   ((u16x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_u16x4v2s(_v, _z, _w)   ((u16x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_u16x4sv2s(_x, _v, _w)  ((u16x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_u16x4sv3(_x, _v)       ((u16x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_u16x4v3s(_v, _w)       ((u16x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_u32x2(_x, _y)          ((u32x2){.x = (_x),   .y = (_y)})

#define rm_u32x2s(_s)             ((u32x2){.x = (_s),   .y = (_s)})

#define rm_u32x3(_x, _y, _z)      ((u32x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_u32x3s(_s)             ((u32x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_u32x3sv2(_x, _v)       ((u32x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_u32x3v2s(_v, _z)       ((u32x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_u32x4(_x, _y, _z, _w)  ((u32x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_u32x4s(_s)             ((u32x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_u32x4sv2(_x, _y, _v)   ((u32x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_u32x4v2s(_v, _z, _w)   ((u32x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_u32x4sv2s(_x, _v, _w)  ((u32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_u32x4sv3(_x, _v)       ((u32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_u32x4v3s(_v, _w)       ((u32x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_u64x2(_x, _y)          ((u64x2){.x = (_x),   .y = (_y)})

#define rm_u64x2s(_s)             ((u64x2){.x = (_s),   .y = (_s)})

#define rm_u64x3(_x, _y, _z)      ((u64x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_u64x3s(_s)             ((u64x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_u64x3sv2(_x, _v)       ((u64x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_u64x3v2s(_v, _z)       ((u64x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_u64x4(_x, _y, _z, _w)  ((u64x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_u64x4s(_s)             ((u64x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_u64x4sv2(_x, _y, _v)   ((u64x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_u64x4v2s(_v, _z, _w)   ((u64x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_u64x4sv2s(_x, _v, _w)  ((u64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_u64x4sv3(_x, _v)       ((u64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_u64x4v3s(_v, _w)       ((u64x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_i8x2(_x, _y)           ((i8x2){.x = (_x),   .y = (_y)})

#define rm_i8x2s(_s)              ((i8x2){.x = (_s),   .y = (_s)})

#define rm_i8x3(_x, _y, _z)       ((i8x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_i8x3s(_s)              ((i8x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_i8x3sv2(_x, _v)        ((i8x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_i8x3v2s(_v, _z)        ((i8x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_i8x4(_x, _y, _z, _w)   ((i8x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_i8x4s(_s)              ((i8x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_i8x4sv2(_x, _y, _v)    ((i8x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_i8x4v2s(_v, _z, _w)    ((i8x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_i8x4sv2s(_x, _v, _w)   ((i8x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_i8x4sv3(_x, _v)        ((i8x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_i8x4v3s(_v, _w)        ((i8x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_i16x2(_x, _y)          ((i16x2){.x = (_x),   .y = (_y)})

#define rm_i16x2s(_s)             ((i16x2){.x = (_s),   .y = (_s)})

#define rm_i16x3(_x, _y, _z)      ((i16x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_i16x3s(_s)             ((i16x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_i16x3sv2(_x, _v)       ((i16x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_i16x3v2s(_v, _z)       ((i16x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_i16x4(_x, _y, _z, _w)  ((i16x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_i16x4s(_s)             ((i16x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_i16x4sv2(_x, _y, _v)   ((i16x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_i16x4v2s(_v, _z, _w)   ((i16x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_i16x4sv2s(_x, _v, _w)  ((i16x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_i16x4sv3(_x, _v)       ((i16x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_i16x4v3s(_v, _w)       ((i16x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_i32x2(_x, _y)          ((i32x2){.x = (_x),   .y = (_y)})

#define rm_i32x2s(_s)             ((i32x2){.x = (_s),   .y = (_s)})

#define rm_i32x3(_x, _y, _z)      ((i32x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_i32x3s(_s)             ((i32x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_i32x3sv2(_x, _v)       ((i32x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_i32x3v2s(_v, _z)       ((i32x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_i32x4(_x, _y, _z, _w)  ((i32x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_i32x4s(_s)             ((i32x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_i32x4sv2(_x, _y, _v)   ((i32x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_i32x4v2s(_v, _z, _w)   ((i32x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_i32x4sv2s(_x, _v, _w)  ((i32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_i32x4sv3(_x, _v)       ((i32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_i32x4v3s(_v, _w)       ((i32x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_i64x2(_x, _y)          ((i64x2){.x = (_x),   .y = (_y)})

#define rm_i64x2s(_s)             ((i64x2){.x = (_s),   .y = (_s)})

#define rm_i64x3(_x, _y, _z)      ((i64x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_i64x3s(_s)             ((i64x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_i64x3sv2(_x, _v)       ((i64x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_i64x3v2s(_v, _z)       ((i64x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_i64x4(_x, _y, _z, _w)  ((i64x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_i64x4s(_s)             ((i64x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_i64x4sv2(_x, _y, _v)   ((i64x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_i64x4v2s(_v, _z, _w)   ((i64x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_i64x4sv2s(_x, _v, _w)  ((i64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_i64x4sv3(_x, _v)       ((i64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_i64x4v3s(_v, _w)       ((i64x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_f32x2(_x, _y)          ((f32x2){.x = (_x),   .y = (_y)})

#define rm_f32x2s(_s)             ((f32x2){.x = (_s),   .y = (_s)})

#define rm_f32x3(_x, _y, _z)      ((f32x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_f32x3s(_s)             ((f32x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_f32x3sv2(_x, _v)       ((f32x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_f32x3v2s(_v, _z)       ((f32x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_f32x4(_x, _y, _z, _w)  ((f32x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_f32x4s(_s)             ((f32x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_f32x4sv2(_x, _y, _v)   ((f32x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_f32x4v2s(_v, _z, _w)   ((f32x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_f32x4sv2s(_x, _v, _w)  ((f32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_f32x4sv3(_x, _v)       ((f32x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_f32x4v3s(_v, _w)       ((f32x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_f64x2(_x, _y)          ((f64x2){.x = (_x),   .y = (_y)})

#define rm_f64x2s(_s)             ((f64x2){.x = (_s),   .y = (_s)})

#define rm_f64x3(_x, _y, _z)      ((f64x3){.x = (_x),   .y = (_y),   .z = (_z)})

#define rm_f64x3s(_s)             ((f64x3){.x = (_s),   .y = (_s),   .z = (_s)})

#define rm_f64x3sv2(_x, _v)       ((f64x3){.x = (_x),   .y = (_v).x, .z = (_v).y})
#define rm_f64x3v2s(_v, _z)       ((f64x3){.x = (_v).x, .y = (_v).y, .z = (_z)})

#define rm_f64x4(_x, _y, _z, _w)  ((f64x4){.x = (_x),   .y = (_y),   .z = (_z),   .w = (_w)})

#define rm_f64x4s(_s)             ((f64x4){.x = (_s),   .y = (_s),   .z = (_s),   .w = (_s)})

#define rm_f64x4sv2(_x, _y, _v)   ((f64x4){.x = (_x),   .y = (_y),   .z = (_v).x, .w = (_v).y})
#define rm_f64x4v2s(_v, _z, _w)   ((f64x4){.x = (_v).x, .y = (_v).y, .z = (_z),   .w = (_w)})
#define rm_f64x4sv2s(_x, _v, _w)  ((f64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_w)})
#define rm_f64x4sv3(_x, _v)       ((f64x4){.x = (_x),   .y = (_v).x, .z = (_v).y, .w = (_v).z})
#define rm_f64x4v3s(_v, _w)       ((f64x4){.x = (_v).x, .y = (_v).y, .z = (_v).z, .w = (_w)})

#define rm_splat2(_v)             (_v).x, (_v).y
#define rm_splat3(_v)             (_v).x, (_v).y, (_v).z
#define rm_splat4(_v)             (_v).x, (_v).y, (_v).z, (_v).w

#define RM_INLINE static inline
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
#define RM_ABS(_x) (((_x) < 0) ? -(_x) : (_x))
#define RM_MIN(_a, _b) (((_a) < (_b)) ? (_a) : (_b))
#define RM_MAX(_a, _b) (((_a) > (_b)) ? (_a) : (_b))
#define RM_CLAMP(_val, _min, _max) (RM_MIN(RM_MAX((_val), (_min)), (_max)))
RM_INLINE u8 rm_min_u8(const u8 a, const u8 b) {
    return RM_MIN(a, b);
}
RM_INLINE u8 rm_max_u8(const u8 a, const u8 b) {
    return RM_MAX(a, b);
}
RM_INLINE u8 rm_clamp_u8(const u8 val, const u8 min, const u8 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE u8 rm_mod_u8(const u8 a, const u8 b) {
    return a % b;
}
RM_INLINE u16 rm_min_u16(const u16 a, const u16 b) {
    return RM_MIN(a, b);
}
RM_INLINE u16 rm_max_u16(const u16 a, const u16 b) {
    return RM_MAX(a, b);
}
RM_INLINE u16 rm_clamp_u16(const u16 val, const u16 min, const u16 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE u16 rm_mod_u16(const u16 a, const u16 b) {
    return a % b;
}
RM_INLINE u32 rm_min_u32(const u32 a, const u32 b) {
    return RM_MIN(a, b);
}
RM_INLINE u32 rm_max_u32(const u32 a, const u32 b) {
    return RM_MAX(a, b);
}
RM_INLINE u32 rm_clamp_u32(const u32 val, const u32 min, const u32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE u32 rm_mod_u32(const u32 a, const u32 b) {
    return a % b;
}
RM_INLINE u64 rm_min_u64(const u64 a, const u64 b) {
    return RM_MIN(a, b);
}
RM_INLINE u64 rm_max_u64(const u64 a, const u64 b) {
    return RM_MAX(a, b);
}
RM_INLINE u64 rm_clamp_u64(const u64 val, const u64 min, const u64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE u64 rm_mod_u64(const u64 a, const u64 b) {
    return a % b;
}
RM_INLINE i8 rm_abs_i8(const i8 x) {
    return RM_ABS(x);
}
RM_INLINE i8 rm_min_i8(const i8 a, const i8 b) {
    return RM_MIN(a, b);
}
RM_INLINE i8 rm_max_i8(const i8 a, const i8 b) {
    return RM_MAX(a, b);
}
RM_INLINE i8 rm_clamp_i8(const i8 val, const i8 min, const i8 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i8 rm_mod_i8(const i8 a, const i8 b) {
    return a % b;
}
RM_INLINE i8 rm_sign_i8(const i8 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE i8 rm_copysign_i8(const i8 x, const i8 s) {
    return rm_abs_i8(x) * rm_sign_i8(s);
}
RM_INLINE i16 rm_abs_i16(const i16 x) {
    return RM_ABS(x);
}
RM_INLINE i16 rm_min_i16(const i16 a, const i16 b) {
    return RM_MIN(a, b);
}
RM_INLINE i16 rm_max_i16(const i16 a, const i16 b) {
    return RM_MAX(a, b);
}
RM_INLINE i16 rm_clamp_i16(const i16 val, const i16 min, const i16 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i16 rm_mod_i16(const i16 a, const i16 b) {
    return a % b;
}
RM_INLINE i16 rm_sign_i16(const i16 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE i16 rm_copysign_i16(const i16 x, const i16 s) {
    return rm_abs_i16(x) * rm_sign_i16(s);
}
RM_INLINE i32 rm_abs_i32(const i32 x) {
    return RM_ABS(x);
}
RM_INLINE i32 rm_min_i32(const i32 a, const i32 b) {
    return RM_MIN(a, b);
}
RM_INLINE i32 rm_max_i32(const i32 a, const i32 b) {
    return RM_MAX(a, b);
}
RM_INLINE i32 rm_clamp_i32(const i32 val, const i32 min, const i32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i32 rm_mod_i32(const i32 a, const i32 b) {
    return a % b;
}
RM_INLINE i32 rm_sign_i32(const i32 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE i32 rm_copysign_i32(const i32 x, const i32 s) {
    return rm_abs_i32(x) * rm_sign_i32(s);
}
RM_INLINE i64 rm_abs_i64(const i64 x) {
    return RM_ABS(x);
}
RM_INLINE i64 rm_min_i64(const i64 a, const i64 b) {
    return RM_MIN(a, b);
}
RM_INLINE i64 rm_max_i64(const i64 a, const i64 b) {
    return RM_MAX(a, b);
}
RM_INLINE i64 rm_clamp_i64(const i64 val, const i64 min, const i64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE i64 rm_mod_i64(const i64 a, const i64 b) {
    return a % b;
}
RM_INLINE i64 rm_sign_i64(const i64 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE i64 rm_copysign_i64(const i64 x, const i64 s) {
    return rm_abs_i64(x) * rm_sign_i64(s);
}
RM_INLINE f32 rm_abs_f32(const f32 x) {
    return RM_ABS(x);
}
RM_INLINE f32 rm_min_f32(const f32 a, const f32 b) {
    return RM_MIN(a, b);
}
RM_INLINE f32 rm_max_f32(const f32 a, const f32 b) {
    return RM_MAX(a, b);
}
RM_INLINE f32 rm_clamp_f32(const f32 val, const f32 min, const f32 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f32 rm_trunc_f32(const f32 x) {
    return (i32)x;
}
RM_INLINE f32 rm_mod_f32(const f32 a, const f32 b) {
    return a - (rm_trunc_f32(a / b) * b);
}
RM_INLINE f32 rm_sign_f32(const f32 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE f32 rm_copysign_f32(const f32 x, const f32 s) {
    return rm_abs_f32(x) * rm_sign_f32(s);
}
RM_INLINE f64 rm_abs_f64(const f64 x) {
    return RM_ABS(x);
}
RM_INLINE f64 rm_min_f64(const f64 a, const f64 b) {
    return RM_MIN(a, b);
}
RM_INLINE f64 rm_max_f64(const f64 a, const f64 b) {
    return RM_MAX(a, b);
}
RM_INLINE f64 rm_clamp_f64(const f64 val, const f64 min, const f64 max) {
    return RM_CLAMP(val, min, max);
}
RM_INLINE f64 rm_trunc_f64(const f64 x) {
    return (i64)x;
}
RM_INLINE f64 rm_mod_f64(const f64 a, const f64 b) {
    return a - (rm_trunc_f64(a / b) * b);
}
RM_INLINE f64 rm_sign_f64(const f64 x) {
    return (x > 0) - (x < 0);
}
RM_INLINE f64 rm_copysign_f64(const f64 x, const f64 s) {
    return rm_abs_f64(x) * rm_sign_f64(s);
}
RM_INLINE f32 rm_floor_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x - 1) : rm_trunc_f32(x);
}
RM_INLINE f64 rm_floor_f64(const f64 x) {
    return (x < 0) ? rm_trunc_f64(x - 1) : rm_trunc_f64(x);
}
RM_INLINE f32 rm_ceil_f32(const f32 x) {
    return (x < 0) ? rm_trunc_f32(x) : rm_trunc_f32(x + 1);
}
RM_INLINE f64 rm_ceil_f64(const f64 x) {
    return (x < 0) ? rm_trunc_f64(x) : rm_trunc_f64(x + 1);
}
RM_INLINE f32 rm_round_f32(const f32 x) {
    f32 t;

    if (x < 0) {
        t = rm_trunc_f32(-x);
        return (t + x <= -0.5F) ? -(t + 1) : -t;
    }

    t = rm_trunc_f32(x);
    return (t - x <= -0.5F) ? (t + 1) : t;
}
RM_INLINE f64 rm_round_f64(const f64 x) {
    f64 t;

    if (x < 0) {
        t = rm_trunc_f64(-x);
        return (t + x <= -0.5) ? -(t + 1) : -t;
    }

    t = rm_trunc_f64(x);
    return (t - x <= -0.5) ? (t + 1) : t;
}
RM_INLINE f32 rm_fract_f32(const f32 x) {
    return x - rm_floor_f32(x);
}
RM_INLINE f64 rm_fract_f64(const f64 x) {
    return x - rm_floor_f64(x);
}
RM_INLINE f32 rm_deg2rad_f32(const f32 x) {
    return x * RM_DEG2RAD_F32;
}
RM_INLINE f64 rm_deg2rad_f64(const f64 x) {
    return x * RM_DEG2RAD_F64;
}
RM_INLINE f32 rm_rad2deg_f32(const f32 x) {
    return x * RM_RAD2DEG_F32;
}
RM_INLINE f64 rm_rad2deg_f64(const f64 x) {
    return x * RM_RAD2DEG_F64;
}
RM_INLINE bool rm_any_u8x2(const u8x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_u8x3(const u8x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_u8x4(const u8x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_u8x2(const u8x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_u8x3(const u8x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_u8x4(const u8x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_u8x2(const u8x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_u8x3(const u8x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_u8x4(const u8x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_u8x2(const u8x2 a, const u8x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_u8x3(const u8x3 a, const u8x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_u8x4(const u8x4 a, const u8x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_u8x2(const u8x2 v, const u8 s) {
    return rm_eq_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_eqs_u8x3(const u8x3 v, const u8 s) {
    return rm_eq_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_eqs_u8x4(const u8x4 v, const u8 s) {
    return rm_eq_u8x4(v, rm_u8x4s(s));
}
RM_INLINE boolx2 rm_neqs_u8x2(const u8x2 v, const u8 s) {
    return rm_neq_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_neqs_u8x3(const u8x3 v, const u8 s) {
    return rm_neq_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_neqs_u8x4(const u8x4 v, const u8 s) {
    return rm_neq_u8x4(v, rm_u8x4s(s));
}
RM_INLINE boolx2 rm_lts_u8x2(const u8x2 v, const u8 s) {
    return rm_lt_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_lts_u8x3(const u8x3 v, const u8 s) {
    return rm_lt_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_lts_u8x4(const u8x4 v, const u8 s) {
    return rm_lt_u8x4(v, rm_u8x4s(s));
}
RM_INLINE boolx2 rm_lteqs_u8x2(const u8x2 v, const u8 s) {
    return rm_lteq_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_lteqs_u8x3(const u8x3 v, const u8 s) {
    return rm_lteq_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_lteqs_u8x4(const u8x4 v, const u8 s) {
    return rm_lteq_u8x4(v, rm_u8x4s(s));
}
RM_INLINE boolx2 rm_gts_u8x2(const u8x2 v, const u8 s) {
    return rm_gt_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_gts_u8x3(const u8x3 v, const u8 s) {
    return rm_gt_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_gts_u8x4(const u8x4 v, const u8 s) {
    return rm_gt_u8x4(v, rm_u8x4s(s));
}
RM_INLINE boolx2 rm_gteqs_u8x2(const u8x2 v, const u8 s) {
    return rm_gteq_u8x2(v, rm_u8x2s(s));
}
RM_INLINE boolx3 rm_gteqs_u8x3(const u8x3 v, const u8 s) {
    return rm_gteq_u8x3(v, rm_u8x3s(s));
}
RM_INLINE boolx4 rm_gteqs_u8x4(const u8x4 v, const u8 s) {
    return rm_gteq_u8x4(v, rm_u8x4s(s));
}
RM_INLINE bool rm_any_u16x2(const u16x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_u16x3(const u16x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_u16x4(const u16x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_u16x2(const u16x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_u16x3(const u16x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_u16x4(const u16x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_u16x2(const u16x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_u16x3(const u16x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_u16x4(const u16x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_u16x2(const u16x2 a, const u16x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_u16x3(const u16x3 a, const u16x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_u16x4(const u16x4 a, const u16x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_u16x2(const u16x2 v, const u16 s) {
    return rm_eq_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_eqs_u16x3(const u16x3 v, const u16 s) {
    return rm_eq_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_eqs_u16x4(const u16x4 v, const u16 s) {
    return rm_eq_u16x4(v, rm_u16x4s(s));
}
RM_INLINE boolx2 rm_neqs_u16x2(const u16x2 v, const u16 s) {
    return rm_neq_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_neqs_u16x3(const u16x3 v, const u16 s) {
    return rm_neq_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_neqs_u16x4(const u16x4 v, const u16 s) {
    return rm_neq_u16x4(v, rm_u16x4s(s));
}
RM_INLINE boolx2 rm_lts_u16x2(const u16x2 v, const u16 s) {
    return rm_lt_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_lts_u16x3(const u16x3 v, const u16 s) {
    return rm_lt_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_lts_u16x4(const u16x4 v, const u16 s) {
    return rm_lt_u16x4(v, rm_u16x4s(s));
}
RM_INLINE boolx2 rm_lteqs_u16x2(const u16x2 v, const u16 s) {
    return rm_lteq_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_lteqs_u16x3(const u16x3 v, const u16 s) {
    return rm_lteq_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_lteqs_u16x4(const u16x4 v, const u16 s) {
    return rm_lteq_u16x4(v, rm_u16x4s(s));
}
RM_INLINE boolx2 rm_gts_u16x2(const u16x2 v, const u16 s) {
    return rm_gt_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_gts_u16x3(const u16x3 v, const u16 s) {
    return rm_gt_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_gts_u16x4(const u16x4 v, const u16 s) {
    return rm_gt_u16x4(v, rm_u16x4s(s));
}
RM_INLINE boolx2 rm_gteqs_u16x2(const u16x2 v, const u16 s) {
    return rm_gteq_u16x2(v, rm_u16x2s(s));
}
RM_INLINE boolx3 rm_gteqs_u16x3(const u16x3 v, const u16 s) {
    return rm_gteq_u16x3(v, rm_u16x3s(s));
}
RM_INLINE boolx4 rm_gteqs_u16x4(const u16x4 v, const u16 s) {
    return rm_gteq_u16x4(v, rm_u16x4s(s));
}
RM_INLINE bool rm_any_u32x2(const u32x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_u32x3(const u32x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_u32x4(const u32x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_u32x2(const u32x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_u32x3(const u32x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_u32x4(const u32x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_u32x2(const u32x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_u32x3(const u32x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_u32x4(const u32x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_u32x2(const u32x2 a, const u32x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_u32x3(const u32x3 a, const u32x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_u32x4(const u32x4 a, const u32x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_u32x2(const u32x2 v, const u32 s) {
    return rm_eq_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_eqs_u32x3(const u32x3 v, const u32 s) {
    return rm_eq_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_eqs_u32x4(const u32x4 v, const u32 s) {
    return rm_eq_u32x4(v, rm_u32x4s(s));
}
RM_INLINE boolx2 rm_neqs_u32x2(const u32x2 v, const u32 s) {
    return rm_neq_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_neqs_u32x3(const u32x3 v, const u32 s) {
    return rm_neq_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_neqs_u32x4(const u32x4 v, const u32 s) {
    return rm_neq_u32x4(v, rm_u32x4s(s));
}
RM_INLINE boolx2 rm_lts_u32x2(const u32x2 v, const u32 s) {
    return rm_lt_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_lts_u32x3(const u32x3 v, const u32 s) {
    return rm_lt_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_lts_u32x4(const u32x4 v, const u32 s) {
    return rm_lt_u32x4(v, rm_u32x4s(s));
}
RM_INLINE boolx2 rm_lteqs_u32x2(const u32x2 v, const u32 s) {
    return rm_lteq_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_lteqs_u32x3(const u32x3 v, const u32 s) {
    return rm_lteq_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_lteqs_u32x4(const u32x4 v, const u32 s) {
    return rm_lteq_u32x4(v, rm_u32x4s(s));
}
RM_INLINE boolx2 rm_gts_u32x2(const u32x2 v, const u32 s) {
    return rm_gt_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_gts_u32x3(const u32x3 v, const u32 s) {
    return rm_gt_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_gts_u32x4(const u32x4 v, const u32 s) {
    return rm_gt_u32x4(v, rm_u32x4s(s));
}
RM_INLINE boolx2 rm_gteqs_u32x2(const u32x2 v, const u32 s) {
    return rm_gteq_u32x2(v, rm_u32x2s(s));
}
RM_INLINE boolx3 rm_gteqs_u32x3(const u32x3 v, const u32 s) {
    return rm_gteq_u32x3(v, rm_u32x3s(s));
}
RM_INLINE boolx4 rm_gteqs_u32x4(const u32x4 v, const u32 s) {
    return rm_gteq_u32x4(v, rm_u32x4s(s));
}
RM_INLINE bool rm_any_u64x2(const u64x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_u64x3(const u64x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_u64x4(const u64x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_u64x2(const u64x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_u64x3(const u64x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_u64x4(const u64x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_u64x2(const u64x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_u64x3(const u64x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_u64x4(const u64x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_u64x2(const u64x2 a, const u64x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_u64x3(const u64x3 a, const u64x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_u64x4(const u64x4 a, const u64x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_u64x2(const u64x2 v, const u64 s) {
    return rm_eq_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_eqs_u64x3(const u64x3 v, const u64 s) {
    return rm_eq_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_eqs_u64x4(const u64x4 v, const u64 s) {
    return rm_eq_u64x4(v, rm_u64x4s(s));
}
RM_INLINE boolx2 rm_neqs_u64x2(const u64x2 v, const u64 s) {
    return rm_neq_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_neqs_u64x3(const u64x3 v, const u64 s) {
    return rm_neq_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_neqs_u64x4(const u64x4 v, const u64 s) {
    return rm_neq_u64x4(v, rm_u64x4s(s));
}
RM_INLINE boolx2 rm_lts_u64x2(const u64x2 v, const u64 s) {
    return rm_lt_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_lts_u64x3(const u64x3 v, const u64 s) {
    return rm_lt_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_lts_u64x4(const u64x4 v, const u64 s) {
    return rm_lt_u64x4(v, rm_u64x4s(s));
}
RM_INLINE boolx2 rm_lteqs_u64x2(const u64x2 v, const u64 s) {
    return rm_lteq_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_lteqs_u64x3(const u64x3 v, const u64 s) {
    return rm_lteq_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_lteqs_u64x4(const u64x4 v, const u64 s) {
    return rm_lteq_u64x4(v, rm_u64x4s(s));
}
RM_INLINE boolx2 rm_gts_u64x2(const u64x2 v, const u64 s) {
    return rm_gt_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_gts_u64x3(const u64x3 v, const u64 s) {
    return rm_gt_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_gts_u64x4(const u64x4 v, const u64 s) {
    return rm_gt_u64x4(v, rm_u64x4s(s));
}
RM_INLINE boolx2 rm_gteqs_u64x2(const u64x2 v, const u64 s) {
    return rm_gteq_u64x2(v, rm_u64x2s(s));
}
RM_INLINE boolx3 rm_gteqs_u64x3(const u64x3 v, const u64 s) {
    return rm_gteq_u64x3(v, rm_u64x3s(s));
}
RM_INLINE boolx4 rm_gteqs_u64x4(const u64x4 v, const u64 s) {
    return rm_gteq_u64x4(v, rm_u64x4s(s));
}
RM_INLINE bool rm_any_i8x2(const i8x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_i8x3(const i8x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_i8x4(const i8x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_i8x2(const i8x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_i8x3(const i8x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_i8x4(const i8x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_i8x2(const i8x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_i8x3(const i8x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_i8x4(const i8x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_i8x2(const i8x2 a, const i8x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_i8x3(const i8x3 a, const i8x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_i8x4(const i8x4 a, const i8x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_i8x2(const i8x2 v, const i8 s) {
    return rm_eq_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_eqs_i8x3(const i8x3 v, const i8 s) {
    return rm_eq_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_eqs_i8x4(const i8x4 v, const i8 s) {
    return rm_eq_i8x4(v, rm_i8x4s(s));
}
RM_INLINE boolx2 rm_neqs_i8x2(const i8x2 v, const i8 s) {
    return rm_neq_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_neqs_i8x3(const i8x3 v, const i8 s) {
    return rm_neq_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_neqs_i8x4(const i8x4 v, const i8 s) {
    return rm_neq_i8x4(v, rm_i8x4s(s));
}
RM_INLINE boolx2 rm_lts_i8x2(const i8x2 v, const i8 s) {
    return rm_lt_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_lts_i8x3(const i8x3 v, const i8 s) {
    return rm_lt_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_lts_i8x4(const i8x4 v, const i8 s) {
    return rm_lt_i8x4(v, rm_i8x4s(s));
}
RM_INLINE boolx2 rm_lteqs_i8x2(const i8x2 v, const i8 s) {
    return rm_lteq_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_lteqs_i8x3(const i8x3 v, const i8 s) {
    return rm_lteq_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_lteqs_i8x4(const i8x4 v, const i8 s) {
    return rm_lteq_i8x4(v, rm_i8x4s(s));
}
RM_INLINE boolx2 rm_gts_i8x2(const i8x2 v, const i8 s) {
    return rm_gt_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_gts_i8x3(const i8x3 v, const i8 s) {
    return rm_gt_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_gts_i8x4(const i8x4 v, const i8 s) {
    return rm_gt_i8x4(v, rm_i8x4s(s));
}
RM_INLINE boolx2 rm_gteqs_i8x2(const i8x2 v, const i8 s) {
    return rm_gteq_i8x2(v, rm_i8x2s(s));
}
RM_INLINE boolx3 rm_gteqs_i8x3(const i8x3 v, const i8 s) {
    return rm_gteq_i8x3(v, rm_i8x3s(s));
}
RM_INLINE boolx4 rm_gteqs_i8x4(const i8x4 v, const i8 s) {
    return rm_gteq_i8x4(v, rm_i8x4s(s));
}
RM_INLINE bool rm_any_i16x2(const i16x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_i16x3(const i16x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_i16x4(const i16x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_i16x2(const i16x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_i16x3(const i16x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_i16x4(const i16x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_i16x2(const i16x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_i16x3(const i16x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_i16x4(const i16x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_i16x2(const i16x2 a, const i16x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_i16x3(const i16x3 a, const i16x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_i16x4(const i16x4 a, const i16x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_i16x2(const i16x2 v, const i16 s) {
    return rm_eq_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_eqs_i16x3(const i16x3 v, const i16 s) {
    return rm_eq_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_eqs_i16x4(const i16x4 v, const i16 s) {
    return rm_eq_i16x4(v, rm_i16x4s(s));
}
RM_INLINE boolx2 rm_neqs_i16x2(const i16x2 v, const i16 s) {
    return rm_neq_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_neqs_i16x3(const i16x3 v, const i16 s) {
    return rm_neq_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_neqs_i16x4(const i16x4 v, const i16 s) {
    return rm_neq_i16x4(v, rm_i16x4s(s));
}
RM_INLINE boolx2 rm_lts_i16x2(const i16x2 v, const i16 s) {
    return rm_lt_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_lts_i16x3(const i16x3 v, const i16 s) {
    return rm_lt_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_lts_i16x4(const i16x4 v, const i16 s) {
    return rm_lt_i16x4(v, rm_i16x4s(s));
}
RM_INLINE boolx2 rm_lteqs_i16x2(const i16x2 v, const i16 s) {
    return rm_lteq_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_lteqs_i16x3(const i16x3 v, const i16 s) {
    return rm_lteq_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_lteqs_i16x4(const i16x4 v, const i16 s) {
    return rm_lteq_i16x4(v, rm_i16x4s(s));
}
RM_INLINE boolx2 rm_gts_i16x2(const i16x2 v, const i16 s) {
    return rm_gt_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_gts_i16x3(const i16x3 v, const i16 s) {
    return rm_gt_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_gts_i16x4(const i16x4 v, const i16 s) {
    return rm_gt_i16x4(v, rm_i16x4s(s));
}
RM_INLINE boolx2 rm_gteqs_i16x2(const i16x2 v, const i16 s) {
    return rm_gteq_i16x2(v, rm_i16x2s(s));
}
RM_INLINE boolx3 rm_gteqs_i16x3(const i16x3 v, const i16 s) {
    return rm_gteq_i16x3(v, rm_i16x3s(s));
}
RM_INLINE boolx4 rm_gteqs_i16x4(const i16x4 v, const i16 s) {
    return rm_gteq_i16x4(v, rm_i16x4s(s));
}
RM_INLINE bool rm_any_i32x2(const i32x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_i32x3(const i32x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_i32x4(const i32x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_i32x2(const i32x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_i32x3(const i32x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_i32x4(const i32x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_i32x2(const i32x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_i32x3(const i32x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_i32x4(const i32x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_i32x2(const i32x2 a, const i32x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_i32x3(const i32x3 a, const i32x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_i32x4(const i32x4 a, const i32x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_i32x2(const i32x2 v, const i32 s) {
    return rm_eq_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_eqs_i32x3(const i32x3 v, const i32 s) {
    return rm_eq_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_eqs_i32x4(const i32x4 v, const i32 s) {
    return rm_eq_i32x4(v, rm_i32x4s(s));
}
RM_INLINE boolx2 rm_neqs_i32x2(const i32x2 v, const i32 s) {
    return rm_neq_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_neqs_i32x3(const i32x3 v, const i32 s) {
    return rm_neq_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_neqs_i32x4(const i32x4 v, const i32 s) {
    return rm_neq_i32x4(v, rm_i32x4s(s));
}
RM_INLINE boolx2 rm_lts_i32x2(const i32x2 v, const i32 s) {
    return rm_lt_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_lts_i32x3(const i32x3 v, const i32 s) {
    return rm_lt_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_lts_i32x4(const i32x4 v, const i32 s) {
    return rm_lt_i32x4(v, rm_i32x4s(s));
}
RM_INLINE boolx2 rm_lteqs_i32x2(const i32x2 v, const i32 s) {
    return rm_lteq_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_lteqs_i32x3(const i32x3 v, const i32 s) {
    return rm_lteq_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_lteqs_i32x4(const i32x4 v, const i32 s) {
    return rm_lteq_i32x4(v, rm_i32x4s(s));
}
RM_INLINE boolx2 rm_gts_i32x2(const i32x2 v, const i32 s) {
    return rm_gt_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_gts_i32x3(const i32x3 v, const i32 s) {
    return rm_gt_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_gts_i32x4(const i32x4 v, const i32 s) {
    return rm_gt_i32x4(v, rm_i32x4s(s));
}
RM_INLINE boolx2 rm_gteqs_i32x2(const i32x2 v, const i32 s) {
    return rm_gteq_i32x2(v, rm_i32x2s(s));
}
RM_INLINE boolx3 rm_gteqs_i32x3(const i32x3 v, const i32 s) {
    return rm_gteq_i32x3(v, rm_i32x3s(s));
}
RM_INLINE boolx4 rm_gteqs_i32x4(const i32x4 v, const i32 s) {
    return rm_gteq_i32x4(v, rm_i32x4s(s));
}
RM_INLINE bool rm_any_i64x2(const i64x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_i64x3(const i64x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_i64x4(const i64x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_i64x2(const i64x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_i64x3(const i64x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_i64x4(const i64x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_i64x2(const i64x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_i64x3(const i64x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_i64x4(const i64x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_i64x2(const i64x2 a, const i64x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_i64x3(const i64x3 a, const i64x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_i64x4(const i64x4 a, const i64x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_i64x2(const i64x2 v, const i64 s) {
    return rm_eq_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_eqs_i64x3(const i64x3 v, const i64 s) {
    return rm_eq_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_eqs_i64x4(const i64x4 v, const i64 s) {
    return rm_eq_i64x4(v, rm_i64x4s(s));
}
RM_INLINE boolx2 rm_neqs_i64x2(const i64x2 v, const i64 s) {
    return rm_neq_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_neqs_i64x3(const i64x3 v, const i64 s) {
    return rm_neq_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_neqs_i64x4(const i64x4 v, const i64 s) {
    return rm_neq_i64x4(v, rm_i64x4s(s));
}
RM_INLINE boolx2 rm_lts_i64x2(const i64x2 v, const i64 s) {
    return rm_lt_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_lts_i64x3(const i64x3 v, const i64 s) {
    return rm_lt_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_lts_i64x4(const i64x4 v, const i64 s) {
    return rm_lt_i64x4(v, rm_i64x4s(s));
}
RM_INLINE boolx2 rm_lteqs_i64x2(const i64x2 v, const i64 s) {
    return rm_lteq_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_lteqs_i64x3(const i64x3 v, const i64 s) {
    return rm_lteq_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_lteqs_i64x4(const i64x4 v, const i64 s) {
    return rm_lteq_i64x4(v, rm_i64x4s(s));
}
RM_INLINE boolx2 rm_gts_i64x2(const i64x2 v, const i64 s) {
    return rm_gt_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_gts_i64x3(const i64x3 v, const i64 s) {
    return rm_gt_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_gts_i64x4(const i64x4 v, const i64 s) {
    return rm_gt_i64x4(v, rm_i64x4s(s));
}
RM_INLINE boolx2 rm_gteqs_i64x2(const i64x2 v, const i64 s) {
    return rm_gteq_i64x2(v, rm_i64x2s(s));
}
RM_INLINE boolx3 rm_gteqs_i64x3(const i64x3 v, const i64 s) {
    return rm_gteq_i64x3(v, rm_i64x3s(s));
}
RM_INLINE boolx4 rm_gteqs_i64x4(const i64x4 v, const i64 s) {
    return rm_gteq_i64x4(v, rm_i64x4s(s));
}
RM_INLINE bool rm_any_f32x2(const f32x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_f32x3(const f32x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_f32x4(const f32x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_f32x2(const f32x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_f32x3(const f32x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_f32x4(const f32x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_f32x2(const f32x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_f32x3(const f32x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_f32x4(const f32x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_f32x2(const f32x2 a, const f32x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_f32x3(const f32x3 a, const f32x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_f32x4(const f32x4 a, const f32x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_f32x2(const f32x2 v, const f32 s) {
    return rm_eq_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_eqs_f32x3(const f32x3 v, const f32 s) {
    return rm_eq_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_eqs_f32x4(const f32x4 v, const f32 s) {
    return rm_eq_f32x4(v, rm_f32x4s(s));
}
RM_INLINE boolx2 rm_neqs_f32x2(const f32x2 v, const f32 s) {
    return rm_neq_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_neqs_f32x3(const f32x3 v, const f32 s) {
    return rm_neq_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_neqs_f32x4(const f32x4 v, const f32 s) {
    return rm_neq_f32x4(v, rm_f32x4s(s));
}
RM_INLINE boolx2 rm_lts_f32x2(const f32x2 v, const f32 s) {
    return rm_lt_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_lts_f32x3(const f32x3 v, const f32 s) {
    return rm_lt_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_lts_f32x4(const f32x4 v, const f32 s) {
    return rm_lt_f32x4(v, rm_f32x4s(s));
}
RM_INLINE boolx2 rm_lteqs_f32x2(const f32x2 v, const f32 s) {
    return rm_lteq_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_lteqs_f32x3(const f32x3 v, const f32 s) {
    return rm_lteq_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_lteqs_f32x4(const f32x4 v, const f32 s) {
    return rm_lteq_f32x4(v, rm_f32x4s(s));
}
RM_INLINE boolx2 rm_gts_f32x2(const f32x2 v, const f32 s) {
    return rm_gt_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_gts_f32x3(const f32x3 v, const f32 s) {
    return rm_gt_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_gts_f32x4(const f32x4 v, const f32 s) {
    return rm_gt_f32x4(v, rm_f32x4s(s));
}
RM_INLINE boolx2 rm_gteqs_f32x2(const f32x2 v, const f32 s) {
    return rm_gteq_f32x2(v, rm_f32x2s(s));
}
RM_INLINE boolx3 rm_gteqs_f32x3(const f32x3 v, const f32 s) {
    return rm_gteq_f32x3(v, rm_f32x3s(s));
}
RM_INLINE boolx4 rm_gteqs_f32x4(const f32x4 v, const f32 s) {
    return rm_gteq_f32x4(v, rm_f32x4s(s));
}
RM_INLINE bool rm_any_f64x2(const f64x2 v) {
    return v.x || v.y;
}
RM_INLINE bool rm_any_f64x3(const f64x2 v) {
    return (v.x || v.y) || v.z;
}
RM_INLINE bool rm_any_f64x4(const f64x2 v) {
    return (v.x || v.y) || (v.z || v.w);
}
RM_INLINE bool rm_all_f64x2(const f64x2 v) {
    return v.x && v.y;
}
RM_INLINE bool rm_all_f64x3(const f64x2 v) {
    return (v.x && v.y) && v.z;
}
RM_INLINE bool rm_all_f64x4(const f64x2 v) {
    return (v.x && v.y) && (v.z && v.w);
}
RM_INLINE boolx2 rm_not_f64x2(const f64x2 v) {
    return rm_boolx2(!v.x, !v.y);
}
RM_INLINE boolx3 rm_not_f64x3(const f64x3 v) {
    return rm_boolx3(!v.x, !v.y, !v.z);
}
RM_INLINE boolx4 rm_not_f64x4(const f64x4 v) {
    return rm_boolx4(!v.x, !v.y, !v.z, !v.w);
}
RM_INLINE boolx2 rm_eq_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x == b.x, a.y == b.y);
}
RM_INLINE boolx3 rm_eq_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x == b.x, a.y == b.y, a.z == b.z);
}
RM_INLINE boolx4 rm_eq_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
}
RM_INLINE boolx2 rm_neq_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x != b.x, a.y != b.y);
}
RM_INLINE boolx3 rm_neq_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x != b.x, a.y != b.y, a.z != b.z);
}
RM_INLINE boolx4 rm_neq_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
}
RM_INLINE boolx2 rm_lt_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x < b.x, a.y < b.y);
}
RM_INLINE boolx3 rm_lt_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x < b.x, a.y < b.y, a.z < b.z);
}
RM_INLINE boolx4 rm_lt_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
}
RM_INLINE boolx2 rm_lteq_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x <= b.x, a.y <= b.y);
}
RM_INLINE boolx3 rm_lteq_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x <= b.x, a.y <= b.y, a.z <= b.z);
}
RM_INLINE boolx4 rm_lteq_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
}
RM_INLINE boolx2 rm_gt_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x > b.x, a.y > b.y);
}
RM_INLINE boolx3 rm_gt_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x > b.x, a.y > b.y, a.z > b.z);
}
RM_INLINE boolx4 rm_gt_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
}
RM_INLINE boolx2 rm_gteq_f64x2(const f64x2 a, const f64x2 b) {
    return rm_boolx2(a.x >= b.x, a.y >= b.y);
}
RM_INLINE boolx3 rm_gteq_f64x3(const f64x3 a, const f64x3 b) {
    return rm_boolx3(a.x >= b.x, a.y >= b.y, a.z >= b.z);
}
RM_INLINE boolx4 rm_gteq_f64x4(const f64x4 a, const f64x4 b) {
    return rm_boolx4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
}
RM_INLINE boolx2 rm_eqs_f64x2(const f64x2 v, const f64 s) {
    return rm_eq_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_eqs_f64x3(const f64x3 v, const f64 s) {
    return rm_eq_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_eqs_f64x4(const f64x4 v, const f64 s) {
    return rm_eq_f64x4(v, rm_f64x4s(s));
}
RM_INLINE boolx2 rm_neqs_f64x2(const f64x2 v, const f64 s) {
    return rm_neq_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_neqs_f64x3(const f64x3 v, const f64 s) {
    return rm_neq_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_neqs_f64x4(const f64x4 v, const f64 s) {
    return rm_neq_f64x4(v, rm_f64x4s(s));
}
RM_INLINE boolx2 rm_lts_f64x2(const f64x2 v, const f64 s) {
    return rm_lt_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_lts_f64x3(const f64x3 v, const f64 s) {
    return rm_lt_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_lts_f64x4(const f64x4 v, const f64 s) {
    return rm_lt_f64x4(v, rm_f64x4s(s));
}
RM_INLINE boolx2 rm_lteqs_f64x2(const f64x2 v, const f64 s) {
    return rm_lteq_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_lteqs_f64x3(const f64x3 v, const f64 s) {
    return rm_lteq_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_lteqs_f64x4(const f64x4 v, const f64 s) {
    return rm_lteq_f64x4(v, rm_f64x4s(s));
}
RM_INLINE boolx2 rm_gts_f64x2(const f64x2 v, const f64 s) {
    return rm_gt_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_gts_f64x3(const f64x3 v, const f64 s) {
    return rm_gt_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_gts_f64x4(const f64x4 v, const f64 s) {
    return rm_gt_f64x4(v, rm_f64x4s(s));
}
RM_INLINE boolx2 rm_gteqs_f64x2(const f64x2 v, const f64 s) {
    return rm_gteq_f64x2(v, rm_f64x2s(s));
}
RM_INLINE boolx3 rm_gteqs_f64x3(const f64x3 v, const f64 s) {
    return rm_gteq_f64x3(v, rm_f64x3s(s));
}
RM_INLINE boolx4 rm_gteqs_f64x4(const f64x4 v, const f64 s) {
    return rm_gteq_f64x4(v, rm_f64x4s(s));
}
RM_INLINE i8x2 rm_neg_i8x2(const i8x2 v) {
    return rm_i8x2(-v.x, -v.y);
}
RM_INLINE i8x3 rm_neg_i8x3(const i8x3 v) {
    return rm_i8x3(-v.x, -v.y, -v.z);
}
RM_INLINE i8x4 rm_neg_i8x4(const i8x4 v) {
    return rm_i8x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE i8x2 rm_abs_i8x2(const i8x2 v) {
    return rm_i8x2(rm_abs_i8(v.x), rm_abs_i8(v.y));
}
RM_INLINE i8x3 rm_abs_i8x3(const i8x3 v) {
    return rm_i8x3(rm_abs_i8(v.x), rm_abs_i8(v.y), rm_abs_i8(v.z));
}
RM_INLINE i8x4 rm_abs_i8x4(const i8x4 v) {
    return rm_i8x4(rm_abs_i8(v.x), rm_abs_i8(v.y), rm_abs_i8(v.z), rm_abs_i8(v.w));
}
RM_INLINE i16x2 rm_neg_i16x2(const i16x2 v) {
    return rm_i16x2(-v.x, -v.y);
}
RM_INLINE i16x3 rm_neg_i16x3(const i16x3 v) {
    return rm_i16x3(-v.x, -v.y, -v.z);
}
RM_INLINE i16x4 rm_neg_i16x4(const i16x4 v) {
    return rm_i16x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE i16x2 rm_abs_i16x2(const i16x2 v) {
    return rm_i16x2(rm_abs_i16(v.x), rm_abs_i16(v.y));
}
RM_INLINE i16x3 rm_abs_i16x3(const i16x3 v) {
    return rm_i16x3(rm_abs_i16(v.x), rm_abs_i16(v.y), rm_abs_i16(v.z));
}
RM_INLINE i16x4 rm_abs_i16x4(const i16x4 v) {
    return rm_i16x4(rm_abs_i16(v.x), rm_abs_i16(v.y), rm_abs_i16(v.z), rm_abs_i16(v.w));
}
RM_INLINE i32x2 rm_neg_i32x2(const i32x2 v) {
    return rm_i32x2(-v.x, -v.y);
}
RM_INLINE i32x3 rm_neg_i32x3(const i32x3 v) {
    return rm_i32x3(-v.x, -v.y, -v.z);
}
RM_INLINE i32x4 rm_neg_i32x4(const i32x4 v) {
    return rm_i32x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE i32x2 rm_abs_i32x2(const i32x2 v) {
    return rm_i32x2(rm_abs_i32(v.x), rm_abs_i32(v.y));
}
RM_INLINE i32x3 rm_abs_i32x3(const i32x3 v) {
    return rm_i32x3(rm_abs_i32(v.x), rm_abs_i32(v.y), rm_abs_i32(v.z));
}
RM_INLINE i32x4 rm_abs_i32x4(const i32x4 v) {
    return rm_i32x4(rm_abs_i32(v.x), rm_abs_i32(v.y), rm_abs_i32(v.z), rm_abs_i32(v.w));
}
RM_INLINE i64x2 rm_neg_i64x2(const i64x2 v) {
    return rm_i64x2(-v.x, -v.y);
}
RM_INLINE i64x3 rm_neg_i64x3(const i64x3 v) {
    return rm_i64x3(-v.x, -v.y, -v.z);
}
RM_INLINE i64x4 rm_neg_i64x4(const i64x4 v) {
    return rm_i64x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE i64x2 rm_abs_i64x2(const i64x2 v) {
    return rm_i64x2(rm_abs_i64(v.x), rm_abs_i64(v.y));
}
RM_INLINE i64x3 rm_abs_i64x3(const i64x3 v) {
    return rm_i64x3(rm_abs_i64(v.x), rm_abs_i64(v.y), rm_abs_i64(v.z));
}
RM_INLINE i64x4 rm_abs_i64x4(const i64x4 v) {
    return rm_i64x4(rm_abs_i64(v.x), rm_abs_i64(v.y), rm_abs_i64(v.z), rm_abs_i64(v.w));
}
RM_INLINE f32x2 rm_neg_f32x2(const f32x2 v) {
    return rm_f32x2(-v.x, -v.y);
}
RM_INLINE f32x3 rm_neg_f32x3(const f32x3 v) {
    return rm_f32x3(-v.x, -v.y, -v.z);
}
RM_INLINE f32x4 rm_neg_f32x4(const f32x4 v) {
    return rm_f32x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE f32x2 rm_abs_f32x2(const f32x2 v) {
    return rm_f32x2(rm_abs_f32(v.x), rm_abs_f32(v.y));
}
RM_INLINE f32x3 rm_abs_f32x3(const f32x3 v) {
    return rm_f32x3(rm_abs_f32(v.x), rm_abs_f32(v.y), rm_abs_f32(v.z));
}
RM_INLINE f32x4 rm_abs_f32x4(const f32x4 v) {
    return rm_f32x4(rm_abs_f32(v.x), rm_abs_f32(v.y), rm_abs_f32(v.z), rm_abs_f32(v.w));
}
RM_INLINE f64x2 rm_neg_f64x2(const f64x2 v) {
    return rm_f64x2(-v.x, -v.y);
}
RM_INLINE f64x3 rm_neg_f64x3(const f64x3 v) {
    return rm_f64x3(-v.x, -v.y, -v.z);
}
RM_INLINE f64x4 rm_neg_f64x4(const f64x4 v) {
    return rm_f64x4(-v.x, -v.y, -v.z, -v.w);
}
RM_INLINE f64x2 rm_abs_f64x2(const f64x2 v) {
    return rm_f64x2(rm_abs_f64(v.x), rm_abs_f64(v.y));
}
RM_INLINE f64x3 rm_abs_f64x3(const f64x3 v) {
    return rm_f64x3(rm_abs_f64(v.x), rm_abs_f64(v.y), rm_abs_f64(v.z));
}
RM_INLINE f64x4 rm_abs_f64x4(const f64x4 v) {
    return rm_f64x4(rm_abs_f64(v.x), rm_abs_f64(v.y), rm_abs_f64(v.z), rm_abs_f64(v.w));
}
RM_INLINE u8x2 rm_min_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(rm_min_u8(a.x, b.x), rm_min_u8(a.y, b.y));
}
RM_INLINE u8x3 rm_min_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(rm_min_u8(a.x, b.x), rm_min_u8(a.y, b.y),
                    rm_min_u8(a.z, b.z));
}
RM_INLINE u8x4 rm_min_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(rm_min_u8(a.x, b.x), rm_min_u8(a.y, b.y),
                    rm_min_u8(a.z, b.z), rm_min_u8(a.w, b.w));
}
RM_INLINE u8x2 rm_max_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(rm_max_u8(a.x, b.x), rm_max_u8(a.y, b.y));
}
RM_INLINE u8x3 rm_max_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(rm_max_u8(a.x, b.x), rm_max_u8(a.y, b.y),
                    rm_max_u8(a.z, b.z));
}
RM_INLINE u8x4 rm_max_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(rm_max_u8(a.x, b.x), rm_max_u8(a.y, b.y),
                    rm_max_u8(a.z, b.z), rm_max_u8(a.w, b.w));
}
RM_INLINE u8x2 rm_add_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(a.x + b.x, a.y + b.y);
}
RM_INLINE u8x3 rm_add_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE u8x4 rm_add_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE u8x2 rm_sub_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(a.x - b.x, a.y - b.y);
}
RM_INLINE u8x3 rm_sub_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE u8x4 rm_sub_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE u8x2 rm_mul_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(a.x * b.x, a.y * b.y);
}
RM_INLINE u8x3 rm_mul_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE u8x4 rm_mul_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE u8x2 rm_div_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(a.x / b.x, a.y / b.y);
}
RM_INLINE u8x3 rm_div_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE u8x4 rm_div_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE u8x2 rm_mod_u8x2(const u8x2 a, const u8x2 b) {
    return rm_u8x2(rm_mod_u8(a.x, b.x), rm_mod_u8(a.y, b.y));
}
RM_INLINE u8x3 rm_mod_u8x3(const u8x3 a, const u8x3 b) {
    return rm_u8x3(rm_mod_u8(a.x, b.x), rm_mod_u8(a.y, b.y),
                    rm_mod_u8(a.z, b.z));
}
RM_INLINE u8x4 rm_mod_u8x4(const u8x4 a, const u8x4 b) {
    return rm_u8x4(rm_mod_u8(a.x, b.x), rm_mod_u8(a.y, b.y),
                    rm_mod_u8(a.z, b.z), rm_mod_u8(a.w, b.w));
}
RM_INLINE u8x2 rm_clamp_u8x2(const u8x2 v, const u8x2 min, const u8x2 max) {
    return rm_u8x2(rm_clamp_u8(v.x, min.x, max.x), rm_clamp_u8(v.y, min.y, max.y));
}
RM_INLINE u8x3 rm_clamp_u8x3(const u8x3 v, const u8x3 min, const u8x3 max) {
    return rm_u8x3(rm_clamp_u8(v.x, min.x, max.x), rm_clamp_u8(v.y, min.y, max.y),
                    rm_clamp_u8(v.z, min.z, max.z));
}
RM_INLINE u8x4 rm_clamp_u8x4(const u8x4 v, const u8x4 min, const u8x4 max) {
    return rm_u8x4(rm_clamp_u8(v.x, min.x, max.x), rm_clamp_u8(v.y, min.y, max.y),
                    rm_clamp_u8(v.z, min.z, max.z), rm_clamp_u8(v.w, min.w, max.w));
}
RM_INLINE u8x2 rm_fma_u8x2(const u8x2 a, const u8x2 b, const u8x2 c) {
    return rm_add_u8x2(rm_mul_u8x2(a, b), c);
}
RM_INLINE u8x3 rm_fma_u8x3(const u8x3 a, const u8x3 b, const u8x3 c) {
    return rm_add_u8x3(rm_mul_u8x3(a, b), c);
}
RM_INLINE u8x4 rm_fma_u8x4(const u8x4 a, const u8x4 b, const u8x4 c) {
    return rm_add_u8x4(rm_mul_u8x4(a, b), c);
}
RM_INLINE u8x2 rm_mins_u8x2(const u8x2 v, const u8 s) {
    return rm_min_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x3 rm_mins_u8x3(const u8x3 v, const u8 s) {
    return rm_min_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x4 rm_mins_u8x4(const u8x4 v, const u8 s) {
    return rm_min_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x2 rm_maxs_u8x2(const u8x2 v, const u8 s) {
    return rm_max_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x3 rm_maxs_u8x3(const u8x3 v, const u8 s) {
    return rm_max_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x4 rm_maxs_u8x4(const u8x4 v, const u8 s) {
    return rm_max_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x2 rm_adds_u8x2(const u8x2 v, const u8 s) {
    return rm_add_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x3 rm_adds_u8x3(const u8x3 v, const u8 s) {
    return rm_add_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x4 rm_adds_u8x4(const u8x4 v, const u8 s) {
    return rm_add_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x2 rm_subs_u8x2(const u8x2 v, const u8 s) {
    return rm_sub_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x2 rm_ssub_u8x2(const u8 s, const u8x2 v) {
    return rm_sub_u8x2(rm_u8x2s(s), v);
}
RM_INLINE u8x3 rm_subs_u8x3(const u8x3 v, const u8 s) {
    return rm_sub_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x3 rm_ssub_u8x3(const u8 s, const u8x3 v) {
    return rm_sub_u8x3(rm_u8x3s(s), v);
}
RM_INLINE u8x4 rm_subs_u8x4(const u8x4 v, const u8 s) {
    return rm_sub_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x4 rm_ssub_u8x4(const u8 s, const u8x4 v) {
    return rm_sub_u8x4(rm_u8x4s(s), v);
}
RM_INLINE u8x2 rm_muls_u8x2(const u8x2 v, const u8 s) {
    return rm_mul_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x3 rm_muls_u8x3(const u8x3 v, const u8 s) {
    return rm_mul_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x4 rm_muls_u8x4(const u8x4 v, const u8 s) {
    return rm_mul_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x2 rm_divs_u8x2(const u8x2 v, const u8 s) {
    return rm_div_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x2 rm_sdiv_u8x2(const u8 s, const u8x2 v) {
    return rm_div_u8x2(rm_u8x2s(s), v);
}
RM_INLINE u8x3 rm_divs_u8x3(const u8x3 v, const u8 s) {
    return rm_div_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x3 rm_sdiv_u8x3(const u8 s, const u8x3 v) {
    return rm_div_u8x3(rm_u8x3s(s), v);
}
RM_INLINE u8x4 rm_divs_u8x4(const u8x4 v, const u8 s) {
    return rm_div_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x4 rm_sdiv_u8x4(const u8 s, const u8x4 v) {
    return rm_div_u8x4(rm_u8x4s(s), v);
}
RM_INLINE u8x2 rm_mods_u8x2(const u8x2 v, const u8 s) {
    return rm_mod_u8x2(v, rm_u8x2s(s));
}
RM_INLINE u8x2 rm_smod_u8x2(const u8 s, const u8x2 v) {
    return rm_mod_u8x2(rm_u8x2s(s), v);
}
RM_INLINE u8x3 rm_mods_u8x3(const u8x3 v, const u8 s) {
    return rm_mod_u8x3(v, rm_u8x3s(s));
}
RM_INLINE u8x3 rm_smod_u8x3(const u8 s, const u8x3 v) {
    return rm_mod_u8x3(rm_u8x3s(s), v);
}
RM_INLINE u8x4 rm_mods_u8x4(const u8x4 v, const u8 s) {
    return rm_mod_u8x4(v, rm_u8x4s(s));
}
RM_INLINE u8x4 rm_smod_u8x4(const u8 s, const u8x4 v) {
    return rm_mod_u8x4(rm_u8x4s(s), v);
}
RM_INLINE u8x2 rm_clamps_u8x2(const u8x2 v, u8 min, u8 max) {
    return rm_clamp_u8x2(v, rm_u8x2s(min), rm_u8x2s(max));
}
RM_INLINE u8x2 rm_fmas_u8x2(const u8x2 a, const u8x2 b, const u8 c) {
    return rm_adds_u8x2(rm_mul_u8x2(a, b), c);
}
RM_INLINE u8x2 rm_fmass_u8x2(const u8x2 a, const u8 b, const u8 c) {
    return rm_adds_u8x2(rm_muls_u8x2(a, b), c);
}
RM_INLINE u8x3 rm_clamps_u8x3(const u8x3 v, u8 min, u8 max) {
    return rm_clamp_u8x3(v, rm_u8x3s(min), rm_u8x3s(max));
}
RM_INLINE u8x3 rm_fmas_u8x3(const u8x3 a, const u8x3 b, const u8 c) {
    return rm_adds_u8x3(rm_mul_u8x3(a, b), c);
}
RM_INLINE u8x3 rm_fmass_u8x3(const u8x3 a, const u8 b, const u8 c) {
    return rm_adds_u8x3(rm_muls_u8x3(a, b), c);
}
RM_INLINE u8x4 rm_clamps_u8x4(const u8x4 v, u8 min, u8 max) {
    return rm_clamp_u8x4(v, rm_u8x4s(min), rm_u8x4s(max));
}
RM_INLINE u8x4 rm_fmas_u8x4(const u8x4 a, const u8x4 b, const u8 c) {
    return rm_adds_u8x4(rm_mul_u8x4(a, b), c);
}
RM_INLINE u8x4 rm_fmass_u8x4(const u8x4 a, const u8 b, const u8 c) {
    return rm_adds_u8x4(rm_muls_u8x4(a, b), c);
}
RM_INLINE u16x2 rm_min_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(rm_min_u16(a.x, b.x), rm_min_u16(a.y, b.y));
}
RM_INLINE u16x3 rm_min_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(rm_min_u16(a.x, b.x), rm_min_u16(a.y, b.y),
                    rm_min_u16(a.z, b.z));
}
RM_INLINE u16x4 rm_min_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(rm_min_u16(a.x, b.x), rm_min_u16(a.y, b.y),
                    rm_min_u16(a.z, b.z), rm_min_u16(a.w, b.w));
}
RM_INLINE u16x2 rm_max_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(rm_max_u16(a.x, b.x), rm_max_u16(a.y, b.y));
}
RM_INLINE u16x3 rm_max_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(rm_max_u16(a.x, b.x), rm_max_u16(a.y, b.y),
                    rm_max_u16(a.z, b.z));
}
RM_INLINE u16x4 rm_max_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(rm_max_u16(a.x, b.x), rm_max_u16(a.y, b.y),
                    rm_max_u16(a.z, b.z), rm_max_u16(a.w, b.w));
}
RM_INLINE u16x2 rm_add_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(a.x + b.x, a.y + b.y);
}
RM_INLINE u16x3 rm_add_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE u16x4 rm_add_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE u16x2 rm_sub_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(a.x - b.x, a.y - b.y);
}
RM_INLINE u16x3 rm_sub_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE u16x4 rm_sub_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE u16x2 rm_mul_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(a.x * b.x, a.y * b.y);
}
RM_INLINE u16x3 rm_mul_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE u16x4 rm_mul_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE u16x2 rm_div_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(a.x / b.x, a.y / b.y);
}
RM_INLINE u16x3 rm_div_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE u16x4 rm_div_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE u16x2 rm_mod_u16x2(const u16x2 a, const u16x2 b) {
    return rm_u16x2(rm_mod_u16(a.x, b.x), rm_mod_u16(a.y, b.y));
}
RM_INLINE u16x3 rm_mod_u16x3(const u16x3 a, const u16x3 b) {
    return rm_u16x3(rm_mod_u16(a.x, b.x), rm_mod_u16(a.y, b.y),
                    rm_mod_u16(a.z, b.z));
}
RM_INLINE u16x4 rm_mod_u16x4(const u16x4 a, const u16x4 b) {
    return rm_u16x4(rm_mod_u16(a.x, b.x), rm_mod_u16(a.y, b.y),
                    rm_mod_u16(a.z, b.z), rm_mod_u16(a.w, b.w));
}
RM_INLINE u16x2 rm_clamp_u16x2(const u16x2 v, const u16x2 min, const u16x2 max) {
    return rm_u16x2(rm_clamp_u16(v.x, min.x, max.x), rm_clamp_u16(v.y, min.y, max.y));
}
RM_INLINE u16x3 rm_clamp_u16x3(const u16x3 v, const u16x3 min, const u16x3 max) {
    return rm_u16x3(rm_clamp_u16(v.x, min.x, max.x), rm_clamp_u16(v.y, min.y, max.y),
                    rm_clamp_u16(v.z, min.z, max.z));
}
RM_INLINE u16x4 rm_clamp_u16x4(const u16x4 v, const u16x4 min, const u16x4 max) {
    return rm_u16x4(rm_clamp_u16(v.x, min.x, max.x), rm_clamp_u16(v.y, min.y, max.y),
                    rm_clamp_u16(v.z, min.z, max.z), rm_clamp_u16(v.w, min.w, max.w));
}
RM_INLINE u16x2 rm_fma_u16x2(const u16x2 a, const u16x2 b, const u16x2 c) {
    return rm_add_u16x2(rm_mul_u16x2(a, b), c);
}
RM_INLINE u16x3 rm_fma_u16x3(const u16x3 a, const u16x3 b, const u16x3 c) {
    return rm_add_u16x3(rm_mul_u16x3(a, b), c);
}
RM_INLINE u16x4 rm_fma_u16x4(const u16x4 a, const u16x4 b, const u16x4 c) {
    return rm_add_u16x4(rm_mul_u16x4(a, b), c);
}
RM_INLINE u16x2 rm_mins_u16x2(const u16x2 v, const u16 s) {
    return rm_min_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x3 rm_mins_u16x3(const u16x3 v, const u16 s) {
    return rm_min_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x4 rm_mins_u16x4(const u16x4 v, const u16 s) {
    return rm_min_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x2 rm_maxs_u16x2(const u16x2 v, const u16 s) {
    return rm_max_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x3 rm_maxs_u16x3(const u16x3 v, const u16 s) {
    return rm_max_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x4 rm_maxs_u16x4(const u16x4 v, const u16 s) {
    return rm_max_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x2 rm_adds_u16x2(const u16x2 v, const u16 s) {
    return rm_add_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x3 rm_adds_u16x3(const u16x3 v, const u16 s) {
    return rm_add_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x4 rm_adds_u16x4(const u16x4 v, const u16 s) {
    return rm_add_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x2 rm_subs_u16x2(const u16x2 v, const u16 s) {
    return rm_sub_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x2 rm_ssub_u16x2(const u16 s, const u16x2 v) {
    return rm_sub_u16x2(rm_u16x2s(s), v);
}
RM_INLINE u16x3 rm_subs_u16x3(const u16x3 v, const u16 s) {
    return rm_sub_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x3 rm_ssub_u16x3(const u16 s, const u16x3 v) {
    return rm_sub_u16x3(rm_u16x3s(s), v);
}
RM_INLINE u16x4 rm_subs_u16x4(const u16x4 v, const u16 s) {
    return rm_sub_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x4 rm_ssub_u16x4(const u16 s, const u16x4 v) {
    return rm_sub_u16x4(rm_u16x4s(s), v);
}
RM_INLINE u16x2 rm_muls_u16x2(const u16x2 v, const u16 s) {
    return rm_mul_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x3 rm_muls_u16x3(const u16x3 v, const u16 s) {
    return rm_mul_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x4 rm_muls_u16x4(const u16x4 v, const u16 s) {
    return rm_mul_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x2 rm_divs_u16x2(const u16x2 v, const u16 s) {
    return rm_div_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x2 rm_sdiv_u16x2(const u16 s, const u16x2 v) {
    return rm_div_u16x2(rm_u16x2s(s), v);
}
RM_INLINE u16x3 rm_divs_u16x3(const u16x3 v, const u16 s) {
    return rm_div_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x3 rm_sdiv_u16x3(const u16 s, const u16x3 v) {
    return rm_div_u16x3(rm_u16x3s(s), v);
}
RM_INLINE u16x4 rm_divs_u16x4(const u16x4 v, const u16 s) {
    return rm_div_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x4 rm_sdiv_u16x4(const u16 s, const u16x4 v) {
    return rm_div_u16x4(rm_u16x4s(s), v);
}
RM_INLINE u16x2 rm_mods_u16x2(const u16x2 v, const u16 s) {
    return rm_mod_u16x2(v, rm_u16x2s(s));
}
RM_INLINE u16x2 rm_smod_u16x2(const u16 s, const u16x2 v) {
    return rm_mod_u16x2(rm_u16x2s(s), v);
}
RM_INLINE u16x3 rm_mods_u16x3(const u16x3 v, const u16 s) {
    return rm_mod_u16x3(v, rm_u16x3s(s));
}
RM_INLINE u16x3 rm_smod_u16x3(const u16 s, const u16x3 v) {
    return rm_mod_u16x3(rm_u16x3s(s), v);
}
RM_INLINE u16x4 rm_mods_u16x4(const u16x4 v, const u16 s) {
    return rm_mod_u16x4(v, rm_u16x4s(s));
}
RM_INLINE u16x4 rm_smod_u16x4(const u16 s, const u16x4 v) {
    return rm_mod_u16x4(rm_u16x4s(s), v);
}
RM_INLINE u16x2 rm_clamps_u16x2(const u16x2 v, u16 min, u16 max) {
    return rm_clamp_u16x2(v, rm_u16x2s(min), rm_u16x2s(max));
}
RM_INLINE u16x2 rm_fmas_u16x2(const u16x2 a, const u16x2 b, const u16 c) {
    return rm_adds_u16x2(rm_mul_u16x2(a, b), c);
}
RM_INLINE u16x2 rm_fmass_u16x2(const u16x2 a, const u16 b, const u16 c) {
    return rm_adds_u16x2(rm_muls_u16x2(a, b), c);
}
RM_INLINE u16x3 rm_clamps_u16x3(const u16x3 v, u16 min, u16 max) {
    return rm_clamp_u16x3(v, rm_u16x3s(min), rm_u16x3s(max));
}
RM_INLINE u16x3 rm_fmas_u16x3(const u16x3 a, const u16x3 b, const u16 c) {
    return rm_adds_u16x3(rm_mul_u16x3(a, b), c);
}
RM_INLINE u16x3 rm_fmass_u16x3(const u16x3 a, const u16 b, const u16 c) {
    return rm_adds_u16x3(rm_muls_u16x3(a, b), c);
}
RM_INLINE u16x4 rm_clamps_u16x4(const u16x4 v, u16 min, u16 max) {
    return rm_clamp_u16x4(v, rm_u16x4s(min), rm_u16x4s(max));
}
RM_INLINE u16x4 rm_fmas_u16x4(const u16x4 a, const u16x4 b, const u16 c) {
    return rm_adds_u16x4(rm_mul_u16x4(a, b), c);
}
RM_INLINE u16x4 rm_fmass_u16x4(const u16x4 a, const u16 b, const u16 c) {
    return rm_adds_u16x4(rm_muls_u16x4(a, b), c);
}
RM_INLINE u32x2 rm_min_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(rm_min_u32(a.x, b.x), rm_min_u32(a.y, b.y));
}
RM_INLINE u32x3 rm_min_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(rm_min_u32(a.x, b.x), rm_min_u32(a.y, b.y),
                    rm_min_u32(a.z, b.z));
}
RM_INLINE u32x4 rm_min_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(rm_min_u32(a.x, b.x), rm_min_u32(a.y, b.y),
                    rm_min_u32(a.z, b.z), rm_min_u32(a.w, b.w));
}
RM_INLINE u32x2 rm_max_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(rm_max_u32(a.x, b.x), rm_max_u32(a.y, b.y));
}
RM_INLINE u32x3 rm_max_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(rm_max_u32(a.x, b.x), rm_max_u32(a.y, b.y),
                    rm_max_u32(a.z, b.z));
}
RM_INLINE u32x4 rm_max_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(rm_max_u32(a.x, b.x), rm_max_u32(a.y, b.y),
                    rm_max_u32(a.z, b.z), rm_max_u32(a.w, b.w));
}
RM_INLINE u32x2 rm_add_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(a.x + b.x, a.y + b.y);
}
RM_INLINE u32x3 rm_add_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE u32x4 rm_add_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE u32x2 rm_sub_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(a.x - b.x, a.y - b.y);
}
RM_INLINE u32x3 rm_sub_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE u32x4 rm_sub_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE u32x2 rm_mul_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(a.x * b.x, a.y * b.y);
}
RM_INLINE u32x3 rm_mul_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE u32x4 rm_mul_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE u32x2 rm_div_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(a.x / b.x, a.y / b.y);
}
RM_INLINE u32x3 rm_div_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE u32x4 rm_div_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE u32x2 rm_mod_u32x2(const u32x2 a, const u32x2 b) {
    return rm_u32x2(rm_mod_u32(a.x, b.x), rm_mod_u32(a.y, b.y));
}
RM_INLINE u32x3 rm_mod_u32x3(const u32x3 a, const u32x3 b) {
    return rm_u32x3(rm_mod_u32(a.x, b.x), rm_mod_u32(a.y, b.y),
                    rm_mod_u32(a.z, b.z));
}
RM_INLINE u32x4 rm_mod_u32x4(const u32x4 a, const u32x4 b) {
    return rm_u32x4(rm_mod_u32(a.x, b.x), rm_mod_u32(a.y, b.y),
                    rm_mod_u32(a.z, b.z), rm_mod_u32(a.w, b.w));
}
RM_INLINE u32x2 rm_clamp_u32x2(const u32x2 v, const u32x2 min, const u32x2 max) {
    return rm_u32x2(rm_clamp_u32(v.x, min.x, max.x), rm_clamp_u32(v.y, min.y, max.y));
}
RM_INLINE u32x3 rm_clamp_u32x3(const u32x3 v, const u32x3 min, const u32x3 max) {
    return rm_u32x3(rm_clamp_u32(v.x, min.x, max.x), rm_clamp_u32(v.y, min.y, max.y),
                    rm_clamp_u32(v.z, min.z, max.z));
}
RM_INLINE u32x4 rm_clamp_u32x4(const u32x4 v, const u32x4 min, const u32x4 max) {
    return rm_u32x4(rm_clamp_u32(v.x, min.x, max.x), rm_clamp_u32(v.y, min.y, max.y),
                    rm_clamp_u32(v.z, min.z, max.z), rm_clamp_u32(v.w, min.w, max.w));
}
RM_INLINE u32x2 rm_fma_u32x2(const u32x2 a, const u32x2 b, const u32x2 c) {
    return rm_add_u32x2(rm_mul_u32x2(a, b), c);
}
RM_INLINE u32x3 rm_fma_u32x3(const u32x3 a, const u32x3 b, const u32x3 c) {
    return rm_add_u32x3(rm_mul_u32x3(a, b), c);
}
RM_INLINE u32x4 rm_fma_u32x4(const u32x4 a, const u32x4 b, const u32x4 c) {
    return rm_add_u32x4(rm_mul_u32x4(a, b), c);
}
RM_INLINE u32x2 rm_mins_u32x2(const u32x2 v, const u32 s) {
    return rm_min_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x3 rm_mins_u32x3(const u32x3 v, const u32 s) {
    return rm_min_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x4 rm_mins_u32x4(const u32x4 v, const u32 s) {
    return rm_min_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x2 rm_maxs_u32x2(const u32x2 v, const u32 s) {
    return rm_max_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x3 rm_maxs_u32x3(const u32x3 v, const u32 s) {
    return rm_max_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x4 rm_maxs_u32x4(const u32x4 v, const u32 s) {
    return rm_max_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x2 rm_adds_u32x2(const u32x2 v, const u32 s) {
    return rm_add_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x3 rm_adds_u32x3(const u32x3 v, const u32 s) {
    return rm_add_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x4 rm_adds_u32x4(const u32x4 v, const u32 s) {
    return rm_add_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x2 rm_subs_u32x2(const u32x2 v, const u32 s) {
    return rm_sub_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x2 rm_ssub_u32x2(const u32 s, const u32x2 v) {
    return rm_sub_u32x2(rm_u32x2s(s), v);
}
RM_INLINE u32x3 rm_subs_u32x3(const u32x3 v, const u32 s) {
    return rm_sub_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x3 rm_ssub_u32x3(const u32 s, const u32x3 v) {
    return rm_sub_u32x3(rm_u32x3s(s), v);
}
RM_INLINE u32x4 rm_subs_u32x4(const u32x4 v, const u32 s) {
    return rm_sub_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x4 rm_ssub_u32x4(const u32 s, const u32x4 v) {
    return rm_sub_u32x4(rm_u32x4s(s), v);
}
RM_INLINE u32x2 rm_muls_u32x2(const u32x2 v, const u32 s) {
    return rm_mul_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x3 rm_muls_u32x3(const u32x3 v, const u32 s) {
    return rm_mul_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x4 rm_muls_u32x4(const u32x4 v, const u32 s) {
    return rm_mul_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x2 rm_divs_u32x2(const u32x2 v, const u32 s) {
    return rm_div_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x2 rm_sdiv_u32x2(const u32 s, const u32x2 v) {
    return rm_div_u32x2(rm_u32x2s(s), v);
}
RM_INLINE u32x3 rm_divs_u32x3(const u32x3 v, const u32 s) {
    return rm_div_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x3 rm_sdiv_u32x3(const u32 s, const u32x3 v) {
    return rm_div_u32x3(rm_u32x3s(s), v);
}
RM_INLINE u32x4 rm_divs_u32x4(const u32x4 v, const u32 s) {
    return rm_div_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x4 rm_sdiv_u32x4(const u32 s, const u32x4 v) {
    return rm_div_u32x4(rm_u32x4s(s), v);
}
RM_INLINE u32x2 rm_mods_u32x2(const u32x2 v, const u32 s) {
    return rm_mod_u32x2(v, rm_u32x2s(s));
}
RM_INLINE u32x2 rm_smod_u32x2(const u32 s, const u32x2 v) {
    return rm_mod_u32x2(rm_u32x2s(s), v);
}
RM_INLINE u32x3 rm_mods_u32x3(const u32x3 v, const u32 s) {
    return rm_mod_u32x3(v, rm_u32x3s(s));
}
RM_INLINE u32x3 rm_smod_u32x3(const u32 s, const u32x3 v) {
    return rm_mod_u32x3(rm_u32x3s(s), v);
}
RM_INLINE u32x4 rm_mods_u32x4(const u32x4 v, const u32 s) {
    return rm_mod_u32x4(v, rm_u32x4s(s));
}
RM_INLINE u32x4 rm_smod_u32x4(const u32 s, const u32x4 v) {
    return rm_mod_u32x4(rm_u32x4s(s), v);
}
RM_INLINE u32x2 rm_clamps_u32x2(const u32x2 v, u32 min, u32 max) {
    return rm_clamp_u32x2(v, rm_u32x2s(min), rm_u32x2s(max));
}
RM_INLINE u32x2 rm_fmas_u32x2(const u32x2 a, const u32x2 b, const u32 c) {
    return rm_adds_u32x2(rm_mul_u32x2(a, b), c);
}
RM_INLINE u32x2 rm_fmass_u32x2(const u32x2 a, const u32 b, const u32 c) {
    return rm_adds_u32x2(rm_muls_u32x2(a, b), c);
}
RM_INLINE u32x3 rm_clamps_u32x3(const u32x3 v, u32 min, u32 max) {
    return rm_clamp_u32x3(v, rm_u32x3s(min), rm_u32x3s(max));
}
RM_INLINE u32x3 rm_fmas_u32x3(const u32x3 a, const u32x3 b, const u32 c) {
    return rm_adds_u32x3(rm_mul_u32x3(a, b), c);
}
RM_INLINE u32x3 rm_fmass_u32x3(const u32x3 a, const u32 b, const u32 c) {
    return rm_adds_u32x3(rm_muls_u32x3(a, b), c);
}
RM_INLINE u32x4 rm_clamps_u32x4(const u32x4 v, u32 min, u32 max) {
    return rm_clamp_u32x4(v, rm_u32x4s(min), rm_u32x4s(max));
}
RM_INLINE u32x4 rm_fmas_u32x4(const u32x4 a, const u32x4 b, const u32 c) {
    return rm_adds_u32x4(rm_mul_u32x4(a, b), c);
}
RM_INLINE u32x4 rm_fmass_u32x4(const u32x4 a, const u32 b, const u32 c) {
    return rm_adds_u32x4(rm_muls_u32x4(a, b), c);
}
RM_INLINE u64x2 rm_min_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(rm_min_u64(a.x, b.x), rm_min_u64(a.y, b.y));
}
RM_INLINE u64x3 rm_min_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(rm_min_u64(a.x, b.x), rm_min_u64(a.y, b.y),
                    rm_min_u64(a.z, b.z));
}
RM_INLINE u64x4 rm_min_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(rm_min_u64(a.x, b.x), rm_min_u64(a.y, b.y),
                    rm_min_u64(a.z, b.z), rm_min_u64(a.w, b.w));
}
RM_INLINE u64x2 rm_max_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(rm_max_u64(a.x, b.x), rm_max_u64(a.y, b.y));
}
RM_INLINE u64x3 rm_max_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(rm_max_u64(a.x, b.x), rm_max_u64(a.y, b.y),
                    rm_max_u64(a.z, b.z));
}
RM_INLINE u64x4 rm_max_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(rm_max_u64(a.x, b.x), rm_max_u64(a.y, b.y),
                    rm_max_u64(a.z, b.z), rm_max_u64(a.w, b.w));
}
RM_INLINE u64x2 rm_add_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(a.x + b.x, a.y + b.y);
}
RM_INLINE u64x3 rm_add_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE u64x4 rm_add_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE u64x2 rm_sub_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(a.x - b.x, a.y - b.y);
}
RM_INLINE u64x3 rm_sub_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE u64x4 rm_sub_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE u64x2 rm_mul_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(a.x * b.x, a.y * b.y);
}
RM_INLINE u64x3 rm_mul_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE u64x4 rm_mul_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE u64x2 rm_div_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(a.x / b.x, a.y / b.y);
}
RM_INLINE u64x3 rm_div_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE u64x4 rm_div_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE u64x2 rm_mod_u64x2(const u64x2 a, const u64x2 b) {
    return rm_u64x2(rm_mod_u64(a.x, b.x), rm_mod_u64(a.y, b.y));
}
RM_INLINE u64x3 rm_mod_u64x3(const u64x3 a, const u64x3 b) {
    return rm_u64x3(rm_mod_u64(a.x, b.x), rm_mod_u64(a.y, b.y),
                    rm_mod_u64(a.z, b.z));
}
RM_INLINE u64x4 rm_mod_u64x4(const u64x4 a, const u64x4 b) {
    return rm_u64x4(rm_mod_u64(a.x, b.x), rm_mod_u64(a.y, b.y),
                    rm_mod_u64(a.z, b.z), rm_mod_u64(a.w, b.w));
}
RM_INLINE u64x2 rm_clamp_u64x2(const u64x2 v, const u64x2 min, const u64x2 max) {
    return rm_u64x2(rm_clamp_u64(v.x, min.x, max.x), rm_clamp_u64(v.y, min.y, max.y));
}
RM_INLINE u64x3 rm_clamp_u64x3(const u64x3 v, const u64x3 min, const u64x3 max) {
    return rm_u64x3(rm_clamp_u64(v.x, min.x, max.x), rm_clamp_u64(v.y, min.y, max.y),
                    rm_clamp_u64(v.z, min.z, max.z));
}
RM_INLINE u64x4 rm_clamp_u64x4(const u64x4 v, const u64x4 min, const u64x4 max) {
    return rm_u64x4(rm_clamp_u64(v.x, min.x, max.x), rm_clamp_u64(v.y, min.y, max.y),
                    rm_clamp_u64(v.z, min.z, max.z), rm_clamp_u64(v.w, min.w, max.w));
}
RM_INLINE u64x2 rm_fma_u64x2(const u64x2 a, const u64x2 b, const u64x2 c) {
    return rm_add_u64x2(rm_mul_u64x2(a, b), c);
}
RM_INLINE u64x3 rm_fma_u64x3(const u64x3 a, const u64x3 b, const u64x3 c) {
    return rm_add_u64x3(rm_mul_u64x3(a, b), c);
}
RM_INLINE u64x4 rm_fma_u64x4(const u64x4 a, const u64x4 b, const u64x4 c) {
    return rm_add_u64x4(rm_mul_u64x4(a, b), c);
}
RM_INLINE u64x2 rm_mins_u64x2(const u64x2 v, const u64 s) {
    return rm_min_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x3 rm_mins_u64x3(const u64x3 v, const u64 s) {
    return rm_min_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x4 rm_mins_u64x4(const u64x4 v, const u64 s) {
    return rm_min_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x2 rm_maxs_u64x2(const u64x2 v, const u64 s) {
    return rm_max_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x3 rm_maxs_u64x3(const u64x3 v, const u64 s) {
    return rm_max_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x4 rm_maxs_u64x4(const u64x4 v, const u64 s) {
    return rm_max_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x2 rm_adds_u64x2(const u64x2 v, const u64 s) {
    return rm_add_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x3 rm_adds_u64x3(const u64x3 v, const u64 s) {
    return rm_add_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x4 rm_adds_u64x4(const u64x4 v, const u64 s) {
    return rm_add_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x2 rm_subs_u64x2(const u64x2 v, const u64 s) {
    return rm_sub_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x2 rm_ssub_u64x2(const u64 s, const u64x2 v) {
    return rm_sub_u64x2(rm_u64x2s(s), v);
}
RM_INLINE u64x3 rm_subs_u64x3(const u64x3 v, const u64 s) {
    return rm_sub_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x3 rm_ssub_u64x3(const u64 s, const u64x3 v) {
    return rm_sub_u64x3(rm_u64x3s(s), v);
}
RM_INLINE u64x4 rm_subs_u64x4(const u64x4 v, const u64 s) {
    return rm_sub_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x4 rm_ssub_u64x4(const u64 s, const u64x4 v) {
    return rm_sub_u64x4(rm_u64x4s(s), v);
}
RM_INLINE u64x2 rm_muls_u64x2(const u64x2 v, const u64 s) {
    return rm_mul_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x3 rm_muls_u64x3(const u64x3 v, const u64 s) {
    return rm_mul_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x4 rm_muls_u64x4(const u64x4 v, const u64 s) {
    return rm_mul_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x2 rm_divs_u64x2(const u64x2 v, const u64 s) {
    return rm_div_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x2 rm_sdiv_u64x2(const u64 s, const u64x2 v) {
    return rm_div_u64x2(rm_u64x2s(s), v);
}
RM_INLINE u64x3 rm_divs_u64x3(const u64x3 v, const u64 s) {
    return rm_div_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x3 rm_sdiv_u64x3(const u64 s, const u64x3 v) {
    return rm_div_u64x3(rm_u64x3s(s), v);
}
RM_INLINE u64x4 rm_divs_u64x4(const u64x4 v, const u64 s) {
    return rm_div_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x4 rm_sdiv_u64x4(const u64 s, const u64x4 v) {
    return rm_div_u64x4(rm_u64x4s(s), v);
}
RM_INLINE u64x2 rm_mods_u64x2(const u64x2 v, const u64 s) {
    return rm_mod_u64x2(v, rm_u64x2s(s));
}
RM_INLINE u64x2 rm_smod_u64x2(const u64 s, const u64x2 v) {
    return rm_mod_u64x2(rm_u64x2s(s), v);
}
RM_INLINE u64x3 rm_mods_u64x3(const u64x3 v, const u64 s) {
    return rm_mod_u64x3(v, rm_u64x3s(s));
}
RM_INLINE u64x3 rm_smod_u64x3(const u64 s, const u64x3 v) {
    return rm_mod_u64x3(rm_u64x3s(s), v);
}
RM_INLINE u64x4 rm_mods_u64x4(const u64x4 v, const u64 s) {
    return rm_mod_u64x4(v, rm_u64x4s(s));
}
RM_INLINE u64x4 rm_smod_u64x4(const u64 s, const u64x4 v) {
    return rm_mod_u64x4(rm_u64x4s(s), v);
}
RM_INLINE u64x2 rm_clamps_u64x2(const u64x2 v, u64 min, u64 max) {
    return rm_clamp_u64x2(v, rm_u64x2s(min), rm_u64x2s(max));
}
RM_INLINE u64x2 rm_fmas_u64x2(const u64x2 a, const u64x2 b, const u64 c) {
    return rm_adds_u64x2(rm_mul_u64x2(a, b), c);
}
RM_INLINE u64x2 rm_fmass_u64x2(const u64x2 a, const u64 b, const u64 c) {
    return rm_adds_u64x2(rm_muls_u64x2(a, b), c);
}
RM_INLINE u64x3 rm_clamps_u64x3(const u64x3 v, u64 min, u64 max) {
    return rm_clamp_u64x3(v, rm_u64x3s(min), rm_u64x3s(max));
}
RM_INLINE u64x3 rm_fmas_u64x3(const u64x3 a, const u64x3 b, const u64 c) {
    return rm_adds_u64x3(rm_mul_u64x3(a, b), c);
}
RM_INLINE u64x3 rm_fmass_u64x3(const u64x3 a, const u64 b, const u64 c) {
    return rm_adds_u64x3(rm_muls_u64x3(a, b), c);
}
RM_INLINE u64x4 rm_clamps_u64x4(const u64x4 v, u64 min, u64 max) {
    return rm_clamp_u64x4(v, rm_u64x4s(min), rm_u64x4s(max));
}
RM_INLINE u64x4 rm_fmas_u64x4(const u64x4 a, const u64x4 b, const u64 c) {
    return rm_adds_u64x4(rm_mul_u64x4(a, b), c);
}
RM_INLINE u64x4 rm_fmass_u64x4(const u64x4 a, const u64 b, const u64 c) {
    return rm_adds_u64x4(rm_muls_u64x4(a, b), c);
}
RM_INLINE i8x2 rm_min_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(rm_min_i8(a.x, b.x), rm_min_i8(a.y, b.y));
}
RM_INLINE i8x3 rm_min_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(rm_min_i8(a.x, b.x), rm_min_i8(a.y, b.y),
                    rm_min_i8(a.z, b.z));
}
RM_INLINE i8x4 rm_min_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(rm_min_i8(a.x, b.x), rm_min_i8(a.y, b.y),
                    rm_min_i8(a.z, b.z), rm_min_i8(a.w, b.w));
}
RM_INLINE i8x2 rm_max_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(rm_max_i8(a.x, b.x), rm_max_i8(a.y, b.y));
}
RM_INLINE i8x3 rm_max_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(rm_max_i8(a.x, b.x), rm_max_i8(a.y, b.y),
                    rm_max_i8(a.z, b.z));
}
RM_INLINE i8x4 rm_max_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(rm_max_i8(a.x, b.x), rm_max_i8(a.y, b.y),
                    rm_max_i8(a.z, b.z), rm_max_i8(a.w, b.w));
}
RM_INLINE i8x2 rm_add_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(a.x + b.x, a.y + b.y);
}
RM_INLINE i8x3 rm_add_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE i8x4 rm_add_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE i8x2 rm_sub_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(a.x - b.x, a.y - b.y);
}
RM_INLINE i8x3 rm_sub_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE i8x4 rm_sub_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE i8x2 rm_mul_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(a.x * b.x, a.y * b.y);
}
RM_INLINE i8x3 rm_mul_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE i8x4 rm_mul_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE i8x2 rm_div_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(a.x / b.x, a.y / b.y);
}
RM_INLINE i8x3 rm_div_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE i8x4 rm_div_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE i8x2 rm_mod_i8x2(const i8x2 a, const i8x2 b) {
    return rm_i8x2(rm_mod_i8(a.x, b.x), rm_mod_i8(a.y, b.y));
}
RM_INLINE i8x3 rm_mod_i8x3(const i8x3 a, const i8x3 b) {
    return rm_i8x3(rm_mod_i8(a.x, b.x), rm_mod_i8(a.y, b.y),
                    rm_mod_i8(a.z, b.z));
}
RM_INLINE i8x4 rm_mod_i8x4(const i8x4 a, const i8x4 b) {
    return rm_i8x4(rm_mod_i8(a.x, b.x), rm_mod_i8(a.y, b.y),
                    rm_mod_i8(a.z, b.z), rm_mod_i8(a.w, b.w));
}
RM_INLINE i8x2 rm_clamp_i8x2(const i8x2 v, const i8x2 min, const i8x2 max) {
    return rm_i8x2(rm_clamp_i8(v.x, min.x, max.x), rm_clamp_i8(v.y, min.y, max.y));
}
RM_INLINE i8x3 rm_clamp_i8x3(const i8x3 v, const i8x3 min, const i8x3 max) {
    return rm_i8x3(rm_clamp_i8(v.x, min.x, max.x), rm_clamp_i8(v.y, min.y, max.y),
                    rm_clamp_i8(v.z, min.z, max.z));
}
RM_INLINE i8x4 rm_clamp_i8x4(const i8x4 v, const i8x4 min, const i8x4 max) {
    return rm_i8x4(rm_clamp_i8(v.x, min.x, max.x), rm_clamp_i8(v.y, min.y, max.y),
                    rm_clamp_i8(v.z, min.z, max.z), rm_clamp_i8(v.w, min.w, max.w));
}
RM_INLINE i8x2 rm_sign_i8x2(const i8x2 v) {
    return rm_i8x2(rm_sign_i8(v.x), rm_sign_i8(v.y));
}
RM_INLINE i8x3 rm_sign_i8x3(const i8x3 v) {
    return rm_i8x3(rm_sign_i8(v.x), rm_sign_i8(v.y),
                    rm_sign_i8(v.z));
}
RM_INLINE i8x4 rm_sign_i8x4(const i8x4 v) {
    return rm_i8x4(rm_sign_i8(v.x), rm_sign_i8(v.y),
                    rm_sign_i8(v.z), rm_sign_i8(v.w));
}
RM_INLINE i8x2 rm_copysign_i8x2(const i8x2 v, const i8x2 s) {
    return rm_i8x2(rm_copysign_i8(v.x, s.x), rm_copysign_i8(v.y, s.y));
}
RM_INLINE i8x3 rm_copysign_i8x3(const i8x3 v, const i8x3 s) {
    return rm_i8x3(rm_copysign_i8(v.x, s.x), rm_copysign_i8(v.y, s.y),
                    rm_copysign_i8(v.z, s.z));
}
RM_INLINE i8x4 rm_copysign_i8x4(const i8x4 v, const i8x4 s) {
    return rm_i8x4(rm_copysign_i8(v.x, s.x), rm_copysign_i8(v.y, s.y),
                    rm_copysign_i8(v.z, s.z), rm_copysign_i8(v.w, s.w));
}
RM_INLINE i8x2 rm_fma_i8x2(const i8x2 a, const i8x2 b, const i8x2 c) {
    return rm_add_i8x2(rm_mul_i8x2(a, b), c);
}
RM_INLINE i8x3 rm_fma_i8x3(const i8x3 a, const i8x3 b, const i8x3 c) {
    return rm_add_i8x3(rm_mul_i8x3(a, b), c);
}
RM_INLINE i8x4 rm_fma_i8x4(const i8x4 a, const i8x4 b, const i8x4 c) {
    return rm_add_i8x4(rm_mul_i8x4(a, b), c);
}
RM_INLINE i8x2 rm_mins_i8x2(const i8x2 v, const i8 s) {
    return rm_min_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x3 rm_mins_i8x3(const i8x3 v, const i8 s) {
    return rm_min_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x4 rm_mins_i8x4(const i8x4 v, const i8 s) {
    return rm_min_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x2 rm_maxs_i8x2(const i8x2 v, const i8 s) {
    return rm_max_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x3 rm_maxs_i8x3(const i8x3 v, const i8 s) {
    return rm_max_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x4 rm_maxs_i8x4(const i8x4 v, const i8 s) {
    return rm_max_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x2 rm_adds_i8x2(const i8x2 v, const i8 s) {
    return rm_add_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x3 rm_adds_i8x3(const i8x3 v, const i8 s) {
    return rm_add_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x4 rm_adds_i8x4(const i8x4 v, const i8 s) {
    return rm_add_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x2 rm_subs_i8x2(const i8x2 v, const i8 s) {
    return rm_sub_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x2 rm_ssub_i8x2(const i8 s, const i8x2 v) {
    return rm_sub_i8x2(rm_i8x2s(s), v);
}
RM_INLINE i8x3 rm_subs_i8x3(const i8x3 v, const i8 s) {
    return rm_sub_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x3 rm_ssub_i8x3(const i8 s, const i8x3 v) {
    return rm_sub_i8x3(rm_i8x3s(s), v);
}
RM_INLINE i8x4 rm_subs_i8x4(const i8x4 v, const i8 s) {
    return rm_sub_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x4 rm_ssub_i8x4(const i8 s, const i8x4 v) {
    return rm_sub_i8x4(rm_i8x4s(s), v);
}
RM_INLINE i8x2 rm_muls_i8x2(const i8x2 v, const i8 s) {
    return rm_mul_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x3 rm_muls_i8x3(const i8x3 v, const i8 s) {
    return rm_mul_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x4 rm_muls_i8x4(const i8x4 v, const i8 s) {
    return rm_mul_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x2 rm_divs_i8x2(const i8x2 v, const i8 s) {
    return rm_div_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x2 rm_sdiv_i8x2(const i8 s, const i8x2 v) {
    return rm_div_i8x2(rm_i8x2s(s), v);
}
RM_INLINE i8x3 rm_divs_i8x3(const i8x3 v, const i8 s) {
    return rm_div_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x3 rm_sdiv_i8x3(const i8 s, const i8x3 v) {
    return rm_div_i8x3(rm_i8x3s(s), v);
}
RM_INLINE i8x4 rm_divs_i8x4(const i8x4 v, const i8 s) {
    return rm_div_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x4 rm_sdiv_i8x4(const i8 s, const i8x4 v) {
    return rm_div_i8x4(rm_i8x4s(s), v);
}
RM_INLINE i8x2 rm_mods_i8x2(const i8x2 v, const i8 s) {
    return rm_mod_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x2 rm_smod_i8x2(const i8 s, const i8x2 v) {
    return rm_mod_i8x2(rm_i8x2s(s), v);
}
RM_INLINE i8x3 rm_mods_i8x3(const i8x3 v, const i8 s) {
    return rm_mod_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x3 rm_smod_i8x3(const i8 s, const i8x3 v) {
    return rm_mod_i8x3(rm_i8x3s(s), v);
}
RM_INLINE i8x4 rm_mods_i8x4(const i8x4 v, const i8 s) {
    return rm_mod_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x4 rm_smod_i8x4(const i8 s, const i8x4 v) {
    return rm_mod_i8x4(rm_i8x4s(s), v);
}
RM_INLINE i8x2 rm_clamps_i8x2(const i8x2 v, i8 min, i8 max) {
    return rm_clamp_i8x2(v, rm_i8x2s(min), rm_i8x2s(max));
}
RM_INLINE i8x2 rm_copysigns_i8x2(const i8x2 v, const i8 s) {
    return rm_copysign_i8x2(v, rm_i8x2s(s));
}
RM_INLINE i8x2 rm_fmas_i8x2(const i8x2 a, const i8x2 b, const i8 c) {
    return rm_adds_i8x2(rm_mul_i8x2(a, b), c);
}
RM_INLINE i8x2 rm_fmass_i8x2(const i8x2 a, const i8 b, const i8 c) {
    return rm_adds_i8x2(rm_muls_i8x2(a, b), c);
}
RM_INLINE i8x3 rm_clamps_i8x3(const i8x3 v, i8 min, i8 max) {
    return rm_clamp_i8x3(v, rm_i8x3s(min), rm_i8x3s(max));
}
RM_INLINE i8x3 rm_copysigns_i8x3(const i8x3 v, const i8 s) {
    return rm_copysign_i8x3(v, rm_i8x3s(s));
}
RM_INLINE i8x3 rm_fmas_i8x3(const i8x3 a, const i8x3 b, const i8 c) {
    return rm_adds_i8x3(rm_mul_i8x3(a, b), c);
}
RM_INLINE i8x3 rm_fmass_i8x3(const i8x3 a, const i8 b, const i8 c) {
    return rm_adds_i8x3(rm_muls_i8x3(a, b), c);
}
RM_INLINE i8x4 rm_clamps_i8x4(const i8x4 v, i8 min, i8 max) {
    return rm_clamp_i8x4(v, rm_i8x4s(min), rm_i8x4s(max));
}
RM_INLINE i8x4 rm_copysigns_i8x4(const i8x4 v, const i8 s) {
    return rm_copysign_i8x4(v, rm_i8x4s(s));
}
RM_INLINE i8x4 rm_fmas_i8x4(const i8x4 a, const i8x4 b, const i8 c) {
    return rm_adds_i8x4(rm_mul_i8x4(a, b), c);
}
RM_INLINE i8x4 rm_fmass_i8x4(const i8x4 a, const i8 b, const i8 c) {
    return rm_adds_i8x4(rm_muls_i8x4(a, b), c);
}
RM_INLINE i16x2 rm_min_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(rm_min_i16(a.x, b.x), rm_min_i16(a.y, b.y));
}
RM_INLINE i16x3 rm_min_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(rm_min_i16(a.x, b.x), rm_min_i16(a.y, b.y),
                    rm_min_i16(a.z, b.z));
}
RM_INLINE i16x4 rm_min_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(rm_min_i16(a.x, b.x), rm_min_i16(a.y, b.y),
                    rm_min_i16(a.z, b.z), rm_min_i16(a.w, b.w));
}
RM_INLINE i16x2 rm_max_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(rm_max_i16(a.x, b.x), rm_max_i16(a.y, b.y));
}
RM_INLINE i16x3 rm_max_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(rm_max_i16(a.x, b.x), rm_max_i16(a.y, b.y),
                    rm_max_i16(a.z, b.z));
}
RM_INLINE i16x4 rm_max_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(rm_max_i16(a.x, b.x), rm_max_i16(a.y, b.y),
                    rm_max_i16(a.z, b.z), rm_max_i16(a.w, b.w));
}
RM_INLINE i16x2 rm_add_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(a.x + b.x, a.y + b.y);
}
RM_INLINE i16x3 rm_add_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE i16x4 rm_add_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE i16x2 rm_sub_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(a.x - b.x, a.y - b.y);
}
RM_INLINE i16x3 rm_sub_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE i16x4 rm_sub_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE i16x2 rm_mul_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(a.x * b.x, a.y * b.y);
}
RM_INLINE i16x3 rm_mul_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE i16x4 rm_mul_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE i16x2 rm_div_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(a.x / b.x, a.y / b.y);
}
RM_INLINE i16x3 rm_div_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE i16x4 rm_div_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE i16x2 rm_mod_i16x2(const i16x2 a, const i16x2 b) {
    return rm_i16x2(rm_mod_i16(a.x, b.x), rm_mod_i16(a.y, b.y));
}
RM_INLINE i16x3 rm_mod_i16x3(const i16x3 a, const i16x3 b) {
    return rm_i16x3(rm_mod_i16(a.x, b.x), rm_mod_i16(a.y, b.y),
                    rm_mod_i16(a.z, b.z));
}
RM_INLINE i16x4 rm_mod_i16x4(const i16x4 a, const i16x4 b) {
    return rm_i16x4(rm_mod_i16(a.x, b.x), rm_mod_i16(a.y, b.y),
                    rm_mod_i16(a.z, b.z), rm_mod_i16(a.w, b.w));
}
RM_INLINE i16x2 rm_clamp_i16x2(const i16x2 v, const i16x2 min, const i16x2 max) {
    return rm_i16x2(rm_clamp_i16(v.x, min.x, max.x), rm_clamp_i16(v.y, min.y, max.y));
}
RM_INLINE i16x3 rm_clamp_i16x3(const i16x3 v, const i16x3 min, const i16x3 max) {
    return rm_i16x3(rm_clamp_i16(v.x, min.x, max.x), rm_clamp_i16(v.y, min.y, max.y),
                    rm_clamp_i16(v.z, min.z, max.z));
}
RM_INLINE i16x4 rm_clamp_i16x4(const i16x4 v, const i16x4 min, const i16x4 max) {
    return rm_i16x4(rm_clamp_i16(v.x, min.x, max.x), rm_clamp_i16(v.y, min.y, max.y),
                    rm_clamp_i16(v.z, min.z, max.z), rm_clamp_i16(v.w, min.w, max.w));
}
RM_INLINE i16x2 rm_sign_i16x2(const i16x2 v) {
    return rm_i16x2(rm_sign_i16(v.x), rm_sign_i16(v.y));
}
RM_INLINE i16x3 rm_sign_i16x3(const i16x3 v) {
    return rm_i16x3(rm_sign_i16(v.x), rm_sign_i16(v.y),
                    rm_sign_i16(v.z));
}
RM_INLINE i16x4 rm_sign_i16x4(const i16x4 v) {
    return rm_i16x4(rm_sign_i16(v.x), rm_sign_i16(v.y),
                    rm_sign_i16(v.z), rm_sign_i16(v.w));
}
RM_INLINE i16x2 rm_copysign_i16x2(const i16x2 v, const i16x2 s) {
    return rm_i16x2(rm_copysign_i16(v.x, s.x), rm_copysign_i16(v.y, s.y));
}
RM_INLINE i16x3 rm_copysign_i16x3(const i16x3 v, const i16x3 s) {
    return rm_i16x3(rm_copysign_i16(v.x, s.x), rm_copysign_i16(v.y, s.y),
                    rm_copysign_i16(v.z, s.z));
}
RM_INLINE i16x4 rm_copysign_i16x4(const i16x4 v, const i16x4 s) {
    return rm_i16x4(rm_copysign_i16(v.x, s.x), rm_copysign_i16(v.y, s.y),
                    rm_copysign_i16(v.z, s.z), rm_copysign_i16(v.w, s.w));
}
RM_INLINE i16x2 rm_fma_i16x2(const i16x2 a, const i16x2 b, const i16x2 c) {
    return rm_add_i16x2(rm_mul_i16x2(a, b), c);
}
RM_INLINE i16x3 rm_fma_i16x3(const i16x3 a, const i16x3 b, const i16x3 c) {
    return rm_add_i16x3(rm_mul_i16x3(a, b), c);
}
RM_INLINE i16x4 rm_fma_i16x4(const i16x4 a, const i16x4 b, const i16x4 c) {
    return rm_add_i16x4(rm_mul_i16x4(a, b), c);
}
RM_INLINE i16x2 rm_mins_i16x2(const i16x2 v, const i16 s) {
    return rm_min_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x3 rm_mins_i16x3(const i16x3 v, const i16 s) {
    return rm_min_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x4 rm_mins_i16x4(const i16x4 v, const i16 s) {
    return rm_min_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x2 rm_maxs_i16x2(const i16x2 v, const i16 s) {
    return rm_max_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x3 rm_maxs_i16x3(const i16x3 v, const i16 s) {
    return rm_max_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x4 rm_maxs_i16x4(const i16x4 v, const i16 s) {
    return rm_max_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x2 rm_adds_i16x2(const i16x2 v, const i16 s) {
    return rm_add_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x3 rm_adds_i16x3(const i16x3 v, const i16 s) {
    return rm_add_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x4 rm_adds_i16x4(const i16x4 v, const i16 s) {
    return rm_add_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x2 rm_subs_i16x2(const i16x2 v, const i16 s) {
    return rm_sub_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x2 rm_ssub_i16x2(const i16 s, const i16x2 v) {
    return rm_sub_i16x2(rm_i16x2s(s), v);
}
RM_INLINE i16x3 rm_subs_i16x3(const i16x3 v, const i16 s) {
    return rm_sub_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x3 rm_ssub_i16x3(const i16 s, const i16x3 v) {
    return rm_sub_i16x3(rm_i16x3s(s), v);
}
RM_INLINE i16x4 rm_subs_i16x4(const i16x4 v, const i16 s) {
    return rm_sub_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x4 rm_ssub_i16x4(const i16 s, const i16x4 v) {
    return rm_sub_i16x4(rm_i16x4s(s), v);
}
RM_INLINE i16x2 rm_muls_i16x2(const i16x2 v, const i16 s) {
    return rm_mul_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x3 rm_muls_i16x3(const i16x3 v, const i16 s) {
    return rm_mul_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x4 rm_muls_i16x4(const i16x4 v, const i16 s) {
    return rm_mul_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x2 rm_divs_i16x2(const i16x2 v, const i16 s) {
    return rm_div_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x2 rm_sdiv_i16x2(const i16 s, const i16x2 v) {
    return rm_div_i16x2(rm_i16x2s(s), v);
}
RM_INLINE i16x3 rm_divs_i16x3(const i16x3 v, const i16 s) {
    return rm_div_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x3 rm_sdiv_i16x3(const i16 s, const i16x3 v) {
    return rm_div_i16x3(rm_i16x3s(s), v);
}
RM_INLINE i16x4 rm_divs_i16x4(const i16x4 v, const i16 s) {
    return rm_div_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x4 rm_sdiv_i16x4(const i16 s, const i16x4 v) {
    return rm_div_i16x4(rm_i16x4s(s), v);
}
RM_INLINE i16x2 rm_mods_i16x2(const i16x2 v, const i16 s) {
    return rm_mod_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x2 rm_smod_i16x2(const i16 s, const i16x2 v) {
    return rm_mod_i16x2(rm_i16x2s(s), v);
}
RM_INLINE i16x3 rm_mods_i16x3(const i16x3 v, const i16 s) {
    return rm_mod_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x3 rm_smod_i16x3(const i16 s, const i16x3 v) {
    return rm_mod_i16x3(rm_i16x3s(s), v);
}
RM_INLINE i16x4 rm_mods_i16x4(const i16x4 v, const i16 s) {
    return rm_mod_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x4 rm_smod_i16x4(const i16 s, const i16x4 v) {
    return rm_mod_i16x4(rm_i16x4s(s), v);
}
RM_INLINE i16x2 rm_clamps_i16x2(const i16x2 v, i16 min, i16 max) {
    return rm_clamp_i16x2(v, rm_i16x2s(min), rm_i16x2s(max));
}
RM_INLINE i16x2 rm_copysigns_i16x2(const i16x2 v, const i16 s) {
    return rm_copysign_i16x2(v, rm_i16x2s(s));
}
RM_INLINE i16x2 rm_fmas_i16x2(const i16x2 a, const i16x2 b, const i16 c) {
    return rm_adds_i16x2(rm_mul_i16x2(a, b), c);
}
RM_INLINE i16x2 rm_fmass_i16x2(const i16x2 a, const i16 b, const i16 c) {
    return rm_adds_i16x2(rm_muls_i16x2(a, b), c);
}
RM_INLINE i16x3 rm_clamps_i16x3(const i16x3 v, i16 min, i16 max) {
    return rm_clamp_i16x3(v, rm_i16x3s(min), rm_i16x3s(max));
}
RM_INLINE i16x3 rm_copysigns_i16x3(const i16x3 v, const i16 s) {
    return rm_copysign_i16x3(v, rm_i16x3s(s));
}
RM_INLINE i16x3 rm_fmas_i16x3(const i16x3 a, const i16x3 b, const i16 c) {
    return rm_adds_i16x3(rm_mul_i16x3(a, b), c);
}
RM_INLINE i16x3 rm_fmass_i16x3(const i16x3 a, const i16 b, const i16 c) {
    return rm_adds_i16x3(rm_muls_i16x3(a, b), c);
}
RM_INLINE i16x4 rm_clamps_i16x4(const i16x4 v, i16 min, i16 max) {
    return rm_clamp_i16x4(v, rm_i16x4s(min), rm_i16x4s(max));
}
RM_INLINE i16x4 rm_copysigns_i16x4(const i16x4 v, const i16 s) {
    return rm_copysign_i16x4(v, rm_i16x4s(s));
}
RM_INLINE i16x4 rm_fmas_i16x4(const i16x4 a, const i16x4 b, const i16 c) {
    return rm_adds_i16x4(rm_mul_i16x4(a, b), c);
}
RM_INLINE i16x4 rm_fmass_i16x4(const i16x4 a, const i16 b, const i16 c) {
    return rm_adds_i16x4(rm_muls_i16x4(a, b), c);
}
RM_INLINE i32x2 rm_min_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(rm_min_i32(a.x, b.x), rm_min_i32(a.y, b.y));
}
RM_INLINE i32x3 rm_min_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(rm_min_i32(a.x, b.x), rm_min_i32(a.y, b.y),
                    rm_min_i32(a.z, b.z));
}
RM_INLINE i32x4 rm_min_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(rm_min_i32(a.x, b.x), rm_min_i32(a.y, b.y),
                    rm_min_i32(a.z, b.z), rm_min_i32(a.w, b.w));
}
RM_INLINE i32x2 rm_max_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(rm_max_i32(a.x, b.x), rm_max_i32(a.y, b.y));
}
RM_INLINE i32x3 rm_max_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(rm_max_i32(a.x, b.x), rm_max_i32(a.y, b.y),
                    rm_max_i32(a.z, b.z));
}
RM_INLINE i32x4 rm_max_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(rm_max_i32(a.x, b.x), rm_max_i32(a.y, b.y),
                    rm_max_i32(a.z, b.z), rm_max_i32(a.w, b.w));
}
RM_INLINE i32x2 rm_add_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(a.x + b.x, a.y + b.y);
}
RM_INLINE i32x3 rm_add_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE i32x4 rm_add_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE i32x2 rm_sub_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(a.x - b.x, a.y - b.y);
}
RM_INLINE i32x3 rm_sub_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE i32x4 rm_sub_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE i32x2 rm_mul_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(a.x * b.x, a.y * b.y);
}
RM_INLINE i32x3 rm_mul_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE i32x4 rm_mul_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE i32x2 rm_div_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(a.x / b.x, a.y / b.y);
}
RM_INLINE i32x3 rm_div_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE i32x4 rm_div_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE i32x2 rm_mod_i32x2(const i32x2 a, const i32x2 b) {
    return rm_i32x2(rm_mod_i32(a.x, b.x), rm_mod_i32(a.y, b.y));
}
RM_INLINE i32x3 rm_mod_i32x3(const i32x3 a, const i32x3 b) {
    return rm_i32x3(rm_mod_i32(a.x, b.x), rm_mod_i32(a.y, b.y),
                    rm_mod_i32(a.z, b.z));
}
RM_INLINE i32x4 rm_mod_i32x4(const i32x4 a, const i32x4 b) {
    return rm_i32x4(rm_mod_i32(a.x, b.x), rm_mod_i32(a.y, b.y),
                    rm_mod_i32(a.z, b.z), rm_mod_i32(a.w, b.w));
}
RM_INLINE i32x2 rm_clamp_i32x2(const i32x2 v, const i32x2 min, const i32x2 max) {
    return rm_i32x2(rm_clamp_i32(v.x, min.x, max.x), rm_clamp_i32(v.y, min.y, max.y));
}
RM_INLINE i32x3 rm_clamp_i32x3(const i32x3 v, const i32x3 min, const i32x3 max) {
    return rm_i32x3(rm_clamp_i32(v.x, min.x, max.x), rm_clamp_i32(v.y, min.y, max.y),
                    rm_clamp_i32(v.z, min.z, max.z));
}
RM_INLINE i32x4 rm_clamp_i32x4(const i32x4 v, const i32x4 min, const i32x4 max) {
    return rm_i32x4(rm_clamp_i32(v.x, min.x, max.x), rm_clamp_i32(v.y, min.y, max.y),
                    rm_clamp_i32(v.z, min.z, max.z), rm_clamp_i32(v.w, min.w, max.w));
}
RM_INLINE i32x2 rm_sign_i32x2(const i32x2 v) {
    return rm_i32x2(rm_sign_i32(v.x), rm_sign_i32(v.y));
}
RM_INLINE i32x3 rm_sign_i32x3(const i32x3 v) {
    return rm_i32x3(rm_sign_i32(v.x), rm_sign_i32(v.y),
                    rm_sign_i32(v.z));
}
RM_INLINE i32x4 rm_sign_i32x4(const i32x4 v) {
    return rm_i32x4(rm_sign_i32(v.x), rm_sign_i32(v.y),
                    rm_sign_i32(v.z), rm_sign_i32(v.w));
}
RM_INLINE i32x2 rm_copysign_i32x2(const i32x2 v, const i32x2 s) {
    return rm_i32x2(rm_copysign_i32(v.x, s.x), rm_copysign_i32(v.y, s.y));
}
RM_INLINE i32x3 rm_copysign_i32x3(const i32x3 v, const i32x3 s) {
    return rm_i32x3(rm_copysign_i32(v.x, s.x), rm_copysign_i32(v.y, s.y),
                    rm_copysign_i32(v.z, s.z));
}
RM_INLINE i32x4 rm_copysign_i32x4(const i32x4 v, const i32x4 s) {
    return rm_i32x4(rm_copysign_i32(v.x, s.x), rm_copysign_i32(v.y, s.y),
                    rm_copysign_i32(v.z, s.z), rm_copysign_i32(v.w, s.w));
}
RM_INLINE i32x2 rm_fma_i32x2(const i32x2 a, const i32x2 b, const i32x2 c) {
    return rm_add_i32x2(rm_mul_i32x2(a, b), c);
}
RM_INLINE i32x3 rm_fma_i32x3(const i32x3 a, const i32x3 b, const i32x3 c) {
    return rm_add_i32x3(rm_mul_i32x3(a, b), c);
}
RM_INLINE i32x4 rm_fma_i32x4(const i32x4 a, const i32x4 b, const i32x4 c) {
    return rm_add_i32x4(rm_mul_i32x4(a, b), c);
}
RM_INLINE i32x2 rm_mins_i32x2(const i32x2 v, const i32 s) {
    return rm_min_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x3 rm_mins_i32x3(const i32x3 v, const i32 s) {
    return rm_min_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x4 rm_mins_i32x4(const i32x4 v, const i32 s) {
    return rm_min_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x2 rm_maxs_i32x2(const i32x2 v, const i32 s) {
    return rm_max_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x3 rm_maxs_i32x3(const i32x3 v, const i32 s) {
    return rm_max_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x4 rm_maxs_i32x4(const i32x4 v, const i32 s) {
    return rm_max_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x2 rm_adds_i32x2(const i32x2 v, const i32 s) {
    return rm_add_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x3 rm_adds_i32x3(const i32x3 v, const i32 s) {
    return rm_add_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x4 rm_adds_i32x4(const i32x4 v, const i32 s) {
    return rm_add_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x2 rm_subs_i32x2(const i32x2 v, const i32 s) {
    return rm_sub_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x2 rm_ssub_i32x2(const i32 s, const i32x2 v) {
    return rm_sub_i32x2(rm_i32x2s(s), v);
}
RM_INLINE i32x3 rm_subs_i32x3(const i32x3 v, const i32 s) {
    return rm_sub_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x3 rm_ssub_i32x3(const i32 s, const i32x3 v) {
    return rm_sub_i32x3(rm_i32x3s(s), v);
}
RM_INLINE i32x4 rm_subs_i32x4(const i32x4 v, const i32 s) {
    return rm_sub_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x4 rm_ssub_i32x4(const i32 s, const i32x4 v) {
    return rm_sub_i32x4(rm_i32x4s(s), v);
}
RM_INLINE i32x2 rm_muls_i32x2(const i32x2 v, const i32 s) {
    return rm_mul_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x3 rm_muls_i32x3(const i32x3 v, const i32 s) {
    return rm_mul_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x4 rm_muls_i32x4(const i32x4 v, const i32 s) {
    return rm_mul_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x2 rm_divs_i32x2(const i32x2 v, const i32 s) {
    return rm_div_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x2 rm_sdiv_i32x2(const i32 s, const i32x2 v) {
    return rm_div_i32x2(rm_i32x2s(s), v);
}
RM_INLINE i32x3 rm_divs_i32x3(const i32x3 v, const i32 s) {
    return rm_div_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x3 rm_sdiv_i32x3(const i32 s, const i32x3 v) {
    return rm_div_i32x3(rm_i32x3s(s), v);
}
RM_INLINE i32x4 rm_divs_i32x4(const i32x4 v, const i32 s) {
    return rm_div_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x4 rm_sdiv_i32x4(const i32 s, const i32x4 v) {
    return rm_div_i32x4(rm_i32x4s(s), v);
}
RM_INLINE i32x2 rm_mods_i32x2(const i32x2 v, const i32 s) {
    return rm_mod_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x2 rm_smod_i32x2(const i32 s, const i32x2 v) {
    return rm_mod_i32x2(rm_i32x2s(s), v);
}
RM_INLINE i32x3 rm_mods_i32x3(const i32x3 v, const i32 s) {
    return rm_mod_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x3 rm_smod_i32x3(const i32 s, const i32x3 v) {
    return rm_mod_i32x3(rm_i32x3s(s), v);
}
RM_INLINE i32x4 rm_mods_i32x4(const i32x4 v, const i32 s) {
    return rm_mod_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x4 rm_smod_i32x4(const i32 s, const i32x4 v) {
    return rm_mod_i32x4(rm_i32x4s(s), v);
}
RM_INLINE i32x2 rm_clamps_i32x2(const i32x2 v, i32 min, i32 max) {
    return rm_clamp_i32x2(v, rm_i32x2s(min), rm_i32x2s(max));
}
RM_INLINE i32x2 rm_copysigns_i32x2(const i32x2 v, const i32 s) {
    return rm_copysign_i32x2(v, rm_i32x2s(s));
}
RM_INLINE i32x2 rm_fmas_i32x2(const i32x2 a, const i32x2 b, const i32 c) {
    return rm_adds_i32x2(rm_mul_i32x2(a, b), c);
}
RM_INLINE i32x2 rm_fmass_i32x2(const i32x2 a, const i32 b, const i32 c) {
    return rm_adds_i32x2(rm_muls_i32x2(a, b), c);
}
RM_INLINE i32x3 rm_clamps_i32x3(const i32x3 v, i32 min, i32 max) {
    return rm_clamp_i32x3(v, rm_i32x3s(min), rm_i32x3s(max));
}
RM_INLINE i32x3 rm_copysigns_i32x3(const i32x3 v, const i32 s) {
    return rm_copysign_i32x3(v, rm_i32x3s(s));
}
RM_INLINE i32x3 rm_fmas_i32x3(const i32x3 a, const i32x3 b, const i32 c) {
    return rm_adds_i32x3(rm_mul_i32x3(a, b), c);
}
RM_INLINE i32x3 rm_fmass_i32x3(const i32x3 a, const i32 b, const i32 c) {
    return rm_adds_i32x3(rm_muls_i32x3(a, b), c);
}
RM_INLINE i32x4 rm_clamps_i32x4(const i32x4 v, i32 min, i32 max) {
    return rm_clamp_i32x4(v, rm_i32x4s(min), rm_i32x4s(max));
}
RM_INLINE i32x4 rm_copysigns_i32x4(const i32x4 v, const i32 s) {
    return rm_copysign_i32x4(v, rm_i32x4s(s));
}
RM_INLINE i32x4 rm_fmas_i32x4(const i32x4 a, const i32x4 b, const i32 c) {
    return rm_adds_i32x4(rm_mul_i32x4(a, b), c);
}
RM_INLINE i32x4 rm_fmass_i32x4(const i32x4 a, const i32 b, const i32 c) {
    return rm_adds_i32x4(rm_muls_i32x4(a, b), c);
}
RM_INLINE i64x2 rm_min_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(rm_min_i64(a.x, b.x), rm_min_i64(a.y, b.y));
}
RM_INLINE i64x3 rm_min_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(rm_min_i64(a.x, b.x), rm_min_i64(a.y, b.y),
                    rm_min_i64(a.z, b.z));
}
RM_INLINE i64x4 rm_min_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(rm_min_i64(a.x, b.x), rm_min_i64(a.y, b.y),
                    rm_min_i64(a.z, b.z), rm_min_i64(a.w, b.w));
}
RM_INLINE i64x2 rm_max_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(rm_max_i64(a.x, b.x), rm_max_i64(a.y, b.y));
}
RM_INLINE i64x3 rm_max_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(rm_max_i64(a.x, b.x), rm_max_i64(a.y, b.y),
                    rm_max_i64(a.z, b.z));
}
RM_INLINE i64x4 rm_max_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(rm_max_i64(a.x, b.x), rm_max_i64(a.y, b.y),
                    rm_max_i64(a.z, b.z), rm_max_i64(a.w, b.w));
}
RM_INLINE i64x2 rm_add_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(a.x + b.x, a.y + b.y);
}
RM_INLINE i64x3 rm_add_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE i64x4 rm_add_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE i64x2 rm_sub_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(a.x - b.x, a.y - b.y);
}
RM_INLINE i64x3 rm_sub_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE i64x4 rm_sub_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE i64x2 rm_mul_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(a.x * b.x, a.y * b.y);
}
RM_INLINE i64x3 rm_mul_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE i64x4 rm_mul_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE i64x2 rm_div_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(a.x / b.x, a.y / b.y);
}
RM_INLINE i64x3 rm_div_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE i64x4 rm_div_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE i64x2 rm_mod_i64x2(const i64x2 a, const i64x2 b) {
    return rm_i64x2(rm_mod_i64(a.x, b.x), rm_mod_i64(a.y, b.y));
}
RM_INLINE i64x3 rm_mod_i64x3(const i64x3 a, const i64x3 b) {
    return rm_i64x3(rm_mod_i64(a.x, b.x), rm_mod_i64(a.y, b.y),
                    rm_mod_i64(a.z, b.z));
}
RM_INLINE i64x4 rm_mod_i64x4(const i64x4 a, const i64x4 b) {
    return rm_i64x4(rm_mod_i64(a.x, b.x), rm_mod_i64(a.y, b.y),
                    rm_mod_i64(a.z, b.z), rm_mod_i64(a.w, b.w));
}
RM_INLINE i64x2 rm_clamp_i64x2(const i64x2 v, const i64x2 min, const i64x2 max) {
    return rm_i64x2(rm_clamp_i64(v.x, min.x, max.x), rm_clamp_i64(v.y, min.y, max.y));
}
RM_INLINE i64x3 rm_clamp_i64x3(const i64x3 v, const i64x3 min, const i64x3 max) {
    return rm_i64x3(rm_clamp_i64(v.x, min.x, max.x), rm_clamp_i64(v.y, min.y, max.y),
                    rm_clamp_i64(v.z, min.z, max.z));
}
RM_INLINE i64x4 rm_clamp_i64x4(const i64x4 v, const i64x4 min, const i64x4 max) {
    return rm_i64x4(rm_clamp_i64(v.x, min.x, max.x), rm_clamp_i64(v.y, min.y, max.y),
                    rm_clamp_i64(v.z, min.z, max.z), rm_clamp_i64(v.w, min.w, max.w));
}
RM_INLINE i64x2 rm_sign_i64x2(const i64x2 v) {
    return rm_i64x2(rm_sign_i64(v.x), rm_sign_i64(v.y));
}
RM_INLINE i64x3 rm_sign_i64x3(const i64x3 v) {
    return rm_i64x3(rm_sign_i64(v.x), rm_sign_i64(v.y),
                    rm_sign_i64(v.z));
}
RM_INLINE i64x4 rm_sign_i64x4(const i64x4 v) {
    return rm_i64x4(rm_sign_i64(v.x), rm_sign_i64(v.y),
                    rm_sign_i64(v.z), rm_sign_i64(v.w));
}
RM_INLINE i64x2 rm_copysign_i64x2(const i64x2 v, const i64x2 s) {
    return rm_i64x2(rm_copysign_i64(v.x, s.x), rm_copysign_i64(v.y, s.y));
}
RM_INLINE i64x3 rm_copysign_i64x3(const i64x3 v, const i64x3 s) {
    return rm_i64x3(rm_copysign_i64(v.x, s.x), rm_copysign_i64(v.y, s.y),
                    rm_copysign_i64(v.z, s.z));
}
RM_INLINE i64x4 rm_copysign_i64x4(const i64x4 v, const i64x4 s) {
    return rm_i64x4(rm_copysign_i64(v.x, s.x), rm_copysign_i64(v.y, s.y),
                    rm_copysign_i64(v.z, s.z), rm_copysign_i64(v.w, s.w));
}
RM_INLINE i64x2 rm_fma_i64x2(const i64x2 a, const i64x2 b, const i64x2 c) {
    return rm_add_i64x2(rm_mul_i64x2(a, b), c);
}
RM_INLINE i64x3 rm_fma_i64x3(const i64x3 a, const i64x3 b, const i64x3 c) {
    return rm_add_i64x3(rm_mul_i64x3(a, b), c);
}
RM_INLINE i64x4 rm_fma_i64x4(const i64x4 a, const i64x4 b, const i64x4 c) {
    return rm_add_i64x4(rm_mul_i64x4(a, b), c);
}
RM_INLINE i64x2 rm_mins_i64x2(const i64x2 v, const i64 s) {
    return rm_min_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x3 rm_mins_i64x3(const i64x3 v, const i64 s) {
    return rm_min_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x4 rm_mins_i64x4(const i64x4 v, const i64 s) {
    return rm_min_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x2 rm_maxs_i64x2(const i64x2 v, const i64 s) {
    return rm_max_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x3 rm_maxs_i64x3(const i64x3 v, const i64 s) {
    return rm_max_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x4 rm_maxs_i64x4(const i64x4 v, const i64 s) {
    return rm_max_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x2 rm_adds_i64x2(const i64x2 v, const i64 s) {
    return rm_add_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x3 rm_adds_i64x3(const i64x3 v, const i64 s) {
    return rm_add_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x4 rm_adds_i64x4(const i64x4 v, const i64 s) {
    return rm_add_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x2 rm_subs_i64x2(const i64x2 v, const i64 s) {
    return rm_sub_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x2 rm_ssub_i64x2(const i64 s, const i64x2 v) {
    return rm_sub_i64x2(rm_i64x2s(s), v);
}
RM_INLINE i64x3 rm_subs_i64x3(const i64x3 v, const i64 s) {
    return rm_sub_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x3 rm_ssub_i64x3(const i64 s, const i64x3 v) {
    return rm_sub_i64x3(rm_i64x3s(s), v);
}
RM_INLINE i64x4 rm_subs_i64x4(const i64x4 v, const i64 s) {
    return rm_sub_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x4 rm_ssub_i64x4(const i64 s, const i64x4 v) {
    return rm_sub_i64x4(rm_i64x4s(s), v);
}
RM_INLINE i64x2 rm_muls_i64x2(const i64x2 v, const i64 s) {
    return rm_mul_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x3 rm_muls_i64x3(const i64x3 v, const i64 s) {
    return rm_mul_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x4 rm_muls_i64x4(const i64x4 v, const i64 s) {
    return rm_mul_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x2 rm_divs_i64x2(const i64x2 v, const i64 s) {
    return rm_div_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x2 rm_sdiv_i64x2(const i64 s, const i64x2 v) {
    return rm_div_i64x2(rm_i64x2s(s), v);
}
RM_INLINE i64x3 rm_divs_i64x3(const i64x3 v, const i64 s) {
    return rm_div_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x3 rm_sdiv_i64x3(const i64 s, const i64x3 v) {
    return rm_div_i64x3(rm_i64x3s(s), v);
}
RM_INLINE i64x4 rm_divs_i64x4(const i64x4 v, const i64 s) {
    return rm_div_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x4 rm_sdiv_i64x4(const i64 s, const i64x4 v) {
    return rm_div_i64x4(rm_i64x4s(s), v);
}
RM_INLINE i64x2 rm_mods_i64x2(const i64x2 v, const i64 s) {
    return rm_mod_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x2 rm_smod_i64x2(const i64 s, const i64x2 v) {
    return rm_mod_i64x2(rm_i64x2s(s), v);
}
RM_INLINE i64x3 rm_mods_i64x3(const i64x3 v, const i64 s) {
    return rm_mod_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x3 rm_smod_i64x3(const i64 s, const i64x3 v) {
    return rm_mod_i64x3(rm_i64x3s(s), v);
}
RM_INLINE i64x4 rm_mods_i64x4(const i64x4 v, const i64 s) {
    return rm_mod_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x4 rm_smod_i64x4(const i64 s, const i64x4 v) {
    return rm_mod_i64x4(rm_i64x4s(s), v);
}
RM_INLINE i64x2 rm_clamps_i64x2(const i64x2 v, i64 min, i64 max) {
    return rm_clamp_i64x2(v, rm_i64x2s(min), rm_i64x2s(max));
}
RM_INLINE i64x2 rm_copysigns_i64x2(const i64x2 v, const i64 s) {
    return rm_copysign_i64x2(v, rm_i64x2s(s));
}
RM_INLINE i64x2 rm_fmas_i64x2(const i64x2 a, const i64x2 b, const i64 c) {
    return rm_adds_i64x2(rm_mul_i64x2(a, b), c);
}
RM_INLINE i64x2 rm_fmass_i64x2(const i64x2 a, const i64 b, const i64 c) {
    return rm_adds_i64x2(rm_muls_i64x2(a, b), c);
}
RM_INLINE i64x3 rm_clamps_i64x3(const i64x3 v, i64 min, i64 max) {
    return rm_clamp_i64x3(v, rm_i64x3s(min), rm_i64x3s(max));
}
RM_INLINE i64x3 rm_copysigns_i64x3(const i64x3 v, const i64 s) {
    return rm_copysign_i64x3(v, rm_i64x3s(s));
}
RM_INLINE i64x3 rm_fmas_i64x3(const i64x3 a, const i64x3 b, const i64 c) {
    return rm_adds_i64x3(rm_mul_i64x3(a, b), c);
}
RM_INLINE i64x3 rm_fmass_i64x3(const i64x3 a, const i64 b, const i64 c) {
    return rm_adds_i64x3(rm_muls_i64x3(a, b), c);
}
RM_INLINE i64x4 rm_clamps_i64x4(const i64x4 v, i64 min, i64 max) {
    return rm_clamp_i64x4(v, rm_i64x4s(min), rm_i64x4s(max));
}
RM_INLINE i64x4 rm_copysigns_i64x4(const i64x4 v, const i64 s) {
    return rm_copysign_i64x4(v, rm_i64x4s(s));
}
RM_INLINE i64x4 rm_fmas_i64x4(const i64x4 a, const i64x4 b, const i64 c) {
    return rm_adds_i64x4(rm_mul_i64x4(a, b), c);
}
RM_INLINE i64x4 rm_fmass_i64x4(const i64x4 a, const i64 b, const i64 c) {
    return rm_adds_i64x4(rm_muls_i64x4(a, b), c);
}
RM_INLINE f32x2 rm_min_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_min_f32(a.x, b.x), rm_min_f32(a.y, b.y));
}
RM_INLINE f32x3 rm_min_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(rm_min_f32(a.x, b.x), rm_min_f32(a.y, b.y),
                    rm_min_f32(a.z, b.z));
}
RM_INLINE f32x4 rm_min_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(rm_min_f32(a.x, b.x), rm_min_f32(a.y, b.y),
                    rm_min_f32(a.z, b.z), rm_min_f32(a.w, b.w));
}
RM_INLINE f32x2 rm_max_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_max_f32(a.x, b.x), rm_max_f32(a.y, b.y));
}
RM_INLINE f32x3 rm_max_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(rm_max_f32(a.x, b.x), rm_max_f32(a.y, b.y),
                    rm_max_f32(a.z, b.z));
}
RM_INLINE f32x4 rm_max_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(rm_max_f32(a.x, b.x), rm_max_f32(a.y, b.y),
                    rm_max_f32(a.z, b.z), rm_max_f32(a.w, b.w));
}
RM_INLINE f32x2 rm_add_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x + b.x, a.y + b.y);
}
RM_INLINE f32x3 rm_add_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE f32x4 rm_add_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE f32x2 rm_sub_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x - b.x, a.y - b.y);
}
RM_INLINE f32x3 rm_sub_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE f32x4 rm_sub_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE f32x2 rm_mul_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x * b.x, a.y * b.y);
}
RM_INLINE f32x3 rm_mul_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE f32x4 rm_mul_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE f32x2 rm_div_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(a.x / b.x, a.y / b.y);
}
RM_INLINE f32x3 rm_div_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE f32x4 rm_div_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE f32x2 rm_mod_f32x2(const f32x2 a, const f32x2 b) {
    return rm_f32x2(rm_mod_f32(a.x, b.x), rm_mod_f32(a.y, b.y));
}
RM_INLINE f32x3 rm_mod_f32x3(const f32x3 a, const f32x3 b) {
    return rm_f32x3(rm_mod_f32(a.x, b.x), rm_mod_f32(a.y, b.y),
                    rm_mod_f32(a.z, b.z));
}
RM_INLINE f32x4 rm_mod_f32x4(const f32x4 a, const f32x4 b) {
    return rm_f32x4(rm_mod_f32(a.x, b.x), rm_mod_f32(a.y, b.y),
                    rm_mod_f32(a.z, b.z), rm_mod_f32(a.w, b.w));
}
RM_INLINE f32x2 rm_clamp_f32x2(const f32x2 v, const f32x2 min, const f32x2 max) {
    return rm_f32x2(rm_clamp_f32(v.x, min.x, max.x), rm_clamp_f32(v.y, min.y, max.y));
}
RM_INLINE f32x3 rm_clamp_f32x3(const f32x3 v, const f32x3 min, const f32x3 max) {
    return rm_f32x3(rm_clamp_f32(v.x, min.x, max.x), rm_clamp_f32(v.y, min.y, max.y),
                    rm_clamp_f32(v.z, min.z, max.z));
}
RM_INLINE f32x4 rm_clamp_f32x4(const f32x4 v, const f32x4 min, const f32x4 max) {
    return rm_f32x4(rm_clamp_f32(v.x, min.x, max.x), rm_clamp_f32(v.y, min.y, max.y),
                    rm_clamp_f32(v.z, min.z, max.z), rm_clamp_f32(v.w, min.w, max.w));
}
RM_INLINE f32x2 rm_sign_f32x2(const f32x2 v) {
    return rm_f32x2(rm_sign_f32(v.x), rm_sign_f32(v.y));
}
RM_INLINE f32x3 rm_sign_f32x3(const f32x3 v) {
    return rm_f32x3(rm_sign_f32(v.x), rm_sign_f32(v.y),
                    rm_sign_f32(v.z));
}
RM_INLINE f32x4 rm_sign_f32x4(const f32x4 v) {
    return rm_f32x4(rm_sign_f32(v.x), rm_sign_f32(v.y),
                    rm_sign_f32(v.z), rm_sign_f32(v.w));
}
RM_INLINE f32x2 rm_copysign_f32x2(const f32x2 v, const f32x2 s) {
    return rm_f32x2(rm_copysign_f32(v.x, s.x), rm_copysign_f32(v.y, s.y));
}
RM_INLINE f32x3 rm_copysign_f32x3(const f32x3 v, const f32x3 s) {
    return rm_f32x3(rm_copysign_f32(v.x, s.x), rm_copysign_f32(v.y, s.y),
                    rm_copysign_f32(v.z, s.z));
}
RM_INLINE f32x4 rm_copysign_f32x4(const f32x4 v, const f32x4 s) {
    return rm_f32x4(rm_copysign_f32(v.x, s.x), rm_copysign_f32(v.y, s.y),
                    rm_copysign_f32(v.z, s.z), rm_copysign_f32(v.w, s.w));
}
RM_INLINE f32x2 rm_fma_f32x2(const f32x2 a, const f32x2 b, const f32x2 c) {
    return rm_add_f32x2(rm_mul_f32x2(a, b), c);
}
RM_INLINE f32x3 rm_fma_f32x3(const f32x3 a, const f32x3 b, const f32x3 c) {
    return rm_add_f32x3(rm_mul_f32x3(a, b), c);
}
RM_INLINE f32x4 rm_fma_f32x4(const f32x4 a, const f32x4 b, const f32x4 c) {
    return rm_add_f32x4(rm_mul_f32x4(a, b), c);
}
RM_INLINE f32x2 rm_mins_f32x2(const f32x2 v, const f32 s) {
    return rm_min_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x3 rm_mins_f32x3(const f32x3 v, const f32 s) {
    return rm_min_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x4 rm_mins_f32x4(const f32x4 v, const f32 s) {
    return rm_min_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x2 rm_maxs_f32x2(const f32x2 v, const f32 s) {
    return rm_max_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x3 rm_maxs_f32x3(const f32x3 v, const f32 s) {
    return rm_max_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x4 rm_maxs_f32x4(const f32x4 v, const f32 s) {
    return rm_max_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x2 rm_adds_f32x2(const f32x2 v, const f32 s) {
    return rm_add_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x3 rm_adds_f32x3(const f32x3 v, const f32 s) {
    return rm_add_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x4 rm_adds_f32x4(const f32x4 v, const f32 s) {
    return rm_add_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x2 rm_subs_f32x2(const f32x2 v, const f32 s) {
    return rm_sub_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2 rm_ssub_f32x2(const f32 s, const f32x2 v) {
    return rm_sub_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x3 rm_subs_f32x3(const f32x3 v, const f32 s) {
    return rm_sub_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x3 rm_ssub_f32x3(const f32 s, const f32x3 v) {
    return rm_sub_f32x3(rm_f32x3s(s), v);
}
RM_INLINE f32x4 rm_subs_f32x4(const f32x4 v, const f32 s) {
    return rm_sub_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x4 rm_ssub_f32x4(const f32 s, const f32x4 v) {
    return rm_sub_f32x4(rm_f32x4s(s), v);
}
RM_INLINE f32x2 rm_muls_f32x2(const f32x2 v, const f32 s) {
    return rm_mul_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x3 rm_muls_f32x3(const f32x3 v, const f32 s) {
    return rm_mul_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x4 rm_muls_f32x4(const f32x4 v, const f32 s) {
    return rm_mul_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x2 rm_divs_f32x2(const f32x2 v, const f32 s) {
    return rm_div_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2 rm_sdiv_f32x2(const f32 s, const f32x2 v) {
    return rm_div_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x3 rm_divs_f32x3(const f32x3 v, const f32 s) {
    return rm_div_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x3 rm_sdiv_f32x3(const f32 s, const f32x3 v) {
    return rm_div_f32x3(rm_f32x3s(s), v);
}
RM_INLINE f32x4 rm_divs_f32x4(const f32x4 v, const f32 s) {
    return rm_div_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x4 rm_sdiv_f32x4(const f32 s, const f32x4 v) {
    return rm_div_f32x4(rm_f32x4s(s), v);
}
RM_INLINE f32x2 rm_mods_f32x2(const f32x2 v, const f32 s) {
    return rm_mod_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2 rm_smod_f32x2(const f32 s, const f32x2 v) {
    return rm_mod_f32x2(rm_f32x2s(s), v);
}
RM_INLINE f32x3 rm_mods_f32x3(const f32x3 v, const f32 s) {
    return rm_mod_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x3 rm_smod_f32x3(const f32 s, const f32x3 v) {
    return rm_mod_f32x3(rm_f32x3s(s), v);
}
RM_INLINE f32x4 rm_mods_f32x4(const f32x4 v, const f32 s) {
    return rm_mod_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x4 rm_smod_f32x4(const f32 s, const f32x4 v) {
    return rm_mod_f32x4(rm_f32x4s(s), v);
}
RM_INLINE f32x2 rm_clamps_f32x2(const f32x2 v, f32 min, f32 max) {
    return rm_clamp_f32x2(v, rm_f32x2s(min), rm_f32x2s(max));
}
RM_INLINE f32x2 rm_copysigns_f32x2(const f32x2 v, const f32 s) {
    return rm_copysign_f32x2(v, rm_f32x2s(s));
}
RM_INLINE f32x2 rm_fmas_f32x2(const f32x2 a, const f32x2 b, const f32 c) {
    return rm_adds_f32x2(rm_mul_f32x2(a, b), c);
}
RM_INLINE f32x2 rm_fmass_f32x2(const f32x2 a, const f32 b, const f32 c) {
    return rm_adds_f32x2(rm_muls_f32x2(a, b), c);
}
RM_INLINE f32x3 rm_clamps_f32x3(const f32x3 v, f32 min, f32 max) {
    return rm_clamp_f32x3(v, rm_f32x3s(min), rm_f32x3s(max));
}
RM_INLINE f32x3 rm_copysigns_f32x3(const f32x3 v, const f32 s) {
    return rm_copysign_f32x3(v, rm_f32x3s(s));
}
RM_INLINE f32x3 rm_fmas_f32x3(const f32x3 a, const f32x3 b, const f32 c) {
    return rm_adds_f32x3(rm_mul_f32x3(a, b), c);
}
RM_INLINE f32x3 rm_fmass_f32x3(const f32x3 a, const f32 b, const f32 c) {
    return rm_adds_f32x3(rm_muls_f32x3(a, b), c);
}
RM_INLINE f32x4 rm_clamps_f32x4(const f32x4 v, f32 min, f32 max) {
    return rm_clamp_f32x4(v, rm_f32x4s(min), rm_f32x4s(max));
}
RM_INLINE f32x4 rm_copysigns_f32x4(const f32x4 v, const f32 s) {
    return rm_copysign_f32x4(v, rm_f32x4s(s));
}
RM_INLINE f32x4 rm_fmas_f32x4(const f32x4 a, const f32x4 b, const f32 c) {
    return rm_adds_f32x4(rm_mul_f32x4(a, b), c);
}
RM_INLINE f32x4 rm_fmass_f32x4(const f32x4 a, const f32 b, const f32 c) {
    return rm_adds_f32x4(rm_muls_f32x4(a, b), c);
}
RM_INLINE f64x2 rm_min_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(rm_min_f64(a.x, b.x), rm_min_f64(a.y, b.y));
}
RM_INLINE f64x3 rm_min_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(rm_min_f64(a.x, b.x), rm_min_f64(a.y, b.y),
                    rm_min_f64(a.z, b.z));
}
RM_INLINE f64x4 rm_min_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(rm_min_f64(a.x, b.x), rm_min_f64(a.y, b.y),
                    rm_min_f64(a.z, b.z), rm_min_f64(a.w, b.w));
}
RM_INLINE f64x2 rm_max_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(rm_max_f64(a.x, b.x), rm_max_f64(a.y, b.y));
}
RM_INLINE f64x3 rm_max_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(rm_max_f64(a.x, b.x), rm_max_f64(a.y, b.y),
                    rm_max_f64(a.z, b.z));
}
RM_INLINE f64x4 rm_max_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(rm_max_f64(a.x, b.x), rm_max_f64(a.y, b.y),
                    rm_max_f64(a.z, b.z), rm_max_f64(a.w, b.w));
}
RM_INLINE f64x2 rm_add_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(a.x + b.x, a.y + b.y);
}
RM_INLINE f64x3 rm_add_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(a.x + b.x, a.y + b.y, a.z + b.z);
}
RM_INLINE f64x4 rm_add_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
RM_INLINE f64x2 rm_sub_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(a.x - b.x, a.y - b.y);
}
RM_INLINE f64x3 rm_sub_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(a.x - b.x, a.y - b.y, a.z - b.z);
}
RM_INLINE f64x4 rm_sub_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
RM_INLINE f64x2 rm_mul_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(a.x * b.x, a.y * b.y);
}
RM_INLINE f64x3 rm_mul_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(a.x * b.x, a.y * b.y, a.z * b.z);
}
RM_INLINE f64x4 rm_mul_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}
RM_INLINE f64x2 rm_div_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(a.x / b.x, a.y / b.y);
}
RM_INLINE f64x3 rm_div_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(a.x / b.x, a.y / b.y, a.z / b.z);
}
RM_INLINE f64x4 rm_div_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}
RM_INLINE f64x2 rm_mod_f64x2(const f64x2 a, const f64x2 b) {
    return rm_f64x2(rm_mod_f64(a.x, b.x), rm_mod_f64(a.y, b.y));
}
RM_INLINE f64x3 rm_mod_f64x3(const f64x3 a, const f64x3 b) {
    return rm_f64x3(rm_mod_f64(a.x, b.x), rm_mod_f64(a.y, b.y),
                    rm_mod_f64(a.z, b.z));
}
RM_INLINE f64x4 rm_mod_f64x4(const f64x4 a, const f64x4 b) {
    return rm_f64x4(rm_mod_f64(a.x, b.x), rm_mod_f64(a.y, b.y),
                    rm_mod_f64(a.z, b.z), rm_mod_f64(a.w, b.w));
}
RM_INLINE f64x2 rm_clamp_f64x2(const f64x2 v, const f64x2 min, const f64x2 max) {
    return rm_f64x2(rm_clamp_f64(v.x, min.x, max.x), rm_clamp_f64(v.y, min.y, max.y));
}
RM_INLINE f64x3 rm_clamp_f64x3(const f64x3 v, const f64x3 min, const f64x3 max) {
    return rm_f64x3(rm_clamp_f64(v.x, min.x, max.x), rm_clamp_f64(v.y, min.y, max.y),
                    rm_clamp_f64(v.z, min.z, max.z));
}
RM_INLINE f64x4 rm_clamp_f64x4(const f64x4 v, const f64x4 min, const f64x4 max) {
    return rm_f64x4(rm_clamp_f64(v.x, min.x, max.x), rm_clamp_f64(v.y, min.y, max.y),
                    rm_clamp_f64(v.z, min.z, max.z), rm_clamp_f64(v.w, min.w, max.w));
}
RM_INLINE f64x2 rm_sign_f64x2(const f64x2 v) {
    return rm_f64x2(rm_sign_f64(v.x), rm_sign_f64(v.y));
}
RM_INLINE f64x3 rm_sign_f64x3(const f64x3 v) {
    return rm_f64x3(rm_sign_f64(v.x), rm_sign_f64(v.y),
                    rm_sign_f64(v.z));
}
RM_INLINE f64x4 rm_sign_f64x4(const f64x4 v) {
    return rm_f64x4(rm_sign_f64(v.x), rm_sign_f64(v.y),
                    rm_sign_f64(v.z), rm_sign_f64(v.w));
}
RM_INLINE f64x2 rm_copysign_f64x2(const f64x2 v, const f64x2 s) {
    return rm_f64x2(rm_copysign_f64(v.x, s.x), rm_copysign_f64(v.y, s.y));
}
RM_INLINE f64x3 rm_copysign_f64x3(const f64x3 v, const f64x3 s) {
    return rm_f64x3(rm_copysign_f64(v.x, s.x), rm_copysign_f64(v.y, s.y),
                    rm_copysign_f64(v.z, s.z));
}
RM_INLINE f64x4 rm_copysign_f64x4(const f64x4 v, const f64x4 s) {
    return rm_f64x4(rm_copysign_f64(v.x, s.x), rm_copysign_f64(v.y, s.y),
                    rm_copysign_f64(v.z, s.z), rm_copysign_f64(v.w, s.w));
}
RM_INLINE f64x2 rm_fma_f64x2(const f64x2 a, const f64x2 b, const f64x2 c) {
    return rm_add_f64x2(rm_mul_f64x2(a, b), c);
}
RM_INLINE f64x3 rm_fma_f64x3(const f64x3 a, const f64x3 b, const f64x3 c) {
    return rm_add_f64x3(rm_mul_f64x3(a, b), c);
}
RM_INLINE f64x4 rm_fma_f64x4(const f64x4 a, const f64x4 b, const f64x4 c) {
    return rm_add_f64x4(rm_mul_f64x4(a, b), c);
}
RM_INLINE f64x2 rm_mins_f64x2(const f64x2 v, const f64 s) {
    return rm_min_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x3 rm_mins_f64x3(const f64x3 v, const f64 s) {
    return rm_min_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x4 rm_mins_f64x4(const f64x4 v, const f64 s) {
    return rm_min_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x2 rm_maxs_f64x2(const f64x2 v, const f64 s) {
    return rm_max_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x3 rm_maxs_f64x3(const f64x3 v, const f64 s) {
    return rm_max_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x4 rm_maxs_f64x4(const f64x4 v, const f64 s) {
    return rm_max_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x2 rm_adds_f64x2(const f64x2 v, const f64 s) {
    return rm_add_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x3 rm_adds_f64x3(const f64x3 v, const f64 s) {
    return rm_add_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x4 rm_adds_f64x4(const f64x4 v, const f64 s) {
    return rm_add_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x2 rm_subs_f64x2(const f64x2 v, const f64 s) {
    return rm_sub_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x2 rm_ssub_f64x2(const f64 s, const f64x2 v) {
    return rm_sub_f64x2(rm_f64x2s(s), v);
}
RM_INLINE f64x3 rm_subs_f64x3(const f64x3 v, const f64 s) {
    return rm_sub_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x3 rm_ssub_f64x3(const f64 s, const f64x3 v) {
    return rm_sub_f64x3(rm_f64x3s(s), v);
}
RM_INLINE f64x4 rm_subs_f64x4(const f64x4 v, const f64 s) {
    return rm_sub_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x4 rm_ssub_f64x4(const f64 s, const f64x4 v) {
    return rm_sub_f64x4(rm_f64x4s(s), v);
}
RM_INLINE f64x2 rm_muls_f64x2(const f64x2 v, const f64 s) {
    return rm_mul_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x3 rm_muls_f64x3(const f64x3 v, const f64 s) {
    return rm_mul_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x4 rm_muls_f64x4(const f64x4 v, const f64 s) {
    return rm_mul_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x2 rm_divs_f64x2(const f64x2 v, const f64 s) {
    return rm_div_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x2 rm_sdiv_f64x2(const f64 s, const f64x2 v) {
    return rm_div_f64x2(rm_f64x2s(s), v);
}
RM_INLINE f64x3 rm_divs_f64x3(const f64x3 v, const f64 s) {
    return rm_div_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x3 rm_sdiv_f64x3(const f64 s, const f64x3 v) {
    return rm_div_f64x3(rm_f64x3s(s), v);
}
RM_INLINE f64x4 rm_divs_f64x4(const f64x4 v, const f64 s) {
    return rm_div_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x4 rm_sdiv_f64x4(const f64 s, const f64x4 v) {
    return rm_div_f64x4(rm_f64x4s(s), v);
}
RM_INLINE f64x2 rm_mods_f64x2(const f64x2 v, const f64 s) {
    return rm_mod_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x2 rm_smod_f64x2(const f64 s, const f64x2 v) {
    return rm_mod_f64x2(rm_f64x2s(s), v);
}
RM_INLINE f64x3 rm_mods_f64x3(const f64x3 v, const f64 s) {
    return rm_mod_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x3 rm_smod_f64x3(const f64 s, const f64x3 v) {
    return rm_mod_f64x3(rm_f64x3s(s), v);
}
RM_INLINE f64x4 rm_mods_f64x4(const f64x4 v, const f64 s) {
    return rm_mod_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x4 rm_smod_f64x4(const f64 s, const f64x4 v) {
    return rm_mod_f64x4(rm_f64x4s(s), v);
}
RM_INLINE f64x2 rm_clamps_f64x2(const f64x2 v, f64 min, f64 max) {
    return rm_clamp_f64x2(v, rm_f64x2s(min), rm_f64x2s(max));
}
RM_INLINE f64x2 rm_copysigns_f64x2(const f64x2 v, const f64 s) {
    return rm_copysign_f64x2(v, rm_f64x2s(s));
}
RM_INLINE f64x2 rm_fmas_f64x2(const f64x2 a, const f64x2 b, const f64 c) {
    return rm_adds_f64x2(rm_mul_f64x2(a, b), c);
}
RM_INLINE f64x2 rm_fmass_f64x2(const f64x2 a, const f64 b, const f64 c) {
    return rm_adds_f64x2(rm_muls_f64x2(a, b), c);
}
RM_INLINE f64x3 rm_clamps_f64x3(const f64x3 v, f64 min, f64 max) {
    return rm_clamp_f64x3(v, rm_f64x3s(min), rm_f64x3s(max));
}
RM_INLINE f64x3 rm_copysigns_f64x3(const f64x3 v, const f64 s) {
    return rm_copysign_f64x3(v, rm_f64x3s(s));
}
RM_INLINE f64x3 rm_fmas_f64x3(const f64x3 a, const f64x3 b, const f64 c) {
    return rm_adds_f64x3(rm_mul_f64x3(a, b), c);
}
RM_INLINE f64x3 rm_fmass_f64x3(const f64x3 a, const f64 b, const f64 c) {
    return rm_adds_f64x3(rm_muls_f64x3(a, b), c);
}
RM_INLINE f64x4 rm_clamps_f64x4(const f64x4 v, f64 min, f64 max) {
    return rm_clamp_f64x4(v, rm_f64x4s(min), rm_f64x4s(max));
}
RM_INLINE f64x4 rm_copysigns_f64x4(const f64x4 v, const f64 s) {
    return rm_copysign_f64x4(v, rm_f64x4s(s));
}
RM_INLINE f64x4 rm_fmas_f64x4(const f64x4 a, const f64x4 b, const f64 c) {
    return rm_adds_f64x4(rm_mul_f64x4(a, b), c);
}
RM_INLINE f64x4 rm_fmass_f64x4(const f64x4 a, const f64 b, const f64 c) {
    return rm_adds_f64x4(rm_muls_f64x4(a, b), c);
}
RM_INLINE f32x2 rm_floor_f32x2(const f32x2 v) {
    return rm_f32x2(rm_floor_f32(v.x), rm_floor_f32(v.y));
}
RM_INLINE f32x3 rm_floor_f32x3(const f32x3 v) {
    return rm_f32x3(rm_floor_f32(v.x), rm_floor_f32(v.y),
                    rm_floor_f32(v.z));
}
RM_INLINE f32x4 rm_floor_f32x4(const f32x4 v) {
    return rm_f32x4(rm_floor_f32(v.x), rm_floor_f32(v.y),
                    rm_floor_f32(v.z), rm_floor_f32(v.w));
}
RM_INLINE f32x2 rm_ceil_f32x2(const f32x2 v) {
    return rm_f32x2(rm_ceil_f32(v.x), rm_ceil_f32(v.y));
}
RM_INLINE f32x3 rm_ceil_f32x3(const f32x3 v) {
    return rm_f32x3(rm_ceil_f32(v.x), rm_ceil_f32(v.y),
                    rm_ceil_f32(v.z));
}
RM_INLINE f32x4 rm_ceil_f32x4(const f32x4 v) {
    return rm_f32x4(rm_ceil_f32(v.x), rm_ceil_f32(v.y),
                    rm_ceil_f32(v.z), rm_ceil_f32(v.w));
}
RM_INLINE f32x2 rm_round_f32x2(const f32x2 v) {
    return rm_f32x2(rm_round_f32(v.x), rm_round_f32(v.y));
}
RM_INLINE f32x3 rm_round_f32x3(const f32x3 v) {
    return rm_f32x3(rm_round_f32(v.x), rm_round_f32(v.y),
                    rm_round_f32(v.z));
}
RM_INLINE f32x4 rm_round_f32x4(const f32x4 v) {
    return rm_f32x4(rm_round_f32(v.x), rm_round_f32(v.y),
                    rm_round_f32(v.z), rm_round_f32(v.w));
}
RM_INLINE f32x2 rm_trunc_f32x2(const f32x2 v) {
    return rm_f32x2(rm_trunc_f32(v.x), rm_trunc_f32(v.y));
}
RM_INLINE f32x3 rm_trunc_f32x3(const f32x3 v) {
    return rm_f32x3(rm_trunc_f32(v.x), rm_trunc_f32(v.y),
                    rm_trunc_f32(v.z));
}
RM_INLINE f32x4 rm_trunc_f32x4(const f32x4 v) {
    return rm_f32x4(rm_trunc_f32(v.x), rm_trunc_f32(v.y),
                    rm_trunc_f32(v.z), rm_trunc_f32(v.w));
}
RM_INLINE f32x2 rm_fract_f32x2(const f32x2 v) {
    return rm_f32x2(rm_fract_f32(v.x), rm_fract_f32(v.y));
}
RM_INLINE f32x3 rm_fract_f32x3(const f32x3 v) {
    return rm_f32x3(rm_fract_f32(v.x), rm_fract_f32(v.y),
                    rm_fract_f32(v.z));
}
RM_INLINE f32x4 rm_fract_f32x4(const f32x4 v) {
    return rm_f32x4(rm_fract_f32(v.x), rm_fract_f32(v.y),
                    rm_fract_f32(v.z), rm_fract_f32(v.w));
}
RM_INLINE f64x2 rm_floor_f64x2(const f64x2 v) {
    return rm_f64x2(rm_floor_f64(v.x), rm_floor_f64(v.y));
}
RM_INLINE f64x3 rm_floor_f64x3(const f64x3 v) {
    return rm_f64x3(rm_floor_f64(v.x), rm_floor_f64(v.y),
                    rm_floor_f64(v.z));
}
RM_INLINE f64x4 rm_floor_f64x4(const f64x4 v) {
    return rm_f64x4(rm_floor_f64(v.x), rm_floor_f64(v.y),
                    rm_floor_f64(v.z), rm_floor_f64(v.w));
}
RM_INLINE f64x2 rm_ceil_f64x2(const f64x2 v) {
    return rm_f64x2(rm_ceil_f64(v.x), rm_ceil_f64(v.y));
}
RM_INLINE f64x3 rm_ceil_f64x3(const f64x3 v) {
    return rm_f64x3(rm_ceil_f64(v.x), rm_ceil_f64(v.y),
                    rm_ceil_f64(v.z));
}
RM_INLINE f64x4 rm_ceil_f64x4(const f64x4 v) {
    return rm_f64x4(rm_ceil_f64(v.x), rm_ceil_f64(v.y),
                    rm_ceil_f64(v.z), rm_ceil_f64(v.w));
}
RM_INLINE f64x2 rm_round_f64x2(const f64x2 v) {
    return rm_f64x2(rm_round_f64(v.x), rm_round_f64(v.y));
}
RM_INLINE f64x3 rm_round_f64x3(const f64x3 v) {
    return rm_f64x3(rm_round_f64(v.x), rm_round_f64(v.y),
                    rm_round_f64(v.z));
}
RM_INLINE f64x4 rm_round_f64x4(const f64x4 v) {
    return rm_f64x4(rm_round_f64(v.x), rm_round_f64(v.y),
                    rm_round_f64(v.z), rm_round_f64(v.w));
}
RM_INLINE f64x2 rm_trunc_f64x2(const f64x2 v) {
    return rm_f64x2(rm_trunc_f64(v.x), rm_trunc_f64(v.y));
}
RM_INLINE f64x3 rm_trunc_f64x3(const f64x3 v) {
    return rm_f64x3(rm_trunc_f64(v.x), rm_trunc_f64(v.y),
                    rm_trunc_f64(v.z));
}
RM_INLINE f64x4 rm_trunc_f64x4(const f64x4 v) {
    return rm_f64x4(rm_trunc_f64(v.x), rm_trunc_f64(v.y),
                    rm_trunc_f64(v.z), rm_trunc_f64(v.w));
}
RM_INLINE f64x2 rm_fract_f64x2(const f64x2 v) {
    return rm_f64x2(rm_fract_f64(v.x), rm_fract_f64(v.y));
}
RM_INLINE f64x3 rm_fract_f64x3(const f64x3 v) {
    return rm_f64x3(rm_fract_f64(v.x), rm_fract_f64(v.y),
                    rm_fract_f64(v.z));
}
RM_INLINE f64x4 rm_fract_f64x4(const f64x4 v) {
    return rm_f64x4(rm_fract_f64(v.x), rm_fract_f64(v.y),
                    rm_fract_f64(v.z), rm_fract_f64(v.w));
}
#endif /* RANMATH_H */
