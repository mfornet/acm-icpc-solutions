#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int dist[310][310];
int ritual[310];

int V[310][20];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(dist, oo, sizeof dist);
    memset(V, oo, sizeof V);

    int n, m, k;
    
    cin >> n >> m >> k;

    for (int i = 0; i < m; ++i)
        cin >> ritual[i];

    for (int i = 0; i < k; ++i){
        int u, v, c;
        cin >> u >> v >> c;
        dist[u][v] = min(dist[u][v], c);
    }

    priority_queue<pair<int,pii>> pq;

    for (int i = 0; i < m; ++i){
        int u = i, x = ritual[i] == 0 ? 1 : 0;
        V[u][x] = 0;

        pq.push({0, {u, x}});
    }

    while (!pq.empty()){
        auto cur = pq.top(); pq.pop();

        int T = -cur.first;
        int u = cur.second.first;
        int r = cur.second.second;

        if (r == n){
            cout << T << endl;
            exit(0);
        }

        if (V[u][r] < T) continue;

        for (int j = 0; j < m; ++j){
            if (dist[u][j] == oo) 
                continue;

            int rr = ritual[j] == r ? r + 1 : r;

            if (T + dist[u][j] < V[j][rr]){
                V[j][rr] = T + dist[u][j];
                pq.push({-V[j][rr], {j, rr}});
            }
        }
    }

    cout << -1 << endl;

    return 0;
}