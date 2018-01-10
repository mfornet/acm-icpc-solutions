#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<int64> dijkstra(vector<vector<pair<int,int64>>> &g, int s){
    vector<int64> dist(g.size(), oo);
    dist[ s ] = 0;
    priority_queue<pair<int64,int>> pq;
    pq.push( {0LL, s} );

    while (!pq.empty()){
        auto cur = pq.top(); pq.pop();

        int64 t = -cur.first;
        int u = cur.second;

        if (dist[u] < t) continue;

        for (auto e : g[u]){
            if (t + e.second < dist[e.first]){
                dist[e.first] = t + e.second;
                pq.push( {-dist[e.first], e.first} );
            }
        }
    }

    return dist;
}

vector<int64> dc(int n, int s, vector<int64> &value, vector<int64> &dp){
    vector<int64> ans(n, oo);

    for (int i = 0; i < n; ++i){
        for (int l = 1; l <= i; ++l){
            if (l * s > i + 1) break;
            int j = i - l + 1;      
            ans[i] = min(ans[i], dp[j - 1] + (value[i] - value[j - 1]) * (i - j) );
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n, b, s, r;
    cin >> n >> b >> s >> r;

    vector<vector< pair<int,int64> >> g1(n), g2(n);

    for (int i = 0; i < r; ++i){
        int u, v;
        int64 w;
        cin >> u >> v >> w;
        u--; v--;

        g1[u].push_back({v, w});
        g2[v].push_back({u, w});
    }

    vector<int64> d1 = dijkstra(g1, b);
    vector<int64> d2 = dijkstra(g2, b);

    vector<int64> value(b);

    for (int i = 0; i < b; ++i){
        assert( d1[i] < oo && d2[i] < oo );
        value[i] = d1[i] + d2[i];
    }

    sort(value.begin(), value.end());

    for (int i = 1; i < b; ++i)
        value[i] += value[i - 1];

    vector<int64> dp(b);

    for (int i = 0; i < b; ++i)
        dp[i] = value[i] * i;

    for (int i = 2; i <= s; ++i){
        vector<int64> ndp = dc( b, i, value, dp );
        dp.swap( ndp );
    }

    cout << dp.back() << endl;

    return 0;
}