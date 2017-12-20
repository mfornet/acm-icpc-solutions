#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct segment_tree
{
    vector<pii> d;

    segment_tree(int n){
        d = vector<pii>(4 * n);
        build(1, 0, n);
    }

    void build(int p, int b, int e){
        if (b + 1 == e)
            d[p] = pii(-b - 1, 0);
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m);
            build(r, m, e);
            d[p] = pii( max(d[l].first, d[r].first), 0);
        }
    }

    void push(int p, int l, int r){
        if (d[p].second){
            int &x = d[p].second;
            d[l].first += x;
            d[l].second += x;
            d[r].first += x;
            d[r].second += x;
            x = 0;
        }
    }

    void update(int p, int b, int e, int x, int y){
        if (x <= b && e <= y){
            d[p].first++;
            d[p].second++;
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            push(p, l, r);

            if (x < m) update(l, b, m, x, y);
            if (m < y) update(r, m, e, x, y);

            d[p] = pii(max(d[l].first, d[r].first), 0);
        }
    }

    int top(){
        return d[1].first;
    }
};

int main(){
    freopen("greedy.in", "r", stdin);
    freopen("greedy.out", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    segment_tree st(n);

    int answer = n;

    for (int i = 0; i < n; ++i){
        int x; cin >> x;
        x = n - x - 1;

        st.update(1, 0, n, x, n);
        answer--;

        if (st.top() >= 0)
            break;
    }

    cout << answer << endl;

    return 0;
}