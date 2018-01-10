#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

bool compare(pii a, pii b){
    return b.first - b.second < a.first - a.second;
    // return max(a.first, b.first + a.second) < max(a.first + b.second, b.first);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<pii> P;
    vector<pii> N;

    for (int i = 0; i < n; ++i){
        pii p;
        cin >> p.first >> p.second;
        p.second -= p.first;

        if (p.second <= 0) N.push_back({p.first, -p.second});
        else P.push_back(p);
    }

    sort(P.begin(), P.end());
    sort(N.begin(), N.end(), compare);

    int64 lo = 0, hi = 0x3f3f3f3f3f3f3f3f;

    while (lo + 1 < hi){
        int64 m = (lo + hi) >> 1;

        int64 space = m;
        bool ok = true;

        for (auto v : P){
            if (v.first > space){
                ok = false;
                break;
            }
            space += v.second;
        }

        if (ok){
            int64 D = 0;
            int64 MX = 0;

            for (auto v : N){
                MX = max(MX, v.first + D);
                D += v.second;
            }

            if (space < MX || D > space) ok = false;
        }

        if (ok) hi = m;
        else lo = m;
    }

    cout << hi << endl;

    return 0;
} 