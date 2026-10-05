#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

int main() {
    ll n;
    cin >> n;

    vector <ld> x(n), y(n);
    for(ll i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
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
    ld a = (sigY - b * sigX) / n;

    ld xNew;
    cin >> xNew;

    cout << "f(x) = " << a << " + " << b << "x\n"; 
    cout << "f(" << xNew << ") = " << a + b * xNew << '\n';
}

/*
7
1 3
2 4
3 4
4 5
5 8
6 9
7 10
10

*/