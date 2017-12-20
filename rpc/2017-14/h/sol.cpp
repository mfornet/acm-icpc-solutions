#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct maper{
    int counter;
    map<string,int> m;

    maper(){
        counter = 0;
    }

    int get(string c){
        //cout << c << endl;
        if (m.find(c) == m.end())
            m[c] = counter++;
        return m[c];
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n){
        maper A;

        vector<pii> edges(n);

        int t = 0;

        for (int i = 0; i < n; ++i){
            string s; cin >> s;

            int u = A.get("X" + s.substr(0,1));
            int v = A.get("Y" + s.substr(1,1));

            edges[i] = pii(u, v);

            t = max({t, u, v});
        }

        t++;

        for (int i = 0; i < n; ++i)
            cout << edges[i].first << " " << edges[i].second << endl;

        vector<int> degree(t);
        vector<int> ds(t, -1);

        function<int(int)> root = [&](int u){
            return ds[u] < 0 ? u : ds[u] = root(ds[u]);
        };

        function<bool(int,int)> join = [&](int u, int v){
            u = root(u), v = root(v);
            if (u == v) return false;

            if (ds[u] < ds[v]) swap(u, v);
            ds[v] += ds[u];
            ds[u] = v;

            return true;
        };

        int cc = t;

        for (int i = 0; i < (int)edges.size(); ++i){
            int u = edges[i].first, v = edges[i].second;

            if (join(u, v))
                cc--;

            degree[u]++;
            degree[v]++;
        }

        int hm = 0;

        for (int i = 0; i < t; ++i){
            if (degree[i] & 1)
                hm++;
        }

        cout << ((cc == 1 && hm <= 2) ? "YES" : "NO" ) << endl;
    }    return 0;
}
