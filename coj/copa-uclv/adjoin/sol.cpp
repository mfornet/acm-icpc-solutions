#include <bits/stdc++.h>

using namespace std;

const int maxn = 100000 + 10;

typedef pair<int,int> pii;
typedef vector<int> vi;

vector<int> adj[ maxn ];
bool seen[ maxn ];

pii dfs(int s, int p){
	pii ans(s, 0);
	seen[s] = true;

	for (auto u : adj[s]){
		if (u == p) continue;
		pii cur = dfs(u, s);

		if (cur.second + 1 > ans.second)
			ans = pii(cur.first, cur.second + 1);
	}

	return ans;
}

int main(){
	int c, l;
	cin >> c >> l;

	for (int i = 0; i < l; ++i){
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	multiset<int> ms;

	for (int i = 0; i < c; ++i){
		if (seen[i]) 
			continue;
		pii a = dfs(i, -1);
		pii b = dfs(a.first, -1);

		ms.insert( b.second );
	}

	while (ms.size() > 1){
		int a = *ms.begin();
		ms.erase( ms.begin() );
		int b = *ms.rbegin();
		ms.erase( ms.find(b) );

		int c = max(b, (a + 1) / 2 + (b + 1) / 2 + 1);
		ms.insert(c);
	}

	cout << *ms.begin() << endl;
}
