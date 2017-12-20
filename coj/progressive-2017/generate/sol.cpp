#include <bits/stdc++.h>

using namespace std;

int mul[ 1010 ][ 1010 ];

void add(int &a, int b, int m){
	a += b;
	if (a >= m)
		a -= m;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int a, c, m, x, q, n;

	while (cin >> a >> c >> m >> x >> q >> n){
		vector<int> freq( m );

		for (int i = 1; i < m; ++i)
			for (int j = 1; j < m; ++j){
				mul[i][j] = j;
				add( mul[i][j], mul[i - 1][j], m );
			}

		for (int i = 1; i <= n; ++i){
			freq[x]++;
			x = mul[x][a];
			add(x, c, m);
		}

		for (int i = 1; i < m; ++i)
			freq[i] += freq[i - 1];

		while (q--){
			int v; cin >> v;
			int p = lower_bound( freq.begin(), freq.end(), v ) - freq.begin();
			cout << p << '\n';
		}
	}

	return 0;
}
