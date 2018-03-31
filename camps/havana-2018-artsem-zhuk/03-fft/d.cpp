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

void solve(string &a, string &b){
    int n = a.length(), m = b.length();
    vector<point> A(n), B(m);

    for (int i = 0; i < n; ++i)
        A[i] = point(a[n - i - 1] - '0');

    for (int i = 0; i < m; ++i)
        B[i] = point(b[m - i - 1] - '0');

    int x = max(n, m);
    int s = 1;
    while (s <= x) s *= 2; s *= 2;

    A.resize(s); 
    B.resize(s);

    fft(A, +1);
    fft(B, +1);

    for (int i = 0; i < s; ++i)
        A[i] = A[i] * B[i];
    fft(A, -1);

    int rem = 0;

    vector<int> answer;

    for (int i = 0; i < s; ++i){
        int cur = int(A[i].x + .5) + rem;
        rem = cur / 10;
        answer.push_back(cur % 10);
    }

    while (answer.back() == 0)
        answer.pop_back();

    assert(!answer.empty());

    for (int i = (int)answer.size() - 1; i >= 0; --i)
        cout << answer[i];
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    int sign = 1;

    if (a[0] == '-')
    {
        sign *= -1;
        a = a.substr(1);
    }

    if (b[0] == '-'){
        sign *= -1;
        b = b.substr(1);
    }

    if (a.length() == 1 && a == "0"){
        cout << 0 << endl;
        return 0;
    }

    if (b.length() == 1 && b == "0"){
        cout << 0 << endl;
        return 0;
    }

    if (sign == -1){
        cout << "-";
    }

    solve(a, b);

    return 0;
}