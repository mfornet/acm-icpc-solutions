#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		int n, k;
		cin >> n >> k;

		vector<int> period(n);
		vector<string> name(n);

		priority_queue<pair<int,int>> pq;

		for (int i = 0; i < n; ++i){
			cin >> name[i] >> period[i];
			pq.push( {-period[i], -i} );
		}

		for (int i = 0; i < k; ++i){
			auto cur = pq.top(); pq.pop();
			cout << -cur.first << " " << name[ -cur.second ] << '\n';
			pq.push( {cur.first - period[ -cur.second ], cur.second} );
		}
	}

	return 0;
}
