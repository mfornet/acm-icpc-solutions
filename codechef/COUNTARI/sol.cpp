#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int maxv = 65536;

int TBLOCK = 30;
int value[ maxn ];

int64 prevv[ maxv ];
int64 post[ maxv ];
int64 freq[ maxv ];
int64 temp[ maxv ];

int64 get(int p, int64 f[maxv]){
    return p < 0 || p >= maxv ? 0 : f[p];
}

struct point
{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
};

point operator+(const point &a, const point &b) { return {a.x + b.x, a.y + b.y}; }
point operator-(const point &a, const point &b) { return {a.x - b.x, a.y - b.y}; }
point operator*(const point &a, const point &b) {
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}
point operator/(const point &a, double d) { return {a.x / d, a.y / d}; }

void fft(point a[maxv], int sign = +1)
{
    int n = maxv;

    for (int i = 1, j = 0; i < n - 1; ++i)
    {
        for (int k = n >> 1; (j ^= k) < k; k >>= 1);

        if (i < j) swap(a[i], a[j]);
    }

    double theta = 2 * atan2(0, -1) * sign;

    for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
    {
        point wm(cos(theta / m), sin(theta / m)), w(1, 0);

        for (int i = 0; i < n; i += m, w = point(1, 0))
            for (int j = i, k = j + mh; j < i + mh; ++j, ++k, w = w * wm)
            {
                point x = a[j], y = a[k] * w;
                a[j] = x + y;
                a[k] = x - y;
            }
    }

    if (sign == -1){
        for (int i = 0; i < n; ++i)
            a[i] = a[i] / n;
    }
}

point polA[maxv], polC[maxv];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // freopen("test.in", "r", stdin);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        post[ value[i] ]++;
    }

    int K = (n + TBLOCK - 1) / TBLOCK;
    int64 answer = 0;

    for (int b = 0; b < n; b += K){
        int e = min(b + K, n);

        for (int i = b; i < e; ++i){
            freq[ value[i] ]++;
            post[ value[i] ]--;
        }

        for (int X = b; X < e; ++X){
            freq[ value[X] ]--;
            for (int Y = b; Y < X; ++Y){
                int vx = value[X], vy = value[Y];
                answer += get( 2 * vx - vy, freq);
                answer += get( 2 * vx - vy, post );
                answer += get( 2 * vy - vx, prevv );
            }
        }

        for (int i = 0; i < maxv; ++i)
            polA[i] = point(prevv[i]), polC[i] = point(post[i]);

        fft(polA);
        fft(polC);

        for (int i = 0; i < maxv; ++i)
            polA[i] = polA[i] * polC[i];

        fft(polA, -1);

        for (int i = 0; i < maxv; ++i)
            temp[i] = int64(round(polA[i].x));

        for (int i = b; i < e; ++i)
            answer += get(2 * value[i], temp);

        for (int i = b; i < e; ++i)
            prevv[ value[i] ]++;
    }

    cout << answer << endl;

    return 0;
}