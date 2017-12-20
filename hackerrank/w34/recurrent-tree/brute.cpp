#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int64 mod = 1000000007;

vi adj[ maxn ];
int64 value[ maxn ];

map<int64,int64> memo;

int64 fib(int64 v){
    if (v <= 1) return 1;

    if (memo.find(v) == memo.end()){
        int64 a = (v - 2) / 2;
        int64 b = (v - 2 + 1) / 2;
        int64 c = v / 2;
        int64 d = (v + 1) / 2;

        memo[v] = (fib(a) * fib(b) % mod + fib(c) * fib(d) % mod) % mod;
    }

    return memo[v];
}

int64 dfs(int s, int p, int64 v){
    v += value[s];
    int64 answer = fib(v);

    for (auto u : adj[s])
        if (u != p)
            answer = (answer + dfs(u, s, v)) % mod;

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // for (int i = 0; i <= 100; ++i)
    //     cout << fib(i) << endl;
    // exit(0);

    int n; cin >> n;

    for (int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        adj[ u ].push_back( v );
        adj[ v ].push_back( u );
    }

    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    int64 answer = 0;

    for (int i = 1; i <= n; ++i)
        answer = (answer + dfs(i, i, 0)) % mod;

    cout << answer << endl;

    return 0;
}