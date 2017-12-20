#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct disjoint_set{
    vector<int> ds;

    disjoint_set(int n){
        ds = vector<int>(n, -1);
    }

    int root(int a){
        return ds[a] < 0 ? a : ds[a] = root( ds[a] );
    }

    bool join(int a, int b){
        a = root(a), b = root(b);
        if (a == b) return false;
        if (ds[a] < ds[b]) swap(a, b);
        ds[b] += ds[a];
        ds[a] = b;
        return true;
    }
};

vector<int> solve(){
    int n, m;
    cin >> n >> m;

    vector<vi> adj(n);
    disjoint_set ds(n);

    int cycle = -1;

    for (int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        u--; v--;

        adj[u].push_back( v );
        adj[v].push_back( u );

        if (!ds.join(u, v))
            cycle = u;
    }

    if (cycle != -1){
        vector<int> answer(n);
        for (int i = 0; i < n; ++i)
            answer[i] = ds.root(i) == ds.root(cycle);
        return answer;
    }

    vector<pii> three;

    for (int i = 0; i < n; ++i){
        if (adj[i].size() >= 4){
            vector<int> answer(n);
            answer[i] = 2;
            for (auto u : adj[i])
                answer[u] = 1;
            return answer;
        }
        else if (adj[i].size() == 3){
            three.push_back({ds.root(i), i});
        }
    }

    sort(three.begin(), three.end());

    auto bfs = [&](int u){
        vector<int> dist(n, oo);
        queue<int> q;
        q.push(u); dist[u] = 0;

        while (!q.empty()){
            int v = q.front(); q.pop();
            for (auto w : adj[v]){
                if (dist[w] > dist[v] + 1){
                    dist[w] = dist[v] + 1;
                    q.push(w);
                }
            }
        }

        return dist;
    };

    for (int i = 1; i < three.size(); ++i){
        if (three[i].first == three[i - 1].first){
            int u = three[i].second, v = three[i - 1].second;

            auto distU = bfs(u);
            auto distV = bfs(v);

            int tdist = distU[ v ];

            vector<int> answer(n);
            for (int j = 0; j < n; ++j){
                if (ds.root(j) == ds.root(u)){
                    if (distU[j] + distV[j] == tdist)
                        answer[j] = 2;
                    else
                        answer[j] = 1;
                }
            }

            return answer;
        }
    }

    for (auto _u : three){
        int u = _u.second;
        bool good = true;

        for (auto v : adj[u]){
            if (adj[v].size() == 1){
                good = false;
                break;
            }
        }

        if (good){
            vector<int> answer(n);
            for (int i = 0; i < n; ++i)
                answer[i] = ds.root(i) == ds.root(u);
            answer[u] = 3;
            for (auto v : adj[u])
                answer[v] = 2;
            return answer;
        }
    }

    return {};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif

    int t; cin >> t;

    while (t--){
        auto answer = solve();

        if (answer.empty())
            cout << "NO" << endl;
        else{
            cout << "YES" << endl;
            for (auto u : answer)
                cout << u << " ";
            cout << endl;
        }
    }

    return 0;
}