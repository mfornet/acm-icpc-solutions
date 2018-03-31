#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int gcd(int a, int b){
    while (b){
        a %= b;
        swap(a, b);
    }
    return a;
}

int modpow(int a, int n, int m){
    int b = 1;

    while (n){
        if (n & 1)
            b = 1LL * b * a % m;
        a = 1LL * a * a % m;
        n >>= 1;
    }

    return b;
}

vector<int> solve(int p, int a, int b){
    vector<int> answer;

    if (b == 0){
        answer = vi(min(p, 10));
        iota(answer.begin(), answer.end(), 0);
        return answer;
    }

    if (a == 0){
        answer = vi(min(p, 10));
        iota(answer.begin(), answer.end(), 0);
        return answer;
    }

    if (p == 2){
        return answer;
    }

    int g = gcd(p - 1, a);
    int t = (p - 1) / g;

    set<int> seen;

    for (int it = 0; seen.size() < min(10, g - 1); ++it){
        int z = rand() % (p - 2) + 2;
        int y = modpow(z, t, p);
        if (y == 1) continue;
        int x = 1LL * b * modpow(y - 1, p - 2, p) % p;
        seen.insert(x);
    }

    answer = vi(seen.begin(), seen.end());

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--){
        int p, a, b;

        cin >> p >> a >> b;

        auto answer = solve(p, a, b);

        sort(answer.begin(), answer.end());

        int s = answer.size();

        cout << s << endl;
        for (int i = 0; i < s; ++i)
            cout << answer[i] << " \n"[i + 1 == s];
        if (s == 0) cout << endl;
    }

    return 0;
}