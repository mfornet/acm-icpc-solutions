#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

struct segment_tree{
    vector<int> data;
    
    segment_tree(int n){
        data = vector<int>(4 * n, -1);
    }

    void push(int p, int l, int r){
        if (data[p] != -1){
            data[l] = data[p];
            data[r] = data[p];
            data[p] = -1;
        }
    }
    
    void update(int p, int b, int e, int x, int y, int v){
        if (x <= b && e <= y){
            data[p] = v;
            return;
        }

        int m = (b + e) >> 1, l = p << 1, r = l | 1;

        push(p, l, r);

        if (x < m) update(l, b, m, x, y, v);
        if (m < y) update(r, m, e, x, y, v);
    }

    int query(int p, int b, int e, int x){
        if (data[p] != -1 || b + 1 == e)
            return data[p];

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        if (x < m) return query(l, b, m, x);
        else       return query(r, m, e, x);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int,pii>> seg(n);

    for (int i = 0; i < n; ++i){
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        seg[i] = {y, {x1, x2}};
    }

    sort(seg.begin(), seg.end());

    int N = 100100;
    segment_tree st(N);

    for (auto s : seg){
        int x1 = s.second.first;
        int x2 = s.second.second;

        int v1 = st.query(1, 0, N, x1);
        int v2 = st.query(1, 0, N, x2);

        if (v1 == -1) v1 = x1;
        if (v2 == -1) v2 = x2;

        int m = (x1 + x2) >> 1;

        st.update(1, 0, N, x1, m + 1, v1);
        st.update(1, 0, N, m + 1, x2+1, v2);
    }

    for (int i = 0; i < m; ++i){
        int x; cin >> x;
        int v = st.query(1, 0, N, x);
        if (v == -1) v = x;

        cout << v << endl;
    }
    
    return 0;
}