#ifndef __FIXEDPOINT_HPP__
#define __FIXEDPOINT_HPP__

#include <ostream>
#include <cstdint>

#define  SIGN_BIT_LEN ( 1)
#define   INT_BIT_LEN ( 3)
#define  FRAC_BIT_LEN (16)
#define TOTAL_BIT_LEN ((SIGN_BIT_LEN)+(INT_BIT_LEN)+(FRAC_BIT_LEN))

#if TOTAL_BIT_LEN > 32
    #error "Error on defining bit lengths"
#endif

class FixedPointNumber
{
    friend std::ostream& operator<<(std::ostream &out, const FixedPointNumber &n);
public:
    FixedPointNumber();
    FixedPointNumber(uint32_t u32);
    FixedPointNumber(double d);

    uint32_t get_value();
    double   to_double();

    FixedPointNumber operator- () const;
    FixedPointNumber operator* (const FixedPointNumber &rhs) const;
    FixedPointNumber operator+ (const FixedPointNumber &rhs) const;

private:
    union {
        uint32_t value;
        struct {
            uint32_t fraction : FRAC_BIT_LEN;
            uint32_t integer  : INT_BIT_LEN;
            uint32_t sign     : SIGN_BIT_LEN;
            uint32_t __empty  : (32-TOTAL_BIT_LEN);
        };
    };

    static uint32_t get_sign_part(uint32_t n);
    static uint32_t get_integer_part(uint32_t n);
    static uint32_t get_fraction_part(uint32_t n);
    static uint32_t get_int_frac_part(uint32_t n);
    static uint32_t apply_bit_mask(uint32_t n);
};

std::ostream& operator<<(std::ostream &out, const FixedPointNumber &n);

#endif