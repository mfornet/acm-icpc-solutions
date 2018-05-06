#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<int> read(){
    int d; cin >> d;

    vector<int> L(d);

    for (int i = 0; i < d; ++i)
        cin >> L[i];

    return L;
}

void solve(){
    int n; cin >> n;

    map<int,int> freq;
    vector<bool> used(n);

    for (int i = 0; i < n; ++i){
        auto L = read();

        int mf = n + 1;
        int w = -1;

        for (auto x : L){
            if (used[x])
                continue;

            int f = freq[x]++;

            if (f < mf){
                mf = f;
                w = x;
            }
        }

        cout << w << endl;

        if (w >= 0)
            used[w] = true;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t-->0)
        solve();

    return 0;
}