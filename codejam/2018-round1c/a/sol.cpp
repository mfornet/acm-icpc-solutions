#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

string solve(){
    int n, l;
    cin >> n >> l;

    set<string> W;

    vector<set<char>> pos(l);

    for (int i = 0; i < n; ++i){
        string s;
        cin >> s;

        W.insert(s);

        for (int j = 0; j < l; ++j)
            pos[j].insert(s[j]);
    }

    int total = 1;

    for (int i = 0; i < l; ++i){
        total = min(n + 1, total * (int)pos[i].size());
    }

    if (total <= n)
        return "-";

    vector<vector<char>> ppos(l);

    for (int i = 0; i < l; ++i)
        ppos[i] = vector<char>(pos[i].begin(), pos[i].end());

    for (int w = 0; ; ++w){
        string x = "";

        for (int i = 0, u = w; i < l; ++i){
            int c = u % ppos[i].size();
            u /= ppos[i].size();
            x = x + ppos[i][c];
        }

        if (W.find(x) == W.end())
            return x;
    }

    assert(false);
    return "";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc){
        string ans = solve();
        cout << "Case #" << tc << ": " << ans << endl;
    }

    return 0;
}