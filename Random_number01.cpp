#include <bits/stdc++.h>
using namespace std;

int main() {
    random_device rd;

    mt19937_64 gen(rd());

    uniform_int_distribution <long long> lld(0, 100);

    long long n = lld(gen);

    cout << n << '\n';
}