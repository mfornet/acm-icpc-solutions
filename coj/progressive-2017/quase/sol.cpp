#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000009;
const int base = 37;
const int maxn = 100001;

int pw[ maxn ];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, q, l;

	pw[0] = 1;
	for (int i = 1; i < maxn; ++i)
		pw[i] = 1LL * pw[i - 1] * base % mod;
	
	while (cin >> n >> q >> l){
		vector<map<int,int>> id(l);

		for (int i = 0; i < n; ++i){
			string s; cin >> s;
			vector<int> pref(l + 1);
			vector<int> suff(l + 1);

			for (int i = 1; i <= l; ++i){
				pref[i] = (1LL * pref[i - 1] * base + s[i - 1] - '0' + 1) % mod;
				suff[i] = (suff[i - 1] + 1LL * pw[i - 1] * (s[l - i] - '0' + 1)) % mod; 
			}

			for (int i = 1; i <= l; ++i)
				id[i - 1][ (1LL * pref[i - 1] * pw[l - i] % mod + suff[l - i]) % mod ]++;
		}

		while (q--){
			int answer = 0;
			string s; cin >> s;

			vector<int> pref(l + 1), suff(l + 1);

			for (int i = 1; i <= l; ++i){
				pref[i] = (1LL * pref[i - 1] * base + s[i - 1] - '0' + 1) % mod;
				suff[i] = (suff[i - 1] + 1LL * pw[i - 1] * (s[l - i] - '0' + 1)) % mod;
			}

			for (int i = 1; i <= l; ++i){
				int h = (1LL * pref[i - 1] * pw[l - i] % mod + suff[l - i]) % mod;
				if (id[i - 1].find(h) != id[i - 1].end()) answer += id[i - 1][ h ];
			}
			
			cout << answer << '\n';
		}
	}

	return 0;
}
