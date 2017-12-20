#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define au(i,x,y) for (int i = x; i <= y; ++i)

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000;

int mat[maxn][maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mat[i][j];

    int answer = 0;

    au(x1,1,n) au(x2,x1,n) au(y1,1,m) au(y2,y1,m){
        int last = -1;
        bool ok = true;
        for (int i = x1; i <= x2 && ok; ++i)
            for (int j = y1; j <= y2 && ok; ++j){
                if (mat[i][j] < last) ok = false;
                last = mat[i][j];
            }
        answer += ok;
    }

    cout << answer << endl;

    return 0;
}