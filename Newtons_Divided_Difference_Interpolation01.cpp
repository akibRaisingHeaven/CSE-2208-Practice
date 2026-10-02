#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const ld eps = 1e-12;

int main() {
    ll n;
    cin >> n;

    vector <pair <ld, ld>> xfx(n);
    for(auto &[x, fx] : xfx) {
        cin >> x >> fx;
    }

    ld x;
    cin >> x;

    vector <vector <ld>> f(n, vector <ld> (n, 0));
    for(ll i = 0; i < n; ++i) {
        f[0][i] = xfx[i].second;
    }

    for(ll i = 1; i < n; ++i) {
        for(ll j = 0; j < n - i; ++j) {
            f[i][j] = (f[i - 1][j + 1] - f[i - 1][j]) / (xfx[j + i].first - xfx[j].first);
        }
    }

    cout << "\nEquation:\n";
    
    bool isFirstTerm = true;
    if(abs(f[0][0]) >= eps) {
        cout << f[0][0];
        isFirstTerm = false;
    }

    for(ll i = 1; i < n; ++i) {
        if(abs(f[i][0]) < eps) {
            continue;
        }

        if(!isFirstTerm) {
            if(f[i][0] > 0) {
                cout << "+";
            }
        }

        cout << f[i][0];
        isFirstTerm = false;

        for(ll j = 0; j < i; ++j) {
            if(abs(xfx[j].first) < eps) {
                cout << "x";
                continue;
            }

            cout << "(x";

            if(xfx[j].first < 0) {
                cout << "+";
            }

            cout << -xfx[j].first << ")";
        }
    }

    cout << '\n';

    ld ans = f[0][0];
    ld val = 1;
    for(ll i = 1; i < n; ++i) {
        val *= (x - xfx[i - 1].first);
        ans += f[i][0] * val;
    }

    cout << "\nf(x) = " << ans << "\n\n";

    ld xNew, fxNew;
    cin >> xNew >> fxNew;

    xfx.push_back({xNew, fxNew});
    ++n;

    vector <vector <ld>> fNew(n, vector <ld> (n, 0));
    for(ll i = 0; i < n; ++i) {
        fNew[0][i] = xfx[i].second;
    }

    for(ll i = 1; i < n; ++i) {
        for(ll j = 0; j < n - i; ++j) {
            fNew[i][j] = (fNew[i - 1][j + 1] - fNew[i - 1][j]) / (xfx[j + i].first - xfx[j].first);
        }
    }

    ld pro = 1;
    for(ll i = 0; i < n - 1; ++i) {
        pro *= x - xfx[i].first;
    }

    ld err = pro * fNew[n - 1][0];
    cout << "Error: " << err << '\n';
}

/*
3
1 0
4 1.386294
6 1.79175
2
5 1.609438

*/