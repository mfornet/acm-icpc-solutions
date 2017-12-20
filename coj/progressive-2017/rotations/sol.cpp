#include <bits/stdc++.h>

using namespace std;

bool freq[ 32 ];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	const long long mask = 31;

	while (t--){
		long long a;
		cin >> a;
		a |= a << 32;

		bool ok = true;
		memset( freq, 0, sizeof freq );

		for (int i = 0; i < 32 && ok; ++i){
			int value = a >> i & mask;
			if (freq[ value ])
				ok = false;
			else
				freq[ value ] = true;
		}

		cout << (ok ? "yes" : "no" ) << '\n';
	}

	return 0;
}
