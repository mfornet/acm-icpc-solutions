#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double oo = 1e9;
const double eps = 1e-5;
const int maxn = 100000 + 10;

// #define double long double

const double pi = acos(-1);

typedef complex<double> point;

struct line { point p, q; };

double dot(point a, point b) { return real(conj(a) * b); }
double cross(point a, point b) { return imag(conj(a) * b); }

point read(){
    double x, y;
    cin >> x >> y;
    return point(x, y);
}

pair<point,int> crosspoint(const line &l, const line &m)
{
    double A = cross(l.q - l.p, m.q - m.p);
    double B = cross(l.q - l.p, l.q - m.p);
    if (abs(A) < eps && abs(B) < eps)
        return {m.p, 1}; // same line
    if (abs(A) < eps)
        return {m.p, 2};
    return {m.p + B / A * (m.q - m.p), 0};
}

double g(point x, point y, point v){
    double t = dot(v, y - x) / dot(v, v);
    if (t < 0.) return oo;
    else return t;
}

double s(line a, point p, point v){
    auto _x = crosspoint(a, {p, p+v});

    if (_x.second == 2){
        return oo;
    }
    else if (_x.second == 1){
        return min(g(p, a.p, v), g(p, a.q, v));
    }
    else{
        auto x = _x.first;

        if (abs(abs(a.p - x) + abs(a.q - x) - abs(a.p - a.q)) < eps)
            return g(p, x, v);
        else
            return oo;
    }
}

double solve(line a, line b, point v){
    // cout << "solve" << endl;
    if (abs(v) < eps) return oo;
    double p = s(a, b.p, v);
    double q = s(a, b.q, v);
    // cout << v << endl;
    // cout << p << " " << q << endl;
    return min(p, q); 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    point a0 = read();
    point a1 = read();
    line al = {a0, a1};

    point b0 = read();
    point b1 = read();
    line bl = {b0, b1};

    point av = read();
    point bv = read();

    double e0 = solve(al, bl, bv - av);
    double e1 = solve(bl, al, av - bv);
    double x = min(e0, e1);

    if (x == oo)
        cout << -1 << endl;
    else{
        cout.precision(17);
        cout << fixed << x << endl;
    }

    return 0;
}
/*
0 0 0 1
1 0 2 0
-1 0
-2 0
*/