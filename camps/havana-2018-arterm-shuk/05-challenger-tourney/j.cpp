#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
const int MOD = 1e9 + 7;
typedef long long i64;
typedef long long int64;
using namespace std;
#define mul(a, b) (((i64)(a) * (b) ) % MOD)
#define sum(a, b) (((a) + (b) ) % MOD)

typedef pair<int,int> pii;

struct segmet_tree{
	struct node{
		vector<int> freq;

		node(){
			freq = vector<int>(26);
		}

		node(int x){
			freq = vector<int>(26);
			freq[x]++;
		}

		node operator+(const node &A) const{
			node answer;

			int b = 25;
			while (b >= 0 && A.freq[b] == 0) b--;

			for (int i = 25; i >= max(0, b) ;--i)
				answer.freq[i] += freq[i];

			for (int i = b; i >= 0; --i)
				answer.freq[i] += A.freq[i];

			return answer;
		}
	};

	vector<node> data;

	segmet_tree(string s){
		int n = (int)s.length();
		data = vector<node>(4 * n);
		build(1, 0, n, s);
	}

	void build(int p, int b, int e, string &s){
		if (b + 1 == e)
			data[p] = node(s[b] - 'a');
		else{
			int m = (b + e) >> 1, l = p << 1, r = l | 1;

			build(l, b, m, s);
			build(r, m, e, s);

			data[p] = data[l] + data[r];
		}
	}

	void update(int p, int b, int e, int x, int c){
		if (b + 1 == e){
			data[p] = node(c);
		}
		else{
			int m = (b + e) >> 1, l = p << 1, r = l | 1;

			if (x < m) 	update(l, b, m, x, c);
			else		update(r, m, e, x, c);

			data[p] = data[l] + data[r];
		}
	}

	node query(int p, int b, int e, int x, int y){
		if (x <= b && e <= y) return data[p];

		int m = (b + e) >> 1, l = p << 1, r = l | 1;

		node answer;

		if (x < m) answer = answer + query(l, b, m, x, y);
		if (m < y) answer = answer + query(r, m, e, x, y);

		return answer;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	#define endl '\n'

	#ifdef QUANTUM
		freopen("data.in", "r", stdin );
	#endif

	string s; cin >> s;

	int n = (int)s.length();

	segmet_tree st(s);

	int t; cin >> t;

	while (t-->0){
		int comm; cin >> comm;

		if (comm == 1){
			int x, y, k;
			cin >> x >> y >> k;

			vector<int> answer = st.query(1, 0, n, x - 1, y).freq;

			char ans = '-';

			for (int i = 25; i >= 0; --i){
				if (answer[i] >= k){
					ans = (char)('a' + i);
					break;
				}
				else
					k -= answer[i];
			}

			cout << ans << endl;
		}
		else{
			int pos; char value;
			cin >> pos >> value;
			st.update(1, 0, n, pos - 1, value - 'a');
		}
	}

	return 0;
}
