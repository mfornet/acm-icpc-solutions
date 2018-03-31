#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
const int MOD = 998244353;
#define mul(a, b) ((i64)(a) * (b) % MOD)

int powmod(int a, int n){
	int s = 1;
	while(n > 0){
		if(n & 1)s = mul(a, s);
		a = mul(a, a);
		n >>= 1;
	}
	return s;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int n; cin >> n;
	vector<int> fn(n + 1, 1);
	fn[n] = 1;
	int facn = 1;
	for(int i = n - 1; i>= 0; i--){
		fn[i] = mul(fn[i + 1], i + 1);
		facn = mul(facn, i + 1);
	}
	int ans = 0;
	for(int i = 1; i<=n; i++){
		ans = (ans + (i & 1 ? -1 : 1) * mul(powmod(2, n - i), fn[i]) + MOD) % MOD;
	}
	ans = (mul(powmod(2, n), facn) + ans) % MOD;
	cout << ans;


}
