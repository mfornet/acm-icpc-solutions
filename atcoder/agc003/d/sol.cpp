#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int64 mul(int64 a, int64 b, int64 M)
{ int64 q = (long double) a * (long double) b / (long double) M;
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

vector<int64> factorize(int64 a){
    vector<int64> fak;
    queue<int64> q;
    q.push(a);

    while (!q.empty()){
        int64 u = q.front(); q.pop();
        if (u == 1) continue;

        if (miller_rabin(u))
            fak.push_back(u);
        else{
            int64 d = pollard_rho(u);
            q.push(d);
            q.push(u / d);
        }
    }
    return fak;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n; cin >> n;
    map<vector<int64>,int> track;
    bool empty = false;

    for (int i = 0; i < n; ++i){
        int64 v; cin >> v;
        auto fak = factorize(v);
        map<int64,int> freq;
        for (auto f : fak)
            freq[f]++;
        vector<int64> id;
        for (auto f : freq){
            int t = f.second % 3;
            if (t == 0) continue;
            id.push_back(f.first);
            id.push_back(t);
        }
        if (id.empty()){
            empty=true;
            continue;
        }
        track[id]++;
    }

    int answer = empty;
    for (auto t : track){
        vector<int64> rival = t.first;
        for (int i = 1; i < (int)rival.size(); i += 2)
            rival[i] = 3 - rival[i];
        int value = track.count(rival) ? track[rival] : 0;
        if (t.second > value || (t.second == value && t.first < rival))
            answer += t.second;
    }
    cout << answer << endl;
    return 0;
}
