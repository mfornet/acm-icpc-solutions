#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000 + 10;

const int mod = 1000000009;

int s[maxn];

int modpow(int a, int n, int m){
    int b = 1;

    while (n){
        if (n & 1)
            b = 1LL * b * a % m;
        a = 1LL * a * a % m;
        n >>= 1;
    }

    return b;
}

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int pascal[maxn][maxn];

int solve(int n, int k){
    s[0] = n;

    for (int a = 1; a <= k; ++a){
        int inv = modpow(a+1,mod-2,mod);
        int c = modpow(n+1,a+1,mod) - 1;
        int t = 0;

        for (int r = 0; r < a; ++r)
            add(t, 1LL * pascal[a+1][r] * s[r] % mod);

        s[a] = c - t;
        if (s[a] < 0) s[a] += mod;
        s[a] = 1LL * s[a] * inv % mod;
    }

    return s[k];
}

int brute(int n, int k){
    int ans = 0;

    for (int i = 1; i <= n; ++i)
        add(ans, modpow(i, k, mod));

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < maxn; ++i){
        pascal[i][0] = 1;

        for (int j = 1; j <= i; ++j){
            pascal[i][j] = pascal[i - 1][j];
            add(pascal[i][j], pascal[i-1][j - 1]);
        }
    }

    int q; cin >> q;

    while (q-->0){
        int64 _n;

        int n, k;

        cin >> _n >> k;

        if (_n <= 2){
            cout << 0 << endl;
            continue;
        }

        n = (_n - 1) % mod;

        cout << (solve(n, k) - 1 + mod) % mod << endl;
        // cout.flush();
    }

    return 0;
}