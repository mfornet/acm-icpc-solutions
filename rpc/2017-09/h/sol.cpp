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

    int n;
    int64 v;

    while (cin >> n >> v){
        int b = -1, e = -1;

        map<int64,int> pos;
        pos[0] = 1;
        int64 acc = 0;

        for (int i = 1; i <= n; ++i){
            int64 val; cin >> val;
            acc += val;

            if (b == -1 && pos.count(acc - v)){
                b = pos[acc - v], e = i;
            }

            pos[acc] = i + 1;
        }

        if (b == -1) cout << -1 << endl;
        else cout << b << " " << e << endl;
        
    }

    return 0;
}
