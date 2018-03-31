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

    vector<int64> D(n + 1);

    for (int i = 1; i <= n; ++i){
        int64 v; cin >> v;
        D[i] = D[i - 1] + v;
    }


    int q; cin >> q;

    while (q--){
        int64 v; cin >> v;
        int pos = lower_bound(D.begin(), D.end(), v) - D.begin();
        if (pos == n + 1)
            cout << "none" << endl;
        else
            cout << pos << endl;
    }


    return 0;
}
