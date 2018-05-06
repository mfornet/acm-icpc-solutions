#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(){
    int n; cin >> n;

    vector<int64> dp(2);
    dp[1] = oo;

    for (int i = 0; i < n; ++i){
        int64 x; cin >> x;
        int p = upper_bound(dp.begin(), dp.end(), 6 * x) - dp.begin();

        for (int j = p - 1; ~j; --j)
            dp[j + 1] = min(dp[j + 1], dp[j] + x);

        if (dp.back() != oo)
            dp.push_back(oo);
    }

    assert(dp.size() <= 1000);

    return dp.size() - 2;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc){
        int ans = solve();
        cout << "Case #" << tc << ": " << ans << endl;
    }


    return 0;
}