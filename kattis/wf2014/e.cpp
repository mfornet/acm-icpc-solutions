#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200;

vi adj[ maxn ];

int64 label[ maxn ];
int64 x[ maxn ];
int64 sight[ maxn ][ maxn ];

int64 base = 4003;

vector<int> answer[ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n; cin >> n;

    for (int i = 1; i <= n; ++i){
        int t; cin >> t;

        for (int j = 0; j < t; ++j){
            int u; cin >> u;
            adj[ i ].push_back( u );
        }

        label[i] = adj[i].size();
    }

    int prev = n + 1;

    while (true){
        // cout << "here" << endl;

        for (int i = 1; i <= n; ++i){
            x[i - 1] = label[i];
        }


        sort(x, x + n);
        int total = unique(x, x + n) - x;
        if (total == prev) break;
        prev = total;

        for (int i = 1; i <= n; ++i){
            label[i] = (lower_bound(x, x + total, label[i]) - x) + 1;
            // cout << label[i] << " ";
        }
        // cout << endl;

        vector<int64> id;

        for (int i = 1; i <= n; ++i){
            int64 h = 0, p = 1;

            for (auto u : adj[i]){
                h = h * base + label[u];
                p *= base;
            }

            for (auto u : adj[i]){
                sight[i][u] = h * base + label[i];
                // cout << sight[i][u] << " ";
                // sight[i][u] = h;
                id.push_back( sight[i][u] );
                h = h * base - label[u] * p + label[u];
            }
            // cout << endl;
        }
        // cout << endl;

        sort(id.begin(), id.end());
        id.resize( unique(id.begin(), id.end()) - id.begin() );

        for (int i = 1; i <= n; ++i){
            int64 h = 0, p = 1;

            for (auto u : adj[i]){
                sight[u][i] = lower_bound(id.begin(), id.end(), sight[u][i]) - id.begin() + 1;
                h = h * base + sight[u][i];
                p *= base;
            }

            label[i] = h;

            for (auto u : adj[i]){
                h = h * base - sight[u][i] * p + sight[u][i];
                label[i] = max( label[i], h );
            }
        }
    }

    map<int64,int> who;

    for (int i = 1; i <= n; ++i){
        if (!who.count( label[i] ))
            who[ label[i] ] = i;
        answer[ who[label[i]] ].push_back(i);
    }

    bool print = false;

    for (int i = 1; i <= n; ++i)
        if (answer[i].size() > 1){
            print = true;
            for (auto u : answer[i])
                cout << u << " ";
            cout << endl;
        }

    if (!print) cout << "none" << endl;

    return 0;
}