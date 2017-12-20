#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#define inf 0x3f3f3f3f
#define ull unsigned long long
#define lson root<<1
#define rson root<<1|1
#define Mid int mid=(l+r)>>1;
#define FREI freopen("in.txt","r",stdin)
#define FREO freopen("out.txt","w",stdout)
#define Mem(a,b) memset(a,b,sizeof(a))
#define ll long long
#define eps 1e-5
#define PB push_back
#define PI acos(-1)
#define zuoyi(n) (1<<(n))
#define Ceil(x,y) ((x+y-1)/y)
using namespace std;
const int MAXN=1e5+10;
const ll mod=1e9+7;
int n,m;
int a[3],b[3];
char s[10];
int main() {
#ifdef ONLINE_JUDGE
#else
    FREI;
#endif // ONINLE_JUDGE
    scanf("%s",s);
    int sum1,sum2;
    sum1=sum2=0;
    for(int i=0;i<3;i++) a[i]=s[i]-48,sum1+=a[i];
    for(int j=3;j<6;j++) b[j-3]=s[j]-48,sum2+=b[j-3];
    if(sum1==sum2) {
        puts("0");
        return 0;
    }
    sort(a,a+3);
    sort(b,b+3);
    if(sum1>sum2){
        if(sum1-sum2<=9-b[0]||sum1-sum2<=a[2]) puts("1");
        else if(sum1-sum2<=9-b[0]+9-b[1]||sum1-sum2<=a[1]+a[2]||sum1-sum2<=9-b[0]+a[2]) puts("2");
        else puts("3");
    }
    if(sum2>sum1){
        if(sum2-sum1<=9-a[0]||sum2-sum1<=b[2]) puts("1");
        else if(sum2-sum1<=9-a[0]+9-a[1]||sum2-sum1<=b[1]+b[2]||sum2-sum1<=9-a[0]+b[2]) puts("2");
        else puts("3");
    }
}