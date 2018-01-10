#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

struct node
{
    int v;
    node *l, *r;
};

node *insert(node *u, int v)
{
    if (!u) return new node{v, nullptr, nullptr};
    if (v < u->v)
        u->l = insert(u->l, v);
    else u->r = insert(u->r, v);
    return u;
}

bool cmp(node *u, node *v)
{
    if (!u || !v) return !u && !v;
    return cmp(u->l, v->l) && cmp(u->r, v->r);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<node*> roots(n);

    int ans = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            int v;
            cin >> v;

            roots[i] = insert(roots[i], v);
        }

        bool ok = true;

        for (int j = 0; j < i && ok; ++j)
            if (cmp(roots[j], roots[i])) ok = false;

        ans += ok;
    }

    cout << ans << endl;

    return 0;
}