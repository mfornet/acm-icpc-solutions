#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100;

struct vec{
    double x, y, z;
    
    vec(double x=0, double y=0, double z=0) : x(x), y(y), z(z) {}
    
    vec operator *(const double k) const{
        return vec(k * x, k * y, k * z);
    }
    
    vec operator +(const vec &v) const{
        return vec(x + v.x, y + v.y, z + v.z);
    }
    
    vec operator -(const vec &v) const{
        return vec(x - v.x, y - v.y, z - v.z);
    }
    
    double norm(){
        return x * x + y * y + z * z;
    }
};

int n;
vec pos[ maxn ], speed[ maxn ];
vec cpos[ maxn ];
double adj[ maxn ][ maxn ];

vector<int> mst( double t ){
    for (int i = 0; i < n; ++i)
        cpos[i] = pos[i] + speed[i] * t;
    
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            adj[i][j] = (cpos[i] - cpos[j]).norm();
            assert( adj[i][j] < 9e17 );
        }
    }
    
    vector<int> par(n, -1); 
    vector<bool> seen(n);

    vector<double> dist(n, 1e18);
    dist[0] = 0;
    
    for (int it = 0, u; it < n; ++it){
        u = -1;

        for (int i = 0; i < n; ++i){
            if (seen[i]) continue;
            if (u == -1 || dist[i] < dist[u])
                u = i;
        }

        seen[u] = true;
        // cout << u << endl;
        
        for (int i = 0; i < n; ++i){
            if (!seen[i] && adj[i][u] < dist[i]){
                dist[i] = adj[i][u];
                par[i] = u;
            }
        }
    }

    return par;
}

const int ITER = 60;

void print(vi &a){
    for (auto u : a)
        cout << u << " ";
    cout << endl;
}

int go(double lo, double hi){
    vi lid = mst(lo), hid = mst(hi);

    if (lid == hid) return 0;

    for (int i = 0; i < ITER; ++i){
        double mid = (lo + hi) / 2;
        vi cid = mst( mid );
        
        if (cid != lid){
            if (cid != hid){
                return go(lo, mid) + go(mid, hi);
            }
            else{
                hi = mid;
            }
        }
        else{
            lo = mid;
        }
    }
    
    return 1;
}

int solve(){
    for (int i = 0; i < n; ++i){
        cin >> pos[i].x >> pos[i].y >> pos[i].z;
        cin >> speed[i].x >> speed[i].y >> speed[i].z;
    }

    return go(0, 1e6) + 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int tc = 1;
    
    while (cin >> n){
        cout << "Case " << tc++ << ": " << solve() << endl; 
    }
    
    return 0;
}