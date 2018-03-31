#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000;

int nxt[maxn][20];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tmp[5];

    for (int i = 0; i < maxn; ++i){
        int u = i;

        for (int j = 0; j < 5; ++j){
            tmp[j] = u % 10; u /= 10;
        }

        sort(tmp, tmp + 5);
        int A = 0, B = 0;

        for (int j = 0; j < 5; ++j)
            A = A * 10 + tmp[j], B = B * 10 + tmp[4 - j];

        assert(B >= A);

        nxt[i][0] = B - A;
    }

    for (int i = 1; i < 20; ++i)
        for (int j = 0; j < maxn; ++j)
            nxt[j][i] = nxt[ nxt[j][i - 1] ][i - 1];

    int t; cin >> t;
    const int M = 999999;

    while (t-->0){
        int x; cin >> x;

        for (int i = 19; i >= 0; --i){
            if (M >> i & 1)
                x = nxt[x][i];
        }

        for (int j = 0; j < 5; ++j){
            tmp[j] = x % 10;
            x /= 10;
        }

        for (int j = 4; j >= 0; --j)
            cout << tmp[j];
        cout << endl;
    }

    return 0;
}