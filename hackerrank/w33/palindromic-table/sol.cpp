#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<vi> T(vector<vi> &M){
    int n = M.size(), m = M[0].size();
    vector<vi> N(m, vi(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            N[j][i] = M[i][j];

    return N;
}

int position[1024];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // freopen("test.in", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<vi> mat(n + 1, vi(m + 1));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mat[i][j];

    bool transpose = n > m;

    if (transpose){
        mat = T( mat );
        swap(n, m);
    }

    vector<vi> sum(n+1, vi(m+1));
    vector<vi> _xor(n+1, vi(m+1));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j){
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + mat[i][j];
            _xor[i][j] = _xor[i-1][j] ^ (1 << mat[i][j]);
        }

    auto getSum = [&](int x1, int y1, int x2, int y2){
        return sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
    };

    int answer = 1;
    int x1=1, y1=1, x2=1, y2=1;

    for (int a = 1; a <= n; ++a)
        for (int b = a; b <= n; ++b){
            memset(position, -1, sizeof position);
            position[0] = 0;

            for (int x = 1, cur = 0; x <= m; ++x){
                cur ^= _xor[b][x] ^ _xor[a-1][x];

                if (position[cur] != -1){
                    if (getSum(a,position[cur]+1,b,x)){
                        int curanswer = (b - a + 1) * (x - position[cur]);
                        if (curanswer > answer){
                            answer = curanswer;
                            x1 = a, x2 = b, y1 = position[cur] + 1, y2 = x;
                        }
                    }
                }
                else
                    position[cur] = x;

                for (int idx = 1; idx < 1024; idx <<= 1){
                    int value = cur ^ idx;
                    if (position[ value ] != -1){
                        int curanswer = (b - a + 1) * (x - position[value]);
                        if (curanswer > answer){
                            answer = curanswer;
                            x1 = a, x2 = b, y1 = position[value] + 1, y2 = x;
                        }
                    }
                }
            }
        }

    if (transpose)
        swap(x1, y1), swap(x2, y2);

    cout << answer << endl;
    cout << x1-1 << " " << y1-1 << " " << x2-1 << " " << y2-1 << endl;

    return 0;
}