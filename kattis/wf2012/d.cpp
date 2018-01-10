#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout<<#x<<"="<<x<<endl;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = 317812;
const int SZ = 27; // 27

int64 fib[110];

int64 getFib(int n){
    assert(n < 92);
    return n < 0 ? 1 - (n + 2) : fib[n];
}

map< pair<int,string>, int64> UM;

int64 solve(int n, string s){
    if (n < 0 || (n <= 30 && fib[n] < s.length())) return 0;
    if (s.length() == 1){
        if (s[0] == '0') return getFib(n - 2);
        else return getFib(n - 1);
    }
    if (UM.count(MP(n, s))) return UM[MP(n,s)];
    int64 &val = UM[MP(n,s)];

    if (n == 2){
        if (s == "10") return val = 1;
        return val = 0;
    }

    string adv = "";
    int st = 0;
    for (int i = 0; i < (int)s.length(); ++i){
        st = ((st << 1) | (s[i] - '0')) & 3;
        if (st == 0 || st == 2) adv += "1";
        else if (st == 3) adv += "0";
        if (i && !st) return val = 0;
    }

    if (st & 1)
        val = solve(n - 1, adv + "1") + solve(n - 1, adv + "0");
    else
        val = solve(n - 1, adv);

    return val;

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fib[0] = fib[1] = 1;
    for (int i = 2; i < 110; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];

    int n, tc = 1;
    while (cin >> n)
    {
        string s;
        cin >> s;
        cout << "Case " << tc++ << ": " << solve(n, s) << endl;
    }

    return 0;
}