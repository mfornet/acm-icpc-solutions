#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef pair<int,int> pii;

const int maxn = 100000 + 10;

vector<int> primes;
int P[maxn];

void sieve(){
	primes.push_back(2);

	for (int i = 3; i < maxn; i += 2){
		if (P[i]) continue;
		primes.push_back(i);

		if (1LL * i * i >= maxn) continue;

		for (int j = i * i; j < maxn; j += 2 * i)
			P[j] = i;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	sieve();

	int t; cin >> t;
//	int t = 40000;

	while (t-->0){
		int x; cin >> x;

//		int x = 100000000;

		int64 NUM = x;
		int64 ANS = 0;

		for (int i = 0; i < (int)primes.size(); ++i){
			int p = primes[i];

			if (p * p > x) break;

			if (x % p == 0){
				int n = 0;

				while (x % p == 0){
					n++;
					x /= p;
				}

				ANS += NUM * n / p;
			}
		}

		if (x > 1)
			ANS += NUM / x;

		cout << ANS << endl;
	}

	return 0;
}
