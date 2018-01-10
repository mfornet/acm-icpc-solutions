#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    double w, h;
    int n;
    cin >> w >> h >> n;

    double r = h / w;
    double k = 2. / (1 - r * r);

    double a0 = 0., a1 = 1;
    double cost = 0;

    for (int i = 1; i <= n; ++i){
        a0 = k * a1 - a0;
        swap(a0, a1);
        cost += a0 * a0 + (r * r - 1) * a0 * a1;
    }

    double x = h / a1 / r;
    cost *= x * x / 2;
    cost += (r + 1) * (r + 1) * w * w / 4;

    cout.precision(9);
    cout << fixed << cost << endl;

    a0 = 0., a1 = 1.;

    for (int i = 0; i < min(n, 10); ++i){
        cout << fixed << a1 * x << endl;
        a0 = k * a1 - a0;
        swap(a0, a1);
    }

    return 0;
} 