#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

typedef complex<int64> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 200000 + 10;

int64 cross(point a, point b){
    return imag(conj(a) * b);
}

int64 dist(point a){
    return real(a) * real(a) + imag(a) * imag(a);
}

int64 s[4 * maxn];

vector<int> manacher(int l)
{
    int n = 2 * l;
    vector<int> rad(n);

    for (int i = 0, j = 0, k; i < n; i += k, j = max(j - k, 0))
    {
        for (; i >= j && i + j + 1 < n
            && s[(i - j) / 2] == s[(i + j + 1) / 2]; ++j);
        rad[i] = j;
        for (k = 1; i >= k &&
            rad[i] >= k && rad[i - k] != rad[i] - k; ++k)
            rad[i + k] = min(rad[i - k], rad[i] - k);
    }

    return rad;
}

bool is_pal(const vector<int> &rad, int b, int e)
{
    int n = rad.size() / 2;
    return b >= 0 && e < n && rad[b + e] >= e - b + 1;
}

int go(){
    int n; cin >> n;

    vector<point> P(n);

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        P[i] = point(x, y);
    }

    point p0 = P[0], p1 = P[1];
    P.push_back(p0);
    P.push_back(p1);

    vector<int64> half;

    for (int i = 0; i < n; ++i){
        half.push_back(dist(P[i] - P[i+1]));
        half.push_back(cross(P[i] - P[i+1], P[i+2] - P[i+1]));
    }

    int t = 0, m = 2 * n;

    for (int j = 0; j < 2; ++j)
        for (int i = 0; i < m; ++i)
            s[t++] = half[i];

    auto rad = manacher(2 * m);

    int answer = 0;

    for (int i = 0; i < m; ++i)
        answer += is_pal(rad, i, i + m - 2);

    assert(~answer & 1);

    return answer / 2;
}

void solve(){
    int n; cin >> n;
    int m = 0, t = 0;

    for (int i = 0; i < n; ++i){
        int v = go();

        cout << v << endl;

        if (v > m)
            m = v, t = 0;

        if (v == m)
            t++;
    }

    cout << m << " " << t << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t-->0)
        solve();

    return 0;
}