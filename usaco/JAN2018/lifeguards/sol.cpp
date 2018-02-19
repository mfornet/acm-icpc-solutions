#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

const int maxn = 100000 + 10;
const int maxk = 100 + 10;

int dp[maxn][maxk][2];

int main(){

#ifndef MARX
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    cin >> n >> k;

    vector<pii> _seg(n);

    for (int i = 0; i < n; ++i)
        cin >> _seg[i].first >> _seg[i].second;

    sort(_seg.begin(), _seg.end(), [&](const pii &a, const pii &b){
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    vector<pii> seg;

    for (int i = 0; i < n; ++i){
        pii u = _seg[i];

        if (seg.empty() || u.second > seg.back().second)
            seg.push_back(u);
        else
            k--;
    }

    // for (auto x : seg)
    //     cout << x.first << " " << x.second << endl;
    // cout << endl;

    k = max(k, 0);
    n = seg.size();

    for (int i = 1; i <= k; ++i){
        dp[n][i][0] = dp[n][i][1] = -oo;
    }

    for (int i = n - 1; i >= 0; --i){
        auto u = seg[i];
        int size_u = u.second - u.first;

        int p = lower_bound(seg.begin(), seg.end(), pii(u.second, 0)) - seg.begin();
        p--;

        // cout << "position: " << i << " : " << p << " : " << size_u << endl;

        auto v0 = seg[p];

        for (int j = 0; j <= k; ++j){
            dp[i][j][0] = dp[i][j][1] = -oo;

            dp[i][j][0] = j ? dp[i+1][j-1][0] : -oo;

            if (p > i){
                dp[i][j][0] = max(dp[i][j][0], 
                        dp[p][max(0, j-(p-i-1))][1] + size_u - (u.second - v0.first));

                dp[i][j][1] = max(dp[i][j][1],
                        dp[p][max(0, j-(p-i-1))][1] + size_u - (u.second - v0.first));
            }

            dp[i][j][0] = max(dp[i][j][0],
                    dp[p+1][max(0,j-(p-i))][0] + size_u);

            dp[i][j][1] = max(dp[i][j][1],
                    dp[p+1][max(0,j-(p-i))][0] + size_u);

            // cout << i << " " << j << " " << 0 << " :: " << dp[i][j][0] << endl;
            // cout << i << " " << j << " " << 1 << " :: " << dp[i][j][1] << endl;
            // cout << endl;
        }
    }

    // cout << "k:" << k << endl;

    cout << dp[0][k][0] << endl;

    return 0;
}
