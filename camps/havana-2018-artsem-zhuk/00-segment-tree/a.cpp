#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int mask = (1 << 30) - 1;

struct segment_tree{
    vector<int> AND, OR, LAZY, MIN;

    segment_tree(vector<int> &value){
        int n = (int)value.size();

        AND = vector<int>(4 * n);
        OR = vector<int>(4 * n);
        LAZY = vector<int>(4 * n);
        MIN = vector<int>(4 * n);

        build(1, 0, n, value);
    }

    void build(int p, int b, int e, vector<int> &value){
        if (b + 1 == e)
            AND[p] = OR[p] = MIN[p] = value[b];
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m, value);
            build(r, m, e, value);

            AND[p] = AND[l] & AND[r];
            OR[p] = OR[l] | OR[r];
            MIN[p] = min(MIN[l], MIN[r]);
        }
    }

    void push(int p, int l, int r){
        if (LAZY[p]){
            LAZY[l] += LAZY[p];
            LAZY[r] += LAZY[p];
            MIN[l] += LAZY[p];
            MIN[r] += LAZY[p];
            OR[l] += LAZY[p];
            OR[r] += LAZY[p];
            AND[l] += LAZY[p];
            AND[r] += LAZY[p];
            LAZY[p] = 0;
        }
    }

    void update_and(int p, int b, int e, int x, int y, int v){
        v |= ~OR[p] & mask;
        int c = ~v & mask;

        if (x <= b && e <= y && 
            ((c & AND[p]) == c)
            ){
            LAZY[p] -= c;
            MIN[p] -= c;
            AND[p] -= c;
            OR[p] -= c;
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            push(p, l, r);

            if (x < m) update_and(l, b, m, x, y, v);
            if (m < y) update_and(r, m, e, x, y, v);

            MIN[p] = min(MIN[l], MIN[r]);
            AND[p] = AND[l] & AND[r];
            OR[p] = OR[l] | OR[r];
        }
    }

    void update_or(int p, int b, int e, int x, int y, int v){
        v &= ~AND[p];
        int c = ~OR[p] & mask;

        if (x <= b && e <= y &&
            ((c & v) == v)
            ){
            LAZY[p] += v;
            MIN[p] += v;
            AND[p] += v;
            OR[p] += v;
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            push(p, l, r);

            if (x < m) update_or(l, b, m, x, y, v);
            if (m < y) update_or(r, m, e, x, y, v);

            MIN[p] = min(MIN[l], MIN[r]);
            AND[p] = AND[l] & AND[r];
            OR[p] = OR[l] | OR[r];
        }
    }

    int query(int p, int b, int e, int x, int y){

        if (x <= b && e <= y) return MIN[p];
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            push(p, l, r);

            int answer = mask;

            if (x < m) answer = min(answer, query(l, b, m, x, y));
            if (m < y) answer = min(answer, query(r, m, e, x, y));

            return answer;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;

    cin >> n;

    vector<int> value(n);
    for (int i = 0; i < n; ++i)
        cin >> value[i];

    segment_tree st(value);

    cin >> m;

    while (m-->0){
        char x; cin >> x;

        if (x == '?'){
            int a, b; cin >> a >> b;
            cout << st.query(1, 0, n, a - 1, b) << endl;
        }
        else if (x == '&'){
            int a, b, x;
            cin >> a >> b >> x;
            st.update_and(1, 0, n, a - 1, b, x);
        }
        else{
            int a, b, x;
            cin >> a >> b >> x;
            st.update_or(1, 0, n, a - 1, b, x);
        }
    }

    return 0;
}