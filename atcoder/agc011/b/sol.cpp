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

    int n;
    cin >> n;

    vector<int64> size(n);

    for (int i = 0; i < n; ++i)
        cin >> size[i];

    sort(size.begin(), size.end());

    vector<int64> acc = size;

    for (int i = 1; i < n; ++i)
        acc[i] += acc[i - 1];

    int total = 1;

    for (int i = n - 2; i >= 0; --i){
        if (2 * acc[i] >= size[i + 1])
            total++;
        else
            break;
    }

    cout << total << endl;

    return 0;
}