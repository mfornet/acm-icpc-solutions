#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 300000 + 10;
const int maxk = 5;

int value[maxn];
int seen[maxn];
vector<int> freq[maxn];
vector<int> st[4 * maxn];

int get_freq(int v, int b, int e){
    return lower_bound(freq[v].begin(), freq[v].end(), e) -
            lower_bound(freq[v].begin(), freq[v].end(), b);
}

vector<int> merge(vector<int> &X, vector<int> &Y, int k, int b, int e){
    for (auto x : X) seen[x] = 0;
    for (auto x : Y) seen[x] = 0;

    int mf = (e - b) / k + 1;
vector<int> answer;

    for (auto x : X){
        seen[x] = 1;
        int f = get_freq(x, b, e);

        if (f >= mf)
            answer.push_back(x);
    }

    for (auto x : Y){
        if (seen[x] == 1) continue;

        int f = get_freq(x, b, e);
        if (f >= mf)
            answer.push_back(x);
    }

    return answer;
}

void build(int p, int b, int e){
    if (b + 1 == e)
        st[p] = {value[b]};
    else{
        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        build(l, b, m);
        build(r, m, e);
        st[p] = merge(st[l], st[r], maxk, b, e);
    }
}

vector<int> query(int p, int b, int e, int x, int y, int k){
    if (x <= b && y <= e)
        return st[p];

    int m = (b + e) >> 1, l = p << 1, r = l | 1;

    vector<int> X = x < m ? query(l, b, m, x, y, k) : vector<int>();
    vector<int> Y = m < y ? query(r, m, e, x, y, k) : vector<int>();

    vector<int> T = merge(X, Y, k, b, e);
    return T;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        freq[value[i]].push_back(i);
    }

    build(1, 0, n);

    for (int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;

        auto Q = query(1, 0, n, l, r, k);

        if (Q.empty()) cout << -1 << endl;
        else cout << *min_element(Q.begin(), Q.end()) << endl;
    }

    return 0;
}