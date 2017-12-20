#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000;

const int mod = 1000000009;
const int64 d = 1000000000 + 1000000;

struct segment_tree{
	struct node{
		int64 b, e, value;
		node *l, *r;

		node(int64 b, int64 e) : b(b), e(e), value(0), l(0), r(0) {}
	};

	node *root;

	segment_tree(){
		root = new node(-d, d);
	}

	void push(node *u){
		int64 m = (u->b + u->e) >> 1;

		if (!u->l)
			u->l = new node(u->b, m);
		if (!u->r)
			u->r = new node(m, u->e);

		u->l->value += u->value;
		u->r->value += u->value;
		u->value = 0;
	}

	void update(node *u, int64 x, int64 y, int64 v){
		int64 b = u->b, e = u->e;

		if (x <= b && e <= y){
			u->value += v;
		}
		else{
			push(u);
			int64 m = (b + e) >> 1;

			if (x < m)
				update(u->l, x, y, v);
			if (m < y)
				update(u->r, x, y, v);
		}
	}

	int64 query(node *u, int64 x){
		int64 b = u->b, e = u->e;

		if (b + 1 == e)
			return u->value;

		push(u);
		int64 m = (b + e) >> 1;

		if (x < m)
			return query(u->l, x);
		else
			return query(u->r, x);
	}

    int64 query(int64 x){
        return query(root, x);
    }

    void update(int64 x, int64 y, int64 v){
        update(root, x, y, v);
    }

} st;

void solve2(int n){
	st = segment_tree();

    int64 answer = 0, step = 1;

	while (n-->0){
		int64 p, v;
		cin >> p >> v;

        int64 value = st.query(p);

        // right side
        int64 size = 1;
        while ( st.query(p + size) + v * size == value )
            size *= 2;
        int64 lo = p, hi = p + size;
        while (lo + 1 < hi){
            int64 mid = (lo + hi) >> 1;

            if ( st.query(mid) + v * (mid - p) == value )
                lo = mid;
            else
                hi = mid;
        }

        int64 B = lo;

        //left side
        size = 1;
        while ( st.query(p - size) + v * size == value )
            size *= 2;
        lo = p - size, hi = p;
        while (lo + 1 < hi){
            int64 mid = (lo + hi) >> 1;

            if ( st.query(mid) + v * (p - mid) == value)
                hi = mid;
            else
                lo = mid;
        }

        int64 A = hi;
        st.update(A, B + 1, v);

        int64 cur = B - A + 1;
        answer = (answer + step++ * cur % mod) % mod;
	}

    cout << answer << endl;
}

void solve(int n){
	int h[6 * maxn];
	memset(h, 0, sizeof h);
	int c = 3 * maxn;

	int fin = 0;
	int cur = 1;

	while (n-->0){
		int p, v;
		cin >> p >> v;
		p += c;

		int answer = 1;
		h[p] += v;

		for (int i = p + 1; h[i] + 2 * v == h[i - 1]; ++i){
			h[i] += v;
			answer++;
		}

		for (int i = p - 1; h[i] + 2 * v == h[i + 1]; --i){
			h[i] += v;
			answer++;
		}

		fin = (fin + 1LL * cur++ * answer % mod) % mod;
	}

	cout << fin << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    int n;

    while (t-->0){
    	cin >> n;
    	solve2(n);
    }

    return 0;
}
