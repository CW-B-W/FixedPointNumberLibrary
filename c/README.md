# C version of FixedPointNumberLibrary
* compact design (header-only)
* no floating point operations (for devices without FPU)

## Usage
Include library
```C
#include "fixed32.h"
```
MUST be compiled with C99 or above, e.g.,
```
gcc YourC.c --std=c99
```

## Example
[FFT example](https://github.com/CW-B-W/FixedPointNumberLibrary/blob/master/c/fixed32_demo.c)
