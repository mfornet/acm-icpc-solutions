#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 10000000 + 10;

int p[maxn];
int64 mx;

void sieve(){
    int t = 0;
    for (int i = 2;; ++i){
        if (p[i]) 
            continue;

        p[i] = ++t;

        if (i >= 1000000 && __builtin_popcount(t) == 1)
        {
            mx = i;
            break;
        }

        for (int j = 2 * i; j < maxn; j += i)
            p[j] = -1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sieve();

    int64 n; cin >> n;

    int64 g = 0;

    for (int64 i = 2; i * i <= n; ++i){
        while (n % i == 0){
            g ^= p[i];
            n /= i;
        }
    }

    if (n >= mx){
        cout << "David" << endl;
    }
    else{
        g ^= p[n];

        cout << (g ? "David" : "Vasya") << endl;
    }

    return 0;
}