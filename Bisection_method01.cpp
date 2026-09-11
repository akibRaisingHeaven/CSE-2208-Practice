#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-3;

long double evaluate(long double x) {
    return 3 * x - cos(x) - 1;
}

long double bisection(long double x1, long double x2) {
    while(true) {
        long double x0 = (x1 + x2) / 2;
        if(abs((x2 - x1) / x2) < eps) {
            return x0;
        }

        long double fx0 = evaluate(x0);

        if(fx0 == 0) {
            return x0;
        }

        long double fx1 = evaluate(x1);
        long double fx2 = evaluate(x2);

        if(fx1 * fx0 < 0) {
            x2 = x0;
        }
        else {
            x1 = x0;
        }
    }
}

int main() {
    long double x1 = -1000, x2 = -999;
    while(x2 < 1000) {
        long double fx1 = evaluate(x1);
        long double fx2 = evaluate(x2);

        if(fx1 * fx2 < 0) {
            break;
        }

        ++x1;
        ++x2;
    }

    cout << bisection(x1, x2) << '\n';
}