#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

vector<pii> edges;

int ask(int u, int v, int w){
    cout << "Q " << u << " " << v << " " << w << endl;
    cout.flush();
    int x; cin >> x;
    return x;
}

void build_tree(set<int> s){
    if (s.size() == 1)
        return;

    auto nodes = vector<int>(s.begin(), s.end());

    if (nodes.size() == 2){
        edges.push_back({nodes[0], nodes[1]});
        return;
    }

    random_shuffle(nodes.begin(), nodes.end());

    int u = nodes[0], v = nodes[1];

    map<int,set<int>> subtree;

    for (int i = 0; i < nodes.size(); ++i){
        int w = nodes[i];
        int x = ask(u, v, w);
        subtree[x].insert(w);
    }

    vector<int> path;

    for (auto t : subtree){
        path.push_back(t.first);
        build_tree(t.second);
    }

    sort(path.begin(), path.end(), [&](int x, int y){
        int t = ask(u, x, y);
        return t == x;
    });

    for (int i = 1; i < (int)path.size(); ++i)
        edges.push_back({path[i-1], path[i]});
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    set<int> s;
    
    for (int i = 1; i <= n; ++i)
        s.insert(i);

    build_tree(s);

    cout << "A" << endl;

    for (auto e : edges)
        cout << e.first << " " << e.second << endl;

    cout.flush();

    return 0;
}