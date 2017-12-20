#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

bool positive(vector<int> &value, int x){
    int n = (int)value.size();
    int m = n / 2;
    int a = m - 1, b = m + 1;

    while (b < n && (value[b] >= x) != (value[b-1]>=x))
        b++;
    while (a >= 0 && (value[a] >= x) != (value[a+1]>=x))
        a--;
    a++;
    b--;

    if ((value[b]>=x)==(value[a]>=x))
        return value[b]>=x;

    if (b - m < m - a)
        return value[b] >= x;
    else
        return value[a] >= x;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    n = 2 * n - 1;

    vector<int> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i];

    int lo = 0, hi = n + 1;

    while (lo + 1 < hi){
        int mid = (lo + hi) / 2;

        if (positive(value, mid))
            lo = mid;
        else
            hi = mid;
    }

    cout << lo << endl;

    return 0;
}
