#include <bits/stdc++.h>
const int MAXA = 1e5 + 10;
const int MAXV = 1e5 + 10;
const int MAXS = 50 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
const int MOD = 7340033;
#define mul(a, b) ((i64)(a) * (b) % MOD)
int fac[MOD];
int ifac[MOD];


typedef vector<int> pol;

const int root = 3;

void add(int &a, int b){
    a += b;
    if (a >= MOD)
        a -= MOD;
}

void sub(int &a, int b){
    a -= b;
    if (a < 0)
        a += MOD;
}

int modpow(int a, int n){
    int b = 1;
    while (n){
        if (n & 1)
            b = 1LL * b * a % MOD;
        n >>= 1;
        a = 1LL * a * a % MOD;
    }
    return b;
}

void fft(pol &x, int sign = +1){
    int n = x.size();

    int h = modpow(root, (MOD - 1) / n);
    if (sign < 0) h = modpow(h, MOD - 2);

    for (int i = 0, j = 1; j < n - 1; ++j){
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(x[i], x[j]);
    }

    for (int m = 1; m < n; m *= 2){
        int w = 1, wk = modpow(h, n / (2 * m));
        for (int i = 0; i < m; ++i){
            for (int j = i; j < n; j += 2 * m)
            {
                int u = x[j], d = 1LL * x[j + m] * w % MOD;
                if ((x[j] = u + d) >= MOD)
                    x[j] -= MOD;
                if ((x[j + m] = u - d) < 0)
                    x[j + m] += MOD;
            }
            w = 1LL * w * wk % MOD;
        }
    }
    if (sign < 0){
        int n_inv = modpow(n, MOD - 2);
        for (auto &a : x)
            a = 1LL * a * n_inv % MOD;
    }
}
int bin(int a, int b){
	return mul(fac[a], mul(ifac[b], ifac[a - b]));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'

	fac[0] = 1;
	for(int i = 1; i < MOD; i++)
		fac[i] = mul(fac[i - 1], i);
	ifac[MOD - 1] = MOD-1; /// wilson!!! hahhahahha
	for(int i = MOD - 2; i>= 0; i--)
		ifac[i] = mul(i+1, ifac[i + 1]);


	int n , a, b, c; cin >> n >> a >> b >> c;

	int k = 2 * (a+ b);
	int size= 1;
	while(size <= k)size*= 2;
	size*= 2;
	pol P0(size), P1(size);
	for(int i = 0; i <= b; i ++){
		P0[2 * i] = bin(b, b - i);
	}
	for(int i = 0; i <= a; i++){
		P1[2 * i] = mul(((a - i) & 1 ? MOD-1 : 1), bin(a, a - i));
	}
	fft(P0, 1);
	fft(P1, 1);
	pol R(size);
	for(int i = 0; i < size; i++)R[i] = mul(P0[i], P1[i]);
	fft(R, -1);
	int ans = 0;
	for(int i = 0; i < size; i++){
		int t = (i + c - a - b + MOD) % MOD;
		ans = (ans + mul(R[i], modpow(t, n))) % MOD;
	}
	ans = mul(ans, modpow(modpow(2, a + b), MOD - 2));
	cout << ans;

}
