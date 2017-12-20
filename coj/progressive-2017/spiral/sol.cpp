#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--){
		long long x;
		cin >> x;
		x--;

		long long lo = -1, hi = 100000000;

		while (lo + 1 < hi){
			long long m = (lo + hi) / 2;
			long long v = 4 * (m + 1) * (m + 1);
			if (v >= x)
				hi = m;
			else
				lo = m;
		}

		x -= 4 * hi * hi; 
		
		int a = 2LL * hi, b = -hi;

		if (x <= 4 * hi + 1){
			a -= x;
		}
		else{
			a -= 4 * hi + 1;
			x -= 4 * hi + 1;

			if (x <= 2 * hi + 1){
				a += x;
				b += x;
			}
			else{
				a += 2 * hi + 1;
				b += 2 * hi + 1;
				x -= 2 * hi + 1;
				a += x;
				b -= x;
			}
		}

		cout << a << " " << b << '\n';
	}

	return 0;
}
