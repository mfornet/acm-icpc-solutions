#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 25;

vector<int> data[ maxn ];
vector<int> cand[ maxn ];
vector<int> pos[ maxn ][ maxn ];

int answer[ maxn ][ maxn ];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        int t; cin >> t;

        for (int j = 0; j < t; ++j){
            string s; cin >> s;
            int value = 0;

            for (auto c : s)
                value |= 1 << (c - 'a');

            data[ i ].push_back( value );

            for (auto c : s)
                pos[ i ][ c - 'a' ].push_back(j);
        }
    }

    memset(answer, -1, sizeof answer);

    for (int i = 0; i < n; ++i){

        // reset
        for (int j = 0; j < n; ++j)
            cand[j] = data[j];


        answer[i][i] = 0;
        queue<int> q;
        q.push(i);

        while (!q.empty()){
            int u = q.front(); q.pop();

            for (int j = 0; j < n; ++j){
                if (answer[j][i] != -1) continue;

                bool ok = false;

                for (auto idx : pos[j][u]){
                    cand[j][ idx ] ^= 1 << u;
                    if (cand[j][idx] == 0){
                        ok = true;
                        break;
                    }
                }

                if (ok){
                    answer[j][i] = answer[u][i] + 1;
                    q.push(j);
                }
            }
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cout << answer[i][j] << " \n"[j + 1 == n];

    return 0;
} 