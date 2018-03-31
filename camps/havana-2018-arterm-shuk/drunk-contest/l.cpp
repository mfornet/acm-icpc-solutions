#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(string &a, string &b){
    for (int i = 0, j = 0; i < (int)b.length(); ++i){
        if (a[j] == b[i]) j++;

        if (j == (int)a.length())
            return i + 1;
    }

    return -1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string a, b;

    cin >> a >> b;

    int p0 = solve(a, b);

    if (p0 == -1){
        cout << 0 << endl;
        exit(0);
    }

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int p1 = solve(a, b);
    assert(p1 != -1);

    p1 = (int)b.length() - p1;

    cout << max(p1 - p0 + 1, 0) << endl;

    return 0;
}