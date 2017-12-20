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

    int N; cin >> N;

    string a, b;
    cin >> a >> b;

    for (int i = N; i; --i){
        if (a.substr(N - i) == b.substr(0, i)){
            cout << 2 * N - i << endl;
            return 0;
        }
    }

    cout << 2 * N << endl;

    return 0;
}
