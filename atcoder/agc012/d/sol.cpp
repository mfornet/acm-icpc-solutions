#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200010;
const int mod = 1000000007;

int fak[ maxn ], inv[ maxn ];

int modpow(int a, int n){
    int v = 1;

    while (n){
        if (n & 1)
            v = 1LL * v * a % mod;
        n >>= 1;
        a = 1LL * a * a % mod;
    }

    return v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    fak[0] = inv[0] = 1;

    for (int i = 1; i < maxn; ++i){
        fak[i] = 1LL * fak[i - 1] * i % mod;
        inv[i] = modpow( fak[i], mod - 2 );
    }

    int n, x, y;
    cin >> n >> x >> y;

    vector<vi> id(n), adj(n);
    vector<int> c(n), w(n);

    auto add_edge = [&](int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    for (int i = 0; i < n; ++i){
        cin >> c[i] >> w[i];
        id[ --c[i] ].push_back(i);
    }

    pii A(oo, -1), B(oo, -1);

    for (int i = 0; i < n; ++i){
        if (id[i].empty()) continue;

        vi &cid = id[i];

        int pos = min_element(cid.begin(), cid.end(), [&](int u, int v){
            return w[u] < w[v];
        }) - cid.begin();

        swap(cid[pos], cid[0]);

        for (int j = 1; j < (int)cid.size(); ++j){
            if (w[ cid[0] ] + w[ cid[j] ] <= x)
                add_edge( cid[0], cid[j] );
        }

        pii C( w[ cid[0] ], cid[0] );

        if (C < A) swap(A, C);
        if (C < B) swap(B, C);
    }

    for (int i = 0; i < n; ++i){
        if (A.second != -1 && c[i] != c[ A.second ] && w[i] + A.first <= y)
            add_edge(i, A.second);
        if (B.second != -1 && c[i] != c[ B.second ] && w[i] + B.first <= y)
            add_edge(i, B.second);
    }

    vector<bool> seen(n);
    vector<int> count(n), lst, last(n, -1);

    int answer = 1, tm = -1;

    function<void(int u)> dfs = [&](int u){
        seen[u] = true;

        if (last[ c[u] ] != tm){
            count[ c[u] ] = 0;
            last[ c[u] ] = tm;
            lst.push_back( c[u] );
        }

        count[ c[u] ]++;

        for (auto v : adj[u]){
            if (!seen[v])
                dfs(v);
        }
    };

    for (int i = 0; i < n; ++i){
        if (seen[i]) continue;

        lst.clear();
        tm = i;

        dfs(i);

        int cur_answer = 1;
        int total = 0;

        for (auto u : lst){
            cur_answer = 1LL * cur_answer * inv[ count[u] ] % mod;
            total += count[u];
        }

        cur_answer = 1LL * cur_answer * fak[ total ] % mod;
        answer = 1LL * answer * cur_answer % mod;
    }

    cout << answer << endl;

    return 0;
}