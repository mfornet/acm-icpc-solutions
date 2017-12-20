#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10; 

int ds[ maxn ];

int root(int a){
    return ds[a] < 0 ? a : ds[a] = root(ds[a]);
}

bool join(int a, int b){
    a = root(a), b = root(b);
    if (a == b) return false;
    if (ds[a] < ds[b]) swap(a, b);
    ds[b] += ds[a];
    ds[a] = b;
    return true;
}

void solve(){
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        ds[i] = -1;

    vector<vi> adj(n + 1);

    int comp = -1;

    for (int i = 0; i < m; ++i){
        int u, v; cin >> u >> v;
        
        adj[u].push_back( v );
        adj[v].push_back( u );
        
        if (!join(u, v))
            comp = u;
    }

    if (comp != -1){
        cout << "YES" << endl;
        for (int i = 1; i <= n; ++i)
            cout << (root(comp) == root(i)) << " ";
        cout << endl;
        return;
    }
    else{
        int u = -1;

        vector<int> three;

        for (int i = 1; i <= n; ++i){
            if (u == -1 || adj[i].size() > adj[u].size())
                u = i;

            if (adj[i].size() == 3)
                three.push_back(i);

            if (adj[u].size() >= 4)
                break;
        }

        if (adj[u].size() <= 2){
            cout << "NO" << endl;
            return;
        }

        if (adj[u].size() == 3){
            set<int> neig;

            for (auto v : adj[u]){
                neig.insert(v);

                if (adj[v].size() == 1){
                    cout << "NO" << endl;
                    return;
                }
            }

            for (int i = 1; i <= n; ++i){
                if (i == u) cout << 3 << " ";
                else if (neig.find(i) != neig.end()) cout << 2 << " ";
                else cout << (root(i) == root(u)) << " ";
            }
            cout << endl;
            return;
        }

        double k = 1. * (int)adj[u].size();
        int v = (int)(floor( (k + sqrt(k * k - 4. * k)) / 2. ) + 1e-5);

        cout << "YES" << endl;
        for (int i = 1; i <= n; ++i){
            if (i == u) cout << v << " ";
            else cout << (root(i) == root(u)) << " ";
        }
        cout << endl;

    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif

    int t; cin >> t;

    while (t--)
        solve();

    return 0;
}