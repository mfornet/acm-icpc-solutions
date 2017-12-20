#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000000009;
const int B1 =           3;
const int B2 =   192301298;

int convert(char c){
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    return 63;
}

vector<int> read(){
    string s; cin >> s;
    int size = (int)s.length() * 6;
    vector<int> value(size);

    for (int i = 0; i < (int)s.length(); ++i){
        int pos = 6 * i, k = 5;
        int cval = convert(s[i]);

        for (int i = 0; i < 6; ++i){
            int t = pos + k--;
            value[t] = (cval & 1) + 1;
            cval >>= 1;
        }
    }

    return value;
}

struct H{
    int value;
    H(int value=0) : value(value) {}

    H operator+(const H &a){
        int ans = value + a.value;
        if (ans >= mod) ans -= mod;
        return H(ans);
    }

    H operator-(const H &a){
        int ans = value - a.value;
        if (ans < 0) ans += mod;
        return H(ans);
    }

    H operator*(const H &a){
        int ans = 1LL * value * a.value % mod;
        return H(ans);
    }

    bool operator<(const H &a) const{
        return value < a.value;
    }
};

pii get_hash(vector<int> value){
    int n = (int)value.size();

    H h1, h2;
    H p1(1), p2(1);
    H b1(B1), b2(B2);

    for (int i = 0; i < n; ++i){
        h1 = h1 * B1 + H(value[i]);
        h2 = h2 * B2 + H(value[i]);
        p1 = p1 * B1, p2 = p2 * B2; 
    }
    
    pair<H,H> answer(h1, h2);

    for (int i = 0; i < n; ++i){
        h1 = h1 * B1 + H(value[i]) - p1 * H(value[i]);
        h2 = h2 * B2 + H(value[i]) - p2 * H(value[i]);
        answer = min(answer, {h1, h2});
    }

    return pii(answer.first.value, answer.second.value);
}

void solve(int n){
    map<pii,vector<int>> bucket;

    for (int i = 0; i < n; ++i){
        vector<int> val = read();
        auto h = get_hash(val);
        bucket[h].push_back(i + 1);
    }

    vector<vector<int>> lst;

    for (auto p : bucket)
        lst.push_back(p.second);

    sort(lst.begin(), lst.end(), [&](vector<int> &a, vector<int> &b){
            if (a.size() != b.size()) return a.size() < b.size();
            return a[0] < b[0];
            });

    for (auto l : lst){
        for (int i = 0; i < (int)l.size(); ++i)
            cout << l[i] << " \n"[i + 1 == (int)l.size()];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, tc = 1; 

    while (cin >> n){
        if (n == 0) break;
        cout << "Case " << tc++ << ":" << endl;
        solve(n);
    }

    return 0;
}
