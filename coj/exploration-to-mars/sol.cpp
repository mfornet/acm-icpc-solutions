#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1024;

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
	int n = (int)a.size();

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

int64 sqr[maxn][maxn];

void fft2d(vector<vector<point>> &M, int sign=+1){
    int n = M.size(), m = (int)M[0].size();

    for (int i = 0; i < n; ++i){
        vector<point> a(m);
        for (int j = 0; j < m; ++j)
            a[j] = M[i][j];
        fft(a, sign);
        for (int j = 0; j < m; ++j)
            M[i][j] = a[j];
    }

    for (int j = 0; j < m; ++j){
        vector<point> a(n);
        for (int i = 0; i < n; ++i)
            a[i] = M[i][j];
        fft(a, sign);
        for (int i = 0; i < n; ++i)
            M[i][j] = a[i];
    }
}

int p(int v){
    return 1 << (__lg(v) + 1);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n1, m1;
    cin >> n1 >> m1;

    int n = p(n1), m = p(m1);

    vector<vector<point>> A(n, vector<point>(m));
    vector<vector<point>> B(n, vector<point>(m));

    for (int i = 0; i < n1; ++i)
        for (int j = 0; j < m1; ++j){
            int v; cin >> v;
            A[i][j] = point(v);
            sqr[i + 1][j + 1] = 1LL * v * v;
            sqr[i + 1][j + 1] += sqr[i][j + 1] + sqr[i + 1][j] - sqr[i][j];
        }

    int n2, m2;
    cin >> n2 >> m2;

    int64 value = 0;

    for (int i = 0; i < n2; ++i)
        for (int j = 0; j < m2; ++j){
            int v; cin >> v;
            B[n2 - 1 - i][m2 - 1 - j] = point(v);
            value += 1LL * v * v;
        }

    fft2d(A);
    fft2d(B);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            A[i][j] = A[i][j] * B[i][j];

    fft2d(A, -1);

    int64 a1 = oo;
    int64 a2 = oo;

    for (int i = n2 - 1; i < n1; ++i)
        for (int j = m2 - 1; j < m1; ++j){
            int64 value = int64(round(A[i][j].x)) * (-2) + 
                        sqr[i + 1][j + 1] - sqr[i + 1][j + 1 - m2] - sqr[i + 1 - n2][j + 1] + sqr[i + 1 - n2][j + 1 - m2];

            if (value < a1) swap(a1, value);
            if (value < a2) swap(a2, value);
        }
    
    cout << a1 + value << " " << a2 + value << endl;

    return 0;
}
