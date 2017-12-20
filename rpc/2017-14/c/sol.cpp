#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<double> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(int n){
    vector<point> V(n);

    double mx = 0;

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;
        mx = max(mx, x);
        V[i] = point(x, y);
    }

    auto func = [&](double x){
        double answer = 0;

        for (int i = 0; i < n; ++i){
            double y = x * V[i].imag() / (x - V[i].real());
            answer = max(answer, y * y);
        }

        return sqrt(answer + x * x);
    };

    int magic = 40;
    double fak = .48;
    double size = 1e5;

    double lo = mx, hi = mx + size;

    double best = 1e9;

    for (int i = 0; i < magic; ++i){
        double delta = (hi - lo) * fak;
        double u = lo + delta;
        double v = hi - delta;

        double xu = func(u);
        double xv = func(v);

        best = min({best, xu, xv});

        if (xu < xv) hi = v;
        else lo = u;
    }

    cout.precision(6);
    cout << fixed << best << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n)
        solve(n);

    return 0;
}
