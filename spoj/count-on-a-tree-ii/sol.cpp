#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int par[maxn][20];
int value[maxn];
int hei[maxn];
vi adj[maxn];

vector<int> tour;
int be[maxn], en[maxn]; // begin, end, in the euler tour

void dfs(int s, int p = 0){
    par[s][0] = p;

    be[s] = tour.size();
    tour.push_back(s);

    for (int i = 1; par[s][i - 1]; ++i)
        par[s][i] = par[ par[s][i - 1] ][i-1];

    for (auto u : adj[s]){
        if (u == p) continue;
        hei[u] = hei[s] + 1;
        dfs(u, s);
    }

    en[s] = tour.size();
    tour.push_back(s);
}

int lca(int u, int v){
    if (hei[u] < hei[v])
        swap(u, v);
    int d = hei[u] - hei[v];

    for (int i = 0; d; ++i){
        if (d >> i & 1){
            d ^= 1 << i;
            u = par[u][i];
        }
    }

    if (u == v) return u;

    for (int i = 19; ~i; --i){
        if (par[u][i] != par[v][i])
            u = par[u][i], v = par[v][i];
    }

    return par[u][0];
}

const int size = 200;

struct query{
    int b, e, l, blk, idx;

    query(int u=0, int v=0, int idx=0) : idx(idx){
        if (be[u] > be[v])
            swap(u, v);

        if (en[u] >= en[v]){
            // lca = u
            b = be[u], e = be[v];
            l = -1, blk = b / size;
        }
        else{
            l = lca(u, v);
            b = en[u], e = be[v];
            blk = b / size;
        }
    }

    bool operator<(const query &q)const{
        if (blk != q.blk) return blk < q.blk;
        return e < q.e;
    }
};

int open;
int freq[maxn];
int state[maxn];

int add(int v){
    if (!freq[v]++)
        open++;
}

int remove(int v){
    if (!--freq[v])
        open--;
}

void flip(int u){
    if (state[u]){
        remove(value[u]);
        state[u] = 0;
    }
    else{
        add(value[u]);
        state[u] = 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    map<int,int> comp;
    int tot = 0;

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        if (comp.find(value[i]) == comp.end())
            comp[value[i]] = tot++;
        value[i] = comp[value[i]];
    }

    for (int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1);

    vector<query> Q(q);
    vector<int> answer(q);

    for (int i = 0; i < q; ++i){
        int u, v; cin >> u >> v;
        Q[i] = query(u, v, i);
    }

    sort(Q.begin(), Q.end());

    int B = 0, E = -1;

    for (auto qry : Q){
        int b = qry.b, e = qry.e;

        while (E < e)
            flip(tour[++E]);
        while (B > b)
            flip(tour[--B]);
        while (E > e)
            flip(tour[E--]);
        while (B < b)
            flip(tour[B++]);

        if (qry.l != -1)
            flip(qry.l);

        answer[qry.idx] = open;

        if (qry.l != -1)
            flip(qry.l);
    }

    for (auto u : answer)
        cout << u << endl;

    return 0;
}
