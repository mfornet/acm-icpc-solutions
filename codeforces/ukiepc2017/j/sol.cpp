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

    map<int,double> len;

    int a = 0;
    double x = 2;

    for (int i = 0; i < 6; ++i){
        len[a] = x;
        a = max(1, 2 * a);
        x /= 2;
    }

    double answer = 0;

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        int code; cin >> code;
        answer += len[code];
    }

    cout.precision(10);

    cout << fixed << answer << endl;


    return 0;
}
