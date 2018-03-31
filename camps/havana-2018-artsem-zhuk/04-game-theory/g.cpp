#include <bits/stdc++.h>
const int MAX = 1e6 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
int ar[MAX];
int dp[MAX];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int k, m;
	cin >> k;
	for(int i = 0; i< k; i++)cin >> ar[i];
	cin >> m;
	dp[0] = 0;
	for(int i = 1; i < MAX; i++){
		bool ok = false;
		for(int j = 0; j < k ; j++){
			if(ar[j] <= i && dp[i - ar[j]] == 0){
				ok = true; break;
			}
		}
		if(ok)dp[i] = 1;
	}



	for(int i = 0; i <m ;i++){
		int a;cin >> a;
		cout << ((dp[a] == 0) ? "Second" : "First") << endl;
	}



}
