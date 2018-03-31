#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef complex<double> point;

const int maxn = 100000;

double a, b, c;
double l1, l2, l3, PER, per, AREA;

point A, B, C;

double cross(point a, point b){
	return imag(conj(a) * b);
}

point getpoint(double p){
	if (p <= l1){
		return point(p, 0);
	}
	else if (p <= l1 + l2){
		p -= l1;
		return (C - B) / abs(C - B) * p + B;
	}
	else{
		p -= l1 + l2;
		return (A - C) / abs(A - C) * p + C;
	}
}

int line(double p){
	if (p <= l1) return 0;
	if (p <= l1 + l2) return 1;
	return 2;
}

double func(double p){
	point x0 = getpoint(p), x1 = getpoint(p + per);
	int q0 = line(p), q1 = line(p + per);

	double sign = 1.;

	if (q1 < q0){
		swap(q1, q0);
		swap(x0, x1);
		sign = -1.;
	}

	assert(q1 != q0);

	double answer = 0.;

	if (q0 == 0 && q1 == 1){
		double cur = cross(B - x0, x1 - x0);
		answer = AREA - cur;
	}
	else if (q0 == 0 && q1 == 2){
		double cur = cross(x1 - x0, A - x0);
		answer = cur - AREA;
	}
	else if (q0 == 1 && q1 == 2){
		double cur = cross(C - x0, x1 - x0);
		answer = AREA - cur;
	}
	else{
		assert(false);
	}

	return answer * sign;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	cin >> a >> b >> c;

	A = point(), B = point(c, 0), C = point(a, b);

	l1 = c, l2 = sqrt((a - c) * (a - c) + b * b), l3 = sqrt(a * a + b * b);
	PER = l1 + l2 + l3;
	per = PER / 2;

	AREA = c * b / 2;

	double lo = 0, hi = per;
	double v0 = func(lo);

	const int MAGIC = 1000;

	for (int i = 0; i < MAGIC; ++i){
		double m = (lo + hi) / 2;
		double v = func(m);

		if (v * v0 < 0){
			hi = m;
		}
		else{
			lo = m;
			v0 = v;
		}
	}

	point p0 = getpoint(lo);
	point p1 = getpoint(lo + per);

//	cout << lo << endl;
//	cout << func(lo) << endl;

	cout.precision(17);

	cout << fixed << p0.real() << " " << p0.imag() << endl;
	cout << fixed << p1.real() << " " << p1.imag() << endl;

	return 0;
}
