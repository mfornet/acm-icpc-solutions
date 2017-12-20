#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int64;

int64 add(int64 &a, int64 b, int64 m){
	a += b;
	if (a >= m)
		a -= m;
}

int64 mul(int64 a, int64 b, int64 M)
{
	int64 c = 0;
	while (b){
		if (b & 1) 
			add(c, a, M);	
		add(a, a, M);
		b >>= 1;
	}
	return c;
}


int64 pow(int64 a, int64 b, int64 M)
{
	int64 x = 1;
	for (; b > 0; b >>= 1)
	{
		if (b & 1) x = mul(x, a, M);
		a = mul(a, a, M);
	}
	return x;
}

bool witness(int64 a, int64 s, int64 d, int64 n)
{
	int64 x = pow(a, d, n);
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

bool miller_rabin(int64 n)
{
	if (n < 2)
		return 0;
	if (n == 2)
		return 1;
	if (n % 2 == 0)
		return 0;
	int64 d = n - 1, s = 0;
	while (d % 2 == 0)
		++s, d /= 2;
	vector<int64> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (int64 p : test)
		if (p >= n) break;
		else if (witness(p, s, d, n))
			return 0;
	return 1;
}

int64 mrand(){
	int64 x = rand() + ((1LL * rand()) << 60);
}

int64 gcd(int64 a, int64 b){
	while (b > 0){
		int64 t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int64 pollard_rho(int64 n)
{
	if (!(n & 1))
		return 2;

	while (true){
	int64 x = mrand() % (n - 2) + 2;
	int64 y = x; 
	int64 c = mrand() % (n - 1) + 1;
	int64 d = 1;
	while (d == 1)
	{
		x = (mul(x, x, n) + c) % n;
		y = (mul(y, y, n) + c) % n;
		y = (mul(y, y, n) + c) % n;
		d = gcd( max(x, y) - min(x, y), n );
	}
	if (d < n) return d;
	}
	return 0;
}

int64 answer[100];
int nCount;

void factorize(int64 n){
	if (miller_rabin(n)){
		answer[ nCount++ ] = n;
		return;
	}

	int64 f = pollard_rho(n);
	factorize( f );
	factorize( n / f );
}

void solve(int64 a){
	nCount = 0;
	factorize(a);
	sort(answer, answer + nCount);

	for (int i = 0; i < nCount; ++i){
		cout << answer[i] << " \n"[i + 1 == nCount];
		cout.flush();
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		int64 a;
		cin >> a;
		assert(a > 1);
		solve(a);
	}

	return 0;
}

