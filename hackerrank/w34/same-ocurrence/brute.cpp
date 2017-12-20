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

    int n, q;
    cin >> n >> q;

    map<int,vector<int>> pos;

    for (int i = 1; i <= n; ++i){
        int v; cin >> v;
        pos[v].push_back( i );
    }

    while (q--){
        int x, y; cin >> x >> y;

        int answer = 0;

        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j){
                int countx = upper_bound(pos[x].begin(), pos[x].end(), j) - lower_bound(pos[x].begin(), pos[x].end(), i);
                int county = upper_bound(pos[y].begin(), pos[y].end(), j) - lower_bound(pos[y].begin(), pos[y].end(), i);
                if (countx == county){
                    // cout << i << " " << j << endl;
                    answer++;
                }
            }

        cout << answer << endl;
    }

    return 0;
}