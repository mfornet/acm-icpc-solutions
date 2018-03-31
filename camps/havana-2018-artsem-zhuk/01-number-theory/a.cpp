#include <bits/stdc++.h>
const int MAX = 5e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b, p) ((i64)(a) * (b) % (p))
#define sum(a, b, p) ((((a) + (b)) % (p) + p) % p)

const int oo = (1 << 30) - 1 + (1 << 30);


struct triple{
	int d, x, y;
};
triple egcd( int a, int b ) {
    if( !b ) return (triple){ a, 1, 0  };
    triple q = egcd( b, a % b );
    return (triple) {q.d, q.y, q.x - a / b * q.y };
}

i64 mulmod(i64 a, i64 b, i64 p){
	i64 s = 0;
	while(b > 0){
		if(b & 1)s = (s + a) % p;
		a = (a + a) % p;
		b >>= 1;
	}
	return s;
}
bool CRT(i64 a1, i64 b1, i64& a2, i64& b2){
	i64 gcd = __gcd(b1, b2);
	if(abs(a1 - a2)%gcd != 0)return false;
	i64 lcm = b1 / gcd * b2;
	triple T = egcd(b1, b2);
	i64 factor = ((a1 - a2) / gcd + lcm ) % lcm;
	i64 temp =  mulmod( mulmod((-T.x + lcm) % lcm, b1, lcm), factor, lcm) + a1;
	a2 = (temp + lcm )%lcm; b2 = lcm;
	return true;
}

int main() {
    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'
    i64 a, b, n, m; cin >> a >> b >> n >>m;

    assert(CRT(a, n, b, m));
    cout << b << endl;

}
