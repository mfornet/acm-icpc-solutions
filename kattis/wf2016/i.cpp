#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int maxn = 50 + 10;

int oo = 0x3f3f3f3f;
int adj[ maxn ][ maxn ];
int dis[ maxn ][ maxn ];
int to[ maxn ][ maxn ];

const double eps = 1e-8, inf = numeric_limits<double>::infinity();

typedef vector<double> vec;
typedef vector<vec> mat;

double simplexMethodPD(mat &A, vec &b, vec &c)
{
    int n = c.size(), m = b.size();
    mat T(m + 1, vec(n + m + 1));
    vector<int> base(n + m), row(m);

    for(int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
            T[j][i] = A[j][i];
        T[j][n + j] = 1;
        base[row[j] = n + j] = 1;
        T[j][n + m] = b[j];
    }

    for (int i = 0; i < n; ++i)
        T[m][i] = c[i];

    while (1)
    {
        int p = 0, q = 0;
        for (int i = 0; i < n + m; ++i)
            if (T[m][i] <= T[m][p])
                p = i;

        for (int j = 0; j < m; ++j)
            if (T[j][n + m] <= T[q][n + m])
                q = j;

        double t = min(T[m][p], T[q][n + m]);

        if (t >= -eps)
        {
            vec x(n);
            for (int i = 0; i < m; ++i)
                if (row[i] < n) x[row[i]] = T[i][n + m];
            // x is the solution
            return -T[m][n + m]; // optimal
        }

        if (t < T[q][n + m])
        {
            // tight on c -> primal update
            for (int j = 0; j < m; ++j)
                if (T[j][p] >= eps)
                    if (T[j][p] * (T[q][n + m] - t) >= 
                        T[q][p] * (T[j][n + m] - t))
                        q = j;

            if (T[q][p] <= eps)
                return inf; // primal infeasible
        }
        else
        {
            // tight on b -> dual update
            for (int i = 0; i < n + m + 1; ++i)
                T[q][i] = -T[q][i];

            for (int i = 0; i < n + m; ++i)
                if (T[q][i] >= eps)
                    if (T[q][i] * (T[m][p] - t) >= 
                        T[q][p] * (T[m][i] - t))
                        p = i;

            if (T[q][p] <= eps)
                return -inf; // dual infeasible
        }

        for (int i = 0; i < m + n + 1; ++i)
            if (i != p) T[q][i] /= T[q][p];

        T[q][p] = 1; // pivot(q, p)
        base[p] = 1;
        base[row[q]] = 0;
        row[q] = p;

        for (int j = 0; j < m + 1; ++j)
            if (j != q)
            {
                double alpha = T[j][p];
                for (int i = 0; i < n + m + 1; ++i)
                    T[j][i] -= T[q][i] * alpha;
            }
    }

    return inf;
}

int realid[ maxn ][ maxn ];
int order[ maxn * maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n; cin >> n;

    int total = 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j){
            cin >> adj[i][j];

            if (adj[i][j] > 0)
                total++;

            if (adj[i][j] < 0) adj[i][j] = oo;
            dis[i][j] = adj[i][j];
        }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j){
            if (i == j) to[i][j] = -1;
            else{
                for (int k = 0; k < n; ++k){
                    if (k != i && dis[i][j] == adj[i][k] + dis[k][j]){
                        to[i][j] = k;
                        break;
                    }
                }
            }
        }

    srand( time(NULL) );

    iota( order, order + total, 0 );
    random_shuffle( order, order + total );

    for (int i = 0, t = 0; i < n; ++i)
        for (int j = 0; j < n; ++j){
            if (adj[i][j] == oo || adj[i][j] == 0) continue;
            realid[i][j] = order[t++];
        }

    mat A;
    vec b;

    double teps = 1e-10;

    for (int i = 0; i < total; ++i){
        vec X( total );

        X[i] = 1.;

        A.push_back( X );
        b.push_back( 1. );
    }

    int r; cin >> r;

    for (int i = 0; i < r; ++i){
        int s, d, t;
        cin >> s >> d >> t;

        vector<int> path;
        
        while (s != -1){
            path.push_back(s);
            s = to[ s ][ d ];
        }

        vec X( total );

        for (int j = 1; j < (int)path.size(); ++j){
            int u = path[j - 1], v = path[j];
            int id = realid[u][v];
            X[ id ] = dis[u][v];

            t -= X[ id ];
        }

        A.push_back( X );
        b.push_back( 1. * t + teps );

        for (int j = 0; j < total; ++j)
            X[j] *= -1;

        A.push_back( X );
        b.push_back( -1. * t + teps );
    }

    mat AA = A;
    vec bb = b;

    vector<int> perm( bb.size() );
    iota(perm.begin(), perm.end(), 0);
    random_shuffle(perm.begin(), perm.end());

    for (int i = 0; i < (int)bb.size(); ++i){
        A[i] = AA[ perm[i] ];
        b[i] = bb[ perm[i] ];
    }

    // for (int i = 0; i < (int)b.size(); ++i){
    //  for (auto a : A[i]) cout << a << " ";
    //  cout << " :: " << b[i] << endl;
    // }

    int q; cin >> q;
    

    cout.precision(17);

    while (q--){
        int u, v;
        int U;
        cin >> u >> v;

        U = u;

        vector<int> path;
        
        vec C( total );

        while (u != -1){
            path.push_back( u );
            u = to[u][v];
        }

        double tmp = 0;

        for (int i = 1; i < (int)path.size(); ++i){
            int u = path[i - 1], v = path[i];
            int id = realid[u][v];
            C[id] = dis[u][v];
            tmp += dis[u][v];
        }

        double ans_min = simplexMethodPD( A, b, C ) + tmp;

        for (int i = 0; i < total; ++i)
            C[i] *= -1;

        double ans_max = -simplexMethodPD( A, b, C ) + tmp;

        cout << U << " " << v << " " << fixed << ans_min << " " << ans_max << endl;
    }

    return 0;
} 