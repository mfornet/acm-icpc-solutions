#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct graph
{
    int n;
    vector<vector<int>> adj;

    graph(int n) : n(n), adj(n) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
    }

    vector<int>& operator[](int u) { return adj[u]; }
};

pair<vector<vector<int>>,vector<int>> scc_gabow(graph &adj)
{
    int n = adj.n;

    vector<vector<int>> scc;
    vector<int> S, B, I(n);

    function<void(int)> dfs = [&](int u)
    {
        B.push_back(I[u] = S.size());
        S.push_back(u);

        for (int v : adj[u])
            if (!I[v]) dfs(v);
            else while (I[v] < B.back()) B.pop_back();

        if (I[u] == B.back())
        {
            scc.push_back({});
            for (B.pop_back(); I[u] < S.size(); S.pop_back())
            {
                scc.back().push_back(S.back());
                I[S.back()] = n + scc.size();
            }
        }
    };

    for (int u = 0; u < n; ++u)
        if (!I[u]) dfs(u);

    return {scc, I}; // in reverse topological order
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n, m;

    cin >> n >> m;

    vector<vi> adj(n);

    for (int i = 0; i < n; ++i){
        int s; cin >> s;

        for (int j = 0; j < s; ++j){
            int v; cin >> v;
            adj[i].push_back(--v);
        }
    }

    int s; cin >> s; --s;

    vector<vector<int>> dp(n, vi(2, -1));

    dp[s][0] = -2;
    queue<pii> q; 

    q.push({s, 0});

    while (!q.empty()){
        pii cur = q.front(); q.pop();
        int u = cur.first;
        int p = cur.second;

        for (auto v : adj[u]){
            if (dp[v][p ^ 1] == -1){
                dp[v][p ^ 1] = u;
                q.push({v, p ^ 1});
            }
        }
    }

    for (int i = 0; i < n; ++i){
        if (adj[i].size() == 0 && dp[i][1] >= 0){
            cout << "Win" << endl;
            vector<int> answer;

            int u = i, p = 1;

            while (u != -2){
                answer.push_back(u);
                u = dp[u][p];
                p ^= 1;
            }

            reverse(answer.begin(), answer.end());

            for (auto x : answer)
                cout << x+1 << " ";
            cout << endl;

            return 0;
        }
    }


    // check draw

    graph g(n);
    g.adj = adj;

    auto ggg = scc_gabow(g);

    auto scc = ggg.first;
    auto I = ggg.second;


    for (auto comp : scc){
        if (comp.size() == 1)
            continue;

        bool reach = false;
        bool final = true;

        for (auto u : comp){
            if (dp[u][0] != -1 || dp[u][1] != -1){
                reach = true;
            }

            for (auto v : adj[u])
                if (I[v] != I[u]){
                    final = false;
                    break;
                }

            if (!final) break;
        }

        if (reach && final){
            cout << "Draw" << endl;
            return 0;
        }
    }

    cout << "Lose" << endl;

    return 0;
}