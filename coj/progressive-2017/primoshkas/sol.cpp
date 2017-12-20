#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n;

	auto solve = [](vector<long long> &X){
		sort(X.begin(), X.end());
		long long answer = 0, median = X[ (int)X.size() / 2 ];
		for (int i = 0; i < (int)X.size(); ++i)
			answer += abs(X[i] - median);
		return answer;
	};

	while (cin >> n){
		vector<long long> X(n), Y(n);

		for (int i = 0; i < n; ++i)
			cin >> X[i] >> Y[i];

		cout << solve(X) + solve(Y) << '\n';
	}

	return 0;
}
