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
            b = 1LL * a * b % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }

    return b;
}

int inverse(int a){
    return modpow(a, mod - 2);
}

int add(int a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
    return a;
}

int sub(int a, int b){
    a -= b;
    if (a < 0)
        a += mod;
    return a;
}

vi multiply(vi a, vi b){
    vi c(a.size() + b.size() - 1);

    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < b.size(); ++j)
            c[i + j] = add(c[i + j], 1LL * a[i] * b[j] % mod);

    return c;
}

vi addpol(vi a, vi &b){
    a.resize(max(a.size(), b.size()));
    for (int i = 0; i < b.size(); ++i)
        a[i] = add(a[i], b[i]);
    return a;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<pii> P(n);

    for (int i = 0; i < n; ++i)
        cin >> P[i].first >> P[i].second;

    vi answer;

    for (int i = 0; i < n; ++i){
        vi cur(1, 1);

        for (int j = 0; j < n; ++j){
            if (i == j)
                cur = multiply(cur, vi(1, P[i].second));
            else{
                cur = multiply(cur, 
                        multiply({sub(0, P[j].first), 1}, vi(1, inverse(sub(P[i].first, P[j].first))))
                    );
            }
        }

        answer = addpol(answer, cur);
    }

    for (auto x : answer)
        cout << x << " ";
    cout << endl;

    return 0;
}