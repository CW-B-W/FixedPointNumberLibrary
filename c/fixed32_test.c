#include <stdio.h>
#include "fixed32.h"

int main()
{
    {
        fixed32 f1 = fixed32_fromfloat(-1.234f);
        fixed32 f2 = fixed32_fromfloat(-2.345f);
        printf("%f\n", fixed32_tofloat(f1));
        printf("%f\n", fixed32_tofloat(f2));

        float f = fixed32_tofloat(fixed32_mul(f1, f2));
        printf("%f\n", f);
        printf("%d\n", fixed32_ge(f1, f2));
    }
    {
        fixed32 f1 = fixed32_fromfloat_fp(-1.234f);
        fixed32 f2 = fixed32_fromfloat_fp(-2.345f);
        printf("%f\n", fixed32_tofloat_fp(f1));
        printf("%f\n", fixed32_tofloat_fp(f2));
        
        float f = fixed32_tofloat_fp(fixed32_mul(f1, f2));
        printf("%f\n", f);
        printf("%d\n", fixed32_ge(f1, f2));
    }
    
    return 0;
}