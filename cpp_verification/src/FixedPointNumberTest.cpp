#include <iostream>
#include "../include/FixedPointNumber.hpp"

using namespace std;

int main()
{
    FixedPointNumber fp1;
    FixedPointNumber fp2;

    fp1 = FixedPointNumber(1.2);
    fp2 = FixedPointNumber(3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber(1.2);
    fp2 = FixedPointNumber(-3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber(-1.2);
    fp2 = FixedPointNumber(3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;

    fp1 = FixedPointNumber(-1.2);
    fp2 = FixedPointNumber(-3.4);
    cout << fp1 << endl;
    cout << fp2 << endl;
    cout << fp1.to_double() << endl;
    cout << fp2.to_double() << endl;
    cout << (-fp1).to_double() << endl;
    cout << (-fp2).to_double() << endl;
    cout << (fp1+fp2).to_double() << endl;
    cout << (fp1*fp2).to_double() << endl;
    cout << endl;
    return 0;
}