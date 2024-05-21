#ifndef _RANMATH_UTIL_H_
#define _RANMATH_UTIL_H_

#include "types.h"

#define RM_ABS(_x)                 (((_x) < 0) ? -(_x) : (_x))
#define RM_MIN(_a, _b)             (((_a) < (_b)) ? (_a) : (_b))
#define RM_MAX(_a, _b)             (((_a) > (_b)) ? (_a) : (_b))
#define RM_POW2(_x)                ((_x) * (_x))
#define RM_CLAMP(_val, _min, _max) (RM_MIN(RM_MAX((_val), (_min)), (_max)))
#define RM_SIGN(_x)                (((_x) > 0) - ((_x) < 0))

#endif /* _RANMATH_UTIL_H_ */
