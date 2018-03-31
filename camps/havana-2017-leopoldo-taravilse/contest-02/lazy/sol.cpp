#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100 + 10;

typedef complex<double> point;

point P[ maxn ];
double F[ maxn ];

double dist[ maxn ][ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;
    double x, y;
    cin >> x >> y;

    P[0] = point(x, y);
    cin >> x >> y;
    P[1] = point(x, y);

    for (int i = 0; i < n; ++i){
        cin >> x >> y; 
        double f; cin >> f;

        P[i + 2] = point(x, y);
        F[i + 2] = f;
    }

    n += 2;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            dist[i][j] = abs( P[i] - P[j] );
            dist[i][j] = min( dist[i][j], abs(dist[i][j] - F[i]) );
        }
    }

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    cout.precision(2);
    cout << fixed << dist[0][1] << endl;

    return 0;
}
