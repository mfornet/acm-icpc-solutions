#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000;

int p[ maxn ];
bool seen[ maxn ];

int modpow(int a, int n, int m){
    int b = 1;

    while (n){
        if (n & 1)
            b = 1LL * b * a % m;
        a = 1LL * a * a % m;
        n >>= 1;
    }

    return b;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 1; i <= n; ++i){
        cin >> p[i];
    }

    vector<int> cycle;

    for (int i = 1; i <= n; ++i){
        if (seen[i]) continue;
        int size = 0;
        int u = i;

        while (!seen[u]){
            size++;
            seen[u] = true;
            u = p[u];
        }

        if (size & 1)
            cycle.push_back( size );
        else
        {
            cout << 0 << endl;
            return 0;
        }
    }
    
    int answer = 1;
    int total = cycle.size();

    for (int i = 0; i < total; ++i){
        answer = 1LL * answer * modpow(2, (cycle[i] - 1) / 2, mod) % mod;

        for (int j = 0; j < i; ++j)
            answer = 1LL * answer * modpow(2, __gcd( cycle[i], cycle[j] ), mod) % mod;
    }

    cout << answer << endl;

    return 0;
}
