#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(){
    int n, e;
    cin >> n >> e;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        v[i] = n - i;

    for (int i = 0; i < e; ++i){
        int k; cin >> k;
        v.push_back( k );
    }

    vector<int> last(n + 1);

    for (int i = 0; i < (int)v.size(); ++i)
        last[ v[i] ] = i;

    int idx = 1;

    for (int i = 1; i <= n; ++i){
        if (last[ i ] < last[ idx ])
            idx = i;
    }

    cout << idx << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--)
        solve();

    return 0;
}
