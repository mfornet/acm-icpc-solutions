#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct CASHIER{
    int64 m, s, p;
};

int64 solve(){
    int64 r, b, c;
    cin >> r >> b >> c;

    vector<CASHIER> cashier(c);

    for (int i = 0; i < c; ++i)
        cin >> cashier[i].m >> cashier[i].s >> cashier[i].p;

    int64 lo = 0, hi = 1000000001000000001ll;

    while (lo + 1 < hi){
        int64 m = (lo + hi) / 2;

        priority_queue<int64> pq;

        for (int i = 0; i < c; ++i){
            if (m < cashier[i].p)
                continue;

            int64 t = min((m - cashier[i].p) / cashier[i].s, cashier[i].m);
            pq.push(t);
        }

        int64 total = 0;

        for (int i = 0; i < r && !pq.empty(); ++i){
            total += pq.top();
            pq.pop();
        }

        if (total >= b)
            hi = m;
        else
            lo = m;
    }

    return hi;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc)
        cout << "Case #" << tc << ": " << solve() << endl;

    return 0;
}