#include <stdio.h>

#include "../ranmath.h"

void
print_vec4(f32x4 v) {
    printf("<x: %f, y: %f, z: %f, w: %f>\n", v.x, v.y, v.z, v.w);
}

void print_vec4i(boolx4 v) {
    printf("<x: %i, y: %i, z: %i, w: %i>\n", v.x, v.y, v.z, v.w);
}

int
main(void) {
    printf("bool: %zu\n", sizeof(bool));
    printf("u8:   %zu\n", sizeof(u8));
    printf("u16:  %zu\n", sizeof(u16));
    printf("u32:  %zu\n", sizeof(u32));
    printf("u64:  %zu\n", sizeof(u64));
    printf("i8:   %zu\n", sizeof(i8));
    printf("i16:  %zu\n", sizeof(i16));
    printf("i32:  %zu\n", sizeof(i32));
    printf("i64:  %zu\n", sizeof(i64));
    printf("f32:  %zu\n", sizeof(f32));
    printf("f64:  %zu\n", sizeof(f64));

    f32x4 v1 = rm_f32x4(1, 2, 3, 4);
    f32x4 v2 = rm_f32x4(1, 1, 1, 1);

    printf("%f\n", rm_dot_f32x4(v1, v2));

    i32x4 test;
    _mm_store_si128((__m128i*)test.raw, _mm_and_si128(_mm_castps_si128(_mm_cmple_ps(rmm_load(v1.raw), rmm_load(v2.raw))),_mm_set1_epi32(1)));

    boolx4 test2;

    test2 = (boolx4){
        .x = test.x,
        .y = test.y,
        .z = test.z,
        .w = test.w
    };
    print_vec4i(test2);
}
