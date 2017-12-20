#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000 + 10;

map<pii,bool> memo;

bool can(int n, int r){
	if (r == 1) return true;
	if (r <= 0 || n == 0) return false;
	if (n * (n - 1) / 2 < r) return false;

	pii c(n, r);

	if (memo.find(c) != memo.end())
		return memo[c];

	bool &ans = memo[c];

	for (int i = 1; i <= n && !ans; ++i){
		if (can(n - i, r - i * (n - i)))
			ans = true;
	}

	return ans;
}

// R + I + 1 = F
void solve(){
	int F; cin >> F;

	int R = 0;

	while (!can(R, F - 1 - R))
		R++;


}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;

    cin >> t;

    while (t--){
    	solve();
    }

    return 0;
}
