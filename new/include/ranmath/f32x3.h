#ifndef _RANMATH_F32X3_H_
#define _RANMATH_F32X3_H_

#include "types.h"
#include "f32x2.h"

typedef struct f32x3_t f32x3;

struct f32x3_t {
    union {
        struct {
            f32 x, y, z;
        };
        struct {
            f32 r, g, b;
        };
        struct {
            f32x2 xy;
            f32 _0;
        };
        struct {
            f32 _1;
            f32x2 yz;
        };
        struct {
            f32x2 rg;
            f32 _2;
        };
        struct {
            f32 _3;
            f32x2 gb;
        };

        f32 raw[3];
    };
};

#define rm_f32x3(_x, _y, _z) ((f32x3) {.x = (_x), .y = (_y), .z = (_z)})
#define rm_f32x3s(_s)        ((f32x3) {.x = (_s), .y = (_s), .z = (_s)})
#define rm_f32x3sv2(_x, _v)  ((f32x3) {.x = (_x), .y = (_v).x, .z = (_v).y})
#define rm_f32x3v2s(_v, _z)  ((f32x3) {.x = (_v).x, .y = (_v).y, .z = (_z)})

#endif /* _RANMATH_F32X3_H_ */
