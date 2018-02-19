#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct segment_tree{
    vector<int64> data;

    segment_tree(int n){
        data = vector<int64>(4 * n);
    }

    void update(int p, int b, int e, int x, int64 v){
        if (b + 1 == e){
            data[p] = v;
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            if (x < m) update(l, b, m, x, v);
            else       update(r, m, e, x, v);
            data[p] = min(data[l], data[r]);
        }
    }

    int64 query(int p, int b, int e, int x, int y){
        if (x <= b && e <= y)
            return data[p];
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            int64 left = oo, right = oo;

            if (x < m) left = query(l, b, m, x, y);
            if (m < y) right = query(r, m, e, x, y);

            return min(left, right);
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> h(n);
    vector<int> p(n);
    

    for (int i = 0; i < n; ++i)
        cin >> h[i];

    for (int i = 1; i < n; ++i)
        cin >> p[i];

    vector<int64> cost(n);
    segment_tree st(n);

    stack<int> stk;

    for (int i = n - 1; i >= 0; --i){
        while (!stk.empty() && h[i] >= h[stk.top()])
            stk.pop();        

        int x = stk.empty() ? n : stk.top();

        cost[i] = x == n ? 0 : cost[x] + p[x] + h[x] - h[i];

        if (i + 1 < x)
            cost[i] = min(cost[i], st.query(1, 0, n, i + 1, x) + h[i]);

        st.update(1, 0, n, i, cost[i] + p[i] - h[i]);
        stk.push(i);
    }

    cout << cost[0] + n << endl;

    return 0;
}