#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<vector<double>> dp(n + 1, vector<double>(k + 1));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = i;

    for (int j = 1; j <= k; ++j){
        for (int i = 0; i < n; ++i)
            dp[i][j] = .5 * (dp[i][j - 1] + dp[i + 1][j - 1]);
        dp[n][j] = .5 * (dp[n - 1][j - 1] + dp[n][j - 1]);
    }


    cout.precision(10);
    cout << fixed << dp[0][k] << endl;

    return 0;
}
