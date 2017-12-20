#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(){
    int k, n;
    cin >> k >> n;

    vector<int> value(n + 1), dp(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    for (int i = 1; i <= k; ++i){
        vector<int> ndp(n + 1);

        for (int j = 1; j <= n; ++j){
            ndp[j] = max(dp[j], ndp[j - 1]);

            for (int r = 1; r <= j; ++r)
                ndp[j] = max(ndp[j], dp[r - 1] + value[j] - value[r]);
        }
        dp.swap(ndp);
    }

    return dp.back();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> q;

    while (q--)
        cout << solve() << endl;

    return 0;
}