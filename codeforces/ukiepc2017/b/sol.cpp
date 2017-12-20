#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define NEXT(i) ((i + 1) % n)

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int maxn = 100000 + 10;

const int oo = 1e9; // adjust

typedef complex<double> point;
typedef vector<point> polygon;

double cross(point a, point b){
    return imag(conj(a) * b);
}


double area2(point a, point b, point c){
    return cross(b - a, c - a);
}

namespace std{
    bool operator<(point a, point b){
        if (a.real() != b.real())
            return a.real() < b.real();
        return a.imag() < b.imag();
    }
}

polygon convex_hull(vector<point> &P)
{
	int n = P.size(), k = 0;
	vector<point> h(2 * n);
	sort(P.begin(), P.end());
	for (int i = 0; i < n; h[k++] = P[i++])
		while (k >= 2 && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
	for (int i = n - 2, t = k + 1; i >= 0; h[k++] = P[i--])
		while (k >= t && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
	return polygon(h.begin(), h.begin() + k - (k > 1));
}

vector<pair<int, int>> antipodal(const polygon &P)
{
	vector<pair<int, int>> ans;
	int n = P.size();

	if (P.size() == 2)
		ans.push_back({ 0, 1 });

	if (P.size() < 3)
		return ans;

	int q0 = 0;

	while (abs(area2(P[n - 1], P[0], P[NEXT(q0)]))
			> abs(area2(P[n - 1], P[0], P[q0])))
		++q0;

	for (int q = q0, p = 0; q != 0 && p <= q0; ++p)
	{
		ans.push_back({ p, q });

		while (abs(area2(P[p], P[NEXT(p)], P[NEXT(q)]))
				> abs(area2(P[p], P[NEXT(p)], P[q])))
		{
			q = NEXT(q);
			if (p != q0 || q != 0)
				ans.push_back({ p, q });
			else
				return ans;
		}

		if (abs(area2(P[p], P[NEXT(p)], P[NEXT(q)]))
				== abs(area2(P[p], P[NEXT(p)], P[q])))
		{
			if (p != q0 || q != n - 1)
				ans.push_back({ p, NEXT(q) });
			else
				ans.push_back({ NEXT(p), q });
		}
	}

	return ans;
}

double check(int a, int b, int c, int d, const polygon &P)
{
	for (int i = 0; i < 4 && a != c; ++i)
	{
		if (i == 1) swap(a, b);
		else swap(c, d);
	}
	if (a == c) // a admits a support line parallel to bd
	{
		double A = abs(area2(P[a], P[b], P[d])); 
		// double of the triangle area
		double base = abs(P[b] - P[d]);
		// base of the triangle abd
		return A / base;
	}
	return oo;
}

double polygon_width(const polygon &P)
{
	if (P.size() < 3)
		return 0;

	auto pairs = antipodal(P);
	double best = oo;
	int n = pairs.size();

	for (int i = 0; i < n; ++i)
	{
		double tmp = check(pairs[i].first, pairs[i].second,
				pairs[NEXT(i)].first, pairs[NEXT(i)].second, P);
		best = min(best, tmp);
	}

	return best;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<point> value(n);

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;

        value[i] = point(x, y);
    }

    value = convex_hull(value);

    cout.precision(10);

    cout << fixed << polygon_width(value) << endl;

    return 0;
}
