#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int maxv = 3e4+10;
int arr[maxn];
int prevv[maxv];
int act[maxv];
int post[maxv];
int piece = 30;
long long sol = 0;
int get (int it, int aux [maxv]){
    return it >= 0 && it< maxv ? aux[it]:0;
}
int get (int it, vector<int> & aux){
    return it > 0 && it < 2*maxv ? aux[it]:0;
}
#define PI 2*acos(0)
// typedef complex<double> base;

struct base
{
    double x, y;
    base(double x = 0, double y = 0) : x(x), y(y) {}
};

base operator+(const base &a, const base &b) { return {a.x + b.x, a.y + b.y}; }
base operator-(const base &a, const base &b) { return {a.x - b.x, a.y - b.y}; }
base operator*(const base &a, const base &b) {
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

base operator/(const base &a, double d) { return {a.x / d, a.y / d}; }

void fft (vector<base> & a, bool invert) {
    int n = (int) a.size();
    for (int i=1, j=0; i<n; ++i) {
        int bit = n >> 1;
        for (; j>=bit; bit>>=1)
            j -= bit;
        j += bit;
        if (i < j) swap (a[i], a[j]);
    }
    for (int len=2; len<=n; len<<=1) {
        double ang = 2*PI/len * (invert ? -1 : 1);
        base wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            base w (1);
            for (int j=0; j<len/2; ++j) {
                base u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w = w * wlen;
    }   }   }
    if (invert){
        for (int i=0; i<n; ++i)
            a[i] = a[i] / n;}
}
void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {
vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);
    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] = fa[i] * fb[i];
    fft (fa, true);
    res.resize (n);
    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].x + 0.5);
}
void solve(int b, int e){
   for(int i = b; i < e; i++){
        act [arr[i]] ++;
        post [arr[i]] --;
    }
    vector<int>aa,bb,cc;
    aa.resize(maxv), bb.resize(maxv), cc.resize(maxv);
    for(int i=0; i<maxv; i++){
            aa[i]=prevv[i];
            bb[i]=post[i];
    }
    multiply(aa,bb,cc);
    for(int i =b; i<e;i++){
        sol+=get(2*arr[i],cc);
        act[arr[i]]--;
        for(int j = b; j<i ; j++){
            sol+= get(2*arr[i]-arr[j],act);
            sol+= get (2*arr[i]-arr[j],post);
            sol+= get(2*arr[j]-arr[i],prevv);
        }
    }
    for(int i =b; i<e; i++){
        prevv[arr[i]]++;
        act[arr[i]] = 0;
    }
}
int main(){
    #ifdef Au
        freopen("data.in", "r",stdin);
        freopen("data.out","w",stdout);
    #endif // Au
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int n,m;
    cin>>n;
    for(int i =0; i<n; i++){
        cin>>m;
        arr[i]=m;
        post[m]++;
    }
    piece = 1 + n/piece;
    for(int i = 0; i<n; i+=piece){
        solve(i, min(i+piece,n));
    }
    cout<<sol<<endl;
    return 0;
}
