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

    int t; cin >> t;

    while (t--){
        int n; cin >> n;

        int64 answer = 1, acc = 1;

        for (int i = 1; i < n; ++i){
            int64 v; cin >> v;
            acc *= v;
            answer += acc;
        }

        cout << answer << endl;
    }


    return 0;
}
