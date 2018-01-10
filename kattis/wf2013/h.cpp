#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout<<#x<<"="<<x<<endl;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = 512;

int dp1[MAXN][MAXN][MAXN];
int dp2[MAXN][MAXN];
int dp3[MAXN];
bool mk[MAXN];

int solve(int n, vi &V){
    memset(dp1, 0, sizeof dp1);
    for (int i = 0; i < n; ++i){
        memset(mk, 0, sizeof mk);
        int cmax = 0, cmin = oo;
        for (int k = i; k < n; ++k){
            mk[ V[k] ] = true;

            cmax = max(cmax, V[k]);
            cmin = min(cmin, V[k]);

            int pnt = cmax;

            for (int j = k + 1; j < n; ++j){
                dp1[i][k][j] = dp1[i][k][j - 1];
                while (pnt > V[j]){
                    if (mk[pnt]) dp1[i][k][j]++;
                    --pnt;
                }
                if (V[j] > cmin) dp1[i][k][j]++;
//              cout << i << " " << k << " " << j << " " << dp1[i][k][j] << endl;
            }
        }
    }
//  cout << endl;

    for (int i = 2; i <= n; ++i){
        for (int j = 0; j + i - 1 < n; ++j){
            dp2[j][j + i - 1] = oo;
            for (int k = j; k + 1 < j + i; ++k){
                dp2[j][j + i - 1] = min(dp2[j][j + i - 1], dp2[j][k] + dp2[k + 1][j + i - 1] + dp1[j][k][j + i - 1]);
//              cout << j << " " << k << " " << j + i - 1 << endl;
//              cout << dp2[j][k] + dp2[k + 1][j + i - 1] + dp1[j][k][j + i - 1] << endl;
            }
        }
    }
    for (int i = 0; i < n; ++i){
        memset(mk, 0, sizeof mk);
        dp3[i] = oo;
        int mx = 0;
        for (int j = i; j >= 0; --j){
            mx = max(mx, V[j]);
            if (mk[ V[j] ]) break;
            mk[ V[j] ] = true;
            if (mx == i - j + 1){
                dp3[i] = min(dp3[i], dp2[j][i] + (j > 0 ? dp3[j - 1] : 0));
            }
        }
//      cout << dp3[i] << endl;
    }

    if (dp3[n - 1] >= oo) return -1;
    return dp3[n - 1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    cin >> n;
    vector<int> V(n);
    for (int i = 0; i < n; ++i)
        cin >> V[i];

    int ans = solve(n, V);
    if (ans == -1) cout << "impossible" << endl;
    else cout << ans << endl;

    return 0;
}

