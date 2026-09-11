#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-3;
const int mxIter = 1000; 


array <long double, 3> jacobi_method(array <array <long double, 4>, 3> &adMat) {
    array <long double, 3> oldArr, newArr;
    array <int, 3> mxIdxArr;
    oldArr.fill(0);
    newArr.fill(0);
    mxIdxArr.fill(-1);

    for(int i = 0; i < 3; ++i) {
        long double mx = 0;
        int mxIdx = -1;
        for(int j = 0; j < 3; ++j) {
            if(abs(mx) < abs(adMat[i][j])) {
                mx = adMat[i][j];
                mxIdx = j;
            }
        }

        mxIdxArr[i] = mxIdx;
    }

    bool invalid = false;
    for(int i = 0; i < 3; ++i) {
        if(mxIdxArr[i] == mxIdxArr[(i + 1) % 3]) {
            invalid = true;
            break;
        }
    }

    if(invalid) {
        throw runtime_error("Matrix cannot be made diagonally dominant for Jacobi method.");
    }

    for(int i = 0; i < 3; ++i) {
        long double sum = 0;
        for(int j = 0; j < 3; ++j) {
            if(j != mxIdxArr[i]) {
                sum += abs(adMat[i][j]);
            }
        }

        if(abs(adMat[i][mxIdxArr[i]]) < sum) {
            invalid = true;
            break;
        }
    }

    if(invalid) {
        throw runtime_error("Matrix cannot be made diagonally dominant for Jacobi method.");
    }

    int iter = 0;
    while(iter++ < mxIter) {
        for(int i = 0; i < 3; ++i) {
            long double sum = adMat[i][3];
            for(int j = 0; j < 3; ++j) {
                if(j != mxIdxArr[i]) {
                    sum -= adMat[i][j] * oldArr[j];
                }
            }

            newArr[mxIdxArr[i]] = sum / adMat[i][mxIdxArr[i]];
        }

        bool converges = true;
        for(int i = 0; i < 3; ++i) {
            if(abs(oldArr[i] - newArr[i]) > eps) {
                converges = false;
            }

            oldArr[i] = newArr[i];
        }

        if(converges) {
            return newArr;
        }
    }

    throw runtime_error("Solution did not converge in maximum iterations.");
}

int main() {
    array <array <long double, 4>, 3> adMat;
    for(auto &arr : adMat) {
        for(auto &val : arr) {
            cin >> val;
        }
    }

    try {
        array <long double, 3> ans = jacobi_method(adMat);

        for(auto &val : ans) {
            cout << val << ' ';
        }

        cout << '\n';
    }
    catch(const exception &e) {
        cerr << "Error: " << e.what() << '\n';
    }
}