#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

const int maxn = 200010;
const int mlog = 20;

int pos[ maxn ];
int vsize[ mlog ], len;

int mr[ maxn ][ mlog ], ml[ maxn ][ mlog ];
int dppref[ 1 << mlog ], dpsuff[ 1 << mlog ];

int bestcover[ maxn ];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n, V;
    cin >> n >> V;

    int v = V >> 1;

    for (int i = 0; i < n; ++i)
        cin >> pos[i];

    for (len = 0; vsize[len++] = v; v >>= 1);
    vsize[ len ] = V;

    for (int i = 0; i <= len; ++i){
        mr[ n - 1 ][i] = n - 1;
        ml[ 0 ][i] = 0;
    }

    for (int i = 1; i < n; ++i){
        for (int j = 0; j <= len; ++j){
            if (pos[i] - pos[i - 1] <= vsize[j])
                ml[i][j] = ml[i - 1][j];
            else
                ml[i][j] = i;
        }
    }

    for (int i = n - 2; i >= 0; --i){
        for (int j = 0; j <= len; ++j){
            if (pos[i + 1] - pos[i] <= vsize[j])
                mr[i][j] = mr[i + 1][j];
            else
                mr[i][j] = i;
        }
    }

    dppref[0] = -1;
    dpsuff[0] = n;

    int mask = (1 << len);

    for (int i = 1; i < mask; ++i){
        dppref[i] = 0;
        dpsuff[i] = n - 1;

        for (int j = 0; j < len; ++j){
            if (i >> j & 1){
                int m = i ^ (1 << j);

                // prefix

                if (dppref[m] == n - 1)
                    dppref[i] = n - 1;
                else
                    dppref[i] = max(dppref[i], mr[ dppref[m] + 1 ][j]);

                // suffix

                if (dpsuff[m] == 0)
                    dpsuff[i] = 0;
                else
                    dpsuff[i] = min( dpsuff[i], ml[ dpsuff[m] - 1 ][j]);
            }
        }
    }

    mask--;

    for (int i = 0; i < n; ++i)
        bestcover[i] = oo;

    for (int i = 0; i <= mask; ++i){
        int comp = mask ^ i;
        int pA = dppref[i], pB = dpsuff[i];
        bestcover[ pA ] = min( bestcover[ pA ], pB );
    }

    for (int i = n - 2; i >= 0; --i)
        bestcover[i] = min( bestcover[i], bestcover[i + 1] );

    for (int i = 0; i < n; ++i){
        int pA = ml[i][len], pB = mr[i][len];

        bool ok = false;

        if (pA == 0){
            if (dpsuff[ mask ] <= pB + 1)
                ok = true;
        }
        else
            ok = bestcover[pA - 1] <= pB + 1;

        cout << (ok ? "Possible" : "Impossible") << endl;
    }

    return 0;
}