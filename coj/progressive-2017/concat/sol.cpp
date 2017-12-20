#include <bits/stdc++.h>

using namespace std;

string tostr(long long a){
	string ans = "";
	while (a){
		ans += (char)('0' + a % 10);
		a /= 10;
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<long long> fib = {1, 1};
	for (int i = 2; i < 92; ++i){
		long long a = fib[i - 1] + fib[i - 2];
		fib.push_back(a);
	}

	set<string> S;
	vector<string> fibstr( fib.size() );
	for (int i = 0; i < 92; ++i)
		fibstr[i] = tostr( fib[i] );

	for (int i = 0; i < 92; ++i)
		for (int j = 0; j < 92; ++j)
			if (i != j) S.insert( fibstr[i] + fibstr[j] );

	vector<string> fibcon( S.begin(), S.end() );

	string s;

	while (cin >> s){
		vector<int> pos( fibcon.size() );
		vector<vector<int>> W(10);

		for (int i = 0; i < (int)fibcon.size(); ++i)
			W[ fibcon[i][0] - '0' ].push_back(i);

		int answer = 0;

		for (int i = 0; i < (int)s.length(); ++i){
			char c = s[i];
			if (c < '0' || c > '9')
				continue;
			int v = c - '0';

			vector<int> cur = W[v];
			W[v].clear();

			for (auto idx : cur){
				pos[ idx ]++;
				if (pos[idx] == (int)fibcon[idx].size())
					answer++;
				else
					W[ fibcon[idx][ pos[idx] ] - '0' ].push_back(idx);
			}
		}

		cout << answer << '\n';
	}

	return 0;
}
