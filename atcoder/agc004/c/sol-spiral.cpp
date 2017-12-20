#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500 + 10;

int board[maxn][maxn];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vi> mat(n, vi(m));

    for (int i = 0; i < n; ++i){
        string s; cin >> s;
        for (int j = 0; j < m; ++j)
            mat[i][j] = s[j] == '#';
    }

    int x = -1, y = 0;
    int sx = n, sy = m - 1;
    int k = 0;

    while (sx > 0 || sy > 0){
        int size = abs(dx[k]) * sx + abs(dy[k]) * sy;
        for (int i = 0; i < size; ++i){
            x += dx[k];
            y += dy[k];
            board[x][y] = 1;
        }
        sx -= 2 * abs(dx[k]);
        sy -= 2 * abs(dy[k]);
        k = (k + 1) & 3;
    }

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << ".#"[mat[i][j] || board[i][j]];
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << ".#"[mat[i][j] || !board[i][j]];
        cout << endl;
    }

    return 0;
}
