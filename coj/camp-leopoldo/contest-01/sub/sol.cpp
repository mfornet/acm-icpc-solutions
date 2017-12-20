#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int fr[ 100 ][ 20000 + 5 ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;

    if (n == 1){
        return 0;
    }

    vector<int> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i];


    int target = value[0] - t - value[1];

    memset( fr, -1, sizeof fr );



    return 0;
}
