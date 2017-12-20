#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	const int limit = 50000000;
	map<int,int> answer;

	for (int i = 1; ; ++i){
		int v = (i + 1) * (i + 2) / 2;
		if (v > limit) break;
		answer[ v ] = i;
	}

	int t; cin >> t;

	while (t--){
		int v; cin >> v;

		if (answer.find(v) != answer.end())
			cout << answer[v] << endl;
		else
			cout << "No solution" << endl;
	}
	

	return 0;
}
