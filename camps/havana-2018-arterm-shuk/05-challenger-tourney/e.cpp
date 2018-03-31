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
	for (int i = 2; i < maxn; ++i){
		if (P[i]) continue;
		primes.push_back(i);
		for (int j = 2 * i; j < maxn; j += i)
			P[j] = i;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n; cin >> n;

	int A = 0, B = 0;

	for (int i = 0; i < n; ++i){
		int x; cin >> x;

		A += max(2 * x - 1, 0);
		B += 2 * x + 1;
	}

	cout << (A <= 200 && 200 < B ? "Yes" : "No") << endl;

	return 0;
}
