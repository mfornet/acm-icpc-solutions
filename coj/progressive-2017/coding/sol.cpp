#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		long long a, b;
		int i;

		cin >> a >> b >> i;

		if ( (b << i) < a )
			cout << (a | (b << i) ) << '\n';
		else if ( (1 << i) <= a )
			cout << (b << i) << '\n';
		else
			cout << (a | (b << i) ) << '\n';
	}

	return 0;
}
