#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

template<typename flow_type>
struct dinic
{
	struct edge
	{
		size_t src, dst, rev;
		flow_type flow, cap;
	};

	int n;
	vector<vector<edge>> adj;

	dinic(int n) : n(n), adj(n), level(n), q(n), it(n) {}

	void add_edge(size_t src, size_t dst, flow_type cap, flow_type rcap = 0)
	{
		adj[src].push_back({src, dst, adj[dst].size(), 0, cap});
		if (src == dst) adj[src].back().rev++;
		adj[dst].push_back({dst, src, adj[src].size() - 1, 0, rcap});
	}

	vector<int> level, q, it;

	bool bfs(int source, int sink)
	{
		fill(level.begin(), level.end(), -1);
		for (int qf = level[q[0] = sink] = 0, qb = 1; qf < qb; ++qf)
		{
			sink = q[qf];
			for (edge &e : adj[sink])
			{
				edge &r = adj[e.dst][e.rev];
				if (r.flow < r.cap && level[e.dst] == -1)
					level[q[qb++] = e.dst] = 1 + level[sink];
			}
		}
		return level[source] != -1;
	}

	flow_type augment(int source, int sink, flow_type flow)
	{
		if (source == sink) return flow;
		for (; it[source] != adj[source].size(); ++it[source])
		{
			edge &e = adj[source][it[source]];
			if (e.flow < e.cap && level[e.dst] + 1 == level[source])
			{
				flow_type delta = augment(e.dst, sink, 
								  min(flow, e.cap - e.flow));
				if (delta > 0)
				{
					e.flow += delta;
					adj[e.dst][e.rev].flow -= delta;
					return delta;
				}
			}
		}
		return 0;
	}

	flow_type max_flow(int source, int sink)
	{
		for (int u = 0; u < n; ++u)
			for (edge &e : adj[u]) e.flow = 0;
		flow_type flow = 0;
		flow_type oo = numeric_limits<flow_type>::max();

		while (bfs(source, sink))
		{
			fill(it.begin(), it.end(), 0);
			for (flow_type f; (f = augment(source, sink, oo)) > 0;)
				flow += f;

		} // level[u] = -1 => source side of min cut
		return flow;
	}
};

vector<int> buildPath(dinic<int> &flow, int fin, int source){
    vector<int> answer;

    while (fin != source){
        answer.push_back(fin);
        bool ok = false;

        for (auto e : flow.adj[fin]){
            if (e.flow < e.cap){
                fin = e.dst;
                ok = true;
                break;
            }
        }

        assert(ok);
    }

    reverse(answer.begin(), answer.end());
    return answer;
}

int weigth[maxn];
int lift[maxn];

int build[maxn];

int buildId[maxn];
int craneIn[maxn];
int craneOut[maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int cid = 0;

    int n; cin >> n;

    for (int i = 1; i <= n; ++i){
        cin >> weigth[i] >> lift[i];

        craneIn[i] = cid++;
        craneOut[i] = cid++;
    }

    int m; cin >> m;

    for (int i = 1; i <= m; ++i){
        cin >> build[i];
        buildId[i] = cid++;
    }

    int S = cid++, T = cid++;

    dinic<int> flow(n * 2 + 2 + m);

    for (int i = 1; i <= m; ++i)
        flow.add_edge(buildId[i], T, 1);

    for (int i = 1; i <= n; ++i){
        if (weigth[i] == 0)
            flow.add_edge(S, craneIn[i], 1);
        flow.add_edge(craneIn[i], craneOut[i], 1);

        for (int j = 1; j <= n; ++j)
            if (lift[i] >= weigth[j] && lift[i] < lift[j])
                flow.add_edge(craneOut[i], craneIn[j], 1);

        for (int j = 1; j <= m; ++j)
            if (lift[i] >= build[j])
                flow.add_edge(craneOut[i], buildId[j], 1);
    }

    if (flow.max_flow(S, T) == m){
        for (int i = 1; i <= m; ++i){
            auto path = buildPath(flow, buildId[i], S);

//            for (auto j : path) cout << j << " "; cout << endl;
            for (int j = 1; j < (int)path.size(); j += 2)
                cout << path[j] / 2 + 1 << " ";
            cout << endl;
        }
    }
    else{
        cout << "impossible" << endl;
    }

    return 0;
}
