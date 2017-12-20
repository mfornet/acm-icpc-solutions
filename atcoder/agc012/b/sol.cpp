#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

vi adj[ maxn ];
bool vis[ maxn ][ 11 ];
int col[ maxn ];

void paint(int s, int d, int c){
    if ( d == -1 || vis[s][d] ) return;

    for (int i = d; i >= 0 && !vis[s][i]; --i)
        vis[s][i] = true;

    if (!col[ s ])
        col[s] = c;

    for (auto u : adj[s])
        paint(u, d - 1, c);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int q; cin >> q;

    vector<int> U(q), D(q), C(q);

    for (int i = 0; i < q; ++i){
        cin >> U[i] >> D[i] >> C[i];
    }

    for (int i = q - 1; i >= 0; --i){
        paint(U[i], D[i], C[i]);
    }

    for (int i = 1; i <= n; ++i){
        cout << col[i] << endl;
    }

    return 0;
}