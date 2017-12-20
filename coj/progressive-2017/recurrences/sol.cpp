#include <bits/stdc++.h>

using namespace std;

long long m(long long a){
	return (a % 10 + 10) % 10;
}

long long solve(long long x, long long y, long long z, long long n){
	long long s = 0;
	for (int i = 1; i <= n; ++i){
		long long X = 4 * x - 3 * y - 3 * z;
		long long Y = 5 * x - 4 * y - 4 * z;
		long long Z = y - x;

		x = X, y = Y, z = Z;
		s += x + y + z;
		s = m(s), x = m(x), y = m(y), z = m(z);
	}

	return s;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		long long n, x, y, z;
		cin >> n >> x >> y >> z;

		long long t = m( 18 * x - 12 * y - 6 * z );
		long long k = n / 3;

		long long x0 = m( x + y + z );
		long long x1 = m( 8 * x - 6 * y - 7 * z );
		long long x2 = m( 17 * x - 13 * y - 7 * z );

		int rem = n % 3;

		long long v = 0;
		if (rem == 1) v = x1;
		if (rem == 2) v = x2;

		long long answer = m( m(k) * t + v );
		cout << answer << endl;
	}

	return 0;
}
