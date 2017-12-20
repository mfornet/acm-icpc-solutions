#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 value[maxn];
int   order[maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    iota(order, order + n, 1);
    sort(order, order + n, [&](int x, int y){
        return value[x] < value[y];
    });

    int64 k; cin >> k;

    int64 answer = 0;

    for (int i = 0; i < n; ++i){
        int u = order[i];
        int64 total = k / value[u];
        total = min(total, u); // :'(
        answer += total;
        k -= total * value[u];
    }

    cout << answer << endl;


    return 0;
}