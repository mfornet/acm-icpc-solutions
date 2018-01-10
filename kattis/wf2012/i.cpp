#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int maxm = 1000000 + 10;

vector<pii> ROW_MIRROR[ maxm ], 
            COL_MIRROR[ maxm ];

int r, c;
int dr[4] = {0, -1, 0, 1};
int dc[4] = {1, 0, -1, 0};

pii intersection;

struct seg{
    int u, a, b;
};

typedef seg event;

struct data{
    vector<seg> h, v;
    int x, y;
};

data build(int x, int y, int d){
    data answer;

    while (true){
        if (d == 0){
            int pos = upper_bound( ROW_MIRROR[x].begin(), ROW_MIRROR[x].end(), 
                                    pii(y, oo) ) - ROW_MIRROR[x].begin();

            if (pos == ROW_MIRROR[x].size()){
                answer.h.push_back( {x, y, c + 1} );
                y = c + 1;
                break;
            }
            else{
                pii cur = ROW_MIRROR[x][pos];
                answer.h.push_back( {x, y, cur.first} );
                y = cur.first;
                d = (d - cur.second + 4) % 4;
            }           
        }
        else if (d == 2){
            int pos = lower_bound( ROW_MIRROR[x].begin(), ROW_MIRROR[x].end(), 
                                    pii(y, -oo) ) - ROW_MIRROR[x].begin() - 1;

            if (pos == -1){
                answer.h.push_back( {x, 0, y} );
                y = -1;
                break;
            }
            else{
                pii cur = ROW_MIRROR[x][pos];
                answer.h.push_back( {x, cur.first, y} );
                y = cur.first;
                d = (d - cur.second + 4) % 4;
            }
        }
        else if (d == 3){
            int pos = upper_bound( COL_MIRROR[y].begin(), COL_MIRROR[y].end(), 
                                    pii(x, oo) ) - COL_MIRROR[y].begin();

            if (pos == COL_MIRROR[y].size()){
                answer.v.push_back( {y, x, r + 1} );
                x = r + 1;
                break;
            }
            else{
                pii cur = COL_MIRROR[y][pos];
                answer.v.push_back( {y, x, cur.first} );
                x = cur.first;
                d = (d + cur.second + 4) % 4;
            }
        }
        else{
            int pos = lower_bound( COL_MIRROR[y].begin(), COL_MIRROR[y].end(),
                                    pii(x, -oo) ) - COL_MIRROR[y].begin() - 1;

            if (pos == -1){
                answer.v.push_back( {y, 0, x} );
                x = -1;
                break;
            }
            else{
                pii cur = COL_MIRROR[y][pos];
                answer.v.push_back( {y, cur.first, x} );
                x = cur.first;
                d = (d + cur.second + 4) % 4;
            }
        }
    }

    answer.x = x, answer.y = y;

    // cout << "horizontal" << endl;
    // for (auto s : answer.h) cout << s.u << " " << s.a << " " << s.b << endl;
    // cout << "vertical" << endl;
    // for (auto s : answer.v) cout << s.u << " " << s.a << " " << s.b << endl;

    return answer;
}

void init(int r, int c, int m, int n){
    for (int i = 1; i <= r; ++i)
        ROW_MIRROR[i].clear();
    for (int i = 1; i <= c; ++i)
        COL_MIRROR[i].clear();
    intersection = pii(r + 1, c + 1);
}

void update(int idx, int v, vi &bit){
    while (idx <= bit.size()){
        bit[idx] += v;
        idx += idx & -idx;
    }
}

int query(int idx, vi &bit){
    int answer = 0;

    while (idx > 0){
        answer += bit[idx];
        idx -= idx & -idx;
    }

    return answer;
}

int64 intersect(vector<seg> &h, vector<seg> &v){
    vector<int> bit( max(r, c) + 1 );

    for (auto s : v){
        h.push_back( {s.a, s.u, -2} );
        h.push_back( {s.b, s.u, -3} );
    }

    sort( h.begin(), h.end(), [](seg &X, seg &Y){
        return X.u < Y.u;
    });

    int64 answer = 0;
    bool found_first = false;

    // cout << "begin" << endl;
    for (auto e : h){
        // cout << e.u << " " << e.a << " " << e.b << endl;

        if (e.b == -2)
            update(e.a, +1, bit);
        else if (e.b == -3)
            update(e.a, -1, bit);
        else{
            if (e.b <= e.a + 1) continue;

            int low = query(e.a, bit);
            int total = query(e.b - 1, bit) - low;

            // cout << low << " " << total << endl;
            answer += total;

            if (total && !found_first){
                int lo = e.a, hi = e.b;
                
                while (lo + 1 < hi){
                    int m = (lo + hi) / 2;
                    int ctot = query(m, bit) - low;
                    if (ctot > 0) hi = m;
                    else lo = m;
                }

                intersection = min( intersection, pii(e.u, hi) );
                found_first = true;
            }
        }
    }


    return answer;
}

void solve(int m, int n){
    init(r, c, m, n);

    for (int i = 0; i < m; ++i){
        int x, y; cin >> x >> y;
        ROW_MIRROR[ x ].push_back(pii(y, -1));
        COL_MIRROR[ y ].push_back(pii(x, -1));
    }

    for (int i = 0; i < n; ++i){
        int x, y; cin >> x >> y;
        ROW_MIRROR[ x ].push_back(pii(y, +1));
        COL_MIRROR[ y ].push_back(pii(x, +1));      
    }

    for (int i = 1; i <= r; ++i)
        sort( ROW_MIRROR[i].begin(), ROW_MIRROR[i].end());

    for (int i = 1; i <= c; ++i)
        sort( COL_MIRROR[i].begin(), COL_MIRROR[i].end());

    auto path1 = build(1, 0, 0);
    
    if (path1.x == r && path1.y == c + 1){
        cout << 0 << endl;
        return;
    }

    auto path2 = build(r, c + 1, 2);

    int64 answer = 0;

    answer += intersect( path1.h, path2.v );
    answer += intersect( path2.h, path1.v );

    if (answer == 0)
        cout << "impossible" << endl;
    else
        cout << answer << " " << intersection.first << " " << intersection.second << endl;

    // exit(0);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int m, n;

    int tc = 1;

    while (cin >> r >> c >> m >> n){
        cout << "Case " << tc++ << ": ";
        solve(m, n);
    }

    return 0;
} 