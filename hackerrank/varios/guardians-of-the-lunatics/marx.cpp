#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const int maxn = 8010;

int64 value[maxn];

int64 cost(int i, int j){
    return (value[j] - value[i]) * (j - i);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        value[i] += value[i-1];
    }

    vector<int64> dp(n+1, oo);
    dp[0] = 0;

    for (int i = 1; i <= k; ++i){
        vector<int64> ndp(n+1);

        function<void(int,int,int,int)> solve = [&](int b, int e, int optB, int optE){
            if (e < b) return;
            int m = (b + e) / 2;

            int limit = min(optE, m - 1);

            int64 best = oo;
            int opt = -1;

            for (int i = optB; i <= limit; ++i){
                int64 cur = dp[i] + cost(i, m);
                if (cur < best){
                    best = cur;
                    opt = i;
                }
            }

            ndp[m] = best;

            solve(b, m - 1, optB, opt);
            solve(m + 1, e, opt, optE);
        };

        solve(1, n, 0, n);
        dp.swap(ndp);
    }

    cout << dp.back() << endl;
}