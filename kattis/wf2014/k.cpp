#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000000 + 10;
const int maxlog = 21;

int go[ 2 * maxn ];
int fast_go[ 2 * maxn ][ maxlog ];
int x[ maxn ], y[ maxn ];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= 2 * n; ++i)
        go[i] = i;

    for (int i = 0; i < k; ++i){
        cin >> x[i] >> y[i];

        if (y[i] < x[i])
            y[i] += n;

        go[ x[i] ] = max( go[ x[i] ], y[i] + 1);
    }

    int size = 0, max_size = 0;

    for (int i = 1; i <= 2 * n; ++i){
        go[i] = max( go[i], go[i - 1] );
        fast_go[i][0] = go[i];

        if (go[i] == i) size = 0;
        else size++;

        max_size = max( size, max_size );
    }

    if (max_size < n){
        cout << "impossible" << endl;
        return 0;
    }

    for (int i = 1; i < maxlog; ++i)
        for (int j = 1; j <= 2 * n; ++j)
            fast_go[ j ][ i ] = fast_go[ fast_go[j][i - 1] ][i - 1];

    int answer = k + 1;

    for (int i = 1; i <= n; ++i){
        if (fast_go[i][ maxlog - 1 ] < i + n)
            continue;

        int total = 1, u = i, target = i + n;

        for (int j = maxlog - 1; j >= 0; --j){
            if ( fast_go[u][j] < target ){
                total += 1 << j;
                u = fast_go[u][j];
            }
        }

        answer = min(answer, total);
    }

    assert( answer <= k );
    cout << answer << endl;

    return 0;
} 