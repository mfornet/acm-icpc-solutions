#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b) ((i64)(a) * b % MOD)


string s;


struct segment_tree{
	struct tern{
		int open, closed, good;
		tern(){open = closed = good = 0;}
	};
	struct node{
		int b, e;
		tern t;
	};
	vector<node> f;
	segment_tree(int nar){
		int _size=33-__builtin_clz(nar);
		f.resize(1<<_size);
		init(1, 0, nar-1);
	}
	tern stuff(tern left, tern right){
		tern nn = tern();
		int ngood = min(left.open, right.closed);
		nn.good = left.good + right.good + ngood;
		nn.open = left.open - ngood + right.open;
		nn.closed = right.closed - ngood + left.closed;
		return nn;
	}
	void init(int nnode, int b, int e){
		f[nnode].b=b; f[nnode].e=e;
		if(b==e){
			if(s[b] == '(')
				f[nnode].t.open = 1;
			else
				f[nnode].t.closed = 1;
			return;
		}
		init(2*nnode, b, (b+e)/2);
		init(2*nnode+1, (b+e)/2 + 1, e);

		f[nnode].t = stuff(f[2 * nnode].t, f[2 * nnode + 1].t);

	}
	tern query(int nnode, int i, int j){
	    if(i>f[nnode].e || j<f[nnode].b)return tern();
	    if(f[nnode].b>=i && f[nnode].e<=j){
	    	return f[nnode].t;
	    }
	    tern p1=query(2*nnode, i, j);
	    tern p2=query(2*nnode+1, i, j);
	    return stuff(p1, p2);
	}

};


int main() {

    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'
    cin >> s;
    segment_tree S(s.size());
     int m ; cin >> m;
     while(m--){
    	 int x, y; cin >> x >> y;x--; y--;
    	 int ans = S.query(1, x, y).good;
    	 cout << 2 * ans << endl;
     }






}
