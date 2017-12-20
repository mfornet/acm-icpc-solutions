#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const double pi = acos(-1);

typedef complex<double> point;

struct line { point p, q; };
struct segment { point p, q; };

double cross(point p, point q){
    return imag( conj(p) * q );
}

double dot(point p, point q){
    return real( imag(p) * q );
}

bool intersectLL(const line &l, const line &m)
{
	return abs(cross(l.q - l.p, m.q - m.p)) > eps || // non-parallel
			abs(cross(l.q - l.p, m.p - l.p)) < eps;   // same line
}

bool intersectLP(const line &l, const point &p)
{
	return abs(cross(l.q - p, l.p - p)) < eps;
}

bool intersectSP(const segment &s, const point &p)
{
	return abs(s.p - p) + abs(s.q - p) - abs(s.q - s.p) < eps; 
	// triangle inequality
	return min(real(s.p), real(s.q)) <= real(p)
			&& real(p) <= max(real(s.p), real(s.q))
			&& min(imag(s.p), imag(s.q)) <= imag(p)
			&& imag(p) <= max(imag(s.p), imag(s.q))
			&& cross(s.p - p, s.q - p) == 0;
}

point projection(const line &l, const point &p)
{
	double t = dot(p - l.p, l.p - l.q) / norm(l.p - l.q);
	return l.p + t * (l.p - l.q);
}

point reflection(const line &l, const point &p)
{
	return p + 2.0 * (projection(l, p) - p);
}

double distanceLP(const line &l, const point &p)
{
	return abs(p - projection(l, p));
}

double distanceLL(const line &l, const line &m)
{
	return intersectLL(l, m) ? 0 : distanceLP(l, m.p);
}

double distanceSP(const segment &s, const point &p)
{
        line l = {s.p, s.q};
	const point r = projection(l, p);
	if (intersectSP(s, r)) return abs(r - p);
	return min(abs(s.p - p), abs(s.q - p));
}

point crosspoint(const line &l, const line &m)
{
	double A = cross(l.q - l.p, m.q - m.p);
	double B = cross(l.q - l.p, l.q - m.p);
	if (abs(A) < eps && abs(B) < eps)
		return m.p; // same line
	if (abs(A) < eps)
		assert(false); // !!!PRECONDITION NOT SATISFIED!!!
	return m.p + B / A * (m.q - m.p);
}

vector<point> get_square(double alpha, vector<point> &square){
    point v = polar(1., alpha);
    point w = v * point(0, 1);

    point a = square[0], b = a + v;
    point c = square[1], d = c + w;
    point e = square[2], f = e + w;

    line l1 = {a, b}, l2 = {c, d}, l3 = {e, f};
    point x = crosspoint(l1, l2), y = crosspoint(l1, l3);

    double dist = abs(x - y);

    if ( cross(y - x, dist * w) * cross(y - x, square[3]) < 0){
        w *= -1;
    }

    return {x, y, y + dist * w,  x + dist * w};
}

double predicate(double alpha, vector<point> &cloud){
    auto newSquare = get_square(alpha, cloud);

    double value = 0;

    for (auto p : cloud){
        double cur_dist = 1e18;

        for (int i = 0; i < 4; ++i){
            segment l = {newSquare[i], newSquare[(i + 1) & 3]};
            cur_dist = min( cur_dist, distanceSP(l, p) );
        }

        value = max( value, cur_dist );
    }

    if (value < eps){ // finish
        cout.precision(12);
        for (auto p : newSquare)
            cout << fixed << real(p) << " " << imag(p) << endl;
        exit(0);
    }

    return value;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<point> square(4);

    for (int i = 0; i < 4; ++i){
        double x, y;
        cin >> x >> y;
        square[i] = point(x, y);
    }

    int intervals = 200;
    double size = pi / 2 / intervals;
    int magic = 100;

    for (int i = 0; i < 1000; ++i)
        cout << i << " " << predicate(pi / 2 / 1000 * i, square) << endl;
    exit(0);

    for (int i = 0; i < intervals; ++i){
        double lo = i * size, hi = lo + size;
        cout << endl;    
        cout << lo << " " << hi << endl;
        for (int j = 0; j < magic; ++j){
            double delta = (hi - lo) * .45;
            double x = lo + delta, y = hi - delta;

            if (predicate(x, square) < predicate(y, square))
                hi = y;
            else
                lo = x;
        }

        double p = (lo + hi) / 2;
        cout << p << endl;
        cout << predicate(p, square) << endl;
    }

    for (int i = 0; i < 4; ++i)
        cout << "0 0\n";

    return 0;
}
