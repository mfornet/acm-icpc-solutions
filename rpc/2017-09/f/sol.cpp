#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500000 + 10;

int bit[maxn];

void upd(int idx, int v){
    if (idx == 0) bit[idx] += v;
    else{
        while (idx < maxn)
        {
            bit[idx] += v;
            idx += idx & -idx;
        }
    }
}

int query(int idx){
    if (idx == -1) return 0;

    int ans = bit[0];
    while (idx){
        ans += bit[idx];
        idx -= idx & -idx;
    }
    return ans;
}

struct info{
    int l, k, idx;
};

void solve(int n){
    vector<int> value(n);
    for (int i = 0; i < n; ++i)
        cin >> value[i];

    int q; cin >> q;
    vector<vector<info>> Q(n);

    for (int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;
        l--; r--;
        Q[r].push_back({l, k, i});
    }

    vector<int> answer(q);
    map<int,int> last;

    for (int i = 0; i < n; ++i){
        if (last.find(value[i]) != last.end())
            upd(last[value[i]], -1);
        upd(i, +1);
        last[value[i]] = i;

        for (auto qry : Q[i]){
            int pref = query(qry.l - 1);
            int k = qry.k + pref;

            if (query(i) < k)
                answer[qry.idx] = -1;
            else{
                int lo = qry.l - 1, hi = i;
                while (lo + 1 < hi){
                    int m = (lo + hi) >> 1;
                    if (query(m) < k)
                        lo = m;
                    else
                        hi = m;
                }
                answer[qry.idx] = hi;
            }
        }
    }

    for (auto p : last)
        upd(p.second, -1);

    for (auto u : answer){
        if (u == -1) cout << ":(" << endl;
        else cout << value[u] << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n){
        solve(n);
    }

    return 0;
}
