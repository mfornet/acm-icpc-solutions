#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000000007;

void add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

vector<int> pw2;

int solve11(string &s){
    int answer = 0;
    if (s[0] != '0' && s.back() != '0'){
        answer = 1;
        for (int i = 1; i + 1 < s.length(); ++i)
            if (s[i] == '?') add(answer, answer);
    }
    return answer;
}

int solve10(string s){
    if (s[0] == '0' || s.back() == '1') return 0;
    s[0] = '1';
    s.back() = '0';

    int total = 0;
    for (auto c : s) total += c == '?';

    int t = 1, a = 0;

    for (int i = 0; i < (int)s.length(); i += 2){
        char x = s[i], y = s[i + 1];
        if (x == '?') total--;
        if (y == '?') total--;

        if (x != '0' && y != '0')
            add(a, 1LL * t * pw2[total] % mod);

        int c = int(x != '1' && y != '1') + int(x != '0' && y != '1') + int(x != '1' && y != '0');
        t = 1LL * t * c % mod;
    }

    return a;
}

int solve00(string s){
    if (s[0] == '1' || s.back() == '1' || s.length() <= 3)
        return 0;

    s[0] = '0';
    s.back() =  '0';

    vector<int> suffix(s.length());
    int total = 0;

    for (int i = s.length() - 3; i >= 0; i -= 2){
        char x = s[i], y = s[i + 1];

        if (x != '0' && y != '0')
            suffix[i] = pw2[total];

        int c = int(x != '1' && y != '1') + int(x != '0' && y != '1') + int(x != '1' && y != '0');
        add(suffix[i], 1LL * c * suffix[i + 2] % mod);

        if (x == '?') total++;
        if (y == '?') total++;
    }

    int answer = 0, nonsolved = 1;

    for (int i = 1; i < s.length(); i += 2){
        char x = s[i], y = s[i + 1];

        if (x == '?') total--;
        if (y == '?') total--;

        if (x != '0' && y != '0'){
            int ways = 0;

            if (s[i + 2] != '0')
                add(ways, pw2[total - int(s[i + 2] == '?')]);

            if (s[i + 2] != '1')
                add(ways, suffix[i + 3]);

            add(answer, 1LL * nonsolved * ways % mod);
        }

        int c = int(x != '1' && y != '1') + int(x != '0' && y != '1') + int(x != '1' && y != '0');
        nonsolved = 1LL * nonsolved * c % mod;
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    pw2 = vector<int>(s.length() + 1);
    pw2[0] = 1;
    for (int i = 1; i < pw2.size(); ++i){
        pw2[i] = pw2[i - 1];
        add(pw2[i], pw2[i]);
    }

    int answer = 0;

    add(answer, solve11(s));
    add(answer, solve00(s));
    add(answer, solve10(s));
    reverse(s.begin(), s.end());
    add(answer, solve10(s));

    cout << answer << endl;

    return 0;
}