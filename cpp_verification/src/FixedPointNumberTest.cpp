#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include "../include/FixedPointNumber.hpp"

using namespace std;

extern void test();

int main()
{
    FixedPointNumber<3, 16> fp1;
    FixedPointNumber<3, 16> fp2;

    fp1 = FixedPointNumber<3, 16>(1.2);
    fp2 = FixedPointNumber<3, 16>(3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber<3, 16>(1.2);
    fp2 = FixedPointNumber<3, 16>(-3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber<3, 16>(-1.2);
    fp2 = FixedPointNumber<3, 16>(3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber<3, 16>(-1.2);
    fp2 = FixedPointNumber<3, 16>(-3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;



    FixedPointNumber<7, 8> fp3;
    FixedPointNumber<7, 8> fp4;

    fp3 = FixedPointNumber<7, 8>(1.2);
    fp4 = FixedPointNumber<7, 8>(3.4);
    cout << fp3 << endl;
    cout << fp4 << endl;
    cout << fp3.to_double() << endl;
    cout << fp4.to_double() << endl;
    cout << (-fp3).to_double() << endl;
    cout << (-fp4).to_double() << endl;
    cout << (fp3+fp4).to_double() << endl;
    cout << (fp3*fp4).to_double() << endl;
    cout << endl;

    fp3 = FixedPointNumber<7, 8>(1.2);
    fp4 = FixedPointNumber<7, 8>(-3.4);
    cout << fp3 << endl;
    cout << fp4 << endl;
    cout << fp3.to_double() << endl;
    cout << fp4.to_double() << endl;
    cout << (-fp3).to_double() << endl;
    cout << (-fp4).to_double() << endl;
    cout << (fp3+fp4).to_double() << endl;
    cout << (fp3*fp4).to_double() << endl;
    cout << endl;

    fp3 = FixedPointNumber<7, 8>(-1.2);
    fp4 = FixedPointNumber<7, 8>(3.4);
    cout << fp3 << endl;
    cout << fp4 << endl;
    cout << fp3.to_double() << endl;
    cout << fp4.to_double() << endl;
    cout << (-fp3).to_double() << endl;
    cout << (-fp4).to_double() << endl;
    cout << (fp3+fp4).to_double() << endl;
    cout << (fp3*fp4).to_double() << endl;
    cout << endl;

    fp3 = FixedPointNumber<7, 8>(-1.2);
    fp4 = FixedPointNumber<7, 8>(-3.4);
    cout << fp3 << endl;
    cout << fp4 << endl;
    cout << fp3.to_double() << endl;
    cout << fp4.to_double() << endl;
    cout << (-fp3).to_double() << endl;
    cout << (-fp4).to_double() << endl;
    cout << (fp3+fp4).to_double() << endl;
    cout << (fp3*fp4).to_double() << endl;
    cout << endl;
    
    return 0;
}