#include <bits/stdc++.h>
#define ll long long
#define ld long double 
using namespace std;

const ld eps = 1e-12;

int main() {
    ll n, m; //m-degree polynomial
    cin >> n >> m;
    ++m;

    vector <ld> x(n), y(n);
    for(ll i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    ld xNew;
    cin >> xNew;

    vector <vector <ld>> aug(m, vector <ld> (m + 1, 0));
    for(ll j = 0; j < m; ++j) {
        for(ll i = 0; i < n; ++i) {
            for(ll k = 0; k < m; ++k) {
                aug[j][k] += powl(x[i], j + k);
            }

            aug[j][m] += powl(x[i], j) * y[i];
        }
    }

    ll rank = 0;
    for(ll col = 0, row = 0; col < m; ++col) {
        ll mxRow = row;
        for(ll i = row + 1; i < m; ++i) {
            if(abs(aug[i][col]) > abs(aug[mxRow][col])) {
                mxRow = i;
            }
        }

        if(abs(aug[mxRow][col]) < eps) {
            continue;
        }

        if(mxRow != row) {
            swap(aug[row], aug[mxRow]);
        }

        for(ll i = row + 1; i < m; ++i) {
            ld factor = aug[i][col] / aug[row][col];
            aug[i][col] = 0;
            for(ll j = col + 1; j <= m; ++j) {
                aug[i][j] -= aug[row][j] * factor;
            }
        }

        ++row;
        ++rank;
    }

    if(rank != m) {
        cout << m << "-degree polynomial is not possible.\n";
    }
    else {
        vector <ld> a(m, 0);
        for(ll i = m - 1; i > -1; --i) {
            ld sum = 0;
            for(ll j = m - 1; j > i; --j) {
                sum += aug[i][j] * a[j];
            }

            a[i] = (aug[i][m] - sum) / aug[i][i];
        }

        cout << "f(x) = ";
        
        bool firstTermPrinted = false;
        if(abs(a[0]) >= eps) {
            cout << a[0];
            firstTermPrinted = true;
        }
        
        for(ll i = 1; i < m; ++i) {
            if(firstTermPrinted) {
                if(abs(a[i]) < eps) {
                    continue;
                }

                if(a[i] > 0) {
                    cout << "+";
                }

                cout << a[i] << 'x';

                if(i > 1) {
                    cout << '^' << i;
                }
            }
            else {
                if(abs(a[i]) < eps) {
                    continue;
                }

                firstTermPrinted = true;
                
                cout << a[i] << 'x';

                if(i > 1) {
                    cout << '^' << i;
                }
            }
        }

        cout << '\n';

        ld ans = 0;
        for(ll i = 0; i < m; ++i) {
            ans += a[i] * powl(xNew, i);
        }

        cout << "f(" << xNew << ") = " << ans << '\n';
    }
}

/*
5 2
1 6
2 11
3 18
4 27
5 38
6

*/