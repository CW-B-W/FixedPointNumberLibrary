#ifndef __FIXEDPOINT_HPP__
#define __FIXEDPOINT_HPP__

#include <ostream>
#include <cstdint>
#include <cmath>

inline static constexpr uint32_t make_bitmask(uint32_t bits);

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
class FixedPointNumber
{
    template<int T1, int T2>
    friend std::ostream& operator<<(std::ostream &out, const FixedPointNumber<T1, T2> &n);
    template<int T1, int T2>
    friend class FixedPointNumber;
    
public:
    inline FixedPointNumber();
    inline FixedPointNumber(uint32_t u32);
    inline FixedPointNumber( int32_t i32);
    inline FixedPointNumber(double d);
    template<int T1, int T2>
    inline FixedPointNumber(const FixedPointNumber<T1, T2> &that);

    inline uint32_t get_value()         const;
    inline double   to_double()         const; // use floating-point operations to convert to double
    inline double   to_double_bitwise() const; // use bitwise        operation to convert to double

    inline FixedPointNumber operator- () const;
    template<int T1, int T2>
    inline FixedPointNumber operator* (const FixedPointNumber<T1, T2> &rhs) const;
    template<int T1, int T2>
    inline FixedPointNumber operator- (const FixedPointNumber<T1, T2> &rhs) const;
    template<int T1, int T2>
    inline FixedPointNumber operator+ (const FixedPointNumber<T1, T2> &rhs) const;

    // min/max available positive value
    static constexpr double PMIN_DOUBLE =  1.0 / (double)(1ULL << FRAC_BIT_LEN);          //std::pow(2, -FRAC_BIT_LEN);
    static constexpr double PMAX_DOUBLE =  ((double)(1ULL << INT_BIT_LEN) - PMIN_DOUBLE); //std::pow(2, INT_BIT_LEN) - PMIN_DOUBLE;
    // min/max available negative value
    static constexpr double NMIN_DOUBLE = -((double)(1ULL << INT_BIT_LEN) - PMIN_DOUBLE); // -std::pow(2, INT_BIT_LEN);
    static constexpr double NMAX_DOUBLE = -1.0 / (double)(1ULL << FRAC_BIT_LEN);          // -std::pow(2, -FRAC_BIT_LEN);

    inline bool is_overflowed()  { return this->overflowed; }
    inline bool is_underflowed() { return this->underflowed; }

private:
    // max available positive integer part value
    static constexpr  int32_t PMAX_INTEGER  =  ((1ULL << INT_BIT_LEN) - 1);
    // min available negative integer part value
    static constexpr  int32_t NMIN_INTEGER  = -((1ULL << INT_BIT_LEN) - 1);

    static constexpr uint32_t SIGN_BIT_LEN  = 1;
    static constexpr uint32_t TOTAL_BIT_LEN = ((SIGN_BIT_LEN)+(INT_BIT_LEN)+(FRAC_BIT_LEN));

    union {
        uint32_t value = 0;
        struct {
            uint32_t fraction : FRAC_BIT_LEN;
            uint32_t integer  : INT_BIT_LEN;
            uint32_t sign     : SIGN_BIT_LEN;
        };
    };

    union  {
        uint32_t status_value = 0;
        struct {
            uint32_t overflowed  : 1;
            uint32_t underflowed : 1;
        };
    };

    inline static uint32_t get_sign_part(uint32_t n);
    inline static uint32_t get_integer_part(uint32_t n);
    inline static uint32_t get_fraction_part(uint32_t n);
    inline static uint32_t get_int_frac_part(uint32_t n);
    inline static uint32_t apply_bitmask(uint32_t n);
};

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
inline std::ostream& operator<<(std::ostream &out, const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &n);



/**************************************************************************
 ************************** Declaration is above  *************************
 **************************************************************************/



/**************************************************************************
 ************************** Definition is below  **************************
 **************************************************************************/

#include <cstdint>
#include <iomanip>
#include <stdexcept>
#include <cassert>

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber()
{
    assert(this->TOTAL_BIT_LEN <= (sizeof(this->value) * 8));
    this->value = 0;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(uint32_t u32)
{
    assert(this->TOTAL_BIT_LEN <= (sizeof(this->value) * 8));
    assert(u32 <= make_bitmask(TOTAL_BIT_LEN));
    this->value = apply_bitmask(u32);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(int32_t i32) : FixedPointNumber(static_cast<uint32_t>(i32))
{
    ;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(double d)
{
    assert(this->TOTAL_BIT_LEN <= (sizeof(this->value) * 8));
    this->value = 0;
    if (d == 0) {
        this->value = 0;
        return;
    }
    else if (d > 0 && d > this->PMAX_DOUBLE) {
        // set to PMAX_DOUBLE
        this->value = (1ULL << (TOTAL_BIT_LEN-1)) - 1;
        this->overflowed = 1;
        return;
    }
    else if (d > 0 && d < this->PMIN_DOUBLE) {
        this->value = 0;
        this->underflowed = 1;
        return;
    }
    else if (d < 0 && d > this->NMAX_DOUBLE) {
        this->value = 0;
        this->underflowed = 1;
        return;
    }
    else if (d < 0 && d < this->NMIN_DOUBLE) {
        // set to NMIN_DOUBLE
        this->value = (1ULL << (TOTAL_BIT_LEN-1)) + 1;
        this->overflowed = 1;
        return;
    }

    bool sign = d < 0;
    if (sign)
        d = -d;
    d *= (1ULL << FRAC_BIT_LEN);
    this->value = apply_bitmask((uint32_t)d);
    if (sign)
        this->value = apply_bitmask(~this->value+1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(const FixedPointNumber<T1, T2> &_that)
{
    assert(this->TOTAL_BIT_LEN <= (sizeof(this->value) * 8));
    this->value = 0;

    FixedPointNumber<T1, T2> that = _that;
    uint32_t sign = that.sign;
    if (sign)
        that = -that;
    
    uint32_t frac = that.get_fraction_part(that.value);
    if (T2 > FRAC_BIT_LEN) {
        /* round from the truncated bits */
        frac = frac >> (T2 - FRAC_BIT_LEN - 1);
        frac += frac & 1;
        frac >>= 1;
    }
    else {
        frac = frac << (FRAC_BIT_LEN - T2);
    }

    uint32_t integer = that.get_integer_part(that.value);

    this->sign = 0;
    this->integer = integer & make_bitmask(INT_BIT_LEN);
    this->fraction = frac & make_bitmask(FRAC_BIT_LEN);
    
    if (sign)
        *this = -(*this);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t  FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_value() const
{
    return apply_bitmask(this->value);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
double FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::to_double() const
{
    const FixedPointNumber &n = *this;
    double d = 0;
    if (n.sign) {
        d = apply_bitmask(~this->value+1);
        d = -d;
    }
    else {
        d = apply_bitmask(this->value);
    }
    d /= (double)(1ULL << FRAC_BIT_LEN);
    return d;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
double FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::to_double_bitwise() const
{
    if (this->value == 0)
        return 0;
    
    uint64_t sign = this->sign;
    uint64_t value = this->value;
    if (sign)
        value = apply_bitmask(~value + 1);

    union {
        struct {
            uint64_t d_frac : 52;
            uint64_t d_exp  : 11;
            uint64_t d_sign : 1;
        };
        double d = 0;
    };

    /*
     *  Because the formula of double is
     *  d = (-1)^d_sign * (1.d_frac) * 2^d_exp
     *  we can convert fixed point number to double with bit operations:
     *  Let the fixed point number to positive
     *  observe in the formula that `(1.d_frac)` always has a `1`
     *  so d must be 2^(d_exp) + ...
     *  which means 2^(d_exp) must match the MSB of fixed-point number
     *  so we simply make 2^d_exp be the MSB
     *  then the bits behind MSB is the fraction part of d
     */

    // find msb
    uint64_t msb = value;
    while (msb & (msb-1))
        msb &= msb - 1;
    
    // let 2^d_exp = MSB
    int64_t exp = __builtin_ctzll(msb) - FRAC_BIT_LEN;
    d_exp = exp + 1023;

    // the fraction part is behind msb
    uint64_t frac = value & ~msb;
    d_frac = frac << (52 - __builtin_ctzll(msb));

    d_sign = sign;

    return d;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator- () const
{
    FixedPointNumber fp;
    uint32_t n = get_int_frac_part(this->value);
    if (n == 0) {
        fp.value = 0;
        return fp;
    }
    fp.value = get_int_frac_part(~n+1);
    fp.sign = !this->sign;
    return fp;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator* (const FixedPointNumber<T1, T2> &rhs) const
{
    const FixedPointNumber &lhs = *this;
    uint32_t sign = lhs.sign ^ rhs.sign;
    uint64_t lv;
    uint64_t rv;
    if (lhs.sign) {
        lv = (-lhs).value;
    }
    else {
        lv = lhs.value;
    }
    if (rhs.sign) {
        rv = (-rhs).value;
    }
    else {
        rv = rhs.value;
    }

    FixedPointNumber res;
    uint64_t product = lv * rv;
    product >>= (T2 - 1);
    product += product & 1; // rounding
    product >>= 1;
    if (product >= (1 << (TOTAL_BIT_LEN-1)))
        res.overflowed = 1;
    res.value = get_int_frac_part(product);

    if (sign)
        return -res;
    else
        return res;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator+ (const FixedPointNumber<T1, T2> &_rhs) const
{
    const FixedPointNumber &lhs = *this;
    FixedPointNumber rhs = FixedPointNumber(_rhs);
    FixedPointNumber res;
    uint64_t lv = lhs.value;
    uint64_t rv = rhs.value;
    uint64_t sum = lv + rv;
    if (get_sign_part(lv) == get_sign_part(rv) && get_sign_part(lv) != get_sign_part(sum)) {
        res.overflowed = 1;
    }
    else if (apply_bitmask(sum) == (1ULL << (TOTAL_BIT_LEN-1))) {
        /* 1000....0001 is the NMIN_DOUBLE   */
        /* 1000....0000 is invalid value */
        res.overflowed = 1;
    }
    res.value = apply_bitmask(sum);
    
    return res;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator- (const FixedPointNumber<T1, T2> &rhs) const
{
    const FixedPointNumber &lhs = *this;
    return lhs + (-rhs);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
std::ostream& operator<<(std::ostream &out, const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &n)
{
    out << "0x";
    uint32_t u32 = 0;
    u32 |= n.sign    << (INT_BIT_LEN + FRAC_BIT_LEN);
    u32 |= n.integer << (FRAC_BIT_LEN);
    u32 |= n.fraction;
    std::ios_base::fmtflags f(out.flags());
    out << std::setw((n.TOTAL_BIT_LEN+3)/4) << std::setfill('0') << std::hex << u32;
    out.flags(f);
    return out;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_sign_part(uint32_t n)
{
    return (n >> (INT_BIT_LEN+FRAC_BIT_LEN)) & ((1ULL << SIGN_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_integer_part(uint32_t n)
{
    return (n >> FRAC_BIT_LEN) & make_bitmask(INT_BIT_LEN);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_fraction_part(uint32_t n)
{
    return n & make_bitmask(FRAC_BIT_LEN);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_int_frac_part(uint32_t n)
{
    return n & make_bitmask(INT_BIT_LEN + FRAC_BIT_LEN);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::apply_bitmask(uint32_t n)
{
    return n & make_bitmask(TOTAL_BIT_LEN);
}

inline static constexpr uint32_t make_bitmask(uint32_t bits)
{
    return (1ULL << bits) - 1;
}

#endif
