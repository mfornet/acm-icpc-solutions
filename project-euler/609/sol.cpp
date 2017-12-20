#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int maxn = 100000100;
const int mod = 1000000007;

int sieve[maxn];
int pi[maxn];

int counter[maxn];

int64 P(int n){
    int64 answer = 1;

    memset(counter, 0, sizeof counter);

    for (int i = 1; i <= n; ++i){
        int u = i;
        vector<int> values;

        int cnt = 0;
        bool start = true;

        while (u){
            if (!sieve[u])
                cnt++;

            if (start)
                start = false;
            else
                counter[cnt]++;

            u = pi[u];
        }
    }

    for (int i = 0; counter[i]; ++i)
        answer = 1LL * answer * counter[i] % mod;

    return answer;
}

int main(){
    for (int i = 2; i * i < maxn; ++i){
        if (sieve[i]) continue;
        for (int j = i * i; j < maxn; j += i)
            sieve[j] = 1;
    }

    for (int i = 2; i < maxn; ++i){
        sieve[i] ^= 1;
        pi[i] = pi[i - 1] + sieve[i];
    }

    cout << P(100000000) << endl;

    return 0;
}
