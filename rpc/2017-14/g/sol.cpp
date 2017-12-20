#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct bit{
    int top;
    vector<int> d;

    bit(int top) : top(top){
        d = vector<int>(top);
    }

    int query(int idx){
        int answer = 0;
        while (idx){
            answer += d[idx];
            idx -= idx & -idx;
        }
        return answer;
    }

    void update(int idx){
        while (idx < top){
            d[idx]++;
            idx += idx & -idx;
        }
    }
};

void solve(int m, int n){
    vector<pii> pos(n);
    vector<int> X = {-1};

    for (int i = 0; i < n; ++i){
        cin >> pos[i].first >> pos[i].second;
        pos[i].first++;
        pos[i].second++;

        X.push_back(pos[i].second);
    }

    sort(X.begin(), X.end());
    X.resize(unique(X.begin(), X.end()) - X.begin());

    sort(pos.begin(), pos.end());

    int64 answer = -1;

    for (int _ = 0; _ < 2; ++_){
        bit B(X.size());

        for (int i = 0, j; i < n; i = j){
            for (j = i; j < n && pos[i].first == pos[j].first; ++j){
                int idx = lower_bound(X.begin(), X.end(), pos[j].second) - X.begin();
                B.update(idx);
            }

            int ctotal = j;

            if (ctotal * 2 < n)
                continue;

            int lo = 0, hi = X.size();

            while (lo + 1 < hi){
                int m = (lo + hi) >> 1;
                int c = B.query(m);

                if (2 * c < n)
                    lo = m;
                else
                    hi = m;
            }

            if (B.query(hi) * 2 == n){
                int64 a = 1LL * pos[i].first * X[hi];
                if (answer == -1 || a < answer)
                    answer = a;
            }

            lo = 1, hi = X.size();

            while (lo + 1 < hi){
                int m = (lo + hi) >> 1;
                int c = ctotal - B.query(m - 1);

                if (2 * c < n)
                    hi = m;
                else
                    lo = m;
            }

            if (2 * (ctotal - B.query(lo - 1)) == n){
                int64 a = 1LL * pos[i].first * (m + 1 - X[lo]);
                if (answer == -1 || a < answer)
                    answer = a;
            }
        }

        reverse(pos.begin(), pos.end());
        for (auto &p : pos)
            p.first = m + 1 - p.first;
    }

    cout << answer << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n;

    while (cin >> m >> n)
        solve(m, n);

    return 0;
}
