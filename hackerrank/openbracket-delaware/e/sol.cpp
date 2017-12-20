#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500000 + 10;

int value[maxn];
vi children[maxn];
int size[maxn];
int n;
int64 answer;

vector<int> order;

int ST[maxn], EN[maxn], pnt;

bool cmp(int u, int v){
    assert(1 <= u <= n);
    assert(1 <= v <= n);
    return size[u] > size[v];
}

void init(){
    order.push_back(1);

    int b = 0;
    while (b < (int)order.size()){
        int u = order[b++];
        for (auto v : children[u])
            order.push_back(v);
    }
}

void _sort(){
    for (int i = (int)order.size() - 1; i >= 0; --i){
        int u = order[i];
        size[u] = 1;
        for (auto v : children[u]) size[u] += size[v];
        sort(children[u].begin(), children[u].end(), cmp);
    }
}

void build(){
    int pnt = 0;
    stack<pii> s; s.push( pii(1,0) );

    while (!s.empty()){
        pii state = s.top(); s.pop();
        int u = state.first;
        int p = state.second;

        if (p == 0){
            ST[u] = pnt++;
            EN[u] = pnt;
        }
        else
            EN[u] = EN[children[u][p-1]];

        if (p == (int)children[u].size())
            continue;

        s.push(pii(u, p+1));
        s.push(pii(children[u][p], 0));
    }

    // for (int i = (int)order.size() - 1; i >= 0; --i){
    //     int u = order[i];

    //     ST[u] = i;
    //     EN[u] = children[u].empty() ? i + 1 : EN[children[u].back()];
    // }

    // ST[s] = pnt++;
    // for (auto u : children[s])
    //     build(u);
    // EN[s] = pnt;
}

struct segment_tree{
    struct node{
        int value, size, lazy;
    };

    vector<node> D;

    segment_tree(int n=1){
        D = vector<node>(4 * n);
        build(1, 0, n);
    }

    void build(int p, int b, int e){
        if (b + 1 == e) D[p] = {0, 1, 0};
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m);
            build(r, m, e);
            D[p] = merge(D[l], D[r]);
        }
    }

    node merge(node u, node v){
        if (u.value != v.value){
            if (u.value < v.value)
                return {u.value, u.size, 0};
            else
                return {v.value, v.size, 0};
        }
        return {u.value, u.size + v.size, 0};
    }

    void push(int u, int l, int r){
        if (D[u].lazy){
            int &lz = D[u].lazy;
            D[l].value += lz;
            D[l].lazy += lz;
            D[r].value += lz;
            D[r].lazy += lz;
            lz = 0;
        }
    }

    void update(int p, int b, int e, int x, int y, int v){
        if (x <= b && e <= y){
            D[p].value += v;
            D[p].lazy += v;
            return;
        }

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r);

        if (x < m) update(l, b, m, x, y, v);
        if (m < y) update(r, m, e, x, y, v);

        D[p] = merge(D[l], D[r]);
    }

    int query(int p, int b, int e, int x, int y){
        if (x <= b && e <= y)
            return D[p].value > 0 ? 0 : D[p].size;

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r);

        int size = 0;
        if (x < m) size += query(l, b, m, x, y);
        if (m < y) size += query(r, m, e, x, y);

        return size;
    }
} st;


vi pos[maxn];

bool dead[maxn];

void solve(int s){
    for (auto u : children[s])
        solve(u);

    int v = value[s];
    int u = pos[v][0] ^ pos[v][1] ^ s;

    if (ST[s] <= ST[u] && EN[u] <= EN[s]){
        st.update(1, 0, n, ST[u], EN[u], +1);
        dead[u] = true;
    }

    int cur = st.query(1, 0, n, ST[s], EN[s]);
    answer += cur;

    int B = ST[s], E = children[s].empty() ? B + 1 : EN[children[s][0]];

    for (int i = 1; i < (int)children[s].size(); ++i){
        int w = children[s][i];

        function<void(int)> dfs = [&](int s){
            if (dead[s]) return;

            int x = pos[value[s]][0] ^ pos[value[s]][1] ^ s;

            if (B <= ST[x] && EN[x] <= E)
                st.update(1, 0, n, ST[x], EN[x], +1);

            int tmp = st.query(1, 0, n, B + 1, E);
            answer += tmp;

            for (auto u : children[s])
                dfs(u);

            if (B <= ST[x] && EN[x] <= E)
                st.update(1, 0, n, ST[x], EN[x], -1);

        };

        dfs(w);
        E = EN[w];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    assert(1 <= n && n <= 200000);

    for (int i = 2; i <= n; ++i){
        int p; cin >> p;
        children[p].push_back(i);
    }

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        assert(1 <= value[i] && value[i] <= n / 2);
    }

    _sort();
    build();

    // cout << "here" << endl;
    // exit(0);

    st = segment_tree(n);

    for (int i = 1; i <= n; ++i)
        pos[ value[i] ].push_back(i);

    for (int i = 1; i <= n / 2; ++i)
        assert(pos[i].size() == 2);

    solve(1);

    cout << answer * 2 - n << endl;

    return 0;
}
