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
