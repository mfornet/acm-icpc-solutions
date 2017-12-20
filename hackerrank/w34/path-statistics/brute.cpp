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
int value[maxn];
int dist1[maxn], dist2[maxn];

void bfs(int p, int dist[maxn]){
    memset(dist, oo, maxn * sizeof(int));
    dist[p] = 0;
    queue<int> q;
    q.push(p);

    while(!q.empty()){
        int u = q.front(); q.pop();

        for (auto v : adj[u]){
            if (dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while (q--){
        int u, v, k;
        cin >> u >> v >> k;
        bfs(u, dist1);
        bfs(v, dist2);

        int D = dist1[v];

        map<int,int> freq;
        for (int i = 1; i <= n; ++i)
            if (dist1[i] + dist2[i] == D)
                freq[ value[i] ]++;

        vector<pii> fin;

        for (auto p : freq)
            fin.push_back({p.second, p.first});

        sort(fin.begin(), fin.end());
        reverse(fin.begin(), fin.end());

        cout << fin[k - 1].second << endl;
    }

    return 0;
}