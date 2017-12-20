#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007;

long long p2(long long a) { return a * a % mod; }
long long p3(long long a) { return a * p2(a) % mod; }
long long p4(long long a) { long long t = p2(a); return t * t % mod; }

long long modpow(long long a, long long n){
	long long b = 1;
	while (n){
		if (n & 1) b = b * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return b;
}

long long i24 = modpow(24LL, mod - 2);
long long i8 = modpow(8LL, mod - 2);

long long f(long long n, long long k){
	n %= mod; k %= mod;
	vector<long long> t = {
		p3(k), -(4LL * p2(k) % mod * n % mod),
		6LL * p2(k) % mod, 6LL * k % mod * p2(n) % mod,
		-(6LL * k % mod * n % mod), 11LL * k % mod, 
		6LL * p2(n) % mod, - (2LL * n % mod), 6LL
	};

	long long answer = 0;

	for (auto v : t)
		answer = (answer + v + mod) % mod;
	
	return answer * k % mod * i24 % mod;
}


//n*(n + 1)*(n*(n + 1) + 2)/8

long long g(long long n){
	n %= mod;
	long long t = n * (n + 1) % mod;
	return t * (t + 2) % mod * i8 % mod;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long t; cin >> t;
	int tc = 1;
	
	while (t--){
		long long n; cin >> n; 
		cout << "Case #" << tc++ << ": ";
		long long tmp = (g(n) - g(n / 2) + mod) % mod;

		if (n & 1)
			cout << (tmp - f(n, n / 2) + mod) % mod<< '\n';
		else
			cout << (tmp - f(n, (n - 1) / 2) + mod) % mod << '\n';
	}

	return 0;
}
