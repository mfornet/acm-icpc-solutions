#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<int> get_freq(string &s){
    vector<int> freq(26);
    for (auto c : s)
        freq[c - 'a']++;
    return freq;
}

string solve(){
    string a, b;
    cin >> a >> b;
    vector<int> freqA = get_freq(a);
    vector<int> freqB = get_freq(b);

    bool winPlayerB = false;
    bool playerAHasMove = false;

    for (int i = 0; i < 26; ++i){
        if (freqA[i] >= 2 && freqB[i] == 0)
            return "A";

        if (freqA[i] && !freqB[i])
            playerAHasMove = true;

        if (freqB[i] && !freqA[i])
            winPlayerB = true;
    }

    if (!playerAHasMove) return "B";
    return winPlayerB ? "B" : "A";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t-->0)
        cout << solve() << endl;

    return 0;
}