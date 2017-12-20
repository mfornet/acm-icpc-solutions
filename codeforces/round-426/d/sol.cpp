#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct edge{
    int v, val, col;
};

int64 answer;

vector<edge> adj[ maxn ];

bool mk[maxn];
int q[maxn], p[maxn], sz[maxn], mc[maxn];

int centroid(int c){
    int b = 0, e = 0;
    q[e++] = c, p[c] = -1, sz[c] = 1, mc[c] = 0;

    while (b < e){
        int u = q[b++];
        for (auto e : adj[u]){
            int v = e.v;
            if (v != p[u] && !mk[v])
                p[v] = u, sz[v] = 1, mc[v] = 0, q[e++] = v;
        }
    }

    for (int i = e - 1; ~i; --i){
        int u = q[i];
        int bc = max(e - sz[u], mc[u]);
        if (2 * bc <= e) return u;
        sz[p[u]] += sz[u], mc[p[u]] = max(mc[p[u]], sz[u]);
    }

    assert(false);
    return -1;
}

void solve(int s){
    int c = centroid(s);
    mk[c] = true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif

    int n;
    cin >> n;

    for (int i = 1; i < n; ++i){
        int u, v, val, col;
        cin >> u >> v >> val >> col;
        if (col == 0) col = -1;
        adj[u].push_back({v, val, col});
        adj[v].push_back({u, val, col});
    }

    solve(1);

    cout << answer << endl;

    return 0;
}