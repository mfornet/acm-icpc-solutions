#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<int> adj[maxn];
int seen[maxn];

int gettype(int s){
    seen[s] = +1;
    if (adj[s].empty())
        return 0;

    vector<int> q = {s};
    int beg = 0;

    int bipartite = 1;

    while (beg < (int)q.size()){
        int u = q[beg++];

        for (auto v : adj[u]){
            if (!seen[v]){
                seen[v] = -seen[u];
                q.push_back(v);
            }
            else if (seen[u] != -seen[v])
                bipartite = 2;
        }
    }

    return bipartite;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> counter(3);

    for (int i = 1; i <= n; ++i){
        if (seen[i]) continue;
        counter[ gettype(i) ]++;
    }

    cout << counter[0] << " " << counter[1] << " " << counter[2] << endl;

    int64 answer = 2LL * counter[0] * n - counter[0] * counter[0]
                    + counter[1] * (2 * counter[1] + counter[2])
                    + counter[2] * counter[2];

    cout << answer << endl;

    return 0;
}