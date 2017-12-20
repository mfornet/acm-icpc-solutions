#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 32;

int sign[ maxn ];
int value[ maxn ];

int dp[maxn][maxn][6001];
int sz[maxn][maxn];

void calc(int b, int e){
    if (sz[b][e]) return;

    if (b == e){
        dp[b][e][ sz[b][e]++ ] = value[b];
        return;
    }

    vector<bool> t(6001);

    for (int i = b; i < e; ++i){
        calc(b, i);
        calc(i + 1, e);

        for (int cx = 0; cx < sz[b][i]; ++cx)
            for (int cy = 0; cy < sz[i + 1][e]; ++cy){
                int x = dp[b][i][cx];
                int y = dp[i + 1][e][cy];
                t[ x + sign[i + 1] * y + 3000] = true;
            }
    }
    
    for (int i = -3000; i <= 3000; ++i)
        if (t[ i + 3000 ])
            dp[b][e][ sz[b][e]++ ] = i;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        if (i){
            string s; cin >> s;
            sign[i] = s == "+" ? 1 : -1;
        }
        cin >> value[i];
    }

    calc(0, n - 1);
    cout << sz[0][n - 1] << endl;

    return 0;
}
