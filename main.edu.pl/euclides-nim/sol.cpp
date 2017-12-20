#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(int p, int q, int n){
    int g = __gcd(p, q);
    if (n % g) return 0;

    p /= g, q /= g, n /= g;

    int s = +1;

    if (p > q){
        s = -1;
        swap(p,q);

        if (n < q)
            n += q;
        else
            n %= q;
    }

    if (n >= p)
        return s;

    if (n % (q - p) == 0)
        return -s;
    else
        return s;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int p, q, n;
    int t; cin >> t;
    while (t--){
        cin >> p >> q >> n;
        int answer = solve(p, q, n);
        cout << (answer == +1 ? "E" : (answer == 0 ? "R" : "P")) << endl;
    }

    return 0;
}