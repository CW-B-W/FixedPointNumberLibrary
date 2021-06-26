#ifndef __FIXED32_H__
#define __FIXED32_H__

#include <stdint.h>

typedef uint32_t fixed32;

#define FIXED32_SIGN_BIT   ( 1)
#define FIXED32_INT_BITS   ( 7)
#define FIXED32_FRAC_BITS  (24)
#define FIXED32_TOTAL_BITS ((FIXED32_SIGN_BIT) + (FIXED32_INT_BITS) + (FIXED32_FRAC_BITS))

#if FIXED32_SIGN_BIT != 1
    #error "FIXED32_SIGN_BIT must be 1"
#endif
#if FIXED32_TOTAL_BITS > 32
    #error "FIXED32_TOTAL_BITS > 32"
#endif

inline uint32_t fixed32_sign(fixed32 f);
inline fixed32  fixed32_neg(fixed32 a);
inline fixed32  fixed32_abs(fixed32 a);

inline fixed32  fixed32_add(fixed32 a, fixed32 b);
       fixed32  fixed32_mul(fixed32 a, fixed32 b);

// inline uint32_t fixed32_gt(fixed32 a, fixed32 b); // is a greater than b?
// inline uint32_t fixed32_ge(fixed32 a, fixed32 b); // is a greater than or equal to b?

inline fixed32  fixed32_fromfloat(float _f);
inline float    fixed32_tofloat(fixed32 f);

#endif