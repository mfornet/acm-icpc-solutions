#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1 << 20;
const int smaxn = 1 << 10;

const int SIZE = 300;

struct query{
    int l, r, k, idx, blk;
    query(int l, int r, int k, int idx) : l(l), r(r), k(k), idx(idx), blk(idx / SIZE) {}

    bool operator<(const query &qry) const{
        if (blk != qry.blk) return blk < qry.blk;
        return r < qry.r;
    }
};

int V[maxn];

int seen[maxn];
int X[maxn];

int freq[maxn];
int bfreq[smaxn];
int total;

int add(int v){
    //cout << "ADD: " << v << endl;
    total++;
    freq[v]++;
    bfreq[v >> 10]++;
}

int remove(int v){
    //cout << "REMOVE: " << v << endl;
    total--;
    freq[v]--;
    bfreq[v >> 10]++;
}

int kth(int k){
    if (k > total) return -1;
    int p = 0;

    while (bfreq[p] < k){
        k -= bfreq[p];
        p++;
    }
    
    p <<= 10;

    while (freq[p] < k){
        k -= freq[p];
        p++;
    }

    return p;
}

int _add(int p){
    //cout << "add pos: " << p << endl;
    int v = V[p];
    //cout << "value: " << v << endl;

    if (seen[v] == 1)
        remove(X[v]);

    X[v] ^= p;
    seen[v]++;

    if (seen[v] == 1)
        add(X[v]);
}

int _rem(int p){
    //cout << "remove pos: " << p << endl;
    int v = V[p];

    if (seen[v] == 1)
        remove(X[v]);

    X[v] ^= p;
    seen[v]--;

    if (seen[v] == 1)
        add(X[v]);
}

void solve(int n){
    vector<int> A(n);
    int t = 0;
    map<int,int> P;

    for (int i = 1; i <= n; ++i)
    {
        cin >> V[i];

        if (!P.count(V[i])){
            A[t] = V[i];
            P[V[i]] = t++;
        }

        V[i] = P[ V[i] ];
    }

    int q; cin >> q;

    vector<query> Q;
    vector<int> answer(q);
    
    for (int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;
        r++;
        Q.push_back(query(l, r, k, i));
    }

    sort(Q.begin(), Q.end());

    int b = 1, e = 1;

    for (auto qry : Q){
        //cout << qry.l << " " << qry.r - 1 << " " << qry.k << " " << qry.idx << endl;

        while (e < qry.r)
            _add(e++);
        while (b > qry.l)
            _add(--b);
        while (e > qry.r)
            _rem(--e);
        while (b < qry.l)
            _rem(b++);

        answer[qry.idx] = kth(qry.k);
    }

    while (b < e)
        _rem(b++);

    for (int i = 0; i < q; ++i){
        if (answer[i] == -1) cout << ":(" << endl;
        else cout << A[V[answer[i]]] << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n){
        solve(n);
        break;
    }

    return 0;
}
