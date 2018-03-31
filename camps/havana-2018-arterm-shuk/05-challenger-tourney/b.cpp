#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

const int maxn = 51;

int a, b, n;
double p;

bool updated[maxn][maxn][maxn][maxn];
double dp[maxn][maxn][maxn][maxn];
double e[maxn];

struct state{
	int clicked, remain, seen, day;
};

vector<double> solve(int remain){
	memset(updated, 0, sizeof updated);
	memset(dp, 0, sizeof dp);

	dp[0][remain][n - remain][0] = 1.;

	queue<state> q;
	q.push((state){0, remain, n - remain, 0});

	vector<double> T(remain + 1);

	double np = 1. / (b - a + 1);

	while (!q.empty()){
		state cur = q.front(); q.pop();
		int c = cur.clicked, r = cur.remain, s = cur.seen, d = cur.day;

		if (updated[c][r][s][d])
			continue;

		//cout << "q: " << c << " " << r << " " << s << " " << d <<endl;

		updated[c][r][s][d] = true;

		if (d >= a)
			T[r] += np * dp[c][r][s][d];

		if (d == b)
			continue;

		if (r + s == 0){
			dp[c][r][s][d + 1] += dp[c][r][s][d];
			q.push((state){c, r, s, d + 1});
		}
		else{
			double cp = dp[c][r][s][d];

			if (r){
				dp[c + 1][r - 1][s][d + 1] += cp * r / (r + s) * p;
				dp[c][r - 1][s + 1][d + 1] += cp * r / (r + s) * (1. - p);
				q.push((state){c + 1, r - 1, s, d + 1});
				q.push((state){c, r - 1, s + 1, d + 1});
			}

			if (s){
				dp[c + 1][r][s - 1][d + 1] += cp * s / (r + s) * p;
				dp[c][r][s][d + 1] += cp * s / (r + s) * (1. - p);

				q.push((state){c + 1, r, s - 1, d + 1});
				q.push((state){c, r, s, d + 1});
			}
		}
	}

	//cout << "Transition" << endl;
	//for (int i = 0; i < (int)T.size(); ++i)
	//	cout << T[i] << " "; cout << endl;

	return T;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	cin >> n >> a >> b >> p;

	for (int i = 1; i <= n; ++i){
		vector<double> T = solve(i);

		e[i] = 1.;

		for (int j = 0; j < i; ++j)
			e[i] += e[j] * T[j];

		e[i] /= 1. - T[i];

		//cout << i << " " << e[i] << endl;
	}

	cout.precision(17);
	cout << fixed << e[n] << endl;

	return 0;
}
