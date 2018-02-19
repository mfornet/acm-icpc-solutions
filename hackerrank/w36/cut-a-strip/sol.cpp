#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(vector<vector<int>> &A, int k){
    int n = A.size() - 1, m = A[0].size() - 1;
    int answer = -139400;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            A[i][j] += A[i-1][j];

    for (int i = 1; i <= n; ++i){
        vector<deque<pii>> q(m+1);
        for (int t = 1; t <= m; ++t)
            q[t].push_back({i - 1, A[i - 1][t]});

        vector<int> best(m+1, 0);
        for (int j = i; j <= n; ++j){
            int dp0 = -139400, dp1 = -139400;
            int stripe_value = -139400;

            for (int t = 1; t <= m; ++t){
                while (!q[t].empty() && q[t].back().second <= A[j][t]){
                    q[t].pop_back();
                }
                q[t].push_back({j, A[j][t]});
                while (q[t].front().first < j - k){
                    q[t].pop_front();
                }

                best[t] = min(A[j][t] - q[t].front().second, best[t]);

                int x = A[j][t] - A[i - 1][t]; // current value
                int y = x - best[t];               // best value

                dp1 = max({dp1 + x, dp0 + y, y});
                dp0 = max(dp0 + x, x);

                stripe_value = max({stripe_value, dp0, dp1});
            }
            answer = max(answer, stripe_value);
        }
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> A(n+1, vector<int>(m+1));
    vector<vector<int>> B(m+1, vector<int>(n+1));

    int MIN = 10000;
    int SUM = 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j){
            cin >> A[i][j];
            B[j][i] = A[i][j];

            MIN = min(MIN, A[i][j]);
            SUM += A[i][j];
        }

    if (MIN >= 0){
        cout << SUM - MIN << endl;
        return 0;
    }

    int value_a = solve(A, k);
    int value_b = solve(B, k);

    cout << max(value_a, value_b) << endl;

    return 0;
}