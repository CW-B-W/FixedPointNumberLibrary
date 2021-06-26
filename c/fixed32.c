#include "fixed32.h"

typedef union {
    float f;
    struct {
        uint32_t frac : 23;
        uint32_t exp  :  8;
        uint32_t sign :  1;
    };
} float_parse;

static uint32_t fixed32_apply_bitmask(uint32_t f);

uint32_t fixed32_sign(fixed32 f)
{
    return (f >> (FIXED32_INT_BITS + FIXED32_FRAC_BITS)) & 1;
}

fixed32 fixed32_neg(fixed32 f)
{
    return fixed32_apply_bitmask(~f + 1);
}

fixed32 fixed32_abs(fixed32 f)
{
    uint32_t f_sign = fixed32_sign(f);
    if (f_sign) {
        f = fixed32_neg(f);
    }
    return f;
}

fixed32 fixed32_add(fixed32 a, fixed32 b)
{
    return a + b;
}

fixed32 fixed32_mul(fixed32 a, fixed32 b)
{
    uint32_t a_abs = fixed32_abs(a);
    uint32_t b_abs = fixed32_abs(b);

    uint64_t product = (uint64_t) a_abs * b_abs;

    fixed32 result = product >> FIXED32_FRAC_BITS;

    uint32_t a_sign = fixed32_sign(a);
    uint32_t b_sign = fixed32_sign(b);
    if (a_sign ^ b_sign) {
        result = fixed32_apply_bitmask(~result + 1);
    }
    return result;
}

fixed32 fixed32_fromfloat(float _f)
{
    // fixed32 v =  _f * (1<<FIXED32_FRAC_BITS);
    // return v;


    float_parse f_parse = (float_parse){.f = _f};
    
    fixed32 fixed = 0;

    int32_t  exp  = f_parse.exp - 127;
    uint32_t frac = f_parse.frac;

    if (FIXED32_FRAC_BITS >= 23)
        fixed = (1 << FIXED32_FRAC_BITS) | (frac << (FIXED32_FRAC_BITS - 23));
    else
        fixed = (1 << FIXED32_FRAC_BITS) | (frac >> (23 - FIXED32_FRAC_BITS));
    if (exp >= 0) {
        fixed <<= exp;
    }
    else {
        fixed >>= (-exp);
    }

    if (f_parse.sign) {
        fixed = fixed32_neg(fixed);
    }
    return fixed;
}

float fixed32_tofloat(fixed32 f)
{
    if (f == 0)
        return 0.0f;

    float_parse f_parse = (float_parse){.f = 0.0f};

    uint32_t sign = fixed32_sign(f);
    f = fixed32_abs(f);

    uint32_t msb = f;
    while (msb & (msb-1))
        msb &= msb - 1;
    
    int32_t ctz = __builtin_ctz(msb);
    int32_t exp = ctz - FIXED32_FRAC_BITS;
    f_parse.exp = exp + 127;

    uint32_t frac = f & ~msb;
    if (23 >= ctz) {
        f_parse.frac = frac << (23 - ctz);
    }
    else {
        f_parse.frac = frac >> (ctz - 23);
    }

    f_parse.sign = sign;

    return f_parse.f;
}

static uint32_t fixed32_apply_bitmask(uint32_t f)
{
    return f & (((uint64_t)1 << FIXED32_TOTAL_BITS) - 1);
}