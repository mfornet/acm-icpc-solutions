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

    int n, c, k;
    cin >> n >> c >> k;

    vi pos(n);

    for (int i = 0; i < n; ++i)
        cin >> pos[i];

    sort(pos.begin(), pos.end());

    int beg = -oo, answer = 0, total = 0;

    for (int i = 0; i < n; ++i){
        if (total == c || pos[i] - beg > k){
            answer++;
            beg = pos[i];
            total = 0;
        }

        total++;
    }

    cout << answer << endl;

    return 0;
}