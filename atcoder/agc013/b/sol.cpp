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
vector<int> path;
bool vis[ maxn ];

void go(int s){
    vis[s] = true;
    path.push_back(s);

    for (auto u : adj[s])
        if (!vis[u]){
            go(u);
            return;
        }
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

    go(1);
    reverse(path.begin(), path.end());
    path.pop_back();
    vis[1] = false;
    go(1);

    cout << path.size() << endl;
    for (auto u : path)
        cout << u << " ";
    cout << endl;

    return 0;
}
