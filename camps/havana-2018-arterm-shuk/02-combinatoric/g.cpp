#include <bits/stdc++.h>
const int MAX = 300 + 10;
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
int bin[MAX][MAX];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int n ;
	vector<int> g(MAX);
	g[0] = 1;
	g[1] = 1;
	for(int i = 0; i <MAX; i++){
		bin[i][0] = 1;
	}
	for(int i = 1; i <MAX; i++)
		for(int j = i; j < MAX; j++){
			bin[j][i] = (bin[j - 1][i] + bin[j - 1][i- 1]) % MOD;
		}
	for(int i =2; i < MAX; i++){
		g[i] = powmod(2, i * (i - 1) / 2);
		for(int j  = 0; j <= i - 2; j++){
			int term = mul(bin[i - 1][j], powmod(2, (i - 1 - j) * (i - 1 - j - 1) / 2));
			term = mul(term, g[j + 1]);

			g[i ] = (g[i] - term + MOD) % MOD;
		}
	}
	while(cin >> n){
		cout << g[n] << endl;
	}


}
