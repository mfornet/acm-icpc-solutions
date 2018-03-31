#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 18;
const int64 mod = 1000000007;

int64 value[ 1 << maxn ];
int64 dp[ 1 << maxn ];
int64 fav[ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> fav[i];

    for (int i = 0; i < (1 << n); ++i){
        int64 f = 0;
        value[i] = 1;
        for (int j = 0; j < n; ++j)
            if (i >> j & 1)
                value[i] = value[i] * fav[j] % mod, f++;
        value[i] *= f;
    }

    for (int i = 1; i < (1 << n); ++i){
        if ((i & (i - 1)) == 0){
            dp[i] = 0;
            continue;
        }
        dp[i] = oo;

        for (int j = i & (i - 1); j; j = i & (j - 1)){
            int u = i ^ j;
            dp[i] = min( dp[i], dp[j] + dp[u] + value[j] + value[u] );
        }
    }

    cout << dp[ (1 << n) - 1 ] << endl;

    return 0;
}
