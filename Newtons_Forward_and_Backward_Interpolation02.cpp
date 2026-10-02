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
        ld u = (x - xy[0].first) / h;

        vector <vector <ld>> deltaY(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaY[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = 0; j < n - i; ++j) {
                deltaY[i][j] = deltaY[i - 1][j + 1] - deltaY[i - 1][j];
            }
        }

        ld ans = deltaY[0][0];
        ld val = 1;
        for(ll i = 1; i < n; ++i) {
            val *= (u - i + 1) / i;
            ans += deltaY[i][0] * val;
        }

        cout << "\nf(x) = " << ans << "\n\n";

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

        val *= (u - n + 2) / (n - 1);

        ld err = val * deltaYNew[n - 1][0];

        cout << "\nError: " << err << '\n';
    }
    else {
        //Backward Interpolation;
        ld v = (x - xy[n - 1].first) / h;

        vector <vector <ld>> deltaY(n, vector <ld> (n, 0));
        for(ll i = 0; i < n; ++i) {
            deltaY[0][i] = xy[i].second;
        }

        for(ll i = 1; i < n; ++i) {
            for(ll j = i; j < n; ++j) {
                deltaY[i][j] = deltaY[i - 1][j] - deltaY[i - 1][j - 1];
            }
        }

        ld ans = deltaY[0][n - 1];
        ld val = 1;
        for(ll i = 1; i < n; ++i) {
            val *= (v + i - 1) / i;
            ans += deltaY[i][n - 1] * val;
        }

        cout << "\nf(x) = " << ans << "\n\n";

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

        val *= (v + n - 2) / (n - 1);

        ld err = val * deltaYNew[n - 1][n - 1];

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