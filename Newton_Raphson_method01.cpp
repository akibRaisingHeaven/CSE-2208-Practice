#include <bits/stdc++.h>
using namespace std;

const long double eps1 = 1e-6, eps2 = 1e-3, eps3 = 1e-12, eps4 = 1e-4;

array <long double, 5> coef = {1, -3, -3, 11, -6};
array <long double, 4> coef_p = {4, -9, -6, 11};

long double f(long double x) {
    long double ans = 0;
    for(int i = 0; i < 5; ++i) {
        ans += coef[i] * powl(x, 4 - i);
    }

    return ans;
}

long double f_prime(long double x) {
    long double ans = 0;
    for(int i = 0; i < 4; ++i) {
        ans += coef_p[i] * powl(x, 3 - i);
    }

    return ans;
}

pair <long double, int> new_raph(long double x) {
    int cnt = 0;
    while(true) {
        ++cnt;
        if(cnt >= 1000) {
            throw runtime_error("Newton-Raphson method failed: too many iterations.");
        }

        long double fx = f(x);
        long double fpx = f_prime(x);

        if(abs(fpx) < eps3) {
            x += eps4;
            continue;
        }

        long double quo = fx / fpx;
        x -= quo;

        if(abs(quo) < eps1) {
            return {x, cnt};
        }
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
                pair <long double, int> pr = new_raph(a);
                roots.insert(pr.first);

                cout << "Root" << ++cnt << ": " << pr.first << '\n';
                cout << "Found in " << pr.second << " iterations with x0 = " << a << "\n\n";
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
        long double val = ldd(gen);

        try {
            pair <long double, int> pr = new_raph(val);

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
            cout << "Found in " << pr.second << " iterations with x0 = " << val << "\n\n";
        }
        catch(const exception &e) {
            cerr << e.what() <<'\n';
            return EXIT_FAILURE;
        }
    }
}