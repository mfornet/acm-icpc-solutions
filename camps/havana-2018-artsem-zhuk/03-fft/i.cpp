#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct point{
    long double x, y;
    point(long double x=0, long double y=0) : x(x), y(y) {}
};

typedef vector<point> pol;

point operator+(const point &a, const point &b){
    return {a.x + b.x, a.y + b.y};
}

point operator-(const point &a, const point &b){
    return {a.x - b.x, a.y - b.y};
}

point operator*(const point &a, const point &b){
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}

point operator/(const point &a, long double d){
    return {a.x / d, a.y / d};
}

void fft(vector<point> &a, int sign = +1){
    int n = a.size();

    for (int i = 1, j = 0; i < n - 1; ++i){
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);
        if (i < j) swap(a[i], a[j]);
    }

    long double theta = atan2l(0, -1) * 2 * sign;

    for (int m, mh = 1; (m = mh << 1) <= n; mh = m){
        point wm(cos(theta / m), sin(theta / m)), w(1, 0);

        for (int i = 0; i < n; i += m, w = point(1, 0)){
            for (int j = i, k = j + mh; j < i + mh; ++j, ++k, w = w * wm){
                point x = a[j], y = a[k] * w;
                a[j] = x + y;
                a[k] = x - y;
            }
        }
    }

    if (sign == -1)
        for (point &p : a) p = p / n;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int h, w, n = 0;
    cin >> h >> w;

    int ew = 2 * w - 1;

    vector<point> vec(h * ew);

    for (int i = 0; i < h; ++i){
        string s;
        cin >> s;

        for (int j = 0; j < w; ++j){
            if (s[j] == '1'){
                vec[i * ew + j] = point(1);
                n++;
            }
        }
    }

    vector<point> rec = vec;
    reverse(rec.begin(), rec.end());

    int size = h * ew;
    int s = 1;

    while (s <= size)
        s *= 2;
    s *= 2;

    vec.resize(s);
    rec.resize(s);

    fft(vec, +1);
    fft(rec, +1);

    for (int i = 0; i < s; ++i)
        vec[i] = vec[i] * rec[i];

    fft(vec, -1);

    double answer = 0.;

    for (int i = 0; i < h; ++i)
        for (int j = i ? -w + 1 : 1; j < w; ++j){
            int idx = i * ew + j;
            idx = h * ew - idx - 1;

            int t = int(vec[idx].x + .5);
            double freq(t);

            double x = sqrt(i * i + j * j);
            answer += x * freq;
        }

    double prob = 6. / n / (n - 1);

    cout.precision(17);
    cout << fixed << prob * answer << endl;

    return 0;
}