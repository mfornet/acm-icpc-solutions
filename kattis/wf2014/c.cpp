#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef complex<double> point;

double cross(point a, point b){
    return imag( conj(a) * b );
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n; cin >> n;

    vector<point> pol(n);

    double x0 = 1e9, x1 = -1e9;

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;
        pol[i] = point(x, y);

        if ( abs(y) < eps ){
            x0 = min(x0, x);
            x1 = max(x1, x);
        }
    }

    //     vxc    v
    double a = 0, b = 0;

    for (int i = 0; i < n; ++i){
        double v = cross( pol[i], pol[ (i + 1) % n ]);
        double x = v * (real(pol[i]) + real(pol[ (i + 1) % n ])) / 3.;

        a += x, b += v;
    }

    a /= 2; b /= 2;
    double v = b;

    double xt = real(pol[0]);
    
    int lo = 0, hi = oo;
    double rlo = 0, rhi = 1e9;

    if (v < 0){
        v *= -1;
        a *= -1;
    }

    if (abs(x0 - xt) < eps){
        if (v * x0 > a){
            cout << "unstable" << endl;
            return 0;
        }
    }
    else if (x0 > xt){
        double m = (a - x0 * v) / (x0 - xt);
        hi = min(hi, int(ceil(m)) );
        rhi = min(rhi, m);
    }
    else{
        double m = (a - x0 * v) / (x0 - xt);
        lo = max(lo, int(floor(m)));
        rlo = max(rlo, m);
    }

    if (abs(x1 - xt) < eps){
        if (v * x1 < a){
            cout << "unstable" << endl;
            return 0;
        }
    }
    else if (x1 > xt){
        double m = (a - x1 * v) / (x1 - xt);
        lo = max(lo, int(floor(m)));
        rlo = max(rlo, m);
    }
    else{
        double m = (a - x1 * v) / (x1 - xt);
        hi = min(hi, int(ceil(m)) );        
        rhi = min(rhi, m);
    }

    if (rhi < rlo)
        cout << "unstable" << endl;
    else{
        cout << lo << " .. ";
        if (hi == oo) cout << "inf" << endl;
        else cout << hi << endl;
    } 

    return 0;
}