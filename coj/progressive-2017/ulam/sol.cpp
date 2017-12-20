#include <bits/stdc++.h>

using namespace std;

// 132788

const int limit = 132788 + 1;
int freq[ limit ];
int ulam[ limit ];
int tCount = 0;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	freq[ 1 ] = freq[ 2 ] = 1;

	for (int i = 1; tCount < 10000 ; ++i){
		if (freq[i] == 1){
			for (int j = 0; j < tCount; ++j){
				int value = i + ulam[j];
				if (value >= limit) continue;
				freq[ value ]++;
			}
			ulam[ tCount++ ] = i;
		}
	}

	int t; cin >> t;

	while (t--){
		int v; cin >> v;
		cout << ulam[v - 1] << '\n';
	}

	return 0;
}
