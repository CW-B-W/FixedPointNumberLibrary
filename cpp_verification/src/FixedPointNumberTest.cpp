#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include "../include/FixedPointNumber.hpp"

using namespace std;

extern void test();

int main()
{
    FixedPointNumber<3, 16> t1(0xFFF9EU);
    FixedPointNumber<7, 8>  t2(0x0067);
    FixedPointNumber<7, 8>  t3(0x008F);
    cout << t1.to_double() << endl;
    cout << t2.to_double() << endl;
    cout << t3.to_double() << endl;
    cout << endl;

    cout << FixedPointNumber<7, 8>(FixedPointNumber<3, 16>(1.2345678)) << endl;
    cout << FixedPointNumber<3, 16>(FixedPointNumber<7, 8>(1.2345678)) << endl;
    cout << endl;

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