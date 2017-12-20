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

    double dist;
    int n; 

    cin >> dist >> n;


    double lo = -1, hi = 0;
    double acc = 0;

    for (int i = 0; i < n; ++i)
    {
        double c; cin >> c;
        acc += c;

        hi = min(hi, dist * (i + 1) - acc);
        lo = max(lo, dist * (i + 1) - acc - 1);
    }

    if (lo >= hi) cout << "im";

    cout << "possible" << endl;

    return 0;
}
