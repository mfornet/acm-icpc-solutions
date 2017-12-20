#include <bits/stdc++.h>

using namespace std;

const int maxn = 1001;
const int mod = 1000000009;

int pascal[maxn][maxn];
int dp[26][maxn][maxn];
int alpha[26];

int go(int p, int n, int k){
	if (p == 26)
		return n == 0 && k == 1;

	int &ans = dp[p][n][k];

	if (ans != -1) return ans;
	ans = 0;
	
	for (int i = 0; i <= min(alpha[p], n); ++i){
		int v = pascal[n][i];
		if (k % v == 0){
			ans += 1LL * go(p + 1, n - i, k / v) * pascal[ alpha[p] ][i] % mod;
			if (ans >= mod) ans -= mod;
		}
	}

	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < maxn; ++i){
		pascal[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			pascal[i][j] = (pascal[i - 1][j - 1] + pascal[i - 1][j]) % mod;
	}

	string s;
	int k;

	while (cin >> s >> k){
		memset(alpha, 0, sizeof alpha);
		memset(dp, -1, sizeof dp);
		for (auto c : s)
			alpha[ c - 'a' ]++;
		sort(alpha, alpha + 26);
		int n = (int)s.length();
		int answer = 0;
		for (int i = 0; i <= n; ++i)
			answer = (answer + go(0, i, k)) % mod;
		cout << answer << endl;
	}

	return 0;
}
