#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include "FixedPointNumber.hpp"

using namespace std;

template<int T1, int T2>
class FixedPointNumberTest : public FixedPointNumber<T1, T2>
{
public:
    FixedPointNumberTest() : FixedPointNumber<T1, T2>()
    {
        cout << "called ctor FixedPointNumber<" << T1 << ", " << T2 << ">" << "()" << endl;
        print_info();
    }
    FixedPointNumberTest(uint32_t u32) : FixedPointNumber<T1, T2>(u32)
    {
        cout << "called ctor FixedPointNumber<" << T1 << ", " << T2 << ">" << "(uint32_t)" << endl;
        print_info();
    }
    FixedPointNumberTest( int32_t i32) : FixedPointNumber<T1, T2>(i32)
    {
        cout << "called ctor FixedPointNumber<" << T1 << ", " << T2 << ">" << "(int32_t)" << endl;
        print_info();
    }
    FixedPointNumberTest(double d)     : FixedPointNumber<T1, T2>(d)
    {
        cout << "called ctor FixedPointNumber<" << T1 << ", " << T2 << ">" << "(double)" << endl;
        print_info();
    }
    template<int T3, int T4>
    FixedPointNumberTest(const FixedPointNumber<T3, T4> &that) : FixedPointNumber<T1, T2>(that)
    {
        // cout << "called ctor FixedPointNumber<" << T1 << ", " << T2 << ">" << "(that)" << endl;
        // print_info();
    }

    FixedPointNumberTest operator- ()
    {
        return FixedPointNumber<T1,T2>::operator-();
    }

    template<int T3, int T4>
    FixedPointNumberTest operator* (const FixedPointNumberTest<T3, T4> &rhs)
    {
        FixedPointNumberTest& lhs = *this;
        cout << "[Test operator*]" << endl;
        cout << "FixedPointNumberTest<" << T1 << ", " << T2 << "> * FixedPointNumberTest<" << T3 << ", " << T4 << ">" << endl;
        cout << "Result will be " << "FixedPointNumberTest<" << T1 << ", " << T2 << ">" << endl;
        cout << '\t' << lhs.to_double() << " * " << rhs.to_double() << endl;
        FixedPointNumberTest res = FixedPointNumber<T1, T2>::operator*(static_cast<FixedPointNumber<T3,T4>>(rhs));
        cout << '\t' << "= " << res.to_double() << endl;
        cout << '\t' << "Expected if full-precision" << endl;
        cout << '\t' << "= " << lhs.to_double() * rhs.to_double() << endl;
        cout << endl;
        return res;
    }

    template<int T3, int T4>
    FixedPointNumberTest operator/ (const FixedPointNumberTest<T3, T4> &rhs)
    {
        FixedPointNumberTest& lhs = *this;
        cout << "[Test operator/]" << endl;
        cout << "FixedPointNumberTest<" << T1 << ", " << T2 << "> * FixedPointNumberTest<" << T3 << ", " << T4 << ">" << endl;
        cout << "Result will be " << "FixedPointNumberTest<" << T1 << ", " << T2 << ">" << endl;
        cout << '\t' << lhs.to_double() << " / " << rhs.to_double() << endl;
        FixedPointNumberTest res = FixedPointNumber<T1, T2>::operator/(static_cast<FixedPointNumber<T3,T4>>(rhs));
        cout << '\t' << "= " << res.to_double() << endl;
        cout << '\t' << "Expected if full-precision" << endl;
        cout << '\t' << "= " << lhs.to_double() * rhs.to_double() << endl;
        cout << endl;
        return res;
    }

    template<int T3, int T4>
    FixedPointNumberTest operator- (const FixedPointNumberTest<T3, T4> &rhs)
    {
        FixedPointNumberTest& lhs = *this;
        cout << "[Test operator-]" << endl;
        cout << "FixedPointNumberTest<" << T1 << ", " << T2 << "> - FixedPointNumberTest<" << T3 << ", " << T4 << ">" << endl;
        cout << "Result will be " << "FixedPointNumberTest<" << T1 << ", " << T2 << ">" << endl;
        cout << '\t' << lhs.to_double() << " - " << rhs.to_double() << endl;
        FixedPointNumberTest res = FixedPointNumber<T1, T2>::operator-(static_cast<FixedPointNumber<T3,T4>>(rhs));
        cout << '\t' << "= " << res.to_double() << endl;
        cout << '\t' << "Expected if full-precision" << endl;
        cout << '\t' << "= " << lhs.to_double() - rhs.to_double() << endl;
        cout << endl;
        return res;
    }

    template<int T3, int T4>
    FixedPointNumberTest operator+ (const FixedPointNumberTest<T3, T4> &rhs)
    {
        FixedPointNumberTest& lhs = *this;
        cout << "[Test operator+]" << endl;
        cout << "FixedPointNumberTest<" << T1 << ", " << T2 << "> + FixedPointNumberTest<" << T3 << ", " << T4 << ">" << endl;
        cout << "Result will be " << "FixedPointNumberTest<" << T1 << ", " << T2 << ">" << endl;
        cout << '\t' << lhs.to_double() << " + " << rhs.to_double() << endl;
        FixedPointNumberTest res = FixedPointNumber<T1, T2>::operator+(static_cast<FixedPointNumber<T3,T4>>(rhs));
        cout << '\t' << "= " << res.to_double() << endl;
        cout << '\t' << "Expected if full-precision" << endl;
        cout << '\t' << "= " << lhs.to_double() + rhs.to_double() << endl;
        cout << endl;
        return res;
    }

    void print_double()
    {
        cout << "[Print double]" << endl;
        cout << '\t' << FixedPointNumber<T1, T2>::to_double() << endl;
        cout << endl;
    }

    void print_value()
    {
        cout << "[Print value]" << endl;
        cout << '\t' << static_cast<FixedPointNumber<T1,T2>>(*this) << endl;
        cout << endl;
    }

    void print_info()
    {
        cout << "[Print info]" << endl;
        cout << "\tdouble = " << FixedPointNumber<T1, T2>::to_double() << endl;
        cout << "\tvalue  = " << static_cast<FixedPointNumber<T1,T2>>(*this) << endl;
        cout << "\tstatus = " << endl;
        cout << "\t\toverflow =  " << static_cast<FixedPointNumber<T1,T2>>(*this).is_overflowed() << endl;
        cout << "\t\tunderflowflow =  " << static_cast<FixedPointNumber<T1,T2>>(*this).is_underflowed() << endl;
        cout << endl;
    }
};

void print_title(string s, int lvl)
{
    constexpr int line_char_num = 60;
    constexpr char char_list[4] = {'=', '-', '*', '%'};
    char pad_char = char_list[lvl];
    int side_pad_num = (line_char_num - s.size() - 2)/2;
    cout << string(side_pad_num, pad_char) << " ";
    cout << s;
    cout << " " << string(side_pad_num - !(s.size()&1), pad_char);
    cout << endl;
}

int main()
{
    print_title("Test 0 - Basic operations", 0);

    print_title("Test constructors", 1);
    FixedPointNumberTest<15, 16> fp;
    fp = FixedPointNumberTest<15, 16>(9999.9999);
    fp = FixedPointNumberTest<15, 16>(0x12345678);
    fp = FixedPointNumberTest<15, 16>(0x12345678U);
    fp = FixedPointNumberTest<15, 16>(FixedPointNumberTest<7,8>(127.127127));
    print_title("Test functions", 1);
    fp.print_value();
    fp.print_double();
    (-fp);
    (fp+fp);
    (fp-fp);
    (fp*fp);
    (fp/fp);

    print_title("End of Test 0", 0);
    cout << endl;
    


    print_title("Test 1 - Op with two diff length fp", 0);

    FixedPointNumberTest<7, 8> fpm1 = 0x10FF;
    FixedPointNumberTest<15, 16> fpm2 = 0x0000FFFF;
    (fpm1 * fpm2);
    (fpm2 * fpm1);

    print_title("End of Test 1", 0);
    cout << endl;



    print_title("Test 2 - Overflow test", 0);

    FixedPointNumberTest<3, 16> fpof;
    print_title("Max/Min of FixedPointNumberTest<3, 16>", 1);
    cout << "Positive Max of FixedPointNumberTest<3, 16> = " << fpof.PMAX_DOUBLE << endl;
    cout << "Positive Min of FixedPointNumberTest<3, 16> = " << fpof.PMIN_DOUBLE << endl;
    cout << "Negative Max of FixedPointNumberTest<3, 16> = " << fpof.NMAX_DOUBLE << endl;
    cout << "Negative Min of FixedPointNumberTest<3, 16> = " << fpof.NMIN_DOUBLE << endl;
    print_title("Set greater than Positive Max", 1);
    fpof = 999.999;
    fpof.print_value();
    print_title("Set less than Positive Max", 1);
    fpof = 0.00000000001;
    fpof.print_value();
    print_title("Set greater than Negative Max", 1);
    fpof = -0.00000000001;
    fpof.print_value();
    print_title("Set less than Negative Min", 1);
    fpof = -999.999;
    fpof.print_value();

    print_title("End of Test 2", 0);
    cout << endl;

    print_title("Test 3 - Add Overflow test", 0);
    FixedPointNumberTest<3, 12> fp_pmaxd = FixedPointNumberTest<3, 12>::PMAX_DOUBLE;
    FixedPointNumberTest<3, 12> fp_pmind = FixedPointNumberTest<3, 12>::PMIN_DOUBLE;
    fp_pmaxd.print_info();
    (fp_pmaxd + fp_pmind).print_info();
    FixedPointNumberTest<3, 12> fp_nmind = FixedPointNumberTest<3, 12>::NMIN_DOUBLE;
    FixedPointNumberTest<3, 12> fp_nmaxd = FixedPointNumberTest<3, 12>::NMAX_DOUBLE;
    fp_nmind.print_info();
    (fp_nmind + fp_nmaxd).print_info();


    print_title("End of Test 3", 0);
    cout << endl;

    print_title("Test 4 - Mul Overflow test", 0);
    
    

    print_title("End of Test 4", 0);
    cout << endl;

    // cout << "-----3-----" << endl;
    // cout << (FixedPointNumber<3, 16>(FixedPointNumber<7, 8>(1.2345678))) << endl;
    // cout << (FixedPointNumber<3, 16>(FixedPointNumber<7, 8>(1.2345678))).to_double() << endl;
    // cout << (FixedPointNumber<7, 8>(FixedPointNumber<3, 16>(1.2345678))) << endl;
    // cout << (FixedPointNumber<7, 8>(FixedPointNumber<3, 16>(1.2345678))).to_double() << endl;
    // cout << endl;
    // cout << "-----4-----" << endl;
    // cout << (FixedPointNumber<3, 16>(FixedPointNumber<7, 8>(-1.2345678))) << endl;
    // cout << (FixedPointNumber<3, 16>(FixedPointNumber<7, 8>(-1.2345678))).to_double() << endl;
    // cout << (FixedPointNumber<7, 8>(FixedPointNumber<3, 16>(-1.2345678))) << endl;
    // cout << (FixedPointNumber<7, 8>(FixedPointNumber<3, 16>(-1.2345678))).to_double() << endl;
    // cout << endl;
    // cout << "-----5-----" << endl;
    // cout << (FixedPointNumber<3, 16>(1.2345678) * FixedPointNumber<7, 8>(1.234)).to_double() << endl;
    // cout << (FixedPointNumber<7, 8>(1.234) * FixedPointNumber<3, 16>(1.2345678)).to_double() << endl;
    // cout << endl;

    // FixedPointNumber<3, 16> fp1;
    // FixedPointNumber<3, 16> fp2;

    // cout << "-----6-----" << endl;
    // fp1 = FixedPointNumber<3, 16>(1.2);
    // fp2 = FixedPointNumber<3, 16>(3.4);
    // cout << fp1 << endl;
    // cout << fp2 << endl;
    // cout << fp1.to_double() << endl;
    // cout << fp2.to_double() << endl;
    // cout << (-fp1).to_double() << endl;
    // cout << (-fp2).to_double() << endl;
    // cout << (fp1+fp2).to_double() << endl;
    // cout << (fp1-fp2).to_double() << endl;
    // cout << (fp1*fp2).to_double() << endl;
    // cout << (fp1/fp2).to_double() << endl;
    // cout << endl;

    // fp1 = FixedPointNumber<3, 16>(1.2);
    // fp2 = FixedPointNumber<3, 16>(-3.4);
    // cout << fp1 << endl;
    // cout << fp2 << endl;
    // cout << fp1.to_double() << endl;
    // cout << fp2.to_double() << endl;
    // cout << (-fp1).to_double() << endl;
    // cout << (-fp2).to_double() << endl;
    // cout << (fp1+fp2).to_double() << endl;
    // cout << (fp1-fp2).to_double() << endl;
    // cout << (fp1*fp2).to_double() << endl;
    // cout << (fp1/fp2).to_double() << endl;
    // cout << endl;

    // fp1 = FixedPointNumber<3, 16>(-1.2);
    // fp2 = FixedPointNumber<3, 16>(3.4);
    // cout << fp1 << endl;
    // cout << fp2 << endl;
    // cout << fp1.to_double() << endl;
    // cout << fp2.to_double() << endl;
    // cout << (-fp1).to_double() << endl;
    // cout << (-fp2).to_double() << endl;
    // cout << (fp1+fp2).to_double() << endl;
    // cout << (fp1-fp2).to_double() << endl;
    // cout << (fp1*fp2).to_double() << endl;
    // cout << (fp1/fp2).to_double() << endl;
    // cout << endl;

    // fp1 = FixedPointNumber<3, 16>(-1.2);
    // fp2 = FixedPointNumber<3, 16>(-3.4);
    // cout << fp1 << endl;
    // cout << fp2 << endl;
    // cout << fp1.to_double() << endl;
    // cout << fp2.to_double() << endl;
    // cout << (-fp1).to_double() << endl;
    // cout << (-fp2).to_double() << endl;
    // cout << (fp1+fp2).to_double() << endl;
    // cout << (fp1-fp2).to_double() << endl;
    // cout << (fp1*fp2).to_double() << endl;
    // cout << (fp1/fp2).to_double() << endl;
    // cout << endl;



    // FixedPointNumber<7, 8> fp3;
    // FixedPointNumber<7, 8> fp4;

    // fp3 = FixedPointNumber<7, 8>(1.2);
    // fp4 = FixedPointNumber<7, 8>(3.4);
    // cout << fp3 << endl;
    // cout << fp4 << endl;
    // cout << fp3.to_double() << endl;
    // cout << fp4.to_double() << endl;
    // cout << (-fp3).to_double() << endl;
    // cout << (-fp4).to_double() << endl;
    // cout << (fp3+fp4).to_double() << endl;
    // cout << (fp3-fp4).to_double() << endl;
    // cout << (fp3*fp4).to_double() << endl;
    // cout << (fp3/fp4).to_double() << endl;
    // cout << endl;

    // fp3 = FixedPointNumber<7, 8>(1.2);
    // fp4 = FixedPointNumber<7, 8>(-3.4);
    // cout << fp3 << endl;
    // cout << fp4 << endl;
    // cout << fp3.to_double() << endl;
    // cout << fp4.to_double() << endl;
    // cout << (-fp3).to_double() << endl;
    // cout << (-fp4).to_double() << endl;
    // cout << (fp3+fp4).to_double() << endl;
    // cout << (fp3-fp4).to_double() << endl;
    // cout << (fp3*fp4).to_double() << endl;
    // cout << (fp3/fp4).to_double() << endl;
    // cout << endl;

    // fp3 = FixedPointNumber<7, 8>(-1.2);
    // fp4 = FixedPointNumber<7, 8>(3.4);
    // cout << fp3 << endl;
    // cout << fp4 << endl;
    // cout << fp3.to_double() << endl;
    // cout << fp4.to_double() << endl;
    // cout << (-fp3).to_double() << endl;
    // cout << (-fp4).to_double() << endl;
    // cout << (fp3+fp4).to_double() << endl;
    // cout << (fp3-fp4).to_double() << endl;
    // cout << (fp3*fp4).to_double() << endl;
    // cout << (fp3/fp4).to_double() << endl;
    // cout << endl;

    // fp3 = FixedPointNumber<7, 8>(-1.2);
    // fp4 = FixedPointNumber<7, 8>(-3.4);
    // cout << fp3 << endl;
    // cout << fp4 << endl;
    // cout << fp3.to_double() << endl;
    // cout << fp4.to_double() << endl;
    // cout << (-fp3).to_double() << endl;
    // cout << (-fp4).to_double() << endl;
    // cout << (fp3+fp4).to_double() << endl;
    // cout << (fp3-fp4).to_double() << endl;
    // cout << (fp3*fp4).to_double() << endl;
    // cout << (fp3/fp4).to_double() << endl;
    // cout << endl;
    
    return 0;
}
