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

    int a, b, c;
    cin >> a >> b >> c;

    if ((a & 1) * (b & 1) * (c & 1) == 0)
        cout << 0 << endl;
    else
        cout << min({1LL * a * b, 1LL * b * c, 1LL * a * c}) << endl;

    return 0;
}
