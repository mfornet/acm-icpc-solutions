#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

struct st{
    struct node{
        node *l, *r;
        int value;
    };

    node* build(int b, int e){
        node *u = new node();

        if (b + 1 == e)
            u->value = -1;
        else
        {
            int m = (b + e) / 2;
            u->l = build(b, m);
            u->r = build(m, e);
        }
        return u;
    }

    int get(node *u, int b, int e, int x){
        if (b + 1 == e) return u->value;
        int m = (b + e) / 2;

        if (x < m)
            return get(u->l, b, m, x);
        else
            return get(u->r, m, e, x);
    }

    node* clone(node *u){
        node *v = new node();
        v->l = u->l, v->r = u->r;
        v->value = u->value;
        return v;
    }

    node* update(node* u, int b, int e, int x, int v){
        u = clone(u);
        if (b + 1 == e)
            u->value = v;
        else{
            int m = (b + e) / 2;
            if (x < m)
                u->l = update(u->l, b, m, x, v);
            else
                u->r = update(u->r, m, e, x, v);
        }
        return u;
    }
} helper;

int n;

pii root(st::node *r, int a){
    while (true){
        int v = helper.get(r, 0, n, a);
        if (v < 0)
            return pii(a, v);
        a = v;
    }
    assert(false);
    return pii(-1, -1);
}

st::node* join(st::node *r, int u, int v){
    pii U = root(r, u), V = root(r, v);
    if (U.first == V.first) return r;
    if (U.second < V.second) swap(U, V);
    r = helper.update(r, 0, n, V.first, U.second + V.second);
    r = helper.update(r, 0, n, U.first, V.first);
    return r;
}

int size(pii A, pii B){
    return A.first == B.first ? -A.second : -A.second - B.second;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int m;
    cin >> n >> m;

    vector<st::node*> R(m + 1);
    R[0] = helper.build(0, n);

    for (int i = 1; i <= m; ++i){
        int u, v;
        cin >> u >> v;
        u--; v--;
        R[i] = join(R[i - 1], u, v);
    }

    int q; cin >> q;
    while(q--){
        int u, v, z;
        cin >> u >> v >> z;
        u--; v--;

        int lo = 0, hi = m;

        while (lo + 1 < hi){
            int mid = (lo + hi) / 2;

            pii A = root( R[mid], u );
            pii B = root( R[mid], v );

            if (size(A, B) < z)
                lo = mid;
            else
                hi = mid;
        }
        cout << hi << endl;
    }

    return 0;
}