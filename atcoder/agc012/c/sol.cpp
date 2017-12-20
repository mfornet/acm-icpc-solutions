#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500;

int64 pascal[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    for (int i = 0; i < maxn; ++i){
        pascal[i][0] = 1;

        for (int j = 1; j <= i; ++j)
            pascal[i][j] = pascal[i - 1][j] + pascal[i - 1][j - 1];
    }

    vector<int64> size(41);

    for (int i = 1; i <= 40; ++i){
        int64 cur = 0;

        for (int j = 2; j <= i; j += 2)
            cur += pascal[i][j];

        size[i] = cur;
    }

    int64 k; cin >> k;

    vector<int> num;

    for (int i = 40, t = 1; k; --i){        
        while (size[i] <= k){

            for (int j = 0; j < i; ++j)
                num.push_back( t );

            k -= size[i];
            ++t;
        }
    }

    cout << num.size() << endl;

    for (auto u : num)
        cout << u << " ";

    cout << endl;

    return 0;
}
