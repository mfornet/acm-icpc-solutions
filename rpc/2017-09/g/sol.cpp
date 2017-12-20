#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(int n){
    vector<string> value(1);
    vector<vi> adj(1);
    map<string,int> id;

    auto getid = [&](string &s){
        int &v = id[s];
        if (v == 0){
            v = (int)value.size();
            value.push_back(s);
            adj.push_back({});
        }
        return v;
    };

    vector<int> deg(2 * n);


    for (int i = 0; i < n; ++i){
        string a, b;
        cin >> a >> b;
        int va = getid(a);
        int vb = getid(b);
        deg[vb]++;
        adj[va].push_back(vb);
    }

    queue<int> q;

    vector<int> level(value.size()), depend(value.size());

    for (int i = 1; i < (int)value.size(); ++i){
        if (deg[i] == 0){
            q.push(i);
            level[i] = 1;
        }
    }

    while (!q.empty()){
        int u = q.front(); q.pop();
        for (auto v : adj[u]){
            depend[v]++;
            level[v] = max(level[v], level[u] + 1);
            if (--deg[v] == 0)
                q.push(v);
        }
    }

    vector<int> order(value.size() - 1);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b){
        if (level[a] != level[b]) return level[a] < level[b];
        if (depend[a] != depend[b]) return depend[a] < depend[b];
        return value[a] < value[b];
    });

    for (auto u : order){
        cout << level[u] << "." << depend[u] << " " << value[u] << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n)
        solve(n);

    return 0;
}
