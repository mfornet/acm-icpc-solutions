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

    vector<int64> a(n), b(n);

    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];

    int64 answer = 0, rem = 0;

    for (int i = n - 1; i >= 0; --i){
        int64 v = a[i] + rem;
        int64 r = v % b[i];
        if (r == 0) continue;
        answer += b[i] - r;
        rem += b[i] - r;
    }

    cout << answer << endl;

    return 0;
}
