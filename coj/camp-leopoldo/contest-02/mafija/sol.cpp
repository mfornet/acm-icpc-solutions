#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500000 + 10;

vi adj[ maxn ];
int go[ maxn ];
int ds[ maxn ];
bool ok[ maxn ];

int root(int a){
    return ds[a] < 0 ? a : ds[a] = root( ds[a] );
}

bool join(int a, int b){
    a = root(a), b = root(b);
    if (a == b) return false;
    if (ds[b] > ds[a])
        swap(a, b);
    ds[b] += ds[a];
    ds[a] = b;
    return true;
}

int dp[ maxn ][2];

int solve(int s){
    dp[s][0] = 0, dp[s][1] = 1;

    for (auto u : adj[s]){
        if (ok[u]) continue;
        solve(u);

        dp[s][0] += max( dp[u][0], dp[u][1] );
        dp[s][1] += dp[u][0];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    memset(ds, -1, sizeof ds);
    vector<int> cyc;

    for (int i = 1; i <= n; ++i){
        cin >> go[i];
        adj[ go[i] ].push_back( i );

        if (!join(i, go[i])){
            cyc.push_back( i );
        }
    }

    int answer = 0;

    for (auto u : cyc){
        while( !ok[u] ){
            ok[ u ] = true;
            u = go[ u ];
        }

        int v = u;
        vector<int> sol(4, -1);

        do{
            solve(v);
            vector<int> csol(4);

            if (sol[0] == -1){
                csol[0] = dp[v][0];
                csol[1] = -oo;
                csol[2] = -oo;
                csol[3] = dp[v][1];
            }
            else{
                csol[0] = dp[v][0] + max( sol[0], sol[1] ); 
                csol[1] = sol[0] + dp[v][1];
                csol[2] = dp[v][0] + max( sol[2], sol[3] ); 
                csol[3] = sol[2] + dp[v][1];
            }

            sol.swap( csol );

            v = go[v];
        } while (v != u);

        answer += max({sol[0], sol[1], sol[2]});
    } 

    cout << answer << endl;

    return 0;
}
