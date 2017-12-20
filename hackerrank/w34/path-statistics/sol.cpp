#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 50000 + 10;

vi adj[ maxn ];
int value[ maxn ];

int order[ 2 * maxn ];
int st[ maxn ], en[ maxn ];
int total;

int height[ maxn ];
int parent[ maxn ][ 20 ];

const int bsize = 500;

typedef tree<pii, null_type, less<pii>,
        rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void dfs(int s, int p){
    parent[s][0] = p;

    for (int i = 1; i < 20 && parent[s][i - 1]; ++i)
        parent[s][i] = parent[ parent[s][i - 1] ][ i - 1 ];

    st[ s ] = total;
    order[ total++ ] = s;

    for (auto u : adj[s]){
        if (u == p) continue;
        height[ u ] = height[ s ] + 1;
        dfs(u, s);
    }

    en[ s ] = total;
    order[ total++ ] = s;
}

int lca(int u, int v){
    if (height[v] > height[u])
        swap(u, v);
    int d = height[u] - height[v];
    for (int i = 0; d; ++i, d >>= 1){
        if (d & 1)
            u = parent[u][i];
    }
    if (u == v) return u;

    for (int i = 19; i >= 0; --i)
        if (parent[u][i] != parent[v][i])
            u = parent[u][i], v = parent[v][i];
    return parent[u][0];
}

struct query{
    int u, v, k, idx;
    int b, e, p;

    query(int u=0, int v=0, int k=0, int idx=0) : u(u), v(v), k(k), idx(idx){
        if (en[v] < en[u])
            b = st[u], e = st[v] + 1, p = -1;
        else
            b = en[u], e = st[v] + 1, p = lca(u, v);
    }

    bool operator<(const query &q) const{
        int B1 = b / bsize;
        int B2 = q.b / bsize;
        if (B1 != B2) return B1 < B2;
        return (B1 & 1) ^ (e < q.e);
    }

    void print(){
        cout << u << " " << v << " " << k << " " << idx << " :: " << b << " " << e << " " << p << endl;
    }
};

struct SqrtList{
    const int bitSize = 10; // bucket size 2^10 = 1024
    int _count;
    vector<int> freq, bucketFreq;

    SqrtList(int n=0){
        int size = 1 << bitSize;
        n = (n + size - 1) / size * size, _count = 0;
        freq = vector<int>(n);
        bucketFreq = vector<int>(n >> bitSize);
    }

    int size(){
        return _count;
    }

    void add(int v){
        _count++;
        freq[v]++;
        bucketFreq[v >> bitSize]++;
    }

    void remove(int v){
        _count--;
        freq[v]--;
        bucketFreq[v >> bitSize]--;
    }

    int getKth(int k){
        int p = 0;

        while (k >= bucketFreq[p])
            k -= bucketFreq[p++];

        p <<= bitSize;
        while (k >= freq[p])
            k -= freq[p++];

        return p;
    }
} counting(maxn);

int freq[ maxn ];
bool state[ maxn ];

vector<int> _index[ maxn ];
int who[ maxn ];

void add(int v){
    if (freq[v])
        counting.remove(_index[v][freq[v]]);
    freq[v]++;
    counting.add(_index[v][freq[v]]);
}

void remove(int v){
    counting.remove(_index[v][freq[v]]);
    freq[v]--;
    if (freq[v])
        counting.add(_index[v][freq[v]]);
}

int globalB, globalE;

void toogle(int p){
    int u = order[p];

    if (!state[u] && globalB <= st[u] && en[u] < globalE)
        return;

    if (!state[u]){
        add(value[u]);
        state[u] = true;
    }
    else{
        remove(value[u]);
        state[u] = false;
    }
}

int getkth(int k){
    return who[counting.getKth( counting.size() - k )];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;

    cin >> n >> q;

    vector<int> vlist;

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        vlist.push_back( value[i] );
    }

    sort(vlist.begin(), vlist.end());
    vlist.resize( unique(vlist.begin(), vlist.end()) - vlist.begin() );
    int sz = (int)vlist.size();

    for (int i = 1; i <= n; ++i){
        value[i] = lower_bound(vlist.begin(), vlist.end(), value[i]) - vlist.begin();
        freq[ value[i] ]++;
    }

    vector<pii> L;
    for (int i = 0; i < sz; ++i){
        for (int j = 1; j <= freq[i]; ++j)
            L.push_back(pii(j, i));
        _index[i] = vector<int>(freq[i] + 1, -1);
        freq[i] = 0;
    }

    sort(L.begin(), L.end());
    for (int i = 0; i < n; ++i)
        _index[ L[i].second ][ L[i].first ] = i, who[i] = L[i].second;

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    vector<query> qlist(q);

    for (int i = 0; i < q; ++i){
        int u, v, k;
        cin >> u >> v >> k;

        if (st[u] > st[v])
            swap(u, v);

        qlist[i] = query(u, v, k, i);
    }

    sort(qlist.begin(), qlist.end());
    vector<int> answer( q );

    int b = 1, e = 1;

    for (auto &qry : qlist){
        globalB = qry.b, globalE = qry.e;

        while (e < qry.e)
            toogle( e++ );

        while (qry.b < b)
            toogle( --b );

        while (e > qry.e)
            toogle( --e );

        while (b < qry.b)
            toogle( b++ );

        if (qry.p != -1)
            toogle(st[qry.p]);

        int kth = getkth(qry.k);
        answer[ qry.idx ] = vlist[ kth ];

        if (qry.p != -1)
            toogle(st[qry.p]);
    }

    for (int i = 0; i < q; ++i)
        cout << answer[i] << endl;

    return 0;
}
\