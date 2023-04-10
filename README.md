# ranmath
Math library by me. 

Will not be the most precise thing in the world but aiming to be within a reasonable amount of libc.

Aiming to be a single header stb-style library.

## How to use
Include ranmath.h in your project;
```C
#include "ranmath.h"
#include "ranmath/ranmath.h"
#include <ranmath.h>
#include <ranmath/ranmath.h>
```
using one of the above.

For all functions to be declared put;
```C
#define RANMATH_IMPLEMENTATION
```
above the include statement.

## Contribute
Feel free to make contributions! Try to fit in with the current code base which may change.

## TODO (in no particular order)
- add own definitions of basic functions
- add inverse of cos, sin, tan etc...
- mat2 and mat4 SIMD
- add other stuff
- optimize
