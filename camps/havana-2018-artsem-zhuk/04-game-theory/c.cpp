#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
const int mod = 1e9 + 7;

typedef vector<int> vi;

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

void add_vec(vi &a, vi b){
    for (int i = 0; i < (int)a.size(); ++i)
        add(a[i], b[i]);
}

const int TSTATE = 8 * 8 * 8 * 8 * 8 * 8;
const int BASE = 7;

int position[1 << 6][7][7][7][7][7][7];
int final_grundy[TSTATE];
int go[TSTATE][2];

int _grundy(int mask, vector<int> &B, vector<int> &valid){
	int seen = 0;

	for (auto x : valid){
		if (mask >> (x - 1) & 1)
			seen |= 1 << B[x - 1];
	}

	int g = 0;
	while (seen >> g & 1)
		g++;
	return g;
}

vector<vi> solve(int size, vector<int> &valid){
	int cindex = 0;

	for (int i = 0; i < (1 << 6); ++i){
		int bits = __builtin_popcount(i);
		int total = 1;

		for (int j = 0; j < bits; ++j)
			total *= BASE;

		for (int j = 0; j < total; ++j){

			int u = j;
			vector<int> b7(6);

			for (int b = 0; b < 6; ++b){
				if (i >> b & 1){
					b7[b] = u % BASE;
					u /= BASE;
				}
			}

			position[i][b7[0]][b7[1]][b7[2]][b7[3]][b7[4]][b7[5]] = cindex;
			final_grundy[cindex] = i & 1 ? b7[0] : -1;
			cindex++;
		}
	}

	for (int i = 0; i < (1 << 6); ++i){
		int bits = __builtin_popcount(i);
		int total = 1;

		for (int j = 0; j < bits; ++j)
			total *= BASE;

		for (int j = 0; j < total; ++j){

			int u = j;
			vector<int> b7(6);

			for (int b = 0; b < 6; ++b){
				if (i >> b & 1){
					b7[b] = u % BASE;
					u /= BASE;
				}
			}

			int pos = position[i][b7[0]][b7[1]][b7[2]][b7[3]][b7[4]][b7[5]];

			go[pos][0] = position[(i << 1) & 63][0][b7[0]][b7[1]][b7[2]][b7[3]][b7[4]];

			int gr = _grundy(i, b7, valid);

			go[pos][1] = position[((i << 1) & 63) | 1][gr][b7[0]][b7[1]][b7[2]][b7[3]][b7[4]];
		}
	}

	vector<vi> W(size + 1, vi(8));
	vector<int> prev(cindex);

	prev[0] = 1;

    for (int i = 1; i <= size; ++i)
    {
    	vector<int> cur(cindex);

    	for (int j = 0; j < cindex; ++j){
    		add(cur[go[j][0]], prev[j]);
    		add(cur[go[j][1]], prev[j]);
    		assert(final_grundy[ go[j][1] ] != -1);
    	}

        for (int j = 0; j < cindex; ++j)
        	if (final_grundy[j] != -1)
        		add(W[i][final_grundy[j]], cur[j]);

        cur.swap(prev);
    }

//    for (auto row : W){
//    	for (auto x : row)
//    		cout << x << " ";
//    	cout << endl;
//    }

    return W;
}

vi multiply(vi a, vi b){
    vi c(8);

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            add(c[i ^ j], 1LL * a[i] * b[j] % mod);

    return c;
}

vi modpow(vi a, i64 n){
    vi ans(8);
    ans[0] = 1;

    while (n){
        if (n & 1)
            ans = multiply(ans, a);
        a = multiply(a, a);
        n >>= 1;
    }

    return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'


	int MX = 0;

	int n; cin >> n;

	vector<pair<i64,int>> games(n);

	for (int i = 0; i < n; ++i){
		cin >> games[i].first >> games[i].second;
		MX = max(MX, games[i].second);
	}

	int t; cin >> t;
	vector<int> moves;

	for (int i = 0; i < t; ++i){
		int v; cin >> v;
		moves.push_back(v);
	}

	auto vec = solve(MX, moves);

	vi sol(8); sol[0] = 1;

	for (int i = 0; i < n; ++i){
		vi cur = vec[ games[i].second ];

		cur = modpow(cur, games[i].first);
		sol = multiply(sol, cur);
	}

	int answer = 0;

	for (int i = 1; i < 8; ++i)
		add(answer, sol[i]);

	cout << answer << endl;
}
