# FixedPointNumberLibrary
Simple header-only library for Fixed-Point Number operations

## Usage
Include library
```C++
#include "FixedPointNumber.hpp"
```
MUST be compile C++17 or above, e.g.,
```
g++ YourCPP.cpp --std=c++17
```

### Create a FixedPointNumber object
* `sign_bit` is always of length 1
* `int_bits` is the length of integer part bits
* `frac_bits` is the length of fraction part bits

The below example instantiates a `FixedPointNumber` which has 1bit sign-bit, Xbits int-bit, Ybits frac-bit

```C++
FixedPointNumber<X, Y> fp(...);
```
And the constructor arguments can be of type
* uint32_t
* int32_t
* double
* FixedPointNumber<V, W>
  * This will construct this `FixedPointNumber<X, Y>` from the value of another object which is a `FixedPointNumber<V, W>`

e.g.
```C++
FixedPointNumber<3, 16> fp1(0xFFF9EU);
FixedPointNumber<7, 8>  fp2(0x0067);
FixedPointNumber<7, 8>  fp3(1.2345678);
FixedPointNumber<3, 16> fp4(fp3);
```

### Functions
* to_double
```C++
FixedPointNumber<3, 16> fp(3.14159265359);
cout << setprecision(10) << fp.to_double() << endl;
// output:
// 3.141586304
```
* operator- (negative)
```C++
FixedPointNumber<3, 16> fp(3.14159265359);
cout << setprecision(10) << (-fp).to_double() << endl;
// output:
// -3.141586304
```
* operator+
```C++
FixedPointNumber<3, 16> fp1(3.14159265359);
FixedPointNumber<3, 16> fp2(2.71828182846);
cout << setprecision(10) << (fp1+fp2).to_double() << endl;
// output:
// 5.859863281
```
* operator*
```C++
FixedPointNumber<7, 8> fp1(3.14159265359);
FixedPointNumber<7, 8> fp2(2.71828182846);
cout << setprecision(10) << (fp1*fp2).to_double() << endl;
// output:
// 8.5234375
```
* operator<<
```C++
FixedPointNumber<7, 8> fp1(0x1234);
cout << fp1 << endl;
cout << fp1.to_double() << endl;
FixedPointNumber<7, 8> fp2(18.203125);
cout << fp2 << endl;
cout << fp2.to_double() << endl;
// output:
// 0x1234
// 18.203125
// 0x1234
// 18.203125
```
