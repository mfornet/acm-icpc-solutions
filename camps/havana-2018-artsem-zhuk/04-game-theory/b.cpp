#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int x1, x2, a, b;
	cin >> x1 >> x2 >> a >> b;

	if(a <= 0 and 0 <= b){
		if(x1 + a <= x2 and x2 <= x1 + b){
			cout << "FIRST" << endl;
			cout << x2 << endl;
			return 0;
		}
		else{
			cout << "DRAW" << endl;
			return 0;
		}
	}

	bool sign = false;
	if(a < 0){
		sign = true;
		a *= -1;
		b *= -1;
		swap(a, b);
		x1 *= -1;
		x2 *= -1;
	}

	if(x1 > x2){
		cout << "DRAW" << endl;
	}
	else{
		int e = x2 - x1;
		if(e % (b + a) == 0)cout << "SECOND" << endl;
		else{
			int r = e % (b + a);
			if(r < a)cout << "DRAW" << endl;
			else if(r <= b){
				cout << "FIRST" << endl;
				if(!sign)cout << (i64)x1 + r << endl;
				else cout << - (i64) x1 - r << endl;
			}
			else cout << "DRAW" << endl;
		}
	}


}
