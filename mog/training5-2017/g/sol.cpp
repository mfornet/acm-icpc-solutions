#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int64> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct edge{
    int to;
    int64 t;
};

vector<edge> adj[maxn];

vector<int64> dijkstra(int size, int source){
    vector<int64> dist(size, oo);

    dist[source] = 0;

    priority_queue<pair<int64,int>> pq;
    pq.push({0, source});

    while (!pq.empty()){
        auto cur = pq.top(); pq.pop();

        int64 d = -cur.first;
        int u = cur.second;

        if (dist[u] < d) continue;

        for (auto e : adj[u]){
            int64 nd = d + e.t;
            if (nd < dist[e.to]){
                dist[e.to] = nd;
                pq.push({-dist[e.to], e.to});
            }
        }
    }

    return dist;
}

struct graph
{
	int n;
	vector<vector<int>> adj;

	graph(int n) : n(n), adj(n) {}

	void add_edge(int u, int v)
	{
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int add_node()
	{
		adj.push_back({});
		return n++;
	}

	vector<int>& operator[](int u) { return adj[u]; }
};

vector<int> biconnected_components(graph &adj)
{
	int n = adj.n;

	vector<int> num(n), low(n), art(n), stk;
	vector<vector<int>> comps;

	function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
	{
		num[u] = low[u] = ++t;
		stk.push_back(u);

		for (int v : adj[u]) if (v != p)
		{
			if (!num[v])
			{
				dfs(v, u, t);
				low[u] = min(low[u], low[v]);

				if (low[v] >= num[u])
				{
					art[u] = (num[u] > 1 || num[v] > 2);

					comps.push_back({u});
					while (comps.back().back() != v)
						comps.back().push_back(stk.back()), 
						stk.pop_back();
				}
			}
			else low[u] = min(low[u], num[v]);
		}
	};

	for (int u = 0, t; u < n; ++u)
		if (!num[u]) dfs(u, -1, t = 0);

	return art;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; ++i){
        int u, v;
        int64 w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int s, t; cin >> s >> t;

    vector<int64> distS = dijkstra(n, s);
    vector<int64> distT = dijkstra(n, t);

    int64 distance = distS[t];

    graph g(n);

    for (int i = 0; i < n; ++i){
        for (auto e : adj[i]){
            if (distS[i] + e.t + distT[e.to] == distance){
                g.add_edge(i, e.to);
//                cout << "edge: " << i << " " << e.to << endl;
            }
        }
    }

    auto answer = biconnected_components(g);
    answer[s] = true;
    answer[t] = true;

    bool start = true;

    for (int i = 0; i < n; ++i){
        if (answer[i]){
            if (start) start = false;
            else cout << " ";
            cout << i;
        }
    }

    cout << endl;

    return 0;
}
