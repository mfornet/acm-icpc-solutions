#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 8000 + 10;

int n, A[ maxn ];           // value-array
vector<int> P[ maxn ];      // positions
int answer[ maxn ][ maxn ];
int freq[ 2 * maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> n >> q;

    map<int,int> compress;
    int cur_value = 0;

    for (int i = 1; i <= n; ++i){
        cin >> A[i];
        if (compress.find(A[i]) == compress.end())
            compress[ A[i] ] = ++cur_value;
        A[i] = compress[ A[i] ];
        P[ A[i] ].push_back( i );
    }

    memset( answer, -1, sizeof answer );

    const int delta = maxn;

    while (q--){
        int u, v;
        cin >> u >> v;
        u = compress[u], v = compress[v];
        if (u == v) u = v = 0;
        if (u > v) swap(u, v);

        // cout << u << " " << v << endl;

        if (answer[u][v] == -1){
            // calculate

            int lo = 0, hi = 0, last = 0, value = 0;
            int p = 0, q = 0, cur, sign;

            freq[ delta ] = 0;

            while (p < P[u].size() && q < P[v].size()){
                if (P[u][p] < P[v][q])
                    cur = P[u][p++], sign = 1;
                else
                    cur = P[v][q++], sign = -1;

                freq[ value + delta ] += cur - last;
                last = cur;
                value += sign;
                if (value > hi){ freq[++hi + delta] = 0; }
                if (value < lo){ freq[--lo + delta] = 0; }
            }

            while (p < P[u].size()){
                cur = P[u][p++], sign = 1;
                freq[ value + delta ] += cur - last;
                last = cur;
                value += sign;
                if (value > hi){ freq[++hi + delta] = 0; }
                if (value < lo){ freq[--lo + delta] = 0; }
            }

            while (q < P[v].size()){
                cur = P[v][q++], sign = -1;
                freq[ value + delta ] += cur - last;
                last = cur;
                value += sign;
                if (value > hi){ freq[++hi + delta] = 0; }
                if (value < lo){ freq[--lo + delta] = 0; }
            }

            freq[ value + delta ] += n + 1 - last;

            answer[u][v] = 0;
            for (int i = lo; i <= hi; ++i){
                // cout << i << " " << freq[i + delta] << endl;
                answer[u][v] += freq[i + delta] * (freq[i + delta] - 1) / 2;
            }
        }

        cout << answer[u][v] << endl;
    }

    return 0;
}