#include <bits/stdc++.h>

using namespace std;

const int limit = 500000 + 1;

long long prime[ limit ];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 2; i < limit; ++i){
		if (prime[i]) continue;

		for (int j = i; j < limit; j += i)
			prime[j] = i;
	}

	auto sigma = [&](int n){
		long long answer = 1;
		while (n > 1){
			long long pMul = prime[ n ];
			long long bPrime = prime[ n ];

			while (prime[ n ] == bPrime){
				pMul *= bPrime;
				n /= bPrime;
			}
			answer *= (pMul - 1) / (bPrime - 1);
		}
		return answer;
	};

	int t; cin >> t;

	while (t--){
		int n, k;
		cin >> n >> k;

		if ( n % k )
			cout << sigma(n) << '\n';
		else
			cout << sigma(n) - 1LL * k * sigma(n / k) << '\n';
	}

	

	return 0;
}
