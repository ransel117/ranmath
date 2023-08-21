#if !defined(RM_NO_INTRINSICS)
#if RM_ARCH == RM_ARCH_X86
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
#include <arm_neon.h>
#endif /* ARM INTRINSICS */
#endif /* NO INTRINSICS */
