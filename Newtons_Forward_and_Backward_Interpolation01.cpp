#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

int main() {
    ll n;
    cin >> n;

    vector <pair <ld, ld>> xy(n);
    for(auto &[x, y] : xy) {
        cin >> x >> y;
    }

    ld x;
    cin >> x;

    sort(xy.begin(), xy.end());
    
    ld diff1 = abs(x - xy[0].first);
    ld diff2 = abs(x - xy[n - 1].first);
    ld h = xy[1].first - xy[0].first;

    if(diff1 <= diff2) {
        //Forward Interpolation;
        vector <vector <ld>> deltaY(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaY[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = 0; j < n - i; ++j) {
                deltaY[i][j] = deltaY[i - 1][j + 1] - deltaY[i - 1][j];
            }
        }

        vector <ld> coeff(n);
        coeff[0] = deltaY[0][0];
        ld fact = 1;
        ld hp = 1;
        for(ll i = 1; i < n; ++i) {
            fact *= i;
            hp *= h;
            coeff[i] = deltaY[i][0] / (fact * hp);
        }

        cout << "The interpolated function:\n";
        cout << coeff[0];
        for(ll i = 1; i < n; ++i) {
            if(coeff[i] >= 0) {
                cout << "+";
            }
            
            cout << coeff[i];
            for(ll j = 0; j < i; ++j) {
                cout << "(x";
                ld val = -xy[0].first - h * j;
                
                if(val >= 0) {
                    cout << "+";
                }
                
                cout << val << ")";
            }
        }

        cout << "\n";

        ld ans = coeff[0];
        for(ll i = 1; i < n; ++i) {
            ld pro = 1;
            for(ll j = 0; j < i; ++j) {
                pro *= x - xy[0].first - h * j;
            }

            ans += pro * coeff[i];
        }

        cout << "f(x) = " << ans << '\n';
    }
    else {
        //Backward Interpolation;
        vector <vector <ld>> deltaY(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaY[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = i; j < n; ++j) {
                deltaY[i][j] = deltaY[i - 1][j] - deltaY[i - 1][j - 1];
            }
        }

        vector <ld> coeff(n);
        coeff[0] = deltaY[0][n - 1];
        ld fact = 1;
        ld hp = 1;
        for(ll i = 1; i < n; ++i) {
            fact *= i;
            hp *= h;
            coeff[i] = deltaY[i][n - 1] / (fact * hp);
        }

        cout << "The interpolated function:\n";
        cout << coeff[0];
        for(ll i = 1; i < n; ++i) {
            if(coeff[i] >= 0) {
                cout << "+";
            }
            
            cout << coeff[i];
            for(ll j = 0; j < i; ++j) {
                cout << "(x";
                ld val = -xy[n - 1].first + h * j;
                
                if(val >= 0) {
                    cout << "+";
                }
                
                cout << val << ")";
            }
        }

        cout << "\n";

        ld ans = coeff[0];
        for(ll i = 1; i < n; ++i) {
            ld pro = 1;
            for(ll j = 0; j < i; ++j) {
                pro *= x - xy[n - 1].first + h * j;
            }

            ans += pro * coeff[i];
        }

        cout << "f(x) = " << ans << '\n';
    }
}

/*
4
3 180
5 150
7 120
9 90
4

5
24 28.06
28 30.19
32 32.75
36 34.94
40 40
33

*/