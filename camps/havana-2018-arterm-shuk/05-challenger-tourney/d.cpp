#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef complex<double> point;

const int maxn = 100000;

void fail(){
	cout << "Epic fail" << endl;
	exit(0);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	int n; cin >> n;

	map<int, vector<int> > D;

	int mdist = 0;

	int mindist = n;
	int mincount = 0;

	for (int i = 1; i <= n; ++i){
		int d; cin >> d;

		D[d].push_back(i);
		mdist = max(mdist, d);

		if (d < mindist){
			mindist = d;
			mincount = 0;
		}

		if (d == mindist)
			mincount++;
	}

	if (2 * mindist < mdist) fail();
	if (mdist & 1){
		if (mincount > 2) fail();
	}
	else
		if (mincount > 1) fail();

	vector<int> skeleton;

	for (int i = 0; i <= mdist; ++i){
		int t = max(i, mdist - i);

		if (D[t].empty()) fail();

		int u = D[t].back();
		D[t].pop_back();

		skeleton.push_back(u);
	}

	cout << "I got it" << endl;

	for (int i = 0; i + 1 < (int)skeleton.size(); ++i)
		cout << skeleton[i] << " " << skeleton[i + 1] << endl;

	for (map<int,vector<int> >::iterator it = D.begin(); it != D.end(); ++it){
		int d = it->first;

		for (int i = 0; i < (int)it->second.size(); ++i){
			int u = it->second[i];

			cout << u << " " << skeleton[mdist - d + 1] << endl;
		}
	}

	return 0;
}
