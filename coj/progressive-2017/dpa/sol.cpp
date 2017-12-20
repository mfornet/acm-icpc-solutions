#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	const int limit = 1001;

	vector<int> sum(limit);

	for (int i = 1; i < limit; ++i)
		for (int j = i + i; j < limit; j += i)
			sum[j] += i;

	int t; cin >> t;

	while (t--){
		int v; cin >> v;
		cout << (sum[v] > v ? "abundant" : sum[v] < v ? "deficient" : "perfect") << '\n';
	}

	return 0;
}
