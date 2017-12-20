#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 cube[1000000 + 10];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i <= 1000000; ++i)
        cube[i] = 1LL * i * i * i;

    int t; cin >> t;

    while (t--){
        int a, b;
        cin >> a >> b;
        int64 x = 1LL * a * b;
        int p = lower_bound(cube, cube + 1000001, x) - cube;

        if (cube[p] != x){
            cout << "No" << endl;
            continue;
        }

        if (a % p == 0 && b % p == 0)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
