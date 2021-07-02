# C version of FixedPointNumberLibrary
* compact design (header-only)
* no floating point operations (for devices without FPU)

## Usage
Include library
```C
#include "fixed32.h"
```
Bit-width is modifiable in `fixed32.h`, sign bit is always of width 1
```C
#define FIXED32_INT_BITS   ( 7)
#define FIXED32_FRAC_BITS  (24)
```
MUST be compiled with C99 or above, e.g.,
```
gcc YourC.c --std=c99
```

## Example
[FFT example](https://github.com/CW-B-W/FixedPointNumberLibrary/blob/master/c/fixed32_demo.c)
