#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 300000;
const int maxn = 200000 + 10;

vector<int> adj[maxn];

int ds[maxn];
int value[maxn];
int position[maxn];
bool cycle[maxn];

int root(int a){
    return ds[a] < 0 ? a : ds[a] = root(ds[a]);
}

bool join(int a, int b){
    a = root(a), b = root(b);

    if (a == b)
        return false;

    if (ds[a] < ds[b])
        swap(a, b);

    ds[b] += ds[a];
    ds[a] = b;

    return true;
}

bool build(int s, int p, int fin, vector<int> &path){
    if (s == fin){
        path.push_back(s);
        return true;
    }

    for (auto u : adj[s]){
        if (u == p) continue;

        if (build(u, s, fin, path)){
            path.push_back(s);
            return true;
        }
    }

    return false;
}

int go(int s, int p=-1){
    int answer = 0;
    for (auto u : adj[s]){
        if (cycle[u] || u == p)
            continue;

        answer = max(answer, 1 + go(u, s));
    }

    return answer;
}

struct segment_tree{
    struct node{
        int a, b, c;

        node(int a=-oo, int b=-oo, int c=-oo) : a(a), b(b), c(c){
        }
    };

    int n;
    vector<node> data;

    segment_tree(vector<pii> &path){
        n = (int)path.size();
        data = vector<node>(4 * n);
        build(1, 0, n, path);
    }

    node merge(node &L, node &R){
            return {
                max(L.a, R.a),
                max(L.b, R.b),
                max({L.c, R.c, L.b + R.a})
            };
    }

    void build(int p, int b, int e, vector<pii> &path){
        if (b + 1 == e){
            data[p] = node(path[b].first, path[b].second, -oo);
        }
        else{
            int m = (b + e) >> 1, l = p << 1, r = l | 1;
            build(l, b, m, path);
            build(r, m, e, path);

            data[p] = merge(data[l], data[r]);
        }

        // cout << b << " " << e << " :: " << data[p].a << " " << data[p].b << " " << data[p].c << endl;
    }

    node query(int p, int b, int e, int x, int y){
        if (x <= b && e <= y)
            return data[p];

        int m = (b + e) >> 1, l = p << 1, r = l | 1;

        node L = x < m ? query(l, b, m, x, y) : node();
        node R = m < y ? query(r, m, e, x, y) : node();

        auto ans = merge(L, R);

        // cout << "qry: " << p << " " << b << " " << e << " : " << ans.a << " " << ans.b << " " << ans.c << endl;

        return ans;
    }
};

bool seen[maxn];

pii farthest(int s, int p=-1){
    seen[s] = true;
    pii ans(s, 0);

    for (auto u : adj[s]){
        if (cycle[u] || u == p) continue;

        pii cur = farthest(u, s);

        if (cur.second + 1 > ans.second){
            ans = {cur.first, cur.second + 1};
        }
    }

    return ans;
}

int calc(int s){
    pii K = farthest(s);
    pii L = farthest(K.first);
    return L.second;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    memset(ds, -1, sizeof ds);

    vector<int> path;
    vector<pii> edge(n);

    for (int i = 1; i <= n; ++i){
        int u, v; cin >> u >> v;

        edge[i - 1] = pii(u, v);

        if (!join(u, v)){
            assert(build(u, -1, v, path));
        }

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int s = path.size();

    for (int i = 0; i < s; ++i){
        cycle[path[i]] = true;
    }

    int tmp = 0;

    for (int i = 1; i <= n; ++i)
    {
        if (!cycle[i] && !seen[i]){
            tmp = max(tmp, calc(i));
        }
    }

    vector<int> depth(2 * s);
    vector<pii> value(2 * s);

    for (int i = 0; i < s; ++i){
        depth[i + s] = depth[i] = go(path[i]);
        position[path[i]] = i;
    }

    for (int i = 0; i < 2 * s; ++i){
        value[i].first = depth[i] + i;
        value[i].second = depth[i] - i;
    }

    segment_tree st(value);

    // for (int i = 0; i < s; ++i){
    //     cout << depth[i] << " " << path[i] << endl;
    // }

    // cout << "===" << endl;
    // for (int i = 0; i < 2 * s; ++i)
    //     cout << value[i].first << " " << value[i].second << endl;
    // cout << endl;

    for (int i = 0; i < n; ++i){
        int u = edge[i].first, v = edge[i].second;

        if (!cycle[u] || !cycle[v]){
            cout << -1 << endl;
            continue;
        }

        if (position[u] > position[v])
            swap(u, v);

        int xu = position[u], xv = position[v];
        if (xu > xv) swap(xu, xv);

        if (xv - xu == 1){
            xu += s;
            swap(xu, xv);
        }

        // cout << u << " " << v << " :: " << xu << " " << xv << endl;
        cout << max(tmp, st.query(1, 0, 2 * s, xu, xv+1).c) << endl;
        // exit(0);
    }

    return 0;
}