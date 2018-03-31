#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
vector<int> g[MAX], gg[MAX];
int deg[MAX];
int grundy[MAX];
void dfs(int v){
	if(g[v].size() == 0){
		grundy[v] = 0;
		return;
	}
	set<int> S;
	for(auto nv: g[v]){
		if(grundy[nv] != -1){
			S.insert(grundy[nv]);
			continue;
		}
		dfs(nv);
		S.insert(grundy[nv]);
	}
	for(int t = 0; t <= (int)S.size(); t++)
		if(S.find(t) == S.end()){
			grundy[v] = t;
			break;
		}

}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int n , m; cin >> n >> m;
	for(int i = 0; i <m; i++){
		int a, b; cin >>a >> b;
		g[a].push_back(b);
		deg[b]++;
	}
	memset(grundy, -1, sizeof(grundy));
	for(int i= 1; i <= n ;i++)
		if(deg[i] == 0)
			dfs(i);
	for(int i = 1; i <=n ;i++)
		cout << grundy[i] << endl;



}
