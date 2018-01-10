/*
	Fast Fourier Transform

	Complexity: O(n log n)

	Tested: http://codeforces.com/gym/100285/problem/G
*/

struct point
{
	double x, y;
	point(double x = 0, double y = 0) : x(x), y(y) {}
};

point operator+(const point &a, const point &b) { return {a.x + b.x, a.y + b.y}; }
point operator-(const point &a, const point &b) { return {a.x - b.x, a.y - b.y}; }
point operator*(const point &a, const point &b) { 
	return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; 
}
point operator/(const point &a, double d) { return {a.x / d, a.y / d}; }

void fft(vector<point> &a, int sign = +1)
{
	int n = a.size();

	for (int i = 1, j = 0; i < n - 1; ++i)
	{
		for (int k = n >> 1; (j ^= k) < k; k >>= 1);

		if (i < j) swap(a[i], a[j]);
	}

	double theta = 2 * atan2(0, -1) * sign;

	for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
	{
		point wm(cos(theta / m), sin(theta / m)), w(1, 0);

		for (int i = 0; i < n; i += m, w = point(1, 0))
			for (int j = i, k = j + mh; j < i + mh; ++j, ++k, w = w * wm)
			{
				point x = a[j], y = a[k] * w;
				a[j] = x + y;
				a[k] = x - y;
			}
	}

	if (sign == -1)
		for (point &p : a) p = p / n;
}
