#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

#define double long double

const double pi = acos(-1);

typedef complex<double> point;

struct circle { point p; double r; };
struct line { point p, q; };

vector<point> tangent(point p, circle C)
{
    double D = abs(p - C.p);

    if (D + eps < C.r) return {};
    point t = C.p - p;

    double theta = asin( C.r / D );
    double d = cos(theta) * D;

    t = t / abs(t) * d;
    if ( abs(D - C.r) < eps ) return {p + t};
    point rot( cos(theta), sin(theta) );
    return {p + t * rot, p + t * conj(rot)};
}

double dot(point a, point b) { return real(conj(a) * b); }

point projection(const line &l, const point &p)
{
    double t = dot(p - l.p, l.p - l.q) / norm(l.p - l.q);
    return l.p + t * (l.p - l.q);
}

point read(){
    double x, y;
    cin >> x >> y;
    return point(x, y);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout.precision(17);

    point a = read();
    point b = read();
    point c = read();
    double r; cin >> r;

    // check outside
    auto p = projection({a, b}, c);

    if (abs(abs(p - a) + abs(p - b) - abs(a-b)) > eps || abs(p-c) >= r){
        cout << fixed << abs(a-b) << endl;
        return 0;
    }

    auto ta = tangent(a, {c,r});
    auto tb = tangent(b, {c,r});

    double best = 1e18;

    for (auto x : ta)
        for (auto y : tb){
            auto _x = x - c;
            auto _y = y - c;

            double alpha = acos(dot(_x, _y) / abs(_x) / abs(_y));
            if (alpha < 0.) alpha += 2 * pi;
            alpha = min(alpha, 2 * pi - alpha);
            double cur = abs(a - x) + abs(y - b) + alpha * r;
            best = min(best, cur);
        }

    cout.precision(17);
    cout << fixed << best << endl;

    return 0;
}
