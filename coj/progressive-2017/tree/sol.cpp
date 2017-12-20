#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;

int add(int a, int b){
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

pair<int,int> add(pair<int,int> a, pair<int,int> b){
	a.first = add(a.first, b.first);
	a.second = add(a.second, b.second);
	return a;
}

pair<int,int> A[ 100 ], B[ 100 ];

struct graph{
	int n;
	vector<vector<int>> adj;
	vector<int> height, pos, father,
		    heavy_father, tour,
		    hson;

	graph(int n) : n(n){
		adj = vector<vector<int>>(n);
	}

	void add_edge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	int dfs(int s, int p=-1){
		father[s] = p;
		hson[s] = -1;
		int child_nodes = 0;
		int tot_nodes = 1; 

		tour.push_back(s);

		for (auto u : adj[s]){
			if (u == p) continue;
			height[u] = height[s] + 1;

			int cur_nodes = dfs(u, s);
			if (cur_nodes > child_nodes)
				hson[s] = u, child_nodes = cur_nodes;
			tot_nodes += cur_nodes;
		}

		hson[s] = 2 * child_nodes >= tot_nodes ? hson[s] : -1;

		return tot_nodes;
	}

	void go(){
		height = pos = father = 
		heavy_father = hson = vector<int>(n, -1);
	
		height[0] = 0;
		dfs(0);

		int cur_pos = 0;

		for (auto u : tour){
			if (pos[u] != -1)
				continue;

			int v = u;
			while (true){
				heavy_father[v] = u;
				pos[v] = cur_pos++;
				if (hson[v] != -1) v = hson[v];
				else break;
			}
		}
	}

	int lca(int u, int v){
		while (heavy_father[u] != heavy_father[v]){ 
			if ( height[ heavy_father[v] ] > height[ heavy_father[u] ] ) 
				swap(u, v); 
			u = father[ heavy_father[u] ];
		}
		if (height[u] > height[v])
			swap(u, v);
		return u;
	}

	int get_path(int u, int l, pair<int,int> A[100]){
		int total = 0;
		while (heavy_father[u] != heavy_father[l]){
			A[total++] = make_pair(pos[heavy_father[u]],pos[u]);
			u = father[ heavy_father[u] ];
		}
		if (u != l)
			A[total++] = {pos[l]+1,pos[u]};
		return total;
	}
};

const int maxn = 100005;

int fib[ maxn ];

int sum(pair<int,int> p, int n){
	return add(1LL * p.first * fib[n + 1] % mod, 1LL * p.second * (fib[n+2] - 1) % mod);	
}

pair<int,int> move(pair<int,int> p, int n){
	return make_pair(add(1LL * p.first * fib[n] % mod,     1LL * p.second * fib[n + 1] % mod),
		add(1LL * p.first * fib[n + 1] % mod, 1LL * p.second * fib[n + 2] % mod));
}

pair<int,int> zero;

struct segment_tree{
	struct node{
		pair<int,int> a, b;
		int s;
	};
	vector<node> data;

	segment_tree(vector<int> &value){
		int n = (int)value.size();
		data = vector<node>(4 * n);
		build(1, 0, n, value);
	}

	void build(int p, int b, int e, vector<int> &value){
		if (b + 1 == e){
			data[p].s = value[b];
		}
		else{
			int m = (b + e) >> 1, l = p << 1, r = l | 1;
			build(l, b, m, value);
			build(r, m, e, value);
			data[p].s = add( data[l].s, data[r].s );
		}
	}

	void push(int p, int l, int r, int b, int m, int e){
		if (data[p].a == zero && data[p].b == zero)
			return;

		int lSize = m - b, rSize = e - m;
		auto aMove = move(data[p].a, lSize);
		auto bMove = move(data[p].b, rSize);
		
		data[l].a = add(data[l].a, data[p].a);
		data[l].b = add(data[l].b, bMove);
		data[l].s = add(data[l].s, sum(data[p].a, lSize));
		data[l].s = add(data[l].s, sum(bMove, lSize));

		data[r].a = add(data[r].a, aMove);
		data[r].b = add(data[r].b, data[p].b);
		data[r].s = add(data[r].s, sum(aMove, rSize));
		data[r].s = add(data[r].s, sum(data[p].b, rSize));

		data[p].a = data[p].b = zero;
	}

	int query(int p, int b, int e, int x, int y){
		if (x <= b && e <= y) return data[p].s;

		int m = (b + e) >> 1, l = p << 1, r = l | 1;
		push(p, l, r, b, m, e);
		int ans = 0;

		if (x < m) ans = add(ans, query(l, b, m, x, y));
		if (m < y) ans = add(ans, query(r, m, e, x, y));

		return ans;
	}

	void update(int p, int b, int e, int x, int y, pair<int,int> &A, pair<int,int> &B){
		if (x <= b && e <= y){
			auto aMove = move(A, b - x);
			auto bMove = move(B, y - e);
			int size = e - b;

			data[p].a = add(data[p].a, aMove);
			data[p].b = add(data[p].b, bMove);
			data[p].s = add(data[p].s, sum(aMove, size));
			data[p].s = add(data[p].s, sum(bMove, size));
		}
		else{
			int m = (b + e) >> 1, l = p << 1, r = l | 1;
			push(p, l, r, b, m, e);
			if (x < m) update(l, b, m, x, y, A, B);
			if (m < y) update(r, m, e, x, y, A, B);
			data[p].s = add(data[l].s, data[r].s);
		}
	}
};

#define UPDATE "2"
#define QUERY "1"

int main(){
	fib[0] = 1;
	for (int i = 2; i < maxn; ++i)
		fib[i] = add(fib[i - 1], fib[i - 2]);

	int n, q;
	while (cin >> n){
		graph g(n);
		vector<pair<pair<int,int>,int>> edges(n - 1);

		for (int i = 0; i + 1 < n; ++i){
			int u, v, d;
			cin >> u >> v >> d;
			u--; v--;
			edges[i] = {{u, v}, d};
			g.add_edge(u, v);
		}
		
		g.go();

		vector<int> value(n);
		for (auto e : edges){
			int u = e.first.first, v = e.first.second;
			if (g.height[v] > g.height[u])
				swap(u, v);
			value[ g.pos[u] ] = e.second;
		}

		segment_tree st(value);
		
		cin >> q;

		while (q--){
			string mode;
			cin >> mode;

			int u, v;
			cin >> u >> v;
			u--; v--;
			
			int l = g.lca(u, v);
			int aCount = g.get_path(u, l, A);
			int bCount = g.get_path(v, l, B);

			if (mode == QUERY){
				int answer = 0;

				for (int i = 0; i < aCount; ++i)
					answer = add(answer, st.query(1, 0, n, A[i].first, A[i].second + 1));
				for (int i = 0; i < bCount; ++i)
					answer = add(answer, st.query(1, 0, n, B[i].first, B[i].second + 1));

				cout << answer << '\n';
			}
			else if (mode == UPDATE){
				pair<int,int> p(3, 4);
				pair<int,int> z(0, 0);

				for (int i = 0; i < aCount; ++i){	
					st.update(1, 0, n, A[i].first, A[i].second + 1, z, p);
					p = move(p, A[i].second - A[i].first + 1);
				}
				for (int i = 0; i < bCount; ++i){
					st.update(1, 0, n, B[i].first, B[i].second + 1, p, z);
					p = move(p, B[i].second - B[i].first + 1);
				}
			}
		}
	}
}
