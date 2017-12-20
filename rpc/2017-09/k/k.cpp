#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500000 + 10;

const int limit = 132788 + 1000;
int freq[ limit ];
int ulam[ limit ];
int tCount = 0;

const int mod = 100000097;
const int base = mod / 3;

int P[maxn];

struct segment_tree{
    vector<int> h;
    segment_tree(vector<int> &value){
        int n = (int)value.size();
        h = vector<int>(4 * n);
        build(1, 0, n, value);
    }

    void build(int p, int b, int e, vector<int> &value){
        if (b + 1 == e) h[p] = value[b];
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m, value);
            build(r, m, e, value);

            h[p] = (1LL * h[l] * P[e - m] % mod + h[r]) % mod;
        }
    }

    void update(int p, int b, int e, int x, int v){
        if (b + 1 == e) h[p] = v;
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            if (x < m) update(l, b, m, x, v);
            else update(r, m, e, x, v);
            h[p] = (1LL * h[l] * P[e - m] % mod + h[r]) % mod;
        }
    }

    int query(int p, int b, int e, int x, int y){
        if (x <= b && e <= y)
            return h[p];

        int m = (b + e) >> 1, l = p << 1, r = l | 1;

        int L = x < m ? query(l, b, m, x, y) : 0;
        int R = m < y ? query(r, m, e, x, y) : 0;

        return (1LL * L * P[max(y - m, 0)] % mod + R) % mod;
    }
};

void solve(int n){
    vector<int> value(n);
    for (int i = 0; i < n; ++i)
        cin >> value[i];

    segment_tree a(value);
    reverse(value.begin(), value.end());
    segment_tree b(value);
    reverse(value.begin(), value.end());

    int q; cin >> q;

    auto rev = [&](int p){
        return n - 1 - p;
    };

    while (q--){
        string cmd;
        int u, v;

        cin >> cmd >> u >> v;

        if (cmd == "U"){
            u--;
            a.update(1, 0, n, u, v);
            b.update(1, 0, n, rev(u), v);
            value[u] = v;
        }
        else{
            u--; v--;

            if (freq[u+1] != 1 && freq[v+1] != 1){
                cout << "N" << endl;
                continue;
            }

            int h1 = a.query(1, 0, n, u, v+1);
            int h2 = b.query(1, 0, n, rev(v), rev(u) + 1);

            // cout << h1 << " " << h2 << endl;

            cout << "YN"[h1 != h2] << endl;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freq[ 1 ] = freq[ 2 ] = 1;

    for (int i = 1; tCount < 10000; ++i){
        if (freq[i] == 1){
            for (int j = 0; j < tCount; ++j){
                int value = i + ulam[j];
                if (value >= limit) continue;
                freq[ value ]++;
            }
            ulam[ tCount++ ] = i;
        }
    }

    P[0] = 1;
    for (int i = 1; i < maxn; ++i)
        P[i] = 1LL * P[i - 1] * base % mod;

    int n;

    while (cin >> n){
        solve(n);
    }
}
