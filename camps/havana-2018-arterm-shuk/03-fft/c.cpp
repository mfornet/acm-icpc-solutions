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

int modpow(int a, int n, int mod){
    int b = 1;
    while (n){
        if (n & 1)
            b = 1LL * b * a % mod;
        n >>= 1;
        a = 1LL * a * a % mod;
    }
    return b;
}

pol square(pol A){
    fft(A, +1);
    for (auto &x : A)
        x = x * x;
    fft(A, -1);
    return A;
}

int64 brute(int n, int m){
    int64 total = 0;

    for (int i = 1; i < m; ++i)
        for (int j = i; j < m; ++j){
            for (int k = 1; k < m; ++k){
                if ((modpow(i, n, m) + modpow(j, n, m)) % m == modpow(k, n, m)){
                    total++;
                }
            }
        }

    return total;
}

int64 solution(int n, int m){
    pol P(m);

    for (int i = 1; i < m; ++i){
        int b = modpow(i, n, m);
        P[b] = P[b] + point(1);
    }

    int size = 1;
    while (size <= m) 
        size *= 2; 
    size *= 2;
    P.resize(size);

    pol Q = square(P);

    for (int i = m; i < (int)Q.size(); ++i)
        Q[i % m] = Q[i % m] + Q[i];
    
    int64 answer = 0;

    for (int i = 0; i < m; ++i){
        int64 p = int64(P[i].x + .5), q = int64(Q[i].x + .5), r = 0;

        if ((i & 1) == 0){
            r += int64(P[i / 2].x + .5);
        }

        if (((m + i) & 1) == 0){
            r += int64(P[(m + i) / 2].x + .5);
        }

        answer += p * (q + r) / 2;
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    cout << solution(n, m) << endl;

    return 0;
}