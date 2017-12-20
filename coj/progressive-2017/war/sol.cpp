#include <bits/stdc++.h>

using namespace std;

const double pi = acos( -1 );
const double g = 9.8;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	double x0, y0, x1, y1, v;

	while (cin >> x0 >> y0 >> x1 >> y1 >> v){
		x0 -= x1;
		y0 -= y1;

		double d = sqrt( x0 * x0 + y0 * y0 );

		double x = g * d / v / v;

		if (x < -1 || x > 1){
			cout << "Impossible" << endl;
			continue;
		}

		double theta = asin( x );

		theta = theta * 180 / pi / 2;

		cout.precision(2);
		cout << fixed << theta << '\n';
	}

	return 0;
}
