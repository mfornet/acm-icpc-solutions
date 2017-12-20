#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const long long oo = 0x3f3f3f3f3f3f3f3f;
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
    while(cin >> n >> m){
        assert(0 <= m && m <= 3000);

    int s, t;
    cin >> s >> t;

    vector< pair<long long, pii> > E(m);

    for (int i = 0; i < m; ++i){
        cin >> E[i].second.first >> E[i].second.second >> E[i].first;
    }

    sort( E.begin(), E.end() );

    long long answer = oo;

    for (int i = 0; i < m; ++i){
        memset( ds, -1, n * sizeof(int) );
        bool found = false;

        for (int j = i; j < m; ++j){
            join(E[j].second.first, E[j].second.second);

            if (root(s) == root(t)){
                found = true;
                answer = min(answer, E[j].first - E[i].first);
                break;
            }
        }

        if (!found) break;
    }

    assert( answer >= 0 );

    if (answer == oo)
        cout << "NO PATH" << endl;
    else
        cout << answer << endl;
    }
    
    return 0;
}
