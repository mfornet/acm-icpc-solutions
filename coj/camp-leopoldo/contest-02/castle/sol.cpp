#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

pii far(int s, int p, vector<vi> &adj){
    pii ans(1, s);

    for (auto u : adj[s]){
        if (u == p) continue;

        pii cur = far(u, s, adj);
        if (cur.first + 1 > ans.first){
            ans = pii( cur.first + 1, cur.second );
        }
    }

    return ans;
}

void solve(){
    int n; cin >> n;
    vector<vi> adj(n);

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back( v );
        adj[v].push_back( u );
    }

    pii K = far(0, -1, adj);
    K = far(K.second, -1, adj);

    cout << K.first << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--)
        solve();

    return 0;
}
