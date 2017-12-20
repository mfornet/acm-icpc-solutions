#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

struct graph
{
	int n;
	vector<vector<int>> adj, radj;

	graph(int n) : n(n), adj(n), radj(n) {}

	void add_edge(int src, int dst)
	{
		adj[src].push_back(dst);
		radj[dst].push_back(src);
	}

	vector<int> rank, semi, low, anc;

	int eval(int v)
	{
		if (anc[v] < n && anc[anc[v]] < n)
		{
			int x = eval(anc[v]);
			if (rank[semi[low[v]]] > rank[semi[x]])
				low[v] = x;
			anc[v] = anc[anc[v]];
		}
		return low[v];
	}

	vector<int> prev, ord;

	void dfs(int u)
	{
		rank[u] = ord.size();
		ord.push_back(u);
		for (auto v : adj[u])
		{
			if (rank[v] < n)
				continue;
			dfs(v);
			prev[v] = u;
		}
	}

	vector<int> idom; // idom[u] is an immediate dominator of u

	void dominator_tree(int r)
	{
		idom.assign(n, n);
		prev = rank = anc = idom;
		semi.resize(n);
		iota(semi.begin(), semi.end(), 0);
		low = semi;
		ord.clear();
		dfs(r);

		vector<vector<int>> dom(n);
		for (int i = (int) ord.size() - 1; i >= 1; --i)
		{
			int w = ord[i];
			for (auto v : radj[w])
			{
				int u = eval(v);
				if (rank[semi[w]] > rank[semi[u]])
					semi[w] = semi[u];
			}
			dom[semi[w]].push_back(w);
			anc[w] = prev[w];
			for (int v : dom[prev[w]])
			{
				int u = eval(v);
				idom[v] = (rank[prev[w]] > rank[semi[u]]
					? u : prev[w]);
			}
			dom[prev[w]].clear();
		}

		for (int i = 1; i < (int) ord.size(); ++i)
		{
			int w = ord[i];
			if (idom[w] != semi[w])
				idom[w] = idom[idom[w]];
		}
	}

	vector<int> dominators(int u)
	{
		vector<int> S;
		for (; u < n; u = idom[u])
			S.push_back(u);
		return S;
	}
};

std::vector<std::vector<int>> strongly_connected_components(const std::vector<std::vector<int>> &g)
{
	size_t n = g.size();
	std::vector<std::vector<int>> scc;
	std::vector<int> S, B, I(n);
	std::function<void(int)> dfs = [&](int u)
	{
		B.push_back(I[u] = S.size());
		S.push_back(u);
		for (int v : g[u])
			if (!I[v]) dfs(v);
			else while (I[v] < B.back()) B.pop_back();
		if (I[u] == B.back())
		{
			scc.push_back({});
			for (B.pop_back(); I[u] < S.size(); S.pop_back())
			{
				scc.back().push_back(S.back());
				I[S.back()] = n + scc.size();
			}
		}
	};
	for (size_t u = 0; u < n; ++u)
		if (!I[u]) dfs(u);
	return scc;
}

int main()
{
#ifdef jcg
	assert(freopen("i1.in", "r", stdin));
	assert(freopen("output.out", "w", stdout));
#endif

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int cs;
	cin >> cs;

	while (cs--)
	{
		int n, m;
		cin >> n >> m;

		vector<vector<int>> g(n);
		graph _g(n);
		for (int i = 0; i < m; ++i)
		{
			int u, v;
			cin >> u >> v;
			g[--u].push_back(--v);
			_g.add_edge(u, v);
		}

		_g.dominator_tree(0);

		auto scc = strongly_connected_components(g);
		vector<int> id(n);
		for (int i = 0; i < scc.size(); ++i)
			for (int u : scc[i]) id[u] = i;

		vector<int> xx = _g.dominators(n-1);

		reverse(xx.begin(), xx.end());

		if (xx.empty())
		{
			cout << 0 << endl << endl;
			continue;
		}

		vector<int> yy;

		for (int u : xx)
			if (scc[id[u]].size() == 1)
				yy.push_back(u);

		// for (int u : xx) cout << u+2/2 << " ";
		// cout << endl;

		if (yy.empty())
			cout << 0 << endl << endl;
		else
		{
			cout << yy.size() << endl;
			for (int i = 0; i < yy.size(); ++i)
				cout << yy[i]+1 << " \n"[i+1==yy.size()];
		}
	}

	return 0;
}