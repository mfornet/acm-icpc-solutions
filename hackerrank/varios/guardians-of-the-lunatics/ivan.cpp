#include <iostream>
using namespace std;

typedef long long Long;
const int MAXN = 9000;
const int MAXM = 900;
Long INF = 1ll<<60;
Long memo[MAXM][MAXN];
Long pre[MAXN];

int L, G;

Long costo( int i, int pos ){
	return (pre[i] - pre[pos-1])*( i - pos + 1 );
}

Long dp( int rest, int pos ){
	if (pos == L + 1) return 0;
	if (rest == 0) return INF;

	if( memo[rest][pos] != -1ll ) return memo[rest][pos];
	Long res = INF;
	for( int i = pos; i <= L; i++ ){
		res = min(res, dp(rest-1, i+1) + costo( i, pos ) );
	}
	return memo[rest][pos] = res;
}

int main(){

	for( int i = 0; i < MAXM; i++ )
		for( int j = 0; j < MAXN; j++ )
			memo[i][j] = -1ll;

	cin >> L >> G;
	for( int i = 1; i <= L; i++ ){
		cin >> pre[i];
		pre[i] += pre[i-1];
	}

	cout << dp( G, 1 ) << '\n';
	return 0;
}