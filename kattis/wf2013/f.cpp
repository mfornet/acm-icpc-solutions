#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout<<#x<<"="<<x<<endl;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

bool check(int n, int k, int d, vi &V){
    int cur = 0;
    for (int i = 0; i + 1 < SZ(V) && cur < n; ++i){
        if (i > 2 * cur * k) return false;
        if (V[i + 1] - V[i] <= d) ++cur, ++i;
    }
    return cur == n;
}

int solve(int n, int k, vi &V){
    sort(V.begin(), V.end());

    int lo = -1, hi = V[2 * n * k - 1] - V[0];

    while (lo + 1 < hi){
        int mid = (lo + hi) >> 1;
        if (check(n, k, mid, V)) hi = mid;
        else lo = mid;
    }

    return hi;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> V(2 * n * k);
    for (int i = 0; i < 2 * n * k; ++i)
        cin >> V[i];

    int ans = solve(n, k, V);
    cout << ans << endl;

    return 0;
}

