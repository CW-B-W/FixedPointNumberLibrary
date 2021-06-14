#include "../include/FixedPointNumber.hpp"

#include <cstdint>
#include <iomanip>
#include <stdexcept>

using namespace std;

FixedPointNumber::FixedPointNumber()
{
    this->value = 0;
}

FixedPointNumber::FixedPointNumber(uint32_t u32)
{
    this->value = u32;
}

FixedPointNumber::FixedPointNumber(double d)
{
    FixedPointNumber &n = *this;
    if (SIGN_BIT_LEN == 1) {
        double n_max =  (1 << INT_BIT_LEN);
        double n_min = -(1 << INT_BIT_LEN);
        if (d >= n_max || d <= n_min) {
            throw invalid_argument("d exceeds max limit");
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
        throw invalid_argument("SIGN_BIT_LEN must be 1");
    }
}

uint32_t FixedPointNumber::get_value()
{
    return this->value;
}

double FixedPointNumber::to_double()
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
        throw invalid_argument("SIGN_BIT_LEN must be 1");
    }

    return d;
}


FixedPointNumber FixedPointNumber::operator- () const
{
    FixedPointNumber fp;
    uint32_t n = get_int_frac_part(this->value);
    fp.value = get_int_frac_part(~n+1);
    fp.sign = !this->sign;
    return fp;
}

FixedPointNumber FixedPointNumber::operator* (const FixedPointNumber &rhs) const
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

FixedPointNumber FixedPointNumber::operator+ (const FixedPointNumber &rhs) const
{
    FixedPointNumber &lhs = *const_cast<FixedPointNumber*>(this);
    return FixedPointNumber(apply_bit_mask(lhs.value + rhs.value));
}

ostream& operator<<(ostream &out, const FixedPointNumber &n)
{
    out << "0x";
    uint32_t u32 = 0;
    u32 |= n.sign    << (INT_BIT_LEN + FRAC_BIT_LEN);
    u32 |= n.integer << (FRAC_BIT_LEN);
    u32 |= n.fraction;
    out << setw((TOTAL_BIT_LEN+3)/4) << setfill('0') << hex << u32;
    return out;
}

uint32_t FixedPointNumber::get_sign_part(uint32_t n)
{
    return (n >> (INT_BIT_LEN+FRAC_BIT_LEN)) & ((1 << SIGN_BIT_LEN)-1);
}

uint32_t FixedPointNumber::get_integer_part(uint32_t n)
{
    return (n >> (FRAC_BIT_LEN)) & ((1 << INT_BIT_LEN)-1);
}

uint32_t FixedPointNumber::get_fraction_part(uint32_t n)
{
    return (n >> (0)) & ((1 << FRAC_BIT_LEN)-1);
}

uint32_t FixedPointNumber::get_int_frac_part(uint32_t n)
{
    return (n >> (0)) & ((1 << (INT_BIT_LEN+FRAC_BIT_LEN))-1);
}

uint32_t FixedPointNumber::apply_bit_mask(uint32_t n)
{
    return n & ((1<<TOTAL_BIT_LEN)-1);
}