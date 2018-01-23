#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

#define double long double

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef complex<double> point;

namespace std
{
    bool operator<(point a, point b)
    {
        if (a.real() != b.real())
            return a.real() < b.real();
        return a.imag() < b.imag();
    }
}

pair<point,point> closest_pair_points(vector<point> &P)
{
    auto cmp = [](point a, point b)
    {
        return make_pair(a.imag(), a.real()) 
                < make_pair(b.imag(), b.real());
    };

    int n = P.size();
    sort(P.begin(), P.end());

    set<point, decltype(cmp)> S(cmp);
    const double oo = 1e9; // adjust
    double ans = oo;

    point a = P[0], b = P[1];

    for (int i = 0, ptr = 0; i < n; ++i)
    {
        while (ptr < i && abs(P[i].real() - P[ptr].real()) >= ans)
            S.erase(P[ptr++]);

        auto lo = S.lower_bound(point(-oo, P[i].imag() - ans - eps));
        auto hi = S.upper_bound(point(-oo, P[i].imag() + ans + eps));

        for (decltype(lo) it = lo; it != hi; ++it){
            double cur = abs(P[i] - *it);

            if (cur < ans){
                ans = cur;
                a = P[i];
                b = *it;
            }
        }

        S.insert(P[i]);
    }

    return {a, b};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<point> V(n);

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;

        V[i] = point(x, y);
    }

    cout.precision(0);
    auto answer = closest_pair_points(V);
    cout << fixed << answer.first.real() << " " << answer.first.imag() << endl;
    cout << fixed << answer.second.real() << " " << answer.second.imag() << endl;

    return 0;
}
