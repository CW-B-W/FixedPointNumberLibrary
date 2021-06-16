#ifndef __FIXEDPOINT_HPP__
#define __FIXEDPOINT_HPP__

#include <ostream>
#include <cstdint>
#include <cmath>

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
    template<int T1, int T2>
    inline FixedPointNumber& operator= (const FixedPointNumber<T1, T2> &rhs);

    inline uint32_t get_value();
    inline double   to_double();

    inline FixedPointNumber operator- () const;
    template<int T1, int T2>
    inline FixedPointNumber operator* (const FixedPointNumber<T1, T2> &rhs) const;
    template<int T1, int T2>
    inline FixedPointNumber operator+ (const FixedPointNumber<T1, T2> &rhs) const;

    // min/max available positive value
    static constexpr double PMIN_DOUBLE =  1.0 / (double)(1ULL << FRAC_BIT_LEN);        //std::pow(2, -FRAC_BIT_LEN);
    static constexpr double PMAX_DOUBLE =  (double)(1ULL << INT_BIT_LEN) - PMIN_DOUBLE; //std::pow(2, INT_BIT_LEN) - PMIN_DOUBLE;
    // min/max available negative value
    static constexpr double NMIN_DOUBLE = -(double)(1ULL << INT_BIT_LEN);               // -std::pow(2, INT_BIT_LEN);
    static constexpr double NMAX_DOUBLE = -1.0 / (double)(1ULL << FRAC_BIT_LEN);        // -std::pow(2, -FRAC_BIT_LEN);

private:
    // max available positive integer part value
    static constexpr int32_t PMAX_INTEGER   =  (1ULL << INT_BIT_LEN) - 1;
    // min available negative integer part value
    static constexpr int32_t NMIN_INTEGER   = -(1ULL << INT_BIT_LEN);

    static constexpr uint32_t SIGN_BIT_LEN  = 1;
    static constexpr uint32_t TOTAL_BIT_LEN = ((SIGN_BIT_LEN)+(INT_BIT_LEN)+(FRAC_BIT_LEN));
    static constexpr uint32_t MAX_INTEGER   = ((1ULL << INT_BIT_LEN) - 1);

    union {
        uint32_t value;
        struct {
            uint32_t fraction : FRAC_BIT_LEN;
            uint32_t integer  : INT_BIT_LEN;
            uint32_t sign     : SIGN_BIT_LEN;
            // uint32_t __empty  : (32-TOTAL_BIT_LEN);
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
    assert(this->TOTAL_BIT_LEN <= 32);
    this->value = 0U;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(uint32_t u32)
{
    assert(this->TOTAL_BIT_LEN <= 32);
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
    assert(this->TOTAL_BIT_LEN <= 32);
    this->value = 0;
    if (d == 0) {
        this->value = 0U;
    }
    else if (d > 0 && d >= this->PMAX_DOUBLE) {
        // set to max available value
        this->value = (1ULL << (TOTAL_BIT_LEN-1))-1;
        return;
    }
    else if (d > 0 && d < this->PMIN_DOUBLE) {
        this->value = 0;
        return;
    }
    else if (d < 0 && d > this->NMAX_DOUBLE) {
        this->value = 0;
        return;
    }
    else if (d < 0 && d <= this->NMIN_DOUBLE) {
        this->value = (1ULL << (TOTAL_BIT_LEN-1));
        return;
    }

    bool sign = d < 0;
    if (sign)
        d = -d;
    d *= (1ULL << FRAC_BIT_LEN);
    this->value = apply_bitmask(d);
    if (sign)
        this->value = apply_bitmask(~this->value+1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(const FixedPointNumber<T1, T2> &that)
{
    assert(this->TOTAL_BIT_LEN <= 32);
    this->value = 0;
    uint32_t sign = that.sign;
    
    int32_t integer = that.get_integer_part(that.value);
    // sign extension
    if (sign) {
        uint32_t bitmask = ~((((uint32_t)1) << T1)-1);
        integer |= bitmask;
    }

    if (integer > 0 && integer > this->PMAX_INTEGER) {
        this->value = (1ULL << (TOTAL_BIT_LEN-1))-1; /* set to max value */
        return;
    }
    else if (integer < 0 && that.integer < this->NMIN_INTEGER) {
        this->value = (1ULL << (TOTAL_BIT_LEN-1));
        return;
    }

    uint32_t frac = that.get_fraction_part(that.value);
    if (T2 > FRAC_BIT_LEN) {
        frac = frac >> (T2 - FRAC_BIT_LEN);
    }
    else {
        frac = frac << (FRAC_BIT_LEN - T2);
    }

    this->sign = sign;
    this->integer = integer & ((1ULL << INT_BIT_LEN)-1);
    this->fraction = frac;
    this->value = apply_bitmask(this->value);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>& FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator= (const FixedPointNumber<T1, T2> &rhs)
{
    *this = FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>(rhs);
    return *this;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t  FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_value()
{
    return apply_bitmask(this->value);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
double FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::to_double()
{
    FixedPointNumber &n = *this;
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
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator- () const
{
    FixedPointNumber fp;
    uint32_t n = get_int_frac_part(this->value);
    fp.value = get_int_frac_part(~n+1);
    fp.sign = !this->sign;
    return fp;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator* (const FixedPointNumber<T1, T2> &rhs) const
{
    FixedPointNumber &lhs = *const_cast<FixedPointNumber*>(this);
    uint8_t  sign = lhs.sign ^ rhs.sign;
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
    uint32_t product = get_int_frac_part((lv * rv) >> (T2));
    FixedPointNumber res(product);
    if (sign)
        return -res;
    else
        return res;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
template<int T1, int T2>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator+ (const FixedPointNumber<T1, T2> &_rhs) const
{
    FixedPointNumber &lhs = *const_cast<FixedPointNumber*>(this);
    FixedPointNumber  rhs = FixedPointNumber(_rhs);
    return FixedPointNumber(apply_bitmask(lhs.value + rhs.value));
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
    return (n >> (FRAC_BIT_LEN)) & ((1ULL << INT_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_fraction_part(uint32_t n)
{
    return (n >> (0)) & ((1ULL << FRAC_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_int_frac_part(uint32_t n)
{
    return (n >> (0)) & ((1ULL << (INT_BIT_LEN+FRAC_BIT_LEN))-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::apply_bitmask(uint32_t n)
{
    return n & ((1ULL << TOTAL_BIT_LEN)-1);
}

#endif
