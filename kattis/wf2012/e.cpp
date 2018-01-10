#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 80;

const int MAX_GO = 20000;

char adj[maxn][maxn];

vi a[ maxn ], b[ maxn ];
int order[maxn];
int deg[maxn];

int taken[maxn];
int answer[maxn];
int tosel[maxn];

int best, N, iter;

void go(int p, int cur){
    if (cur == best || iter == MAX_GO) 
        return;
    
    if (p == N){
        best = cur;
        
        for (int i = 0; i < cur; ++i)
            answer[i] = taken[i];

        return;
    }

    iter++;

    int u = order[p];

    for (auto x : b[u]){
        tosel[x] = 0;
        for (auto y : a[x])
            tosel[x] += deg[y] == 0;
    }

    sort(b[u].begin(), b[u].end(), [&](int x, int y){
        return tosel[x] > tosel[y];
    });

    for (int i = 0, k; i < (int)b[u].size(); ++i){
        int v = b[u][i];

        for (int j = 0; j < (int)a[v].size(); ++j)
            deg[ a[v][j] ]++;

        taken[cur] = v;

        for (k = p; k < N && deg[ order[k] ]; ++k);

        go(k, cur + 1);

        if (iter == MAX_GO) return;

        for (int j = 0; j < (int)a[v].size(); ++j)
            deg[ a[v][j] ]--;
    }
}

void init(int n){
    for (int i = 0; i < n; ++i){
        a[i].clear(); b[i].clear();
        order[i] = deg[i] = 0;
    }
    N = n;
    best = N + 1;
}

void solve(int n){
    init(n);

    for (int i = 0; i < n; ++i){
        cin >> adj[i];
        adj[i][i] = '1';

        for (int j = 0; j < n; ++j){
            if (adj[i][j] == '1'){
                a[i].push_back(j);
                b[j].push_back(i);
            }
        }
    }

    iota(order, order + n, 0);
    
    sort(order, order + n, [&](int u, int v){
        return b[u].size() < b[v].size();
    });

    // for (int i = 0; i < n; ++i)
    //  cout << order[i] << endl;

    iter = 0;

    go(0, 0);
    cout << best;
    for (int i = 0; i < best; ++i)
        cout << " " << answer[i] + 1;
    cout << endl;
    // exit(0);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n;
    int tc = 1;

    while (cin >> n){
        cout << "Case " << tc++ << ": ";
        solve(n);
    }

    return 0;
} 