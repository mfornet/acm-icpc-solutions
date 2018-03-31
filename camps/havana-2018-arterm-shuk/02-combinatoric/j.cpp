#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int p = 1000000007;

int modpow(int a, int n, int m){
    int b = 1;

    while (n){
        if (n & 1)
            b = 1LL * a * b % m;
        a = 1LL * a * a % m;
        n >>= 1;
    }

    return b;
}

int mod(int x){
    while (x < 0)
        x += p;
    while (x >= p)
        x -= p;
    return x;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> P(n), Q(n);

    for (int i = 0; i < n; ++i){
        int a, b;
        cin >> a >> b;
        int c = modpow(b, p - 2, p);

        P[i] = 1LL * a * c % p;
        Q[i] = 1LL * (b - a) * c % p;
    }

    int a = 0, b = 0;

    for (int i = n - 1; i >= 0; --i){
        a = (1 + 1LL * P[i] * a) % p;
        b = (1LL * P[i] * b % p + Q[i]) % p;
    }

    int x0 = 1LL * a * modpow(mod(1 - b), p - 2, p) % p;

    cout << x0 << endl;

    return 0;
}