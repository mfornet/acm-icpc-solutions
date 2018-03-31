#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000 + 5; 

int value[ maxn ][ maxn ];
int ds[ maxn * maxn ];

int root(int a){
    return ds[a] < 0 ? a : ds[a] = root( ds[a] );
}

bool join(int a, int b){
    a = root(a), b = root(b);
    if (a == b) return false;

    if (ds[b] > ds[a]) swap(a, b);
    ds[b] += ds[a];
    ds[a] = b;
    
    return true;
}

bool ok[ maxn ][ maxn ];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pair<int,pii>> E;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j){
            cin >> value[i][j];
            E.push_back( {value[i][j], {i, j}} );
        }

    sort(E.begin(), E.end());

    int q; cin >> q;
    vector<int> query(q);
    vector<int> answer(q);

    for (int i = 0; i < q; ++i)
        cin >> query[i];

    memset(ds, -1, sizeof ds);

    int total = 0;
    for (int i = q - 1, p = n * m; i >= 0; --i){
        while (p && E[p - 1].first > query[i]){
            p--;
            int x = E[p].second.first, y = E[p].second.second;

            int id = x * m + y;
            ok[ x ][ y ] = true;
            total++;

            for (int k = 0; k < 4; ++k){
                int nx = x + dx[k], ny = y + dy[k];
                if (0 <= nx && nx < n && 0 <= ny && ny < m && ok[nx][ny]){
                    int nid = nx * m + ny;
                    if (join(id, nid)) 
                        total--;
                }
            }
        }

        answer[ i ] = total;
    }

    for (int i = 0; i < q; ++i)
        cout << answer[i] << " \n"[i + 1 == q];

    return 0;
}
