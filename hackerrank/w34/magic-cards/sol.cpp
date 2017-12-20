#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000000 + 10;

int n, m, q;
vector<bool> arr[ maxn ];
int64 memo[ maxn ][ 20 ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif

    cin >> n >> m >> q;

    for (int i = 1; i <= n; ++i){
        int t; cin >> t;
        arr[i] = vector<bool>(m);

        for (int j = 0; j < t; ++j){
            int v; cin >> v;
            v--;
            arr[i][v] = true;
        }
    }

    int size = __lg(m) + 1;

    int64 maxsum = 0;
    for (int i = 1; i <= m; ++i)
        maxsum += 1LL * i * i;

    while (q--){
        int l, r;
        cin >> l >> r;
        int d = r - l + 1;

        if (d >= size){
            cout << maxsum << endl;
            continue;
        }

        if (memo[l][d] == 0){
            map<int,int64> seen;

            for (int i = 0; i < m; ++i){
                int curmask = 0;
                for (int j = 0; j < d; ++j)
                    curmask = curmask * 2 + int(arr[j + l][i]);
                seen[ curmask ] += 1LL * (i + 1) * (i + 1);
            }

            if (seen.size() < (1 << d))
                memo[l][d] = maxsum;
            else{
                for (auto &p : seen)
                    memo[l][d] = max( memo[l][d], maxsum - p.second );
            }
        }

        cout << memo[l][d] << endl;
    }

    return 0;
}