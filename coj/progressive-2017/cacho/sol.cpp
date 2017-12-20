#include <bits/stdc++.h>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;

	while (t--)
	{
		bool ok = true;
		int prev = -1;

		for (int i = 1; i <= 5; ++i)
		{
			int v; cin >> v;
			if (prev != -1 && v != prev + 1)
				ok = false;
			prev = v;
		}

		cout << "NY"[ok] << endl;
	}

	return 0;
}
