#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1501;

struct tgraph{
    int n;
    vector<vector<int>> adj;

    tgraph(int n=0) : n(n), adj(n) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int add_node()
    {
        adj.push_back({});
        return n++;
    }

    vector<int>& operator[](int u) { return adj[u]; }
};

struct graph
{
    int n;
    vector<vector<int>> adj;

    graph(int n=0) : n(n), adj(n) {}

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int add_node()
    {
        adj.push_back({});
        return n++;
    }

    vector<int>& operator[](int u) { return adj[u]; }

    vector<int> num, low, art, stk, id;
    vector<vector<int>> comps;

    tgraph tree;

    void biconnected_components()
    {
        num = vector<int>(n);
        low = vector<int>(n);
        art = vector<int>(n);
        stk = vector<int>();
        comps = vector<vector<int>>();

        function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
        {
            num[u] = low[u] = ++t;
            stk.push_back(u);

            for (int v : adj[u]) if (v != p)
            {
                if (!num[v])
                {
                    dfs(v, u, t);
                    low[u] = min(low[u], low[v]);

                    if (low[v] >= num[u])
                    {
                        art[u] = (num[u] > 1 || num[v] > 2);

                        comps.push_back({u});
                        while (comps.back().back() != v)
                            comps.back().push_back(stk.back()),
                            stk.pop_back();
                    }
                }
                else low[u] = min(low[u], num[v]);
            }
        };

        for (int u = 0, t; u < n; ++u)
            if (!num[u]) dfs(u, -1, t = 0);

        tree = tgraph(0);
        id = vector<int>(n);

        for (int u = 0; u < n; ++u)
            if (art[u]) id[u] = tree.add_node();

        for (auto &comp : comps)
        {
            int node = tree.add_node();
            for (int u : comp)
                if (!art[u]) id[u] = node;
                else tree.add_edge(node, id[u]);
        }
    }

    bool connected(int u, int v){
        if (art[u]) swap(u, v);

        if (art[u]){
            //art  art
            set<int> X;

            for (auto x : tree.adj[ id[v] ])
                X.insert(x);

            for (auto x : tree.adj[ id[u] ])
                if (X.find(x) != X.end())
                    return true;

            return false;
        }
        else if (!art[v]){
            // ~art ~art
            return id[u] == id[v];
        }
        else{
            // ~art art
            for (auto x : tree.adj[ id[v] ]){
                if (x == id[u])
                    return true;
            }

            return false;
        }
    }
};

struct pos_t{
    int x, y, k;
};

char M[maxn][maxn];
int ID[maxn][maxn];

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

bool vis[maxn][maxn][4];

int main(){
    freopen("pushabox.in", "r", stdin);
    freopen("pushabox.out", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;

    cin >> n >> m >> q;

    pii A, B;

    int total_nodes = 0;

    for (int i = 0; i < n; ++i){
        cin >> M[i];

        for (int j = 0; j < m; ++j){
            if (M[i][j] == 'A'){
                A = pii(i,j);
                M[i][j] = '.';
            }
            else if (M[i][j] == 'B'){
                B = pii(i,j);
                M[i][j] = '.';
            }

            if (M[i][j] == '.')
                ID[i][j] = total_nodes++;
        }
    }

    graph G(total_nodes);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            if (M[i][j] == '.'){
                if (i && M[i-1][j] == '.')
                    G.add_edge(ID[i][j], ID[i-1][j]);
                if (j && M[i][j-1] == '.')
                    G.add_edge(ID[i][j], ID[i][j-1]);
            }
        }

    G.biconnected_components();

    // debug area

    // for (int i = 0; i < n; ++i){
    //     for (int j = 0; j < m; ++j){
    //         if (M[i][j] == '.') cout << ID[i][j] << " ";
    //         else cout << "# ";
    //     }
    //     cout << endl;
    // }

    // cout << G.n << endl;
    // for (int i = 0; i < G.n; ++i)
    //     cout << G.art[i] << " ";
    // cout << endl;

    // for (int i = 0; i < G.n; ++i)
    //     cout << G.id[i] << " ";
    // cout << endl;

    // end debug

    vector<vector<bool>> mark(n, vector<bool>(m));
    mark[A.first][A.second] = true;
    queue<pii> foo; foo.push(A);

    while (!foo.empty()){
        pii u = foo.front(); foo.pop();

        if (u == B)
            break;

        for (int i = 0; i < 4; ++i){
            int x = u.first + dx[i], y = u.second + dy[i];

            if (0 <= x && x < n && 0 <= y && y < m && !mark[x][y] && M[x][y] == '.'){
                mark[x][y] = true;
                foo.push(pii(x, y));
            }
        }
    }

    pos_t start = {0, 0, -1};

    if (mark[B.first][B.second]){ // final position
        for (int i = 0; i < 4; ++i){
            int x = B.first + dx[i], y = B.second + dy[i];

            if (0 <= x && x < n && 0 <= y && y < m && mark[x][y]){
                start = {B.first, B.second, i};
                break;
            }
        }
    }

    set<pii> final;
    final.insert(B);

    if (start.k != -1){
        // go everywhere

        queue<pos_t> q;
        q.push(start);
        vis[start.x][start.y][start.k] = true;

        while (!q.empty()){
            auto cur = q.front(); q.pop();
            int x = cur.x, y = cur.y, k = cur.k;

            // cout << x + 1 << " " << y + 1 << " " << k << endl;

            final.insert(pii(x, y));

            int nx = x + dx[k], ny = y + dy[k];
            int nid = ID[nx][ny];

            for (int k = 0; k < 4; ++k){
                if (vis[x][y][k]) continue;

                int fx = x + dx[k], fy = y + dy[k];

                if (0 <= fx < n && 0 <= fy < m && M[fx][fy] == '.'){
                    if (G.connected(nid, ID[fx][fy])){
                        vis[x][y][k] = true;
                        q.push({x, y, k});
                    }
                }
            }

            int bx = x - dx[k], by = y - dy[k];

            if (0 <= bx && bx < n && 0 <= by && by < m && M[bx][by] == '.' &&
                !vis[bx][by][k]){
                vis[bx][by][k] = true;
                q.push({bx, by, k});
            }
        }
    }

    while (q-->0){
        int x, y;
        cin >> x >> y;
        x--; y--;

        // cout << x + 1 << " " << y + 1 << " ";
        cout << (final.find(pii(x,y)) == final.end() ? "NO" : "YES") << endl;
    }

    return 0;
}