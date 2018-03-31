#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef vector<int> pol;

const int mod = 7340033;
const int root = 3;

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

void sub(int &a, int b){
    a -= b;
    if (a < 0)
        a += mod;
}

int modpow(int a, int n){
    int b = 1;
    while (n){
        if (n & 1)
            b = 1LL * b * a % mod;
        n >>= 1;
        a = 1LL * a * a % mod;
    }
    return b;
}

void fft(pol &x, int sign = +1){
    int n = x.size();

    int h = modpow(root, (mod - 1) / n);
    if (sign < 0) h = modpow(h, mod - 2);

    for (int i = 0, j = 1; j < n - 1; ++j){
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(x[i], x[j]);
    }

    for (int m = 1; m < n; m *= 2){
        int w = 1, wk = modpow(h, n / (2 * m));
        for (int i = 0; i < m; ++i){
            for (int j = i; j < n; j += 2 * m)
            {
                int u = x[j], d = 1LL * x[j + m] * w % mod;
                if ((x[j] = u + d) >= mod)
                    x[j] -= mod;
                if ((x[j + m] = u - d) < 0)
                    x[j + m] += mod;
            }
            w = 1LL * w * wk % mod;
        }
    }
    if (sign < 0){
        int n_inv = modpow(n, mod - 2);
        for (auto &a : x)
            a = 1LL * a * n_inv % mod;
    }
}

pol inverse(pol &a){
    assert(a[0] != 0);

    pol r(1, modpow(a[0], mod - 2));

    while (r.size() < a.size()){
        int csize = 2 * (int)r.size();

        r.resize(csize);
        pol tr = r;
        tr.resize(2 * csize);
        pol tf(2 * csize);
        for (int i = 0; i < csize; ++i)
            tf[i] = a[i];

        fft(tr, +1);
        fft(tf, +1);

        for (int i = 0; i < 2 * csize; ++i)
            tr[i] = 1LL * tr[i] * tr[i] % mod * tf[i] % mod;

        fft(tr, -1);

        for (int i = 0; i < csize; ++i){
            add(r[i], r[i]);
            sub(r[i], tr[i]);
        }
    }

    return r;
}

pol multiply(pol a, pol b){
    int sz = 2 * (int)a.size();

    a.resize(sz); fft(a, +1);
    b.resize(sz); fft(b, +1);

    for (int i = 0; i < sz; ++i)
        a[i] = 1LL * a[i] * b[i] % mod;

    fft(a, -1);
    return a;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    pol P(s.length());

    for (int i = 0; i < (int)s.length(); ++i)
        P[i] = s[i] - '0';

    int size = 1;
    while (size <= P.size())
        size *= 2;
    size *= 2;
    P.resize(size);

    pol S = multiply(P, P);

    int64 answer = 0;

    for (int i = 0; i < (int)S.size(); i += 2){
        if (i & 1) 
            continue;
        if (P[i / 2])
            answer += S[i] - 1;
    }

    cout << (answer >> 1) << endl;

    return 0;
}