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

    int64 n; cin >> n;

    int64 a = 1, b = 1, c = 1;

    for (int64 p = 2; p * p <= n; ++p){
        int64 t = 0;
        int64 k = 1;

        while (n % p == 0){
            n /= p;
            k *= p;
            t++;
        }

        if (t == 0) continue;

        a *= k / p * (p - 1);
        b *= (t + 1);
        c *= (k * p - 1) / (p - 1);   
    }

    if (n > 1){
        int64 t = 1;
        int64 k = n;
        int64 p = n;
        a *= k / p * (p - 1);
        b *= (t + 1);
        c *= (k * p - 1) / (p - 1);
    }

    cout << a << " " << b << " " << c << endl;

    return 0;
}