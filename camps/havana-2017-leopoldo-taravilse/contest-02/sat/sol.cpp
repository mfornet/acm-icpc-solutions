#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct sat{
    int n;
    vector<vector<int>> imp;

    sat(int n) : n(n), imp(2 * n) {}

    void add_edge(int u, int v){
        imp[u].push_back(v);
    }

    int neg(int u) { return (n << 1) - u - 1; }

    void implication(int u, int v){
        add_edge(u, v);
        add_edge(neg(v), neg(u));
    }

    void _or(int u, int v){
        implication(neg(u), v);
    }

    bool solve(){
        int size = 2 * n;
        vector<int>  S, B, I(size);

        function<void(int)> dfs = [&](int u){
            B.push_back( I[u] = S.size() );
            S.push_back( u );

            for (int v : imp[u]){
                if (!I[v]) dfs(v);
                else while (I[v] < B.back()) B.pop_back();
            }

            if (I[u] == B.back())
                for (B.pop_back(), ++size; I[u] < S.size(); S.pop_back())
                    I[ S.back() ] = size;
        };

        for (int u = 0; u < 2 * n; ++u)
            if (!I[u]) dfs(u);

        vector<bool> values(n);

        for (int u = 0; u < n; ++u)
            if (I[u] == I[neg(u)]) 
                return false;

        return true;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    sat S(n);

    for (int i = 1; i <= m; ++i){
        string a; cin >> a;
        string b; cin >> b; 

        auto parse = [&](string s){
            int n = 0;
            for (int i = 1; i < (int)s.length(); ++i)
                n = n * 10 + s[i] - '0';
            n--;

            if (s[0] == '-')
                n = S.neg( n );
            return n;
        };

        int u = parse(a);
        int v = parse(b);
/*
        cout << a << " " << u << endl;
        cout << b << " " << v << endl;
*/
        S._or( u, v );
    }

    cout << S.solve() << endl;

    return 0;
}
