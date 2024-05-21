#ifndef _RANMATH_TYPES_H_
#define _RANMATH_TYPES_H_ 1

#if !defined(RM_NO_INLINE)
#if defined(_MSC_VER)
#define RM_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define RM_INLINE static inline __attribute((always_inline))
#else
#define RM_INLINE static inline
#endif
#else
#define RM_INLINE
#endif

#if defined(__GNUC__) || defined(__clang__)
#define RM_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#define RM_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#else
#define RM_UNLIKELY(expr) (expr)
#define RM_LIKELY(expr)   (expr)
#endif

#define RM_PLATFORM_LINUX   0x1
#define RM_PLATFORM_WINDOWS 0x2

#if defined(__linux__)
#define RM_PLATFORM RM_PLATFORM_LINUX
#elif defined(_MSC_VER)
#define RM_PLATFORM             RM_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN     1
#define _CRT_SECURE_NO_WARNINGS 1
#define NOMINMAX                1
#else
#error unsupported platform
#endif /* CHECK PLATFORM */

#define RM_ARCH_X86 (1 << 0)
/* 32-bit arm and 64-bit arm, RM_ARCH_ARM is for either */
#define RM_ARCH_AARCH32 (1 << 0)
#define RM_ARCH_AARCH64 (1 << 1)
#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__) ||            \
    defined(_M_AMD64) || defined(__i386__) || defined(_M_IX86)
#define RM_ARCH RM_ARCH_X86
#elif defined(__aarch64__) || defined(_M_ARM64)
#define RM_ARCH_ARM RM_ARCH_AARCH64 | RM_ARCH_AARCH32
#define RM_ARCH     RM_ARCH_ARM
#elif defined(__arm__) || defined(_M_ARM)
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
/*
 * since windows only defines the AVX and AVX2 macros we fallthrough
 * so that everything will be enabled
 */
#if defined(__AVX2__)
#if !defined(RM_AVX2)
#define RM_AVX2 1
#endif
#endif /* AVX2 INTRINSICS */

#if defined(__AVX__) || defined(RM_AVX2)
#if !defined(RM_AVX)
#define RM_AVX 1
#endif
#endif /* AVX INTRINSICS */

#if defined(__SSE4_2__) || defined(RM_AVX)
#if !defined(RM_SSE4_2)
#define RM_SSE4_2 1
#endif
#endif /* SSE4.2 INTRINSICS */

#if defined(__SSE4_1__) || defined(RM_SSE4_2)
#if !defined(RM_SSE4_1)
#define RM_SSE4_1 1
#endif
#endif /* SSE4.1 INTRINSICS */

#if defined(__SSSE3__) || defined(RM_SSE4_1)
#if !defined(RM_SSSE3)
#define RM_SSSE3 1
#endif
#endif /* SSSE3 INTRINSICS */

#if defined(__SSE3__) || defined(RM_SSSE3)
#if !defined(RM_SSE3)
#define RM_SSE3 1
#endif
#endif /* SSE3 INTRINSICS */

#if defined(__SSE2__) || (defined(_M_IX86_FP) && _M_IX86_FP == 2) ||           \
    defined(RM_SSE3)
#if !defined(RM_SSE2)
#define RM_SSE2 1
#endif
#endif /* SSE2 INTRINSICS */

#if defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP == 1) ||            \
    defined(RM_SSE2)
#if !defined(RM_SSE)
#define RM_SSE 1
#endif
#endif /* SSE1 INTRINSICS */
#endif /* X86 SIMD INTRINSICS */

#if RM_ARCH == RM_ARCH_ARM
#if (defined(__ARM_NEON__) || defined(__ARM_NEON)) &&                          \
    (defined(__ARM_NEON_FP__) || defined(__ARM_NEON_FP))
#if !defined(RM_NEON)
#define RM_NEON 1
#endif
#endif /* NEON INTRINSICS */
#endif /* ARM SIMD INTRINSICS */
#endif /* NO INTRINSICS */

#if !defined(RM_UNALIGNED)
#if defined(_MSC_VER)
/* do not use alignment for older visual studio versions */
#if _MSC_VER < 1913 /*  Visual Studio 2017 version 15.6  */
#define RM_UNALIGNED 1
#define RM_ALIGN(_X) /* no alignment */
#else
#define RM_ALIGN(_X) __declspec(align((_X)))
#endif
#else
#define RM_ALIGN(_X) __attribute((aligned((_X))))
#endif
#endif

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
// #include <x86intrin.h>
#endif /* X86 INTRINSICS */

#if RM_ARCH == RM_ARCH_ARM
#if defined(RM_NEON)
#include <arm_neon.h>
#endif
#endif /* ARM INTRINSICS */
#endif /* NO INTRINSICS */

typedef RM_ALIGN(1) uint8_t u8;
typedef RM_ALIGN(2) uint16_t u16;
typedef RM_ALIGN(4) uint32_t u32;
typedef RM_ALIGN(8) uint64_t u64;
typedef RM_ALIGN(1) int8_t i8;
typedef RM_ALIGN(2) int16_t i16;
typedef RM_ALIGN(4) int32_t i32;
typedef RM_ALIGN(8) int64_t i64;
typedef RM_ALIGN(4) float f32;
typedef RM_ALIGN(8) double f64;

typedef struct f32_cvt_t f32_cvt;
typedef struct f64_cvt_t f64_cvt;

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
        struct {
            u32 umsw, ulsw;
        };
        struct {
            i32 imsw, ilsw;
        };
#elif RM_BYTE_ORDER == RM_BYTE_ORDER_LITTLE_ENDIAN
        struct {
            u32 ulsw, umsw;
        };
        struct {
            i32 ilsw, imsw;
        };
#endif /* RM_BYTE_ORDER */
    };
};

#define f32_as_u32(_x)       (((f32_cvt) {.f = (_x)}).u)
#define f64_as_u64(_x)       (((f64_cvt) {.f = (_x)}).u)
#define u32_as_f32(_x)       (((f32_cvt) {.u = (_x)}).f)
#define u64_as_f64(_x)       (((f64_cvt) {.u = (_x)}).f)
#define u32_as_f64(_x0, _x1) (((f64_cvt) {.u0 = (_x0), .u1 = (_x1)}).f)

#define rm_splat2(_v) (_v).x, (_v).y
#define rm_splat3(_v) (_v).x, (_v).y, (_v).z
#define rm_splat4(_v) (_v).x, (_v).y, (_v).z, (_v).w

#define RM_E_F64        0x1.5bf0a8b145769p+1
#define RM_LOG2E_F64    0x1.71547652b82fep+0
#define RM_LOG10E_F64   0x1.bcb7b1526e50ep-2
#define RM_LN2_F64      0x1.62e42fefa39efp-1
#define RM_LN10_F64     0x1.26bb1bbb55516p+1
#define RM_PI_F64       0x1.921fb54442d18p+1
#define RM_2PI_F64      0x1.921fb54442d18p+2
#define RM_PI_2_F64     0x1.921fb54442d18p+0
#define RM_PI_4_F64     0x1.921fb54442d18p-1
#define RM_1_PI_F64     0x1.45f306dc9c883p-2
#define RM_2_PI_F64     0x1.45f306dc9c883p-1
#define RM_PISQ_F64     0x1.3bd3cc9be45dep+3
#define RM_SQRTPI_F64   0x1.c5bf891b4ef6ap+0
#define RM_1_SQRTPI_F64 0x1.20dd750429b6dp-1
#define RM_2_SQRTPI_F64 0x1.20dd750429b6dp+0
#define RM_SQRT2_F64    0x1.6a09e667f3bcdp+0
#define RM_1_SQRT2_F64  0x1.6a09e667f3bcdp-1
#define RM_DEG2RAD_F64  0x1.1df46a2529d39p-6
#define RM_RAD2DEG_F64  0x1.ca5dc1a63c1f8p+5

#define RM_E_F32        ((f32)RM_E_F64)
#define RM_LOG2E_F32    ((f32)RM_LOG2E_F64)
#define RM_LOG10E_F32   ((f32)RM_LOG10E_F64)
#define RM_LN2_F32      ((f32)RM_LN2_F64)
#define RM_LN10_F32     ((f32)RM_LN10_F64)
#define RM_PI_F32       ((f32)RM_PI_F64)
#define RM_PISQ_F32     ((f32)RM_PISQ_F64)
#define RM_SQRTPI_F32   ((f32)RM_SQRTPI_F64)
#define RM_1_SQRTPI_F32 ((f32)RM_1_SQRTPI_F64)
#define RM_2_SQRTPI_F32 ((f32)RM_2_SQRTPI_F64)
#define RM_2PI_F32      ((f32)RM_2PI_F64)
#define RM_PI_2_F32     ((f32)RM_PI_2_F64)
#define RM_PI_4_F32     ((f32)RM_PI_4_F64)
#define RM_1_PI_F32     ((f32)RM_1_PI_F64)
#define RM_2_PI_F32     ((f32)RM_2_PI_F64)
#define RM_SQRT2_F32    ((f32)RM_SQRT2_F64)
#define RM_1_SQRT2_F32  ((f32)RM_1_SQRT2_F64)
#define RM_DEG2RAD_F32  ((f32)RM_DEG2RAD_F64)
#define RM_RAD2DEG_F32  ((f32)RM_RAD2DEG_F64)

#endif /* _RANMATH_TYPES_H_ */
