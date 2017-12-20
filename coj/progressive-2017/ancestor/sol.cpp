#include <bits/stdc++.h>

using namespace std;

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

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string dna = "AGTC";

	string a, b;
	
	while (cin >> a >> b){
		int lena = (int)a.length(), lenb = (int)b.length();
		int size = 1; 

		while (size < max(lena, lenb) )
			size *= 2;
		size *= 2;

		vector<int> score( size );

		for (auto c : dna){
			vector<point> A(size), B(size);
			for (int i = 0; i < lena; ++i)
				A[i] = point(a[ lena - i - 1 ] == c);
			for (int i = 0; i < lenb; ++i)
				B[i] = point(b[ i ] == c);
			fft(A, +1);
			fft(B, +1);
			for (int i = 0; i < size; ++i)
				A[i] = A[i] * B[i];
			fft(A, -1);
			for (int i = 0; i < size; ++i)
				score[i] += int(A[i].x+0.1);
		}

		int answer = 0;
		int pos = -1;
		for (int i = 0; i < (int)score.size(); ++i){
			if (score[i] > answer){
				answer = score[i];
				pos = i;
			}
		}

		cout << answer << endl;
		if (answer == 0)
			cout << "No matches" << '\n';
		else{
			int x = lena - pos - 1;
			int y = 0;

			if (x > 0) y = -x, x = 0;

			while (x < lena || y < lenb){
				if (x < 0 || x >= lena)
					cout << b[y];
				else if (y < 0 || y >= lenb)
					cout << a[x];
				else
					cout << (a[x] == b[y] ? a[x] : 'X');
				x++; y++;
			}
			cout << '\n';
		}
		cout << '\n';
	}

	return 0;
}
