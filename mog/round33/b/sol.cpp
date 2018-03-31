#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<int64> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct union_find
{
    vector<int> p;

    union_find(int n) : p(n, -1) {}

    bool join(int u, int v)
    {
        if ((u = root(u)) == (v = root(v)))
            return false;
        if (p[u] > p[v])
            swap(u, v);
        p[u] += p[v];
        p[v] = u;
        return true;
    }

    int root(int u)
    {
        return p[u] < 0 ? u : p[u] = root(p[u]);
    }
};

int64 rectilinear_mst(vector<point> ps)
{
    vector<int> id(ps.size());
    iota(id.begin(), id.end(), 0);

    struct edge
    {
        int src, dst;
        int64 weight;
    };

    vector<edge> edges;
    for (int s = 0; s < 2; ++s)
    {
        for (int t = 0; t < 2; ++t)
        {
            sort(id.begin(), id.end(), [&](int i, int j)
            {
                return real(ps[i] - ps[j]) < imag(ps[j] - ps[i]);
            });

            map<int64, int> sweep;

            for (int i : id)
            {
                for (auto it = sweep.lower_bound(-imag(ps[i]));
                        it != sweep.end(); sweep.erase(it++))
                {
                    int j = it->second;
                    if (imag(ps[j] - ps[i]) < real(ps[j] - ps[i]))
                        break;
                    int64 d = abs(real(ps[i] - ps[j])) 
                            + abs(imag(ps[i] - ps[j]));
                    edges.push_back({ i, j, d });
                }
                sweep[-imag(ps[i])] = i;
            }

            for (auto &p : ps)
                p = point(imag(p), real(p));
        }

        for (auto &p : ps)
            p = point(-real(p), imag(p));
    }

    int64 cost = 0;
    sort(edges.begin(), edges.end(), [](edge a, edge b)
    {
        return a.weight < b.weight;
    });

    union_find uf(ps.size());
    for (edge e : edges)
        if (uf.join(e.src, e.dst))
            cost += e.weight;

    return cost;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<point> P(n);

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        P[i] = point(x, y);
    }

    cout << 2 * rectilinear_mst(P) << endl;

    return 0;
}