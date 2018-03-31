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

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

vi multiply(vi A, vi B){
    vi C((int)A.size() + (int)B.size() - 1);

    for (int i = 0; i < (int)A.size(); ++i)
        for (int j = 0; j < (int)B.size(); ++j)
            add(C[i + j], 1LL * A[i] * B[j] % mod);

    return C;
}

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

    if (n == 2){
        cout << 1 << endl;
        return 0;
    }

    vector<int> P(1, 1);

    for (int i = 1; i < n; ++i){
        vector<int> Q = {1, mod - i};
        P = multiply(P, Q);
    }

    for (auto &x : P)
        x = (mod - x) % mod;
    P[0] = 0;

    int answer = 0;
    int k = 1;

    while ((1 << (k+1)) < n){
        answer++;
        k++;
    }

    for (int i = 1; i < P.size(); ++i){
        int a = modpow(2, (k + 1) * i);        
        int b = modpow(2, k * i);        
        int d = (a - b + mod) % mod;
        int num = modpow(d, mod - 2);
        add(answer, 1LL * P[i] * num % mod); 
    }

    cout << (answer + 1) % mod << endl;

    return 0;
}