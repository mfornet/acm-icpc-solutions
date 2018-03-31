#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef pair<int,int> pii;

const int maxn = 100000 + 10;

vector<int> adj[maxn];
int A[maxn];
int B[maxn];

pair<int,int> dfs(int s, int p, int C[maxn]){
	pii ans(s, 0);

	for (int i = 0; i < (int)adj[s].size(); ++i){
		int u = adj[s][i];
		if (u == p) continue;

		C[u] = C[s] + 1;
		pii cur = dfs(u, s, C);

		if (cur.second + 1 > ans.second){
			ans = pair<int,int>(cur.first, cur.second + 1);
		}
	}

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n; cin >> n;

	for (int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	pii x = dfs(1, -1, A);
	A[x.first] = 0;

	pii y = dfs(x.first, -1, A);
	B[y.first] = 0;
	pii z = dfs(y.first, -1, B);

	for (int i = 1; i <= n; ++i){
		cout << max(A[i], B[i]) << " \n"[i == n];
	}




	return 0;
}
