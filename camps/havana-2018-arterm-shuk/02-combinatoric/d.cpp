#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000000007;

int modpow(int a, int n){
    int b = 1;

    while (n){
        if (n & 1)
            b = 1LL * b * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }

    return b;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> A(n);

    for (int i = 0; i < n; ++i)
        cin >> A[i];

    int answer = 1;
    int64 cumsum = 0;

    for (int i = 0; i < n; ++i){
        cumsum += A[i];
        cumsum %= mod;
        answer = 1LL * answer * modpow((i + 1) + cumsum, mod - 2) %  mod 
                    * (i + 1) % mod;
    }

    cout << answer << endl;

    return 0;
}