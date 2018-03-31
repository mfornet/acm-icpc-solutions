#include <bits/stdc++.h>
const int MAX = 5e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b, p) ((i64)(a) * (b) % (p))
#define sum(a, b, p) ((((a) + (b)) % (p) + p) % p)

const int oo = (1 << 30) - 1 + (1 << 30);
int powmod(int x, int n, int mod){
	int z = 1;
	while(n > 0){
		if(n&1)z = ((i64)z*x)%mod;
		x = ((i64)x*x)%mod;
		n>>=1;
	}
	return z;
}
int gcd(int a, int b){
    while(b!=0)a%=b, swap(a, b);
    return a;
}
int n, p;
int nsols = 0;
int ssols = 0;

void solve(int a11, int p){
	int g = (p - 1) / a11 + p;
	i64 a1 = (i64)a11 * g;
	i64 a2 = g;

	nsols ++;
	if(n == 0) ssols = (ssols + p - 1) % MOD;
	else if(n == 1) ssols = (ssols + a1) % MOD;
	else if(n == 2) ssols = (ssols + a2) % MOD;
	else ssols = (ssols + mul(a2 % MOD, powmod(p, n - 2, MOD), MOD)) % MOD;


	g = (p - 1) / a11 + 1;
	a1 = (i64)a11 * g;
	a2 = (i64)p * g;

	nsols ++;
	if(n == 0) ssols = (ssols + p - 1) % MOD;
	else if(n == 1) ssols = (ssols + a1) % MOD;
	else if(n == 2) ssols = (ssols + a2) % MOD;
	else ssols = (ssols + mul(a2 % MOD, powmod(p, n - 2, MOD), MOD)) % MOD;

}
int main() {
    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'

     cin >> p >> n;


    int q = p - 1;
    for(int a1 = 1; a1 <= q; a1++){
    	if(a1 * a1 > q)break;
    	if(q % a1 == 0){
    		solve(a1, p);
    		if(a1 * a1 != q)solve(q / a1, p);
    	}
    }
    cout << nsols << " " << ssols << endl;
}
