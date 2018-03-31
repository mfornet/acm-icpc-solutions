#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int P = 2016 * 2017 + 1;
const int g = 5;

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

    int n; cin >> n;

    int64 sol = 0;

    for (int i = 0; i < n; ++i){
        int64 c; cin >> c;

        if (i == 0){
            sol = c * n % P;
            continue;
        }

        int64 cur =  c * (modpow(g, 1LL * i * n, P) - 1) % P * 
                        modpow(modpow(g, i, P) - 1, P - 2, P) % P;

        sol = (sol + cur) % P;
    }

    cout << sol << endl;

    return 0;
}