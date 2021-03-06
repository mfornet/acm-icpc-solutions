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

I a[MAX],t[4*MAX], n;

I build(I id = 1, I st = 1, I ed = n)
{
	if(st==ed)return t[id] = a[st];
	I piv = (st+ed)>>1;
	return t[id] = __gcd(build(id<<1,st,piv),build(id<<1|1,piv+1,ed));
}

//~ PII upd (I p, I v, I id = 1, I st = 1, I ed = 2e5)
//~ {
	//~ if(p>ed||p<st)return t[id];
	//~ if(st==ed)return t[id] = {v,v};
	//~ I piv = (st+ed)>>1;
	//~ return t[id] = upd(p,v,id<<1,st,piv) + upd(p,v,id<<1|1,piv+1,ed);
//~ }

I qry(I qx, I qy, I id = 1, I st = 1, I ed = n)
{
	if(qx>ed||qy<st)return 0;
	if(qx<=st&&ed<=qy)return t[id];
	I piv = (st+ed)>>1;
	return __gcd(qry(qx,qy,id<<1,st,piv),qry(qx,qy,id<<1|1,piv+1,ed));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	ifor(i,1,n)cin>>a[i];
	build();
	I k;cin>>k;
	ifor(i,1,k)
	{
		I x,y;cin>>x>>y;
		cout << qry(x,y) << endl;
		
	}
    
  return 0;
}
