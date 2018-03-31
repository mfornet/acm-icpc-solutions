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


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n, m;

	cin >> n >> m;

	vector< vector<int> > V(n, vector<int>(m));

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> V[i][j];

	int answer = 0;
	int best = 0;

	for (int i = 0; i < m; ++i){
		int a = 1000000, b = 1000000;

		for (int j = 0; j < n; ++j){
			int v = V[j][i];

			if (v < a) swap(v, a);
			if (v < b) swap(v, b);
		}

		answer += a;
		best = max(best, min(2 * a, b) - a);
	}

	cout << answer + best << endl;

	return 0;
}
