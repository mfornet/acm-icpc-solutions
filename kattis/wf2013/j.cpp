#include <bits/stdc++.h>
#include <ext/algorithm>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#ifdef HOME
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl << flush;
#else
#define DB(x)
#endif

#define all(c) (c).begin(),(c).end()
#define endl '\n'
#define mp make_pair
#define first x
#define second y

typedef long long i64;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<double> point;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;

double sqr(double v){
    return v * v;
}

double cross(point a, point b){
    return imag(conj(a) * b);
}

vector<double> solve_quadratic(double A, double B, double C){
    double D = sqr(B) - 4 * A * C;
    if (D < -EPS) return {};
    if (D < EPS) return {-B / 2.0 / A};
    else{
        double x1 = (-B - sqrt(D)) / 2.0 / A;
        double x2 = (-B + sqrt(D)) / 2.0 / A;
        return {x1, x2};
    }
}

vector<point> circle_segment_intersection(point a, point b, double r){
    double x0 = a.real(), y0 = a.imag();
    double dx = b.real() - a.real(), dy = b.imag() - a.imag();
    double A = sqr(dx) + sqr(dy);
    double B = 2 * (dx * x0 + dy * y0);
    double C = sqr(x0) + sqr(y0) - sqr(r);
//  DB(A); DB(B); DB(C);

    vector<double> ans = solve_quadratic(A, B, C);
//  DB(ans.size());
    vector<point> inters;

    for (auto t : ans){
        if (-EPS < t && t < 1.0 + EPS){
            inters.push_back( point(x0 + t * dx, y0 + t * dy) );
        }
    }
    return inters;
}

double sign(double x){
    if (x < -EPS) return -1.0;
    else if (x < EPS) return 0.0;
    else return 1.0;
}

double angle(point a, point b){
    a /= abs(a), b /= abs(b);
    return max(arg(a / b), arg(b / a));
}

double circle_triangle_area(point a, point b, double r){
    vector<point> inters = circle_segment_intersection(a, b, r);
    if (abs(cross(a, b)) < EPS) return 0;
    if (norm(a) < r * r + EPS && norm(b) < r * r + EPS){
        return cross(a, b) / 2;
    }
    else if (norm(a) > r * r + EPS && norm(b) > r * r + EPS){
        if ((int)inters.size() == 2){
            double area = cross(inters[0], inters[1]) / 2;
            double rad = angle(inters[0], a) + angle(b, inters[1]);
            rad *= sign(area);
            area += rad * sqr(r) / 2;
            return area;
        }
        else{
            double rad = angle(b, a);
            rad *= sign(cross(a, b));
//          DB("CASEX"); DB(rad);
            return rad * sqr(r) / 2;
        }
    }
    else{
//      DB("HERE");
//      DB(inters.size());
//      DB(inters[0]);
        double s = sign(cross(a, b));
//      DB(s);
        if (norm(a) > r * r + EPS) swap(a, b);
        double area = abs(cross(a, inters[0])) / 2;
        double rad = angle(b, inters[0]);
//      DB(rad);
        area += rad * sqr(r) / 2;
        return s * area;
    }
}

double circle_polygon_area(vector<point> &pol, double r){
    double ans = 0;
    for (int i = 0; i + 1 < (int)pol.size(); ++i){
        double cur = circle_triangle_area(pol[i], pol[i + 1], r);
//      DB(cur); DB("---");
        ans += cur;
    }
    return abs(ans);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, r;
    while (cin >> n >> r){
        vector<point> pol(n + 1);
        for (int i = 0; i < n; ++i){
            int x, y; cin >> x >> y;
            pol[i] = point(x, y);
        }
        pol[n] = pol[0];

        cout.precision(9);
        cout << fixed << circle_polygon_area(pol, r) << endl;
    }

    return 0;
}

