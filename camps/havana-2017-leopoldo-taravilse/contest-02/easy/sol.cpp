#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vi adj[ maxn ];
bool ok[ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m; 
    long long r, e;
    cin >> n >> m >> r >> e;

    for (int i = 0; i < m; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back( v );
        adj[v].push_back( u );
    }

    long long answer = 0;

    for (int i = 1; i <= n; ++i){
        if (ok[i]) continue;

        long long nodes = 0, edges = 0;

        queue<int> q; q.push( i );
        ok[ i ] = true;

        while (!q.empty()){
            int u = q.front(); q.pop();
            nodes++;
            edges += adj[u].size();

            for (auto v : adj[u]){
                if (ok[v]) continue;
                q.push( v );
                ok[ v ] = true;
            }
        }

        edges /= 2;

        answer += min( e * nodes, r * (nodes * (nodes - 1) / 2 - edges) );
    }

    cout << answer << endl;

    return 0;
}
