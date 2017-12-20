#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200000 + 10;
const int mod = 1000000007;

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int m(int a){
    if (a < 0) a += mod;
    return a;
}

vector<int> upgrade(vector<int> v, int &s){
    vector<int> ans(v.size() + 1);
    
    for (int i = (int)v.size() - 1; i >= 0; --i){
        add( ans[i], v[i] );
        add( ans[i + 1], m( s * v[i] ) );
        s *= -1;
    }

    return ans;
}

int modpow(int a, int b){
    int c = 1;
    while (b){
        if (b & 1)
            c = 1LL * a * c % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return c;
}

int fak[ maxn ], ifak[ maxn ];

int comb(int n, int k){
    return 1LL * fak[n] * ifak[k] % mod * ifak[n - k] % mod;
}

vector<int> generate(int n){
    vector<int> v( 2 * n + 1 );
    for (int i = 0; i <= n; ++i)
        v[2 * i] = comb(n, i);
    return v;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fak[0] = ifak[0] = 1;
    for (int i = 1; i < maxn; ++i){
        fak[i] = 1LL * fak[i - 1] * i % mod;
        ifak[i] = modpow( fak[i], mod - 2 );
    }

    int n; 
    cin >> n;

    int m = n;
    while (m % 4 != 1)
        m--;

    auto V = generate( (m - 1) / 3 );

    int s = +1;

    while (m < n){
        V = upgrade(V, s);
        m++;
    }

    int answer = 0;

    for (int i = 0; i < n; ++i){
        int cValue; cin >> cValue;
        add(answer, 1LL * V[i] * cValue % mod); 
    }

    cout << answer << endl;

    return 0;
}
