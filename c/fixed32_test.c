#include <stdio.h>
#include "fixed32.h"

int main()
{
    {
        fixed32 f1 = fixed32_fromfloat(-1.234f);
        fixed32 f2 = fixed32_fromfloat(-2.345f);
        printf("%f\n", fixed32_tofloat(f1));
        printf("%f\n", fixed32_tofloat(f2));

        float f_mul = fixed32_tofloat(fixed32_mul(f1, f2));
        float f_div = fixed32_tofloat(fixed32_div(f1, f2));
        float f_div_re = fixed32_tofloat(fixed32_div(f2, f1));
        printf("%f\n", f_mul);
        printf("%f\n", f_div);
        printf("%f\n", f_div_re);
    }
    
    return 0;
}