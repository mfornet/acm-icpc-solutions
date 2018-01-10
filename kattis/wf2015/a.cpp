#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

double p, a, b, c, d;
int n;

double price(double x){
    return p * (sin(a * x + b) + cos(c * x + d));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> p >> a >> b >> c >> d >> n;

    double ans = 0, m = price(1);

    for (int i = 2; i <= n; ++i){
        double cur = price(i);
        ans = max(ans, m - cur);
        m = max(m, cur);
    }

    cout.precision(9);
    cout << fixed << ans << endl;

    return 0;
}

