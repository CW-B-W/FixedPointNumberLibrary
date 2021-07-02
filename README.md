# FixedPointNumberLibrary
Simple C++ header-only library for Fixed-Point Number operations

[C version here](https://github.com/CW-B-W/FixedPointNumberLibrary/tree/master/c), designed to be compact

### Main files
* include/FixedPointNumber.hpp
  * the header-only library of `class FixedPointNumber`
* src/FixedPointNumberTest.cpp
  * the test of `class FixedPointNumber`
* src/FixedPointNumberDemo.cpp
  * the demo of 1D-convolution using `class FixedPointNumber`
  * more examples will be listed below
* makefile

## Usage
Include library
```C++
#include "FixedPointNumber.hpp"
```
MUST be compiled with C++17 or above, e.g.,
```
g++ YourCPP.cpp --std=c++17
```

### Create a FixedPointNumber object
* `sign_bit` is always of width 1
* `int_bits` is the width of integer part bits
* `frac_bits` is the width of fraction part bits

The below example instantiates a `FixedPointNumber` which has  
* 1bit `sign-bit`
* Xbits `int-bit`
* Ybits `frac-bit`

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
// support operator=
FixedPointNumber<3, 16> fp5 = 1.2345678;
FixedPointNumber<3, 16> fp6 = fp1;
```

### Functions
* to_double
```C++
FixedPointNumber<3, 16> fp(3.14159265359);
cout << setprecision(10) << fp.to_double() << endl;
// output:
// 3.141586304
```
* get_value
```C++
FixedPointNumber<7, 8> fp(0x1234);
cout << "0x" << hex << fp.get_value() << endl;
// output:
// 0x1234
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
FixedPointNumber<3, 16> fp3(3.14159265359);
FixedPointNumber<7, 8>  fp4(2.71828182846);
cout << setprecision(10) << (fp3+fp4).to_double() << endl; // result will be FixedPointNumber<3, 16>
cout << setprecision(10) << (fp4+fp3).to_double() << endl; // result will be FixedPointNumber<7, 8>
// output:
// 5.859863281
// 5.856430054
// 5.85546875
```
* operator*
```C++
FixedPointNumber<7, 8>  fp1(3.14159265359);
FixedPointNumber<7, 8>  fp2(2.71828182846);
cout << setprecision(10) << (fp1*fp2).to_double() << endl;
FixedPointNumber<7, 8>  fp3(3.14159265359);
FixedPointNumber<5, 10> fp4(2.71828182846);
cout << setprecision(10) << (fp3*fp4).to_double() << endl; // result will be FixedPointNumber<7, 8>
cout << setprecision(10) << (fp4*fp3).to_double() << endl; // result will be FixedPointNumber<5, 10>
// output:
// 8.5234375
// 8.5234375
// 8.53515625
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

## Examples
[Convolution](https://github.com/CW-B-W/FixedPointNumberLibrary/blob/master/src/FixedPointNumberDemo.cpp)
[FIR Filter](https://github.com/CW-B-W/DIC-Frequency_Analysis_System/blob/master/cpp_verification/src/FIR.cpp)
[FFT](https://github.com/CW-B-W/DIC-Frequency_Analysis_System/blob/master/cpp_verification/src/FFT.cpp)
