#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000000007;

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int solve(int n, int k){
    vector<vi> adj(n);

    for (int i = 0; i + 1 < n; ++i){
        int u, v; cin >> u >> v;
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> seen(n);
    vector<int> where(n);
    vector<int> order(n);

    seen[0] = true;

    for (int i = 0, t = 1; i < n; ++i){
        for (auto u : adj[order[i]]){
            if (seen[u]) continue;
            seen[u] = true;
            where[u] = t;
            order[t++] = u;
        }
    }

    int answer = 0;

    vector<vi> dp0(n, vi(k+1));
    vector<vi> dp1(n, vi(k+1));
    vector<vi> dp2(n, vi(k+1));

    auto merge = [&](vi a, vi b){
        vector<int> c(k+1);
        for (int i = 0; i <= k; ++i)
            for (int j = 0; j <= i; ++j)
                add(c[i], 1LL * a[j] * b[i - j] % mod);
        return c;
    };

    for (int i = n - 1; i >= 0; --i){
        int u = order[i];

        dp0[u][0] = 1;
        dp1[u][1] = 1;
        dp2[u][1] = 1;

        for (auto v : adj[u]){
            if (where[v] < where[u])
                continue;

            vi sm(k+1);
            vi sm02(k+1);

            for (int j = 0; j <= k; ++j){
                add(sm[j], dp0[v][j]);
                add(sm[j], dp1[v][j]);
                add(sm[j], dp2[v][j]);

                add(sm02[j], dp0[v][j]);
                add(sm02[j], dp2[v][j]);
            }

            dp0[u] = merge(dp0[u], sm02);
            dp1[u] = merge(dp1[u], dp0[v]);
            dp2[u] = merge(dp2[u], sm);

        }

            for (int j = 0; j <= k; ++j){
                dp2[u][j] -= dp1[u][j];
                if (dp2[u][j] < 0)
                    dp2[u][j] += mod;
            }
/*        cout << "node: " << u << endl;
        for (int j = 0; j <= k; ++j)
            cout << dp0[u][j] << " ";
        cout << endl;
        for (int j = 0; j <= k; ++j)
            cout << dp1[u][j] << " ";
        cout << endl;
        for (int j = 0; j <= k; ++j)
            cout << dp2[u][j] << " ";
        cout << endl;
        cout << endl;
*/
    }

    add(dp0[0][k], dp2[0][k]);
    return dp0[0][k];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    while (cin >> n >> k){
        cout << solve(n, k) << endl;
    }

    return 0;
}
