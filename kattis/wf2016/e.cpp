#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int64 mul(int64 a, int64 b, int64 M)
{
    // a %= M;
    // int64 ans = 0;
    // while (b){
    //     if (b & 1) ans = (ans + a) % M;
    //     b /= 2;
    //     a = (a + a) % M;
    // }

    // return ans;

    int64 q = (long double) a * (long double) b / (long double) M;
    int64 r = a * b - q * M;
    return (r + 5 * M) % M;
}

int64 pow(int64 a, int64 b, int64 M)
{
    int64 x = 1;
    for (; b > 0; b >>= 1)
    {
        if (b & 1) x = mul(x, a, M);
        a = mul(a, a, M);
    }
    return x;
}

bool witness(int64 a, int64 s, int64 d, int64 n)
{
    int64 x = pow(a, d, n);
    if (x == 1 || x == n - 1)
        return 0;
    for (int i = 0; i < s - 1; i++)
    {
        x = mul(x, x, n);
        if (x == 1)
            return 1;
        if (x == n - 1)
            return 0;
    }
    return 1;
}

bool miller_rabin(int64 n)
{
    if (n < 2)
        return 0;
    if (n == 2)
        return 1;
    if (n % 2 == 0)
        return 0;
    int64 d = n - 1, s = 0;
    while (d % 2 == 0)
        ++s, d /= 2;
    vector<int64> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int64 p : test)
        if (p >= n) break;
        else if (witness(p, s, d, n))
            return 0;
    return 1;
}


int64 pollard_rho(int64 n)
{
    if (!(n & 1))
        return 2;
    while (1)
    {
        int64 x = (int64) rand() % n, y = x;
        int64 c = rand() % n;
        if (c == 0 || c == 2) c = 1;
        for (int i = 1, k = 2;; i++)
        {
            x = mul(x, x, n);
            if (x >= c) x -= c;
            else x += n - c;
            if (x == n) x = 0;
            if (x == 0) x = n - 1;
            else x--;
            int64 d = __gcd(x > y ? x - y : y - x, n);
            if (d == n)
                break;
            if (d != 1) return d;
            if (i == k)
            {
                y = x;
                k <<= 1;
            }
        }
    }
    return 0;
}

int64 sol = 10;

void rev(int64 y, int64 b, int64 l){
    // cout << "CHECK: " << b << endl;
    if (b <= sol) return;

    int64 ans = 0;
    int64 p = 1;
    while (y){
        if (y % b >= 10) return;
        ans += p * (y % b);
        y /= b;
        p *= 10;
    }

    if (ans >= l) sol = max(sol, b);
}

void bt(vector<pii> &f, int p, int64 y, int64 l, int64 s){
    if (p == (int)f.size()) rev(y, s, l);
    else{
        for (int i = 0; i <= f[p].second; ++i){
            bt(f, p + 1, y, l, s);
            s *= f[p].first;
        }
    }
}

map<int64,int64> freq;
vector<pii> primes;

void facorize(int64 a){
    if (!miller_rabin(a)){
        int64 d = pollard_rho(a);
        facorize(d);
        facorize(a / d);
    }
    else{
        freq[a]++;
    }
}

void check(int64 y, int64 a, int64 l){
    freq.clear();
    for (int64 i = 2, b = a; i * i * i <= b && a > 1; ++i)
        if (a % i == 0)
        {
            do
            {
                freq[i]++;
                a/=i;
            }while (a % i == 0);
        }
    if (miller_rabin(a)) freq[a]++;
    else if (a != 1) {
        int64 p = pollard_rho(a);
        freq[p]++;
        freq[a/p]++;
    }
    primes = vector<pii>(freq.begin(), freq.end());

    bt(primes, 0, y, l, 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 y, l;
    cin >> y >> l;

    for (int i = 0; i < 10; ++i)
        check(y, y - i, l);

    cout << sol << endl;

    return 0;
}