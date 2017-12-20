#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> value(n);
    vector<bool> ok(n + 1);

    for (int i = 0; i < n; ++i){
        cin >> value[i];
    }

    ok[n] = true;

    for (int i = n - 1; i >= 0; --i){
        if (i + value[i] + 1 > n) continue;
        if (ok[ i + value[i] + 1 ])
            ok[i] = true;
    }

    for (int i = 0; i <= n; ++i){
        if (ok[i]) cout << i << endl;
    }

    return 0;
}
