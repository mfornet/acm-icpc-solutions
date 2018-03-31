#include <bits/stdc++.h>
const int MAX = 5e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b, p) ((i64)(a) * (b) % (p))
#define sum(a, b, p) ((((a) + (b)) % (p) + p) % p)

const int oo = (1 << 30) - 1 + (1 << 30);


int main() {
    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'
    i64 a, b; cin >> a >> b ;
    if(a == 0 and b == 0)cout << 1 << endl;
    else if(a == 0)cout << -1 << endl;
    else cout << ((b - a) * (b + a - 1) + 1) % MOD << endl;


}
