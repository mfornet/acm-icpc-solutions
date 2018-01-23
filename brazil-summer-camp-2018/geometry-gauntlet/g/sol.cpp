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

int64 dot(point a, point b) { return real(conj(a) * b); }
int64 cross(point a, point b) { return imag(conj(a) * b); }
int64 area2(point a, point b, point c) { return cross(b - a, c - a); }

namespace std
{
    bool operator<(point a, point b)
    {
        if (a.real() != b.real())
            return a.real() < b.real();
        return a.imag() < b.imag();
    }
}


vector<point> convex_hull(vector<point> &P)
{
    int n = P.size(), k = 0;
    vector<point> h(2 * n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; h[k++] = P[i++])
        while (k >= 2 && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
    for (int i = n - 2, t = k + 1; i >= 0; h[k++] = P[i--])
        while (k >= t && area2(h[k - 2], h[k - 1], P[i]) <= 0) --k;
    return vector<point>(h.begin(), h.begin() + k - (k > 1));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<point> V(n);

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        V[i] = point(x, y);
    }

    auto ch = convex_hull(V);

    int t = ch.size();

    for (int i = 0; i < t; ++i)
        ch.push_back(ch[i]);

    int64 best = 0;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            auto e = [&](int x){
                return cross(ch[x] - ch[i], ch[j] - ch[i]);
            };

            if (e(0) < e(1)){
                
            }
        }
    }

    cout << best / 2 << (best & 1 ? ".5" : ".0") << endl;

    return 0;
}
