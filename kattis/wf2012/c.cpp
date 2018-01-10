#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 20;

int dist[maxn][maxn];
int DPA[1 << maxn][maxn];
int DPB[1 << maxn][maxn];

int calc(int mask, int fin, int DP[1 << maxn][maxn]){
    int &answer = DP[mask][fin];

    if (answer != -1) return answer;
    answer = oo;

    if ( (mask & (mask - 1)) ){
        
        mask ^= 1 << fin;
        int tmask = mask;
        for (int i = 0; tmask; ++i){
            if (tmask >> i & 1){
                tmask ^= 1 << i;
                answer = min(answer, calc(mask, i, DP) + dist[i][fin] );
            }
        }

    }

    return answer;
}

void solve(int n, int m){
    memset(dist, oo, sizeof dist);

    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;

    for (int i = 0; i < m; ++i){
        int u, v, t;
        cin >> u >> v >> t;
        dist[u][v] = dist[v][u] = t;
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );

    if (n == 3){
        int answer = 2 * (dist[0][1] + dist[1][2]);
        cout << answer << endl;
        return;
    }

    memset( DPA, -1, sizeof DPA );
    memset( DPB, -1, sizeof DPB );

    DPA[1][0] = 0;
    DPB[1 << (n - 1)][n - 1] = 0;

    int t = 1 << (n - 1);
    int f = (1 << (n - 1)) - 2;
    int h = (n - 2) / 2;

    int answer = oo;

    // cout << endl;
    // cout << "h: " << h << endl;

    for (int i = 0; i < (1 << (n - 1)); i += 2){
        if (__builtin_popcount(i) == h){
            // cout << i << endl;

            int a = i, b = f ^ i;
            // cout << bitset<5>(a) << " " << bitset<5>(b) << endl;

            int as = a | 1, bs = b | 1;
            int at = a | t, bt = b | t;

            int X = oo, Y = oo;

            for (int u = 1; u < n - 1; ++u){
                if ((a >> u & 1) == 0) continue;

                for (int v = 1; v < n - 1; ++v){
                    if ((b >> v & 1) == 0) continue;

                    X = min(X, calc(as, u, DPA) + dist[u][v] + calc(bt, v, DPB));
                    Y = min(Y, calc(at, u, DPB) + dist[v][u] + calc(bs, v, DPA));
                    // cout << "XY: " << X << " " << Y << endl;
                }
            }

            answer = min(answer, X + Y);
            // cout << "answer: " << answer << endl;
        }
    }

    cout << answer << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n, m;
    int tc = 1;

    while ( cin >> n >> m ){
        cout << "Case " << tc++ << ": ";
        solve(n, m);
    }

    return 0;
} 