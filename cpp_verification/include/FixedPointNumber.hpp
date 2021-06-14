#ifndef __FIXEDPOINT_HPP__
#define __FIXEDPOINT_HPP__

#include <ostream>
#include <cstdint>

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
class FixedPointNumber
{
    template<int T1, int T2>
    friend std::ostream& operator<<(std::ostream &out, const FixedPointNumber<T1, T2> &n);
    
public:
    inline FixedPointNumber();
    inline FixedPointNumber(uint32_t u32);
    inline FixedPointNumber(double d);

    inline uint32_t get_value();
    inline double   to_double();

    inline FixedPointNumber operator- () const;
    inline FixedPointNumber operator* (const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &rhs) const;
    inline FixedPointNumber operator+ (const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &rhs) const;

private:
    static constexpr uint32_t SIGN_BIT_LEN  = 1;
    static constexpr uint32_t TOTAL_BIT_LEN = ((SIGN_BIT_LEN)+(INT_BIT_LEN)+(FRAC_BIT_LEN));
    union {
        uint32_t value;
        struct {
            uint32_t fraction : FRAC_BIT_LEN;
            uint32_t integer  : INT_BIT_LEN;
            uint32_t sign     : SIGN_BIT_LEN;
            uint32_t __empty  : (32-TOTAL_BIT_LEN);
        };
    };

    inline static uint32_t get_sign_part(uint32_t n);
    inline static uint32_t get_integer_part(uint32_t n);
    inline static uint32_t get_fraction_part(uint32_t n);
    inline static uint32_t get_int_frac_part(uint32_t n);
    inline static uint32_t apply_bit_mask(uint32_t n);
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

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber()
{
    this->value = 0;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(uint32_t u32)
{
    this->value = u32;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::FixedPointNumber(double d)
{
    if (SIGN_BIT_LEN == 1) {
        double n_max =  (1 << INT_BIT_LEN);
        double n_min = -(1 << INT_BIT_LEN);
        if (d >= n_max || d <= n_min) {
            throw std::invalid_argument("d exceeds max limit");
        }

        bool sign = d < 0;
        if (sign)
            d = -d;
        d *= (1 << FRAC_BIT_LEN);
        this->value = d;
        if (sign)
            this->value = apply_bit_mask(~this->value+1);

    }
    else {
        throw std::invalid_argument("SIGN_BIT_LEN must be 1");
    }
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t  FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_value()
{
    return this->value;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
double FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::to_double()
{
    FixedPointNumber &n = *this;
    double d = 0;
    if (SIGN_BIT_LEN == 1) {
        if (n.sign) {
            d = apply_bit_mask(~this->value+1);
            d = -d;
        }
        else {
            d = this->value;
        }
        d /= (1 << FRAC_BIT_LEN);
    }
    else {
        throw std::invalid_argument("SIGN_BIT_LEN must be 1");
    }

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
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator* (const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &rhs) const
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
    uint32_t product = get_int_frac_part((lv * rv) >> FRAC_BIT_LEN);
    FixedPointNumber res(product);
    if (sign)
        return -res;
    else
        return res;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::operator+ (const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &rhs) const
{
    FixedPointNumber &lhs = *const_cast<FixedPointNumber*>(this);
    return FixedPointNumber(apply_bit_mask(lhs.value + rhs.value));
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
std::ostream& operator<<(std::ostream &out, const FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN> &n)
{
    out << "0x";
    uint32_t u32 = 0;
    u32 |= n.sign    << (INT_BIT_LEN + FRAC_BIT_LEN);
    u32 |= n.integer << (FRAC_BIT_LEN);
    u32 |= n.fraction;
    out << std::setw((n.TOTAL_BIT_LEN+3)/4) << std::setfill('0') << std::hex << u32;
    return out;
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_sign_part(uint32_t n)
{
    return (n >> (INT_BIT_LEN+FRAC_BIT_LEN)) & ((1 << SIGN_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_integer_part(uint32_t n)
{
    return (n >> (FRAC_BIT_LEN)) & ((1 << INT_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_fraction_part(uint32_t n)
{
    return (n >> (0)) & ((1 << FRAC_BIT_LEN)-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::get_int_frac_part(uint32_t n)
{
    return (n >> (0)) & ((1 << (INT_BIT_LEN+FRAC_BIT_LEN))-1);
}

template<int INT_BIT_LEN, int FRAC_BIT_LEN>
uint32_t FixedPointNumber<INT_BIT_LEN, FRAC_BIT_LEN>::apply_bit_mask(uint32_t n)
{
    return n & ((1<<TOTAL_BIT_LEN)-1);
}

#endif