#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef complex<int64> point;

int64 cross(point a, point b) { return imag(conj(a) * b); }

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;

    cin >> n >> m >> k;

    vector<point> P(n);

    int u = 0;

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        P[i] = point(x, y);

        if (P[i].imag() < P[u].imag() || (P[i].imag() == P[u].imag() && P[i].real() < P[u].real()))
            u = i;
    }

    rotate(P.begin(), P.begin() + u, P.end());

    while (m-->0){
        int64 x, y;
        cin >> x >> y;

        point p(x, y);

        if (p.imag() < P[0].imag() || cross(P[n-1] - P[0], p - P[0]) > 0){
            continue;
        }

        int lo = 1, hi = P.size() - 1;

        while (lo + 1 < hi){
            int m = (lo + hi) >> 1;

            if (cross(P[m] - P[0], p - P[0]) >= 0)
                lo = m;
            else
                hi = m;
        }

        if (cross(P[lo+1] - P[lo], p - P[lo]) >= 0){
            k--;
        }
    }

    cout << (k <= 0 ? "YES" : "NO") << endl;

    return 0;
}

/*
5 4 2
1 -1
1 2
0 4
-1 2
-1 -1
-2 -1
1 -1
0 1
2 3
*/