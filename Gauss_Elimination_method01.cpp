#include <bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;

const ld eps = 1e-9;

int main() {
    ll n;
    cin >> n;

    vector <vector <ld>> aug(n, vector <ld> (n + 1, 0));
    for(auto &vec : aug) {
        for(auto &val : vec) {
            cin >> val;
        }
    }

    ll rank = 0;
    for(ll col = 0, row = 0; col < n && row < n; ++col) {
        ld mx = abs(aug[row][col]);
        ll idx = row;
        for(ll i = row + 1; i < n; ++i) {
            if(mx < abs(aug[i][col])) {
                mx = abs(aug[i][col]);
                idx = i;
            }
        }

        if(mx < eps) {
            continue;
        }

        swap(aug[row], aug[idx]);

        for(ll i = row + 1; i < n; ++i) {
            ld factor = aug[i][col] / aug[row][col];
            aug[i][col] = 0;
            for(ll j = col + 1; j <= n; ++j) {
                aug[i][j] -= aug[row][j] * factor;
            }
        }

        ++row;
        ++rank;
    }

    if(rank == n) {
        cout << "The system has a unique solution\n";

        vector <ld> x(n, 0);
        for(ll i = n - 1; i > -1; --i) {
            ld sum = 0;
            for(ll j = n - 1; j > i; --j) {
                sum += aug[i][j] * x[j];
            }

            x[i] = (aug[i][n] - sum) / aug[i][i];
        }

        for(auto &val : x) {
            cout << val << ' ';
        }

        cout << '\n';
    }
    else {
        bool incon = false;
        for(ll i = 0; i < n; ++i) {
            bool flag = true;
            for(ll j = 0; j < n; ++j) {
                if(abs(aug[i][j] >= eps)) {
                    flag = false;
                    break;
                }
            }

            if(flag && abs(aug[i][n]) >= eps) {
                incon = true;
                break;
            }
        }

        if(incon) {
            cout << "The system has no solution\n";
        }
        else {
            cout << "The system has infinite solutions\n";
        }
    }
}

/*
3
2 3 1 9
1 2 3 6
3 1 2 8

4
4 5 6 7 12
3 7 9 -2 45
10 -3 -5 -6 1
0 8 8 -1 -6

4
4 5 6 7 12
3 7 9 -2 45
10 -3 -5 -6 1
-20 6 10 12 -6

3
0 1 1 3
2 3 5 4
7 6 -2 5

2
1 1 2
2 2 4

2
1 1 2
2 2 5

*/