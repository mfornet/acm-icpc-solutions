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

    string d = "NSWE";

    bool ok = true;

    for (int i = 0; i < 4; i += 2){
        bool a = s.find(d[i]) == s.npos;
        bool b = s.find(d[i+1]) == s.npos;
        if (a != b) ok = false;
    }

    cout << (ok ? "Yes" : "No") << endl;

    return 0;
}
