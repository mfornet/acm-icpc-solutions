#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

string player[2] = {
    "Takeover Incorporated",
    "Buyout Limited"
};

int64 V[2][maxn];
int64 K[2][maxn];

bool check(int n, int m){
    for (int i = 0; i < n; ++i) K[0][i] = V[0][i];
    for (int i = 0; i < m; ++i) K[1][i] = V[1][i];

    while (n && m){
        if (K[1][m - 1] > K[0][n - 1])
            n--;
        else if (m > 1)
        {
            K[1][m - 2] += K[1][m - 1];
            m--;
        }

        if (K[0][n - 1] > K[1][m - 1])
            m--;
        else if (n > 1){
            K[0][n - 2] += K[0][n - 1];
            n--;
        }
    }

    return m == 0;
}

int solve(int n, int m){
    for (int i = 0; i < n; ++i)
        cin >> V[0][i];
    sort(V[0], V[0] + n);

    for (int i = 0; i < m; ++i)
        cin >> V[1][i];
    sort(V[1], V[1] + m);

    if (V[0][n - 1] > V[1][m - 1]){
        if (check(n, m - 1))
            return 0;
    }

    if (n > 1){
        V[0][n - 2] += V[0][n - 1];
        if (check(n - 1, m))
            return 0;
    }

    return 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n, m;

    int tc = 1;

    while (cin >> n >> m)
        cout << "Case " << tc++ << ": " << player[ solve(n, m) ] << endl;

    return 0;
}