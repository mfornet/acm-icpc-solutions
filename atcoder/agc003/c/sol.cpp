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

    int n; cin >> n;

    vector<int> value(n);
    vector<int> x(n);

    for (int i = 0; i < n; ++i){
        cin >> x[i];
        value[i] = x[i];
    }

    sort(x.begin(), x.end());

    int answer = 0;

    for (int i = 0; i < n; ++i){
        int p = lower_bound(x.begin(), x.end(), value[i]) - x.begin();
        if ((p & 1) != (i & 1))
            answer++;
    }

    cout << answer / 2 << endl;

    return 0;
}
