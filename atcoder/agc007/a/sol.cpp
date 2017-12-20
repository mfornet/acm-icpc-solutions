#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int mat[20][20];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i){
        string s; cin >> s;
        for (int j = 0; j < m; ++j)
            mat[i][j] = s[j] == '#';
    }

    int x = 0, y = 0;
    while (mat[x][y]){
        mat[x][y]--;
        if (mat[x+1][y]) x++;
        else if (mat[x][y+1]) y++;
    }

    bool ok = true;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (mat[i][j]) ok = false;

    cout << (ok ? "Possible" : "Impossible") << endl;

    return 0;
}
