#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200010;

int ds[ maxn ], answer[ maxn ];
int x[ maxn ], v[ maxn ], pnt = 0;
int U[ maxn ], V[ maxn ];

int root(int a){
    while (ds[a] >= 0)
        a = ds[a];
    return a;
}

void join(int a, int b){
    a = root(a), b = root(b);
    if (a == b)
        pnt += 2;
    else{
        if (ds[a] < ds[b])
            swap(a, b);
        x[pnt] = a, v[pnt] = ds[a]; pnt++;
        x[pnt] = b, v[pnt] = ds[b]; pnt++;
        ds[b] += ds[a];
        ds[a] = b;
    }
}

int size(int a, int b){
    a = root(a), b = root(b);
    if (a == b) return -ds[a];
    return -ds[a] - ds[b];
}

struct query{
    int u, v, z, idx;
};

void rollback(){
    for (int i = 0; i < 2; ++i){
        --pnt;
        ds[ x[pnt] ] = v[pnt];
    }
}

void solve(int b, int m, int e, vector<query> Q){
    vector<query> L, H;

    for (auto q : Q){
        if (b == e)
            answer[ q.idx ] = b + 1;
        else{
            if (size( q.u, q.v ) >= q.z)
                L.push_back(q);
            else
                H.push_back(q);
        }
    }

    // cout << b << " " << m << " " << e << endl;
    // for (auto l : L) cout << l.idx << " "; cout << endl;
    // for (auto l : H) cout << l.idx << " "; cout << endl;
    // cout << endl;

    if (!H.empty()){
        int tm = (m + 1 + e) / 2;
        for (int i = m + 1; i <= tm; ++i)
            join(U[i], V[i]);
        solve(m + 1, tm, e, H);
        for (int i = m + 1; i <= tm; ++i)
            rollback();
    }
    if (!L.empty()){
        int tm = (b + m) / 2;
        for (int i = tm + 1; i <= m; ++i)
            rollback();
        solve(b, tm, m, L);
        for (int i = tm + 1; i <= m; ++i)
            join(U[i], V[i]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    freopen("dfast.out", "w", stdout);
#endif

    memset( ds, -1, sizeof ds );

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i)
        cin >> U[i] >> V[i];

    int q; cin >> q;

    vector<query> Q(q);

    for (int i = 0; i < q; ++i){
        cin >> Q[i].u >> Q[i].v >> Q[i].z;
        Q[i].idx = i;
    }

    for (int i = 0; i <= m / 2; ++i)
        join( U[i], V[i] );

    solve(0, m / 2, m, Q);

    for (int i = 0; i < q; ++i)
        cout << answer[i] << endl;

    cerr << 1. * clock() / CLOCKS_PER_SEC << endl;

    return 0;
}