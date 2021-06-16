#include <iostream>
#include <vector>
#include <cstdint>
#include <cassert>
#include <cmath>
#include "FixedPointNumber.hpp"

using namespace std;

extern uint32_t H[32];
extern uint32_t X[1024];

template <typename T1, typename T2>
vector<T1> convolution(vector<T1> x, vector<T2> h) {
    vector<T1> y;
    for (int i = h.size()-1; i < x.size()+h.size()-1; ++i) {
        T1 yi = 0;
        for (int k = 0; k < h.size(); ++k) {
            if (i-k < x.size()) {
                yi = yi + x[i-k] * h[k];
            }
        }
        y.emplace_back(yi);
    }
    return y;
}

template <typename T1, typename T2>
vector<T1> convolution_high_precision(vector<T1> x, vector<T2> h) {
    vector<T1> y;
    for (int i = h.size()-1; i < x.size()+h.size()-1; ++i) {
        FixedPointNumber<7, 24> yi = 0;
        for (int k = 0; k < h.size(); ++k) {
            if (i-k < x.size()) {
                yi = yi + (FixedPointNumber<7, 24>)x[i-k] * (FixedPointNumber<7, 24>)h[k];
            }
        }
        y.emplace_back(yi);
    }
    return y;
}

int main(int argc, char** argv)
{
    string dir = argv[1];
    string path;
    FILE* fp = NULL;

    vector<FixedPointNumber<7, 8>> x_vec;
    path = dir + "/X_FixedPoint.dat";
    fp = fopen(path.c_str(), "r");
    assert(fp);
    for (int i = 0; i < 1024; ++i) {
        uint32_t x_in;
        fscanf(fp, "%x", &x_in);
        x_vec.emplace_back(x_in);
    }
    fclose(fp);

    vector<FixedPointNumber<3, 16>> h_vec;
    path = dir + "/H_FixedPoint.dat";
    fp = fopen(path.c_str(), "r");
    assert(fp);
    for (int i = 0; i < 32; ++i) {
        uint32_t h_in;
        fscanf(fp, "%x", &h_in);
        h_vec.emplace_back(h_in);
    }
    fclose(fp);

    int errcnt;
    vector<FixedPointNumber<7, 8>> y_vec;
    cout << "==================== Low Precision ====================" << endl;
    y_vec = convolution(x_vec, h_vec);
    path = dir + "/Y_FixedPoint.dat";
    fp = fopen(path.c_str(), "r");
    assert(fp);
    errcnt = 0;
    y_vec.clear();
    for (int i = 0; i < 1024; ++i) {
        uint32_t y_in;
        fscanf(fp, "%x", &y_in);
        if (abs((int)y_in - (int)y_vec[i].get_value()) > 1) {
            cout << i << "-th:" << endl;
            cout << '\t' << "Result = " << y_vec[i] << endl;
            cout << '\t' << "Expect = " << FixedPointNumber<7, 8>(y_in) << endl;
            errcnt += 1;
        }
    }
    fclose(fp);
    if (errcnt) {
        cout << errcnt << ' ' << "errors" << endl;
    }
    else {
        cout << "All are correct" << endl;
    }
    cout << endl << endl;


    cout << "==================== High Precision ===================" << endl;
    y_vec = convolution_high_precision(x_vec, h_vec);
    path = dir + "/Y_FixedPoint.dat";
    fp = fopen(path.c_str(), "r");
    assert(fp);
    errcnt = 0;
    y_vec.clear();
    for (int i = 0; i < 1024; ++i) {
        uint32_t y_in;
        fscanf(fp, "%x", &y_in);
        if (abs((int)y_in - (int)y_vec[i].get_value()) > 1) {
            cout << i << "-th:" << endl;
            cout << '\t' << "Result = " << y_vec[i] << endl;
            cout << '\t' << "Expect = " << FixedPointNumber<7, 8>(y_in) << endl;
            errcnt += 1;
        }
    }
    fclose(fp);
    if (errcnt) {
        cout << errcnt << ' ' << "errors" << endl;
    }
    else {
        cout << "All are correct" << endl;
    }
    cout << endl << endl;

    return 0;
}