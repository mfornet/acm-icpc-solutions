#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500 + 10;

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

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << ".#"[(i + 1 < n) && (mat[i][j] || i == 0 || (j&1))];
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << ".#"[i && (mat[i][j] || (i + 1 == n) || ((j&1)^1))];
        cout << endl;
    }

    return 0;
}
