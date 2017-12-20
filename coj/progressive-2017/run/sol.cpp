#include <bits/stdc++.h>

using namespace std;

bool seen[ 1000000 + 1 ];
int value[ 100000 ];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		int n; cin >> n;
		int answer = 0;

		for (int i = 0, j = 0; i < n; ++i){
			cin >> value[i];
			while (seen[ value[i] ])
				seen[ value[j++] ] = false;
			seen[ value[i] ] = true;
			answer = max( answer, i - j + 1 );
		}

		cout << answer << '\n';
		
	}

	return 0;
}
