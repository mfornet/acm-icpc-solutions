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

    for (int i = 1; i * i <= n; ++i){
        if (n % i) continue;

        int x = i, y = n / i;

        // x <= y

        if ((x + y) & 1) continue;

        cout << (y - x) / 2 << " " << (y + x) / 2 << endl;
        return 0;
    }

    cout << "impossible" << endl;


    return 0;
}
