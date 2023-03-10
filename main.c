#include <stdio.h>
#include <math.h>
#include <float.h>

#define RANMATH_IMPLEMENTATION
#include "ranmath.h"

void printv4(const vec4 v) {
    printf("%F, %F, %F, %F\n", v.x, v.y, v.z, v.w);
}

void printm4(const mat4 m) {
    printv4(m.cols[0]);
    printv4(m.cols[1]);
    printv4(m.cols[2]);
    printv4(m.cols[3]);
}


int main(void) {
    mat4 test1, test2;

    test1 = rm_mat4_inv(rm_mat4_identity());
    test2 = rm_mat4_identity();

    printm4(test1);
    printf("\n");
    printm4(test2);

    __m128 test, x0, x1;

    x0 = rmm_set(1, 2, 3, 4);
    x1 = rmm_set(5, 6, 7, 8);

    test = rmm_shuffle2(x0, x1, 2, 0, 2, 0);

    vec4 v;

    v = (vec4){test[0], test[1], test[2], test[3]};

    printf("\n");
    printv4(v);

    printf("\n");
    printf("%.32f\n", rm_sqrtf(0));
    printf("%.32f\n", rm_rsqrtf(0));
    printf("%.32f\n", rm_sqrtd(0));
    printf("%.32f\n", rm_rsqrtd(0));

    return 0;
}
