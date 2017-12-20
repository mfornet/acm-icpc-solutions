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

    int n, k, p, m;

    cin >> n >> k >> p >> m;

    const int msize = 100000;
    n = msize / n * n;

    int s = 1;
    while (2 * s <= n)
        s *= 2;

    for (int i = 0; i < s; ++i)
        cout << (__builtin_popcount(i) % 2 + 1) << " ";
    for (int i = s; i < n; ++i)
        cout << 1 << " ";
    cout << endl;

    for (int i = 0; i < s; ++i)
        cout << (((__builtin_popcount(i) % 2) ^ 1) + 1) << " ";
    for (int i = s; i < n; ++i)
        cout << 1 << " ";
    cout << endl;

    return 0;
}