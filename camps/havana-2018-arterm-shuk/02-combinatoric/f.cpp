#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000000 + 10;
const int mod = 1000000007;

int _freq[maxn];
int freq[maxn];     
int answer[maxn];
int mob[maxn];
bool prime[maxn];
int pw[maxn];

void sieve(){
    mob[1] = 1;

    pw[0] = 1;
    for (int i = 1; i < maxn; ++i)
        pw[i] = (pw[i - 1] << 1) % mod;

    for (int i = 2; i < maxn; ++i){
        if (prime[i]) continue;

        for (int j = i; j < maxn; j += i){
            prime[j] = true;
            int u = j / i;

            if (u % i)
                mob[j] = mob[u] * -1;
        }
    }

    for (int i = 1; i < maxn; ++i)
        for (int j = i; j < maxn; j += i)
            freq[i] += _freq[j];
}

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;  
    cin >> n;

    for (int i = 0; i < n; ++i){
        int v; cin >> v;
        _freq[v]++;
    }

    sieve();

    for (int i = 1; i < maxn; ++i){
        if (mob[i] == 0) continue;

        for (int j = 1; j * i < maxn; ++j)
            add(answer[j], (mob[i] * (pw[freq[i * j]] - 1) + mod) % mod);
    }

    int ans = 0;

    for (int i = 1; i < maxn; ++i)
        add(ans, 1LL * i * answer[i] % mod);

    cout << ans << endl;

    return 0;
}