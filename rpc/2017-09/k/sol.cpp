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

const int mod = 100000007;
const int base0 = rand() % mod;
const int base1 = rand() % mod;

int P[2][maxn];

struct T{
    int a, b;

    T(int a=0, int b=0) : a(a), b(b) {}

    T operator*(const int k) const{
        return T(int(1LL * a * P[0][k] % mod), int(1LL * b * P[1][k] % mod));
    }

    T operator+(const T t) const{
        return T((a + t.a) % mod, (b + t.b) % mod);
    }

    bool operator==(const T t) const{
        return a == t.a && b == t.b;
    }
};


struct segment_tree{
    vector<T> h;
    segment_tree(vector<int> &value){
        int n = (int)value.size();
        h = vector<T>(4 * n);
        build(1, 0, n, value);
    }

    void build(int p, int b, int e, vector<int> &value){
        if (b + 1 == e) h[p] = {value[b], value[b]};
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m, value);
            build(r, m, e, value);
            h[p] = h[l] * (e - m)+ h[r];
        }
    }

    void update(int p, int b, int e, int x, int v){
        if (b + 1 == e) h[p] = {v,v};
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            if (x < m) update(l, b, m, x, v);
            else update(r, m, e, x, v);
            h[p] = h[l] * (e - m) + h[r];
            // h[p] = (1LL * h[l] * P[e - m] % mod + h[r]) % mod;
        }
    }

    T query(int p, int b, int e, int x, int y){
        T ans;
        if (x <= b && e <= y){
            ans = h[p];
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;

            T zero;

            T L = x < m ? query(l, b, m, x, y) : zero;
            T R = m < y ? query(r, m, e, x, y) : zero;
            ans = L * max(y - m, 0) + R;
        }

        // cout << b << " " << e << " :: " << ans.a << " " << ans.b << endl;

        return ans;

        // return (1LL * L * P[max(y - m, 0)] % mod + R) % mod;
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

            if (freq[value[u]] != 1 && freq[value[v]] != 1){
                cout << "N" << endl;
                continue;
            }

            T h1 = a.query(1, 0, n, u, v+1);
            T h2 = b.query(1, 0, n, rev(v), rev(u) + 1);

            cout << h1.a << " " << h1.b << endl;
            cout << h2.a << " " << h2.b << endl;

            cout << "NY"[h1 == h2] << endl;
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

    P[0][0] = P[1][0] = 1;

    for (int i = 1; i < maxn; ++i){
        P[0][i] = 1LL * P[0][i - 1] * base0 % mod;
        P[1][i] = 1LL * P[1][i - 1] * base1 % mod;
    }

    int n;

    // cout << base0 << " " << base1 << endl;

    while (cin >> n){
        solve(n);
        break;
    }
}
