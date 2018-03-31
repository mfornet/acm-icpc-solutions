#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1010; 

int64 mat[ maxn ][ maxn ];
int64 acc[ maxn ][ maxn ];

int64 MIN[ maxn ][ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            cin >> mat[i][j];
            acc[i][j] = mat[i][j] - acc[i - 1][j] - acc[i][j - 1] + acc[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; ++i){
        deque<pii> dq;

        for (int j = m; j; --j){
            while (!dq.empty() && dq.front().first >= mat[i][j])
                dq.pop_front();

            

        }
    }


    return 0;
}
