#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct segment_tree{
    vector<int>  data, lz;

    segment_tree(int n){
        data = vector<int>(4 * n);
        lz = vector<int>(4 * n);
    }

    void push(int p, int l, int r){
        if (lz[p]){
            data[l] += lz[p];
            lz[l] += lz[p];

            data[r] += lz[p];
            lz[r] += lz[p];

            lz[p] = 0;
        }
    }

    void update(int p, int b, int e, int x, int y, int s){
        if (x <= b && e <= y){
            data[p] += s;
            lz[p] += s;
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;

            push(p, l, r);

            if (x < m) update(l, b, m, x, y, s);
            if (m < y) update(r, m, e, x, y, s);

            data[p] = max(data[l], data[r]);
        }
    }

    pii query(int p, int b, int e){
        if (b + 1 == e)
            return {data[p], b};

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r);

        if (data[l] > data[r])
            return query(l, b, m);
        else
            return query(r, m, e);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;

    cin >> n >> k;

    vector<pii> V(n);

    for (int i = 0; i < n; ++i){
        cin >> V[i].first >> V[i].second;
    }

    sort(V.begin(), V.end());

    const int S = 10000 + 10;

    int lo = 0, hi = S;
    int X, Y;

    auto ok = [&](int size){
        segment_tree st(S);

        for (int i = 0, j = 0; i < n; ++i){
            st.update(1, 0, S, V[i].second, V[i].second + size + 1, +1);

            while (V[i].first - V[j].first > size){
                st.update(1, 0, S, V[j].second, V[j].second + size + 1, -1);
                j++;
            }

            auto best = st.query(1, 0, S);

            if (best.first >= k){
                X = V[j].first;
                Y = best.second - size;
                return true;
            }
        }

        return false;
    };

    while (lo + 1 < hi){
        int mid = (lo + hi) / 2;
        if (ok(mid))
            hi = mid;
        else
            lo = mid;
    }

    ok(hi);

    cout << hi << endl;
    cout << X << " " << Y << endl;

    return 0;
}
