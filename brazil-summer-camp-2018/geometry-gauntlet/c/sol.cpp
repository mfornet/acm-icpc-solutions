#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int maxn = 100000 + 10;

#define double long double

typedef complex<int64> point;

int64 cross(point a, point b) { return imag(conj(a) * b); }
int64 dot(point a, point b) { return real(conj(a) * b); }
int64 area2(point a, point b, point c) { return cross(b - a, c - a); }

namespace std
{
    bool operator<(const point &a, const point &b)
    {
        return real(a) < real(b) || (real(a) == real(b) && imag(a) < imag(b));
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
    vector<point> P(n);

    map<pii,int> idx;

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        P[i] = point(x, y);
        if (idx.find(pii(x, y)) == idx.end())
            idx[pii(x,y)] = i + 1;
    }

    auto ch = convex_hull(P);

    cout << ch.size() << endl;

    double per = 0.;
    int64 ar = 0;

    int kk = ch.size();
    for (int i = 0; i < kk; ++i){
        cout << idx[pii(ch[i].real(), ch[i].imag())] << " ";

        auto t = ch[i] - ch[(i+1)%kk];
        per += sqrt(t.real() * t.real() + t.imag() * t.imag());
        ar += cross(ch[i], ch[(i+1)%kk]);
    }

    cout << endl;

    cout.precision(25);
    cout << fixed << per << endl;
    cout << abs(ar) / 2 << (abs(ar) & 1 ? ".5" : ".0") << endl;

    return 0;
}
