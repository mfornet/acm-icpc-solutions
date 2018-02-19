#include <bits/stdc++.h>

// #define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 0x3f3f3f3f;
const int maxn = 110;

int n, k;
int m[maxn][maxn];
int a[maxn], b[maxn]; // b - mate
bool dp[maxn][maxn];

bool dfs(int s, vector<bool> &mark){
    if (mark[s]) return false;
    mark[s] = true;

    for (int i = 0; i < n; ++i){
        if (m[s][i] == -1) 
            continue;

        if (b[i] == -1 || dfs(b[i], mark)){
            b[i] = s;
            a[s] = i;
            return true;
        }
    }

    return false;
}

bool solve(){
    memset(a, -1, sizeof a);
    memset(b, -1, sizeof b);

    vector<int> order(n);

    for (int i = 0; i < n; ++i)
        order[i] = i;

    random_shuffle(order.begin(), order.end());

    for (int i = 0; i < n; ++i){
        vector<bool> mark(n);
        bool ok = dfs(order[i], mark);

        if (!ok){
            cout << "No" << endl;
            exit(0);
        }
    }

    int t = 0;

    for (int i = 0; i < n; ++i){
        t = (t + m[i][a[i]]) % k;
        cerr << "edge: " << i << " " << a[i] << " " << m[i][a[i]] << endl;
    }

    cerr << "remainder: " << t << endl;

    for (int i = 0; i < n; ++i){
        cerr << "start: " << i << endl;
        queue<pii> q; 

        memset(dp, 0, sizeof dp);

        dp[i][t] = true;
        q.push(pii(i,t));

        while (!q.empty()){
            pii cur = q.front(); q.pop();
            int u = cur.first, r = cur.second;

            cerr << u << " " << r << endl;

            if (u == i && r == 0){
                return true;
            }

            for (int j = 0; j < n; ++j){
                if (m[u][j] == -1) continue;

                int v = b[j];
                int rr = (r + m[u][j] - m[v][j]) % k;
                if (rr < 0) rr += k;

                if (!dp[v][rr]){
                    cerr << "--" << endl;
                    cerr << u << " " << r << " :" << j << ": " << v << " " << rr << endl; 
                    cerr << m[u][j] << " " << m[v][j] << endl;
                    dp[v][rr] = true;
                    q.push(pii(v, rr));
                }
            }
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cin >> m[i][j];
    }

    while (clock() / CLOCKS_PER_SEC < 3.2){
        // cout << "ITERATION" << endl;

        if (solve()){
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}