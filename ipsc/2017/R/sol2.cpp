#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int64 mod = 1000000009;

int64 modpow(int64 a, int64 n){
	int64 b = 1;

	while (n){
		if (n & 1)
			b = 1LL * b * a % mod;
		n >>= 1;
		a = 1LL * a * a % mod;
	}

	return b;
}

int64 m(int64 a){
	return (a % mod + mod) % mod;
}

void solve(int n, int c, int k){
	double a[n], b[n];
	int64 A[n], B[n];

	int go[n];

	for (int i = 0; i < n; ++i)
		A[i] = B[i] = a[i] = b[i] = go[i] = 0;

	a[0] = 1.;
	A[0] = 1;

	for (int i = 2; i <= n; ++i){

		int64 K = 1LL * (i - 1) * modpow(c, mod - 2) % mod;

		for (int j = i; j; --j){
			a[j] = (a[j - 1] * (i - 1)) / c;
			A[j] = A[j - 1] * K % mod;
		}

		a[0] = 0;
		A[0] = 0;

		double p = -(1. - (i - 1.) / c);
		int64 P = m( -(1 - K) );

		double det = 1. - pow(-p, i / __gcd(i,k) );
		int64 DET = m( 1LL - modpow(m(-P), i / __gcd(i,k)) );

		for (int j = 0; j < i; ++j){
			go[j] = ((j - k) % i + i) % i;
		}

		if (k % i == 0){

			int64 K2 = modpow( m(1LL + P), mod - 2 );

			for (int j = 0; j < i; ++j){
				b[j] = a[j] / (1. + p);
				B[j] = A[j] * K2 % mod;
			}

		}
		else{
			for (int j = 0; j < i; ++j){
				int pos = j;

				double x = 1. / det;
				int64 X = modpow(DET, mod - 2);

				do{
					b[j] += x * a[ pos ];
					B[j] += X * A[pos] % mod;
					B[j] = m(B[j]);

					x *= -p;
					X = X * m(-P) % mod;

					pos = go[ pos ];

				}while(pos != j);
			}
		}

		for (int j = 0; j < i; ++j){
			a[j] = b[j];
			A[j] = B[j];

			b[j] = 0;
			B[j] = 0;
		}

		// for (int j = 0; j < i; ++j)
		// 	cout << a[j] << " ";
		// cout << endl;
	}

    double best = 0;
    int64 hash = 0;
    int answer = -1;

    for (int x = 0; x < n; ++x){
        if (a[x] > best){
            best = a[x];
            answer = x;
            hash = A[x];
        }
    }

    cout << answer << " " << hash << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t --> 0){
    	int n, c, k;
    	cin >> n >> c >> k;
    	solve(n, c, k);
    }


    return 0;
}
