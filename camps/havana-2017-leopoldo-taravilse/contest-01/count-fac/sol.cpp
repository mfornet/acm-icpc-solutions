#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 d[ maxn ];
int64 dp[ maxn ];
unordered_map<int,int64> prec;

int main(){/*
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    */
    int t; 
    //cin >> t;
    scanf("%d", &t);

    while (t--){
        int64 n; 
        scanf("%lld", &n);

        int64 it = 2;
        int foo = 0;

        while (it * it <= n){
            if (n % it == 0){
                d[ foo++ ] = it;
                d[ foo++ ] = n / it;
            }
            it++;
        }

        d[ foo++ ] = n;
        sort(d, d + foo);
        foo = unique( d, d + foo) - d;

        for (int i = 0; i < foo; ++i){
            int64 total = 0;

            if (prec.find( d[i] ) != prec.end()){
                dp[ i ] = prec[ d[i] ];
                continue;
            }

            for (int j = 0, t = i - 1; d[j] * d[j] <= d[i]; ++j){
                if (d[i] % d[j] == 0){
                    while (d[j] * d[t] != d[i])
                        t--;

                    int64 cur = dp[j] * dp[t];
                    if (j < t) cur *= 2;
                    total += cur;
                }
            }

            if (total == 0) total++;
            dp[ i ] = total;
            prec[ d[i] ] = total;
        }

        //cout << dp[foo - 1] << endl;
        printf("%lld\n", dp[ foo - 1 ]);
    }

    return 0;
}
