#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int alpha = 26;
const char zero = 'a';

char value[ maxn ];

char pat[ 200 ];
char revpat[ 200 ];

vi adj[ maxn ];
int par[ maxn ][ 20 ];
int hei[ maxn ];

vector<vi> buildAutomata(char p[200], int len){
    vector<vi> go( len + 1, vi(alpha) );
    for (int i = 1, f = 0; i <= len; ++i){
        go[i - 1][p[i - 1] - zero] = i;
        for (int j = 0; j < alpha; ++j)
            go[i][j] = go[f][j];
        if (i < len) f = go[f][p[i]-zero];
    }
    return go;
}

void dfs(int s, int p){
    par[s][0] = p;
    for (int i = 1; par[s][i - 1]; ++i)
        par[s][i] = par[ par[s][i - 1] ][i - 1];

    for (auto u : adj[s]){
        if (u == p) continue;
        hei[u] = hei[s] + 1;
        dfs(u, s);
    }
}

int goup(int u, int d){
    for (int i = 0; d; ++i, d >>= 1)
        if (d & 1) u = par[u][i];
    return u;
}

int lca(int u, int v){
    if (hei[u] < hei[v])
        swap(u, v);

    u = goup(u, hei[u] - hei[v]);

    if (u == v) return u;

    for (int i = 19; ~i; --i)
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];

    return par[u][0];
}

struct query{
    int u, v, l;
} qlist[ maxn ];

int answer[ maxn ];
vi U[ maxn ], V[ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    cin >> value >> pat;
    int l = strlen( pat );

    for (int i = 0; i < l; ++i)
        revpat[ l - i - 1 ] = pat[i];

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    for (int i = 0; i < q; ++i){
        cin >> qlist[i].u >> qlist[i].v;
        qlist[i].l = lca(qlist[i].u, qlist[i].v);
        U[ qlist[i].u ].push_back(i);
        V[ qlist[i].v ].push_back(i);
    }

    auto pi1 = buildAutomata(pat, l);
    auto pi2 = buildAutomata(revpat, l);

    // code
    solve(1, 0, pi1, pi2);


    return 0;
}