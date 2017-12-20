#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 102;

int mat[ maxn ][ maxn ];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];

    int answer = 0;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            int value = mat[i][j];
            
            for (int k = 0; k < 4; ++k){
                int x = i + dx[k], y = j + dy[k];
                bool ok = true;

                while (0 <= x && x < n && 0 <= y && y < m && ok){
                    ok = value > mat[x][y];
                    x += dx[k];
                    y += dy[k];
                }

                answer += ok;
            }
        }
    }

    cout << answer << endl;

    return 0;
}
