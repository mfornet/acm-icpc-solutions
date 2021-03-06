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

    vector<int64> value(n);
    int64 sum = 0;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        sum += value[i];
    }

    sum /= n;

    int64 a = 0;
    int64 cur = 0;

    for (int i = 0; i < n; ++i){
        cur += value[i];
        a += abs(sum * (i + 1) - cur);
    }

    cout << a << endl;

    return 0;
}