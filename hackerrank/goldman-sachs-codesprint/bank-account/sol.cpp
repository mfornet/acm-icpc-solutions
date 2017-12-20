#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(){
    int n, x, k, d;
    cin >> n >> k >> x >> d;

    k *= 100;

    int optionA = d * 100;
    int optionB = 0;

    for (int i = 0; i < n; ++i){
        int v; cin >> v;
        optionB += max(k, v * x);
    }

    // cout << optionA << " " << optionB << endl;

    if (optionB > optionA)
        cout << "upfront" << endl;
    else
        cout << "fee" << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q; cin >> q;

    while (q--)
        solve();

    return 0;
}