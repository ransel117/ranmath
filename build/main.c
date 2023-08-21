#include "ranmath.h"
#include <stdio.h>

void printi8x2(char* msg, i8x2 v) {
    printf("%s %d, %d\n", msg, v.x, v.y);
}

i32 main(void) {
    i8x2 test;

    test = rm_i8x2(1, -2);
    printf("%d\n", rm_any_i8x2(test));
    printf("%d\n", rm_all_i8x2(test));
    printi8x2("test: ", test);
    i8x2 test2 = rm_neg_i8x2(test);
    printi8x2("test2:", test2);
    printi8x2("test: ", test);
    rm_neg_i8x2(test);
    printi8x2("test: ", test);

    printf("%d\n", RM_BYTE_ORDER);

    return 0;
}
