#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

const int maxn = 100000;

vector<int> adj[maxn];
vector<int> lst[maxn][31];
int par[maxn];

void dfs(int s, int p){
	for (int i = 0; i < (int)adj[s].size(); ++i){
		int u = adj[s][i];
		if (u == p) continue;
		par[u] = s;
		dfs(u, s);
	}
}

int part(int u, int d, int idx){
	return upper_bound(lst[u][d].begin(), lst[u][d].end(), idx) - lst[u][d].begin();
}

int total(int u, int d, int idx){
	int answer = part(u, d, idx);

	while (true){
		int v = par[u]; d--;

		if (v && d >= 0){
			answer += part(v, d, idx) - (d ? part(u, d - 1, idx) : 0);
			u = v;
		}
		else break;
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n; cin >> n;

	for (int i = 0; i < n - 1; ++i){
		int u, v; cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 0);

	for (int u = 1; u <= n; ++u){
		lst[u][0].push_back(u);

		int v = par[u];

		for (int j = 1; j <= 30 && v; ++j){
			lst[v][j].push_back(u);
			v = par[v];
		}
	}

	for (int u = 1; u <= n; ++u)
		for (int i = 0; i <= 30; ++i)
			sort(lst[u][i].begin(), lst[u][i].end());

	int q; cin >> q;

	while (q-->0){
		int c, d, k;
		cin >> c >> d >> k;

		int lo = 0, hi = n;

		while (lo + 1 < hi){
			int mid = (lo + hi) >> 1;

			int cur = total(c, d, mid);

			if (cur < k) lo = mid;
			else hi = mid;
		}

		cout << hi << endl;
	}


	return 0;
}
