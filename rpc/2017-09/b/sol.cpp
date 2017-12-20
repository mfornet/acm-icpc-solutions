#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n){
        vector<int> tree;
        vector<int> deg(n+1, 1);
        for (int i = 0; i < n - 2; ++i){
            int v; cin >> v;
            tree.push_back(v);
            deg[v]++;
        }
        tree.push_back(n);

        set<int> leaf;
        for (int i = 1; i <= n; ++i)
            if (deg[i] == 1)
                leaf.insert(i);

        vector<pii> E;

        for (auto u : tree){
            int x = *leaf.begin();
            int y = u;

            deg[x]--;
            deg[y]--;

            if (x > y) swap(x, y);
            E.push_back(pii(x,y));

            if (deg[x] == 1) leaf.insert(x);
            if (deg[y] == 1) leaf.insert(y);
            if (deg[x] == 0) leaf.erase(x);
            if (deg[y] == 0) leaf.erase(y);
        }

        sort(E.begin(), E.end());
        for (auto e : E)
            cout << e.first << " " << e.second << endl;
    }

    return 0;
}
