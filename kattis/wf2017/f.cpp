#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int maxn = 300;

int64 cost[maxn][maxn];
int64 dp[maxn][maxn];

int main(){
    #ifdef MARX
    freopen("test.in", "r", stdin);
    #endif

    int n, k;
    cin >> n >> k;

    vector< pair<int64,int64> > data(n);

    for (int i = 0; i < n; ++i)
        cin >> data[i].first >> data[i].second;

    sort(data.begin(), data.end());

    // misc

    auto sqr = [](int64 x){ return x * x; };

    auto calc_cost = [&](int beg, int end, int x){
        int64 answer = 0;
        for (int i = beg; i <= end; ++i)
            answer += sqr( data[i].first - x ) * data[i].second;
        return answer;
    };

    // prec cost

    for (int i = 0; i < n; ++i){
        for (int j = i, opt = data[i].first; j < n; ++j){
            int64 bestcost = calc_cost(i, j, opt);
            while (opt < 256){
                int64 nxtcost = calc_cost(i, j, opt + 1);
                if (nxtcost < bestcost){
                    bestcost = nxtcost;
                    opt++;
                }
                else break;
            }
            cost[i][j] = bestcost;
        }
    }

    // calc dp

    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;

    for (int p = 1; p <= n; ++p){
        for (int t = 1; t <= k; ++t)
            for (int i = 0; i < p; ++i)
                dp[p][t] = min(dp[p][t], dp[i][t - 1] + cost[i][p - 1]);
    }

    cout << dp[n][k] << endl;
}