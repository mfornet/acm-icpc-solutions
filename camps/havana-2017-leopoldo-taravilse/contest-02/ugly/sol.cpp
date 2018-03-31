#include <bits/stdc++.h>

using namespace std;
#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200;

vi adj[ maxn ];
bool ok[ maxn ];
bool nc[ maxn ];

bool bfs(int s){
    queue<int> q;
    q.push( s );
    ok[ s ] = true;

    bool ans = false;

    while (!q.empty()){
        int u = q.front(); q.pop();
        ans |= nc[u];
        for (auto v : adj[u]){
            if (ok[v]) continue;

            ok[v] = true;
            q.push( v );
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    while(cin >> n >> m){
        for (int i = 0; i < maxn; ++i){
            adj[i].clear();
            ok[i] = nc[i] = false;
        }

    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;

        adj[u].push_back( v );
        adj[v].push_back( u );
    }

    int lonely = 0;
    int total = 0;
    int rlonely = 0;

    for (int i = 1; i <= n; ++i){
        memset(ok, 0, sizeof ok);
        ok[i] = true;
        bool bad = false;

        for (auto u : adj[i]){
            if (ok[u]){
                bad = true;
                break;
            }
            bfs(u);
        }

        nc[i] = !bad;
    }

    for (int i = 1; i <= n; ++i){
        if (!nc[i])
            continue;

        if (adj[i].empty()){
            rlonely++;
            continue;
        }

        //cout << "nc: " << i << endl;

        memset(ok, 0, sizeof ok);
        ok[i] = true;

        int yes = 0, no = 0;

        for (auto u : adj[i]){
            if (bfs(u))
                yes++;
            else
                no++;
        }

        if (adj[i].size() == 1)
            no++;

        if (yes == 0) lonely++;
        else if (no) total++;
    }

    if (total == 0 && lonely == 0){
        if (rlonely == 1 || rlonely == 2) 
            cout << rlonely + 1 << endl;
        else 
            cout << rlonely << endl;
        continue;
    }
    //cout << total << " " << lonely << endl;
    cout << (total + 1) / 2 + lonely + rlonely << endl;
    //return 0;
    }

    return 0;
}
