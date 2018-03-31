#include <bits/stdc++.h>
const int MAX = 3000 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
const int MOD = 1e9 + 7;
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
int bin[MAX][MAX];
int a[MAX];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'

	for(int i = 0; i <MAX; i++){
		bin[i][0] = 1;
	}
	for(int i = 1; i <MAX; i++)
		for(int j = i; j < MAX; j++){
			bin[j][i] = (bin[j - 1][i] + bin[j - 1][i- 1]) % MOD;
		}
	int n ; cin >> n;
	int s = 0;
	for(int i = 0; i< n; i++)cin >> a[i], s+= a[i];
	vector<int> kk(MAX, 1);

	for(int j = 0; j <= s; j++ ){
		for(int i = 0; i <n; i++){
			kk[j] = mul(kk[j], bin[a[i] + j][j]);
		}
	}
	int ans = 0;
	for(int t = 1; t <= s; t++){
		int cur = kk[t - 1];
		for(int i = 1; i <= t - 1; i++){
			cur = (cur + ((i & 1 ? -1 : 1) * mul(bin[t][i], kk[t - i - 1]) + MOD) % MOD) % MOD;
		}
		ans = (ans + cur) % MOD;
	}
	cout << ans;


}
