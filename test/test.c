#include <stdio.h>

#include "../ranmath.h"

void print_vec4(f32x4 v){
    printf("<x: %f, y: %f, z: %f, w: %f>\n", v.x, v.y, v.z, v.w);
}

int main(void){
    f32x4 v1 = rm_f32x4(1,2,3,4);
    f32x4 v2 = rm_f32x4(1,1,1,1);

    printf("%f\n", rm_dot_f32x4(v1, v2));
}
