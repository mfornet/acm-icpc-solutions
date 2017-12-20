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

    int n, l;
    cin >> n >> l;

    int last = -oo;
    int ok = -1;

    for (int i = 0; i < n; ++i)
    {
        int v; cin >> v;
        if (v + last >= l)
            ok = i;
        last = v;
    }

    if (ok == -1)
        cout << "Impossible" << endl;
    else{
        cout << "Possible" << endl;
        for (int i = 1; i < ok; ++i)
            cout << i << endl;
        for (int i = n - 1; i >= ok; --i)
            cout << i << endl;
    }

    return 0;
}
