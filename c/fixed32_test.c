#include <stdio.h>
#include "fixed32.h"

int main()
{
    fixed32 f1 = fixed32_fromfloat(12.34f);
    fixed32 f2 = fixed32_fromfloat(23.45f);
    printf("%f\n", fixed32_tofloat(f1));
    printf("%f\n", fixed32_tofloat(f2));

    float f = fixed32_tofloat(fixed32_mul(f1, f2));

    printf("%f\n", f);
    return 0;
}