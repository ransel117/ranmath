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
#if defined(__x86_64__)    || defined(_M_X64)      ||   \
    defined(__amd64__)     || defined(_M_AMD64)    ||   \
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

/* get the supported SIMD instruction sets for target CPU */
#if !defined(RM_NO_INTRINSICS)
#if RM_ARCH == RM_ARCH_X86
/* since windows only defines the AVX and AVX2 macros we fallthrough so that everything will be enabled */
#if defined(__AVX2__)
#if !defined(RM_AVX2)
#define RM_AVX2
#endif
#endif /* AVX2 INTRINSICS */

#if defined(__AVX__) || defined(RM_AVX2)
#if !defined(RM_AVX)
#define RM_AVX
#endif
#endif /* AVX INTRINSICS */

#if defined(__SSE4_2__) || defined(RM_AVX)
#if !defined(RM_SSE4_2)
#define RM_SSE4_2
#endif
#endif /* SSE4.2 INTRINSICS */

#if defined(__SSE4_1__) || defined(RM_SSE4_2)
#if !defined(RM_SSE4_1)
#define RM_SSE4_1
#endif
#endif /* SSE4.1 INTRINSICS */

#if defined(__SSSE3__) || defined(RM_SSE4_1)
#if !defined(RM_SSSE3)
#define RM_SSSE3
#endif
#endif /* SSSE3 INTRINSICS */

#if defined(__SSE3__) || defined(RM_SSSE3)
#if !defined(RM_SSE3)
#define RM_SSE3
#endif
#endif /* SSE3 INTRINSICS */

#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP == 2) ||    \
    defined(RM_SSE3)
#if !defined(RM_SSE2)
#define RM_SSE2
#endif
#endif /* SSE2 INTRINSICS */

#if defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP == 1) || \
    defined(RM_SSE2)
#if !defined(RM_SSE)
#define RM_SSE
#endif
#endif /* SSE1 INTRINSICS */
#endif /* X86 SIMD INTRINSICS */

#if RM_ARCH == RM_ARCH_ARM
#if (defined(__ARM_NEON__) || defined(__ARM_NEON)) &&       \
    (defined(__ARM_NEON_FP__) || defined(__ARM_NEON_FP))
#if !defined(RM_NEON)
#define RM_NEON
#endif
#endif /* NEON INTRINSICS */
#endif /* ARM SIMD INTRINSICS */
#endif /* NO INTRINSICS */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* TEMPORARY, WILL STAY UNTIL EVERYTHING ELSE IS IMPLEMENTED */
#include <math.h>

/* include the highest available version */
#if !defined(RM_NO_INTRINSICS)
#if RM_ARCH == RM_ARCH_X86
#if defined(RM_AVX2) || defined(RM_AVX)
#include <immintrin.h>
#elif defined(RM_SSE4_2)
#include <nmmintrin.h>
#elif defined(RM_SSE4_1)
#include <smmintrin.h>
#elif defined(RM_SSSE3)
#include <tmmintrin.h>
#elif defined(RM_SSE3)
#include <pmmintrin.h>
#elif defined(RM_SSE2)
#include <emmintrin.h>
#elif defined(RM_SSE)
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

#define f32_as_u32(_x)            (((f32_cvt){.f = (_x)}).u)
#define f64_as_u64(_x)            (((f64_cvt){.f = (_x)}).u)
#define u32_as_f32(_x)            (((f32_cvt){.u = (_x)}).f)
#define u64_as_f64(_x)            (((f64_cvt){.u = (_x)}).f)
#define u32_as_f64(_x0, _x1)      (((f64_cvt){.u0 = (_x0), .u1 = (_x1)}).f)
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
