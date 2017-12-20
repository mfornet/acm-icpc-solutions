#include <bits/stdc++.h>

using namespace std;

long long mul(long long a, long long b, long long M)
{
	long long q = (long double) a * (long double) b / (long double) M;
	long long r = a * b - q * M;
	return (r + 5 * M) % M;
}


long long pow(long long a, long long b, long long M)
{
	long long x = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1) x = mul(x, a, M);
		a = mul(a, a, M);
	}
	return x;
}

bool witness(long long a, long long s, long long d, long long n)
{
	long long x = pow(a, d, n);
	if (x == 1 || x == n - 1)
		return 0;
	for (int i = 0; i < s - 1; i++)
	{
		x = mul(x, x, n);
		if (x == 1)
			return 1;
		if (x == n - 1)
			return 0;
	}
	return 1;
}

bool miller_rabin(long long n)
{
	if (n < 2)
		return 0;
	if (n == 2)
		return 1;
	if (n % 2 == 0)
		return 0;
	long long d = n - 1, s = 0;
	while (d % 2 == 0)
		++s, d /= 2;
	vector<long long> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (long long p : test)
		if (p >= n) break;
		else if (witness(p, s, d, n))
			return 0;
	return 1;
}

long long pollard_rho(long long n)
{
	if (!(n & 1))
		return 2;
	while (1)
	{
		long long x = (long long) rand() % n, y = x;
		long long c = rand() % n;
		if (c == 0 || c == 2) c = 1;
		for (int i = 1, k = 2;; i++)
		{
			x = mul(x, x, n);
			if (x >= c) x -= c;
			else x += n - c;
			if (x == n) x = 0;
			if (x == 0) x = n - 1;
			else x--;
			long long d = __gcd(x > y ? x - y : y - x, n);
			if (d == n)
				break;
			if (d != 1) return d;
			if (i == k)
			{
				y = x;
				k <<= 1;
			}
		}
	}
	return 0;
}

vector<long long> factorize(long long n){
	if (miller_rabin(n))
		return {n};

	long long f = pollard_rho(n);
	auto answer = factorize( f );
	auto tmp = factorize( n / f );
	for (auto _f : tmp) answer.push_back( _f );
	return answer;
}

long long sigma(long long n){
	auto f = factorize( n );
	sort( f.begin(), f.end() );

	long long answer = 1;
	int t = (int)f.size();

	for (int i = 0, j; i < t; i = j){
		long long p = f[i], pp = f[i];
		for (j = i; j < t && f[j] == f[i]; ++j)
			pp *= p;
		answer *= (pp - 1) / (p - 1);
	}

	return answer;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		long long a;
		cin >> a;

		long long s = sigma(a) - a;

		cout << (s < a ? "deficient" : s > a ? "abundant" : "perfect" ) << '\n';
	}

	return 0;
}
