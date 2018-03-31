#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int p = 1000000007;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int answer = 1;

    for (int i = m - 1, j = n; i >= 0; --i){
        while (j > 0 && a[j - 1] >= b[i])
            j--;

        int t = n - j - (m - i - 1);

        if (t <= 0){
            answer = 0;
            break;
        }

        answer = 1LL * answer * t % p;
    }

    cout << answer << endl;

    return 0;
}