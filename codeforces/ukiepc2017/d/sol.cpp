#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;

    vector<int> value(s.length());
    vector<int> where(s.length());
    vector<int> freq(26);
    vector<int> pos(26);

    for (auto c : s)
        freq[c - 'a']++;

    for (int i = 1; i < 26; ++i)
        pos[i] = pos[i - 1] + freq[i - 1];

    for (int i = 0; i < (int)s.length(); ++i){
        value[i] = pos[s[i] - 'a']++;
        where[value[i]] = i;
    }

    vector<pii> answer;

    for (int i = 0; i < (int)s.length(); ++i){
        if (value[i] == i) continue;
        int pos = where[i];
        answer.push_back({where[i] + 1, i + 1});

        int x = where[i];

        where[value[i]] = where[i];
        where[i] = i;

        swap(value[i], value[x]);
    }

    reverse(answer.begin(), answer.end());

    for (auto x : answer)
        cout << x.first << " " << x.second << endl;

    return 0;
}
