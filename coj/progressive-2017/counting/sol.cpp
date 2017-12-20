#include <bits/stdc++.h>

using namespace std;

const int limit = 5000 + 1;
const int mod = 1000000007;

void add(int &a, int b){
	a += b;
	if (a >= mod)
		a -= mod;
}

int pascal[ limit ][ limit ];
int prime[ limit ];
int value[ limit ];
int acc[ limit ];

int A[47][limit], B[47][limit];

int pDiv(int n){
	int answer = 1;
	while (n > 1){
		int p = prime[ n ];
		int count = 1;
		while (prime[n] == p){
			count++;
			n /= p;
		}
		answer *= count;
	}
	return answer - 1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < limit; ++i){
		pascal[i][0] = 1;
		for (int j = 1; j <= i; ++j){
			pascal[i][j] = pascal[i - 1][j];
			add( pascal[i][j], pascal[i - 1][j - 1] );
		}
	}

	for (int i = 2; i < limit; ++i){
		if (prime[i]) continue;
		for (int j = i; j < limit; j += i)
			prime[j] = i;
	}

	int mx = 0;

	for (int i = 1; i < limit; ++i){
		value[i] = pDiv(i);
		acc[i] = acc[i - 1] + value[i];
		mx = max( mx, value[i] );
	}

	for (int k = 1; k < 47; ++k){
		B[k][0] = 1;
		for (int i = 1; i < limit; ++i){
			A[k][i] = A[k][i - 1] + min( value[i], k );
			B[k][i] = 1LL * B[k][i - 1] * pascal[ value[i] ][ min(value[i], k) ] % mod;
		}
	}

	int t; cin >> t;

	while (t--){
		int n, k;
		cin >> n >> k;
		if (k < 47)
			cout << A[k][n] << " " << B[k][n] << '\n';
		else
			cout << acc[n] << " " << 1 << '\n';
	}


	return 0;
}
