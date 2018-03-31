#include <bits/stdc++.h>

using namespace std;

typedef int I;
typedef double D;
typedef long long int LL;
typedef long double LD;
typedef complex<D> CPX;
typedef pair<I,I> PII;
typedef pair<LL,LL> PLL;
typedef pair<D,LL> PDLL;
typedef pair<D,I> PDI;
typedef vector<I> VI;
typedef vector<LL> VLL;
typedef vector<D> VD;
typedef vector<LD> VLD;
typedef vector<CPX> VCPX;
typedef vector<PII> VPII;
typedef vector<PLL> VPLL;
typedef vector<PDLL> VPDLL;
typedef vector<PDI> VPDI;
typedef pair<VI,VI> PVI;
typedef set<I> SI;
typedef set<LL> SLL;
typedef set<D> SD;
typedef set<LD> SLD;
typedef set<CPX> SCPX;
typedef set<PII> SPII;
typedef set<PLL> SPLL;
typedef set<PDLL> SPDLL;
typedef set<PDI> SPDI;

#define endl '\n'
#define fr first
#define sc second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define ins insert
#define ers erase
#define lb lower_bound
#define ub upper_bound
#define fd find
#define all(x) (x).begin(),(x).end()
#define srt(x) sort(all(x))
#define srtn(x,N) sort((x),(x)+(N))
#define lsrt(x,L) sort(all(x),(L))
#define lsrtn(x,N,L) sort((x),(x)+(N),(L))
#define sz(v) ((int)(v).size())
#define ifor(i,st,ed) for(int i=(st);i<=(ed);++i)
#define dfor(i,st,ed) for(int i=(st);i>=(ed);--i)
#define efor(it,x) for(auto it:(x))
#define cout(x) cout<<fixed<<setprecision(x)
#define pln1(a) cout<<(a)<<endl
#define pln2(a,b) cout<<(a)<<' '<<(b)<<endl
#define pln3(a,b,c) cout<<(a)<<' '<<(b)<<' '<<(c)<<endl
#define pln4(a,b,c,d) cout<<(a)<<' '<<(b)<<' '<<(c)<<' '<<(d)<<endl
#define ppln1(p,a) cout(p)<<(a)<<endl
#define ppln2(p,a,b) cout(p)<<(a)<<' '<<(b)<<endl
#define ppln3(p,a,b,c) cout(p)<<(a)<<' '<<(b)<<' '<<(c)<<endl
#define ppln4(p,a,b,c,d) cout(p)<<(a)<<' '<<(b)<<' '<<(c)<<' '<<(d)<<endl
#define debug(x) cerr<<#x<<" = "<<x<<endl

const I MAX = 2e5+7;

I a[MAX], n;
I t[4*MAX];

//~ void dw(I id, I st, I ed)
//~ {
	//~ if(lz[id])
	//~ {
		//~ t[id]+=lz[id];
		//~ if(st!=ed)
		//~ {
			//~ lz[id<<1] +=lz[id];
			//~ lz[id<<1|1] +=lz[id];
		//~ }
		//~ lz[id] = 0;
	//~ }
//~ }

I build(I id = 1, I st = 1, I ed = n)
{
	if(st==ed)return t[id] = a[st];
	I piv = (st+ed)>>1;
	return t[id] = max(build(id<<1,st,piv),build(id<<1|1,piv+1,ed));
}

I upd (I p, I v, I id = 1, I st = 1, I ed = n)
{
	if(p>ed||p<st)return t[id];
	if(st==ed)return t[id] = v;
	I piv = (st+ed)>>1;
	return t[id] = max(upd(p,v,id<<1,st,piv),upd(p,v,id<<1|1,piv+1,ed));
}

I search(I x, I id, I st, I ed)
{
	if(t[id]<x)return 1e9;
	if(st==ed)return st;
	if(t[id<<1]>=x)return search(x,id<<1,st,(st+ed)>>1);
	else return search(x,id<<1|1,(st+ed)/2 + 1, ed);
}

I qry(I qx, I qy, I x, I id = 1, I st = 1, I ed = n)
{
	if(qx>ed||qy<st)return 1e9;
	if(qx<=st&&ed<=qy)return search(x,id,st,ed);
	I piv = (st+ed)>>1;
	return min(qry(qx,qy,x,id<<1,st,piv),qry(qx,qy,x,id<<1|1,piv+1,ed));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	I m;cin>>n>>m;
	ifor(i,1,n)cin>>a[i];
	build();
	ifor(i,1,m)
	{
		I q;cin>>q;
		if(q==1){
			I x,y;cin>>x>>y;
			cout << (qry(x,n,y)==1e9 ? -1 : qry(x,n,y) ) << endl;
		}
		else
		{
			I p, v;cin>>p>>v;
			upd(p,v);
		}
	}
    
  return 0;
}
