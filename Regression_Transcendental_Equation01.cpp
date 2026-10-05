#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

//y = a(x^b)

int main() {
    ll n;
    cin >> n;

    vector <ld> x(n), y(n);
    for(ll i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        x[i] = logl(x[i]);
        y[i] = logl(y[i]);
    }

    ld sigXY = 0;
    ld sigX = 0;
    ld sigY = 0;
    ld sigXsq = 0;

    for(ll i = 0; i < n; ++i) {
        sigX += x[i];
        sigY += y[i];
        sigXY += x[i] * y[i];
        sigXsq += x[i] * x[i];
    }

    ld b = (n * sigXY - sigX * sigY) / (n * sigXsq - sigX * sigX);
    ld a = expl((sigY - b * sigX) / n);

    ld xNew;
    cin >> xNew;

    cout << "f(x) = " << a << "(x^" << b << ")\n";
    cout << "f(" << xNew << ") = " << a * powl(xNew, b) << '\n';
}

/*
5
1 50
2 80
3 96
4 120
5 145
6

*/