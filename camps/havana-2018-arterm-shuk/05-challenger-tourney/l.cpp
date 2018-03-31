#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

const int maxn = 100000 + 10;

vector< pair<int,int64> > adj[maxn];
int64 dist[maxn];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back(make_pair(v, w));
	}

	memset(dist, 0x3f, sizeof dist);

	priority_queue< pair<int64,int> > pq;
	dist[1] = 0;
	pq.push(make_pair(0, 1));

	while (!pq.empty()){
		pair<int64,int> cur = pq.top(); pq.pop();

		int64 t = -cur.first;
		int u = cur.second;

		if (dist[u] < t) continue;

		for (int i = 0; i < (int)adj[u].size(); ++i){
			int v = adj[u][i].first;
			int64 c = adj[u][i].second;

			if (t + c < dist[v]){
				dist[v] = t + c;
				pq.push(make_pair(-dist[v], v));
			}
		}
	}

	if (dist[n] == 0x3f3f3f3f3f3f3f3f)
		cout << "Infinity" << endl;
	else
		cout << dist[n] << endl;

	return 0;
}
