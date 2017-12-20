#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200000 + 10;

int value[maxn];
vi children[maxn];
int size[maxn];

int ST[maxn], EN[maxn], pnt;

bool cmp(int u, int v){
    return size[u] > size[v];
}

void _sort(int s){
    size[s] = 1;
    for (auto u : children[s]){
        _sort(u);
        size[s] += size[u];
    }
    sort(children[s].begin(), children[s].end(), cmp);
}

void build(int s){
    ST[s] = pnt++;
    for (auto u : children[s])
        build(u);
    EN[s] = pnt;
}

struct segment_tree{
    struct node{
        int value, size, lazy;
    }  D[4 * maxn];

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
        // if (p == 1) cout << "update: " << x << " " << y << " " << v << endl;
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
        // cout << p << " " << b << " " << e << " " << x << " " << y << endl;
        if (x <= b && e <= y){
            // cout << p << " " << D[p].value << " " << D[p].size << endl;
            return D[p].value > 0 ? 0 : D[p].size;
        }

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r);

        int size = 0;
        if (x < m) size += query(l, b, m, x, y);
        if (m < y) size += query(r, m, e, x, y);

        return size;
    }

    void print(int p, int b, int e){
        if (b + 1 == e) cout << D[p].value << " ";
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            push(p, l, r);
            print(l, b, m);
            print(r, m, e);
        }
    }
} st;

int n;
int64 answer;

vi pos[maxn];

bool dead[maxn];

void solve(int s){
    // cout << "solve: " << s << endl;
    for (auto u : children[s])
        solve(u);

    int v = value[s];
    int u = pos[v][0] ^ pos[v][1] ^ s;

    if (ST[s] <= ST[u] && EN[u] <= EN[s]){
        st.update(1, 0, n, ST[u], EN[u], +1);
        dead[u] = true;
    }

    int cur = st.query(1, 0, n, ST[s], EN[s]);
    // cout << s << " " << cur << " :: " << ST[s] << " " << EN[s] << endl;
    // if (s == 3) exit(0);
    answer += cur;
    // cout << s << " " << ST[s] << " " << EN[s] << " :: " << n << endl;

    int B = ST[s], E = children[s].empty() ? B + 1 : EN[children[s][0]];

    for (int i = 1; i < (int)children[s].size(); ++i){
        int w = children[s][i];

        // cout << "start dfs: " << s << " " << w << endl;

        function<void(int)> dfs = [&](int s){
            if (dead[s]) return;

            int x = pos[value[s]][0] ^ pos[value[s]][1] ^ s;

            if (B <= ST[x] && EN[x] <= E)
                st.update(1, 0, n, ST[x], EN[x], +1);

            // st.print(1, 0, n);
            // cout << endl;
            int tmp = st.query(1, 0, n, B + 1, E);
            // cout << "DFS: " << s << " " << tmp << endl;
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

    for (int i = 2; i <= n; ++i){
        int p; cin >> p;
        children[p].push_back(i);
    }

    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    _sort(1);
    build(1);
    st.build(1, 0, n);

    for (int i = 1; i <= n; ++i)
        pos[ value[i] ].push_back(i);

    solve(1);

    // cout << answer << endl;
    cout << answer * 2 - n << endl;

    return 0;
}
