#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const ld eps = 1e-12;

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

        cout << "\nEquation:\n";

        bool isFirstTerm = true;

        if(abs(coeff[0]) >= eps) {
            cout << coeff[0];
            isFirstTerm = false;
        }

        for(ll i = 1; i < n; ++i) {
            if(abs(coeff[i]) < eps) {
                continue;
            }

            if(!isFirstTerm) {
                if(coeff[i] > 0) {
                    cout << "+";
                }
            }
            
            cout << coeff[i];
            isFirstTerm = false;

            for(ll j = 0; j < i; ++j) {
                ld val = -xy[0].first - h * j;
                
                if(abs(val) < eps) {
                    cout << "x";
                    continue;
                }

                cout << "(x";

                if(val > 0) {
                    cout << "+";
                }
                
                cout << val << ")";
            }
        }

        cout << "\n";

        ld ans = coeff[0];
        ld pro = 1;
        for(ll i = 1; i < n; ++i) {
            pro *= x - xy[0].first - h * (i - 1);
            ans += pro * coeff[i];
        }

        cout << "\nf(x) = " << ans << "\n\n";

        pro = 1;
        for(ll i = 0; i < n; ++i) {
            pro *= x - xy[0].first - h * i;
        }

        ld xNew, yNew;
        cin >> xNew >> yNew;

        xy.push_back({xNew, yNew});
        ++n;

        sort(xy.begin(), xy.end());

        vector <vector <ld>> deltaYNew(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaYNew[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = 0; j < n - i; ++j) {
                deltaYNew[i][j] = deltaYNew[i - 1][j + 1] - deltaYNew[i - 1][j];
            }
        }

        vector <ld> coeffNew(n);
        coeffNew[0] = deltaYNew[0][0];
        fact = 1;
        hp = 1;
        for(ll i = 1; i < n; ++i) {
            fact *= i;
            hp *= h;
            coeffNew[i] = deltaYNew[i][0] / (fact * hp);
        }
        
        ld err = coeffNew[n - 1] * pro;

        cout << "\nError: " << err << '\n';
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

        cout << "\nEquation:\n";
        
        bool isFirstTerm = true;

        if(abs(coeff[0]) >= eps) {
            cout << coeff[0];
            isFirstTerm = false;
        }

        for(ll i = 1; i < n; ++i) {
            if(abs(coeff[i]) < eps) {
                continue;
            }

            if(!isFirstTerm) {
                if(coeff[i] > 0) {
                    cout << "+";
                }
            }
            
            cout << coeff[i];
            isFirstTerm = false;

            for(ll j = 0; j < i; ++j) {
                ld val = -xy[n - 1].first + h * j;
                
                if(abs(val) < eps) {
                    cout << "x";
                    continue;
                }

                cout << "(x";

                if(val > 0) {
                    cout << "+";
                }
                
                cout << val << ")";
            }
        }

        cout << "\n";

        ld ans = coeff[0];
        ld pro = 1;
        for(ll i = 1; i < n; ++i) {
            pro *= x - xy[n - 1].first + h * (i - 1);
            ans += pro * coeff[i];
        }

        cout << "\nf(x) = " << ans << "\n\n";

        pro = 1;
        for(ll i = 0; i < n; ++i) {
            pro *= x - xy[n - 1].first + h * i;
        }

        ld xNew, yNew;
        cin >> xNew >> yNew;

        xy.push_back({xNew, yNew});
        ++n;

        sort(xy.begin(), xy.end());

        vector <vector <ld>> deltaYNew(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaYNew[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = i; j < n; ++j) {
                deltaYNew[i][j] = deltaYNew[i - 1][j] - deltaYNew[i - 1][j - 1];
            }
        }

        vector <ld> coeffNew(n);
        coeffNew[0] = deltaYNew[0][n - 1];
        fact = 1;
        hp = 1;
        for(ll i = 1; i < n; ++i) {
            fact *= i;
            hp *= h;
            coeffNew[i] = deltaYNew[i][n - 1] / (fact * hp);
        }

        ld err = coeffNew[n - 1] * pro;

        cout << "\nError: " << err << '\n';
    }
}

/*
4
3 180
5 150
7 120
9 90
4
11 60

5
24 28.06
28 30.19
32 32.75
36 34.94
40 40
33
20 25.12

3
1 1
2 8
3 27
2.5
4 64

*/