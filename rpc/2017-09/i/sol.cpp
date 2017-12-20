#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int t(int64 m){
    int a = 0;
    int r = 0;

    while (m){
        if (m & 1) r++;
        else r = 0;
        a = max(a, r);
        m >>= 1;
    }

    return a;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 m;
    int k;

    while (cin >> m >> k){
        if (t(m) >= k){
            cout << m << endl;
            continue;
        }

        int64 answer = 0;
        int64 v = (1LL << k) - 1;
        int64 t = 1;

        for (int i = 0; v < (1LL << 50); ++i){
            int64 cur = (m | v) & ~(t - 1);

            if (cur >= m){
                if (answer == 0) answer = cur;
                else answer = min(answer, cur);
            }

            v <<= 1;
            t <<= 1;
        }

        cout << answer << endl;
    }

    return 0;
}
