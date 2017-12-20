#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int ds[ maxn ];

int root(int a){
    return ds[a] < 0 ? a : ds[a] = root( ds[a] );
}

bool join(int a, int b){
    a = root(a), b = root(b);
    if (a == b)
        return false;

    if (ds[b] > ds[a])
        swap(a, b);

    ds[b] += ds[a];
    ds[a] = b;
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<long long,pii>> E(m);

    long long sum = 0;

    for (int i = 0; i < m; ++i){
        cin >> E[i].second.first >> E[i].second.second >> E[i].first;
        sum += E[i].first;
    }

    sort(E.begin(), E.end());
    reverse( E.begin(), E.end() );
    memset(ds, -1, sizeof ds);

    long long mx = 0;

    for (int i = 0; i < m; ++i){
        int u = E[i].second.first, v = E[i].second.second;

        if (join(u, v))
            sum -= E[i].first;
        else
            mx = max(mx, E[i].first);
    }

    cout << sum << " " << mx << endl;

    return 0;
}
