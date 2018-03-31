#include <bits/stdc++.h>

using namespace std;

typedef int I;
typedef double D;
typedef long long int LL;
typedef long long int int64;
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

const I MAX = 1e4+7, P = 2007;

I f[MAX],g[MAX];

I fpow(I b, I p)
{
	LL r = 1ll;
	while(p)
	{
		if(p&1)r*=b,r%=P;
		b = 1ll*b*b%P;
		p>>=1;
	}
	return r;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    I n;cin>>n;
    ifor(i,1,n)cin>>f[i];
    g[1] = fpow(f[1],P-2);
    ifor(i,1,n)for(I j = i+i; j<=n; j+=i)
    {
		g[j]-=1ll*(1ll*g[1]*g[i]%P)*f[j/i]%P;
		if(g[j]<0)g[j]+=P;
	}
	ifor(i,1,n)cout << g[i] << " \n"[i==n];

  return 0;
}

