#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef pair<int,int> pii;

const int maxn = 100000 + 10;

vector<int> primes;
int P[maxn];

void sieve(){
	for (int i = 2; i < maxn; ++i){
		if (P[i]) continue;
		primes.push_back(i);
		for (int j = 2 * i; j < maxn; j += i)
			P[j] = i;
	}
}

int read(char c){
	if ('0' <= c && c <= '9')
		return c - '0';
	return 10 + (int)(c - 'A');
}

void convert(int64 x){
//	cout << "CONVERT: " << x << " ";
	if (x < 10) cout << x;
	else cout << (char)('A' + x - 10);
//	cout << endl;
}

void tofak(int64 v){
	if (v == 0){
		cout << 0 << endl;
		return;
	}

	if (v < 0){
		cout << "-" << endl;
		v *= -1;
	}

	int64 fak = 1;
	int idx = 1;

	while (fak <= v)
		fak *= ++idx;

	while (idx > 1){
		fak /= idx--;
		convert(v / fak);
		v %= fak;
	}

	cout << endl; //cout.flush();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	string s; cin >> s;

	int64 answer = 0;

	for (int i = 0, j; i < (int)s.length(); i = j){
		for (j = i + 1; j < (int)s.length() && s[j] != '+' && s[j] != '-'; ++j);

		int64 sign = 1;

		if (s[i] == '-'){
			sign = -1;
			i++;
		}

		if (s[i] == '+') i++;

		int64 fak = 1;
		int64 num = 0;
		int idx = 1;

		for (int k = j - 1; k >= i; --k){
			fak *= idx++;
			num += fak * read(s[k]);
		}

		num *= sign;

		answer += num;
	}

	tofak(answer);

	return 0;
}
