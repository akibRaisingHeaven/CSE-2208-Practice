#include <bits/stdc++.h>
using namespace std;

const long double eps1 = 1e-6, eps2 = 1e-3, eps3 = 1e-12, eps4 = 1e-4;

array <long double, 5> coef = {1, -3, -3, 11, -6};

long double f(long double x) {
    long double ans = 0;
    for(int i = 0; i < 5; ++i) {
        ans += coef[i] * powl(x, 4 - i);
    }

    return ans;
}

pair <long double, int> secant(long double x1, long double x2) {
    int cnt = 0;
    while(true) {
        ++cnt;
        if(cnt >= 1000) {
            throw runtime_error("Secant method failed: too many iterations.");
        }

        long double fx1 = f(x1);
        long double fx2 = f(x2);

        if(abs(fx2 - fx1) < eps3) {
            x2 += eps4;
            continue;
        }

        long double x3 = (x1 * fx2 - x2 * fx1) / (fx2 - fx1);
        long double fx3 = f(x3);

        if(abs(x3 - x2) < eps1 && abs(fx3) < eps1) {
            return {x3, cnt};
        }

        x1 = x2;
        x2 = x3;
    }
}

int main() {
    long double l = -100.1, r = 100.1;

    long double a = l;
    long double b = l + 0.5;

    set <long double> roots;
    int cnt = 0;

    while(b <= r) {
        long double fa = f(a), fb = f(b);

        if(fa * fb < 0) {
            try {
                pair <long double, int> pr = secant(a, b);
                roots.insert(pr.first);

                cout << "Root" << ++cnt << ": " << pr.first << '\n';
                cout << "Found in " << pr.second << " iterations with x1 = " << a << " and x2 = " << b << "\n\n";
            }
            catch(const exception &e) {
                cerr << e.what() <<'\n';
                return EXIT_FAILURE;
            }
        }

        a += 0.5;
        b += 0.5;
    }

    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution <long double> ldd(l, r);

    for(int i = 0; i < 10000; ++i) {
        long double val1 = ldd(gen);
        long double val2 = val1 + 0.5;

        try {
            pair <long double, int> pr = secant(val1, val2);

            auto it = roots.lower_bound(pr.first);
            
            if(it != roots.end()) {
                long double diff = abs(pr.first - *it);
                if(diff < eps2) {
                    continue;
                }

                if(it != roots.begin()) {
                    --it;
                    diff = abs(pr.first - *it);
                    if(diff < eps2) {
                        continue;
                    }
                }
            }
            else if(!roots.empty()) {
                --it;
                long double diff = abs(pr.first - *it);
                if(diff < eps2) {
                   continue;
                }
            }

            roots.insert(pr.first);

            cout << "Root" << ++cnt << ": " << pr.first << '\n';
            cout << "Found in " << pr.second << " iterations with x1 = " << val1 << " and x2 = " << val2 << "\n\n";
        }
        catch(const exception &e) {
            cerr << e.what() <<'\n';
            return EXIT_FAILURE;
        }
    }
}