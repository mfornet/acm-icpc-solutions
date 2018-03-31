#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;

int conway(int a, int b){
	if(a > b)return -conway(b, a);
	int aa = a, pa;
	while(aa > 0){
		pa = aa;
		aa &= aa - 1;
	}
	//cout << a << " " << b << " " << pa << endl;
	b -= pa;

	return - (b / pa);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'




	int test; cin >> test;
	while(test--){
		int n; cin >> n;
		i64 val = 0;

		for(int i = 0; i <n; i++){
			int a, b; cin >> a >> b;
			val += conway(b, a);
		}
		if(val > 0)cout << "Alice" << endl;
		else cout << "Bob" << endl;
	}

}
