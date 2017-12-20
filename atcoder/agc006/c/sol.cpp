#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct permutation{
    vector<int> P;
    permutation(int n){
        P = vector<int>(n);
        iota(P.begin(), P.end(), 0);
    }
    permutation operator*(permutation &p){
        int n = (int)P.size();
        permutation ans(n);
        for (int i = 0; i < n; ++i)
            ans[i] = p[P[i]];
        return ans;
    }
    int size(){
        return P.size();
    }
    int& operator[](int p){
        return P[p];
    }
};

permutation modpow(permutation &p, int64 n){
    permutation a(p.size());
    while (n){
        if (n & 1)
            a = a * p;
        p = p * p;
        n >>= 1;
    }
    return a;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    vector<int> x(n);

    for (int i = 0; i < n; ++i)
        cin >> x[i];

    int m; 
    int64 k;
    cin >> m >> k;

    vector<int> ip(n - 1);

    iota(ip.begin(), ip.end(), 0);

    for (int i = 0; i < m; ++i){
        int u; cin >> u;
        assert(2 <= u && u <= n - 1);
        u -= 2;
        assert(0 <= u && u + 1 < n - 1);
        swap(ip[u], ip[u+1]);
    }

    permutation p(n - 1);
    for (int i = 0; i < n - 1; ++i)
        p[ip[i]] = i;

    p = modpow(p, k);

    int pos = x[0];

    cout << pos << ".0" << endl;
    for (int i = 0; i < n - 1; ++i){
        int u = p[i]; 
        int diff = x[u+1] - x[u];
        pos += diff;
        cout << pos << ".0" << endl;
    }

    return 0;
}
