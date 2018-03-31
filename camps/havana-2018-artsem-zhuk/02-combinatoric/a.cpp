#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	vector<i64> fac(1, 1);
	string s; cin >> s;
	int n = s.size();
	for(int i = 1; i <= n;i++)fac.push_back(fac.back() * i);
	vector<int> uf(26);
	for(int i = 0; i< n; i++)
		uf[s[i] - 'a']++;
	i64 ans = fac[n];
	for(int i = 0; i < 26; i++)ans /= fac[uf[i]];
	cout << ans << endl;


}
