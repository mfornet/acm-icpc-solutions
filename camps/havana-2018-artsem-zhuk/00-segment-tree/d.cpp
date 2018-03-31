#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b) ((i64)(a) * b % MOD)


int ar[MAX];


struct segment_tree{
	struct node{
		int b, e;
		i64 d0;
		int d1;
	};
	vector<node> f;
	segment_tree(int nar){
		int _size=33-__builtin_clz(nar);
		f.resize(1<<_size);
		init(1, 0, nar-1);
	}
	void init(int nnode, int b, int e){
		f[nnode].d0 = f[nnode].d1 =0;
		f[nnode].b=b; f[nnode].e=e;
		if(b==e)return;
		init(2*nnode, b, (b+e)/2);
		init(2*nnode+1, (b+e)/2 + 1, e);
	}
	i64 query0(int nnode, int i, int j){
	    if(i>f[nnode].e || j<f[nnode].b)return 0;
	    if(f[nnode].b>=i && f[nnode].e<=j)return f[nnode].d0;
	    i64 p1=query0(2*nnode, i, j);
	    i64 p2=query0(2*nnode+1, i, j);
	    return (p1 +  p2);
	}
	void update0(int nnode, int i, int d){
	    if(i>f[nnode].e || i<f[nnode].b)return;
	    if(f[nnode].b>=i && f[nnode].e<=i){
	    	f[nnode].d0 += d;
	        return;
	    }
	    update0(2*nnode, i, d);
	    update0(2*nnode+1, i, d);
	    f[nnode].d0 = f[2 * nnode].d0 + f[2 * nnode + 1].d0;
	}
	int query1(int nnode, int i, int j){
		    if(i>f[nnode].e || j<f[nnode].b)return 0;
		    if(f[nnode].b>=i && f[nnode].e<=j)return f[nnode].d1;
		    int p1=query1(2*nnode, i, j);
		    int p2=query1(2*nnode+1, i, j);
		    return p1 + p2;
		}
		void update1(int nnode, int i, int d){
		    if(i>f[nnode].e || i<f[nnode].b)return;
		    if(f[nnode].b>=i && f[nnode].e<=i){
		    	f[nnode].d1 += d;
		        return;
		    }
		    update1(2*nnode, i, d);
		    update1(2*nnode+1, i, d);
		    f[nnode].d1=(f[2*nnode].d1 + f[2*nnode+1].d1);
		}
};


int main() {

    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'
    int n; cin >>n ;
    for(int i =0; i < n; i++){
    	cin >> ar[i]; ar[i]--;
    }
    segment_tree S(n);
    i64 ans = 0;
    for(int i = 0; i < n; i++){
    	i64 a = S.query0(1, ar[i], n - 1);
    	int am = S.query1(1, ar[i], n - 1);
    	S.update0(1, ar[i], am);
    	S.update1(1, ar[i], 1);
    	ans += a;
    }
    cout << ans << endl;






}
