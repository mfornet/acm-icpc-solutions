#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200000 + 10;
const int mod = 1000000007;

vi adj[maxn];
bool mk[maxn];
int q[maxn], p[maxn], sz[maxn], mc[maxn];

int add(int a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

struct matrix{
    int a, b, c, d;

    matrix operator+(const matrix &m) const{
        matrix ans = {add(a,m.a), add(b,m.b), add(c,m.c), add(d,m.d)};
        return ans;
    }

    matrix operator*(const matrix &m) const{
        matrix ans = {  add(1LL * a * m.a % mod, 1LL * b * m.c % mod),
                        add(1LL * a * m.b % mod, 1LL * b * m.d % mod),
                        add(1LL * c * m.a % mod, 1LL * d * m.c % mod),
                        add(1LL * c * m.b % mod, 1LL * d * m.d % mod)
                    };
        return ans;
    }

    void print(){
        cout << a << " " << b << "\n" << c << " " << d << "\n" << endl;
    }
};

matrix value[ maxn ];

matrix matpow(matrix m, int n){
    matrix a = {1, 0, 0, 1};
    while (n){
        if (n & 1)
            a = a * m;
        m = m * m;
        n >>= 1;
    }
    return a;
}

int centroid(int c){
    int b = 0, e = 0;
    q[e++] = c, p[c] = -1, sz[c] = 1, mc[c] = 0;

    while (b < e){
        int u = q[b++];
        for (auto v : adj[u]) if (v != p[u] && !mk[v])
                p[v] = u, sz[v] = 1, mc[v] = 0, q[e++] = v;
    }

    for (int i = e - 1; ~i; --i){
        int u = q[i];
        int bc = max(e - sz[u], mc[u]);
        if (2 * bc <= e) return u;
        sz[p[u]] += sz[u], mc[p[u]] = max(mc[p[u]], sz[u]);
    }

    assert(false);
    return -1;
}

matrix dfs(int s, int p, matrix t){
    t = t * value[s];
    matrix answer = t;

    for (auto u : adj[s]){
        if (u == p || mk[u])
            continue;
        answer = answer + dfs(u, s, t);
    }

    return answer;
}

matrix solve(int s){
    int c = centroid(s);

    matrix answer = value[c];
    matrix current = value[c];
    matrix eye = {1,0,0,1};

    mk[c] = true;

    // cout << "centroid: " << c << endl;

    for (auto u : adj[c]){
        if (mk[u]) continue;
        matrix T = dfs(u, c, eye);
        matrix A = current * T;

        // cout << "======" << endl;
        // T.print();
        // current.print();
        // A.print();

        answer = answer + A + A;
        // cout << answer.a << endl;
        // cout << endl;
        current = current + T * value[c];
    }

    // cout << answer.a << endl;

    for (auto u : adj[c]){
        if (mk[u]) continue;
        matrix C = solve(u);
        answer = answer + C;
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;

        adj[ u ].push_back( v );
        adj[ v ].push_back( u );
    }

    matrix fib = {1, 1, 1, 0};

    for (int i = 1; i <= n; ++i){
        int v; cin >> v;
        value[i] = matpow(fib, v);
        // value[i].print();
    }

    matrix answer = solve(1);
    cout << answer.a << endl;

    return 0;
}