#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100010;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    int n; cin >> n;

    vector<int> v(3 * n);

    for (int i = 0; i < 3 * n; ++i){
        cin >> v[i];
    }

    sort(v.begin(), v.end());

    int64 answer = 0;

    for (int i = 0; i < n; ++i)
        answer += v[3 * n - 2 - 2 * i];

    cout << answer << endl;

    return 0;
}