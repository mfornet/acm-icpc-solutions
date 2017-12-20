#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

bool solve(){
    int n; cin >> n;

    vector<int> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i];

    int last = 0;

    for (int i = 0; 2 * i < n; ++i){
        if (value[i] < 1 || value[i] > 7)
            return false;

        if (value[i] != value[n - i - 1])
            return false;

        if (value[i] != last){
            if (value[i] != last + 1)
                return false;
            last = value[i];
        }
    }

    return last == 7;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--)
        cout << (solve() ? "yes" : "no") << endl;

    return 0;
}