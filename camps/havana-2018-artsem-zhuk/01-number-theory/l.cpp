#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 gcd(int64 a, int64 b, int64 &x, int64 &y){
    if (b == 0)
        return x = 1, y = 0, a;
    int64 r = gcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}

int64 inverse(int64 a, int64 mod){
    int64 x, y;
    int64 g = gcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

int64 modpow(int64 a, int64 d, int64 mod){
    int64 c = 1;

    while (d){
        if (d & 1)
            c = c * a % mod;
        a = a * a % mod;
        d >>= 1;
    }

    return c;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 n, e, c, p, q;

    cin >> n >> e >> c;

    for (int64 i = 2; ; ++i){
        if (n % i == 0){
            p = i;
            q = n / i;
            break;
        }
    }

    int64 mod = (p - 1) * (q - 1);

    int64 d = inverse(e, mod);

    int64 m = modpow(c, d, n);

    cout << m << endl;

    return 0;
}