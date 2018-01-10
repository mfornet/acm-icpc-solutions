#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;      // Amount of lanes
    ld w,   // Width of each lane
    u, v,       // Ships and ferry velocity
    t1, t2;     // Available start time

    cin >> n >> w >> u >> v >> t1 >> t2;

    vector<pair<ld,ld>> ships;

    for (int i = 0; i < n; ++i){
        char dir; cin >> dir;
        int tot; cin >> tot;

        for (int j = 0; j < tot; ++j){
            ld l, p; cin >> l >> p;

            if (dir == 'E') p *= -1;

            ld s = p / u - w * (i + 1) / v;
            ld e = p / u - w * i / v + l / u;

            ships.push_back(MP(s, e));
        }
    }

    sort(ships.begin(), ships.end());

    ld enter = t1, ans = 0;

    for (auto sh : ships){
        if (sh.first > t2) break;
        ans = max(ans, sh.first - enter);
        enter = max(enter, sh.second);
    }

    ans = max(ans, t2 - enter);

    cout.precision(9);
    cout << fixed << ans << endl;

    return 0;
}

