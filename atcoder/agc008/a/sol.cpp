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

    int x, y;
    cin >> x >> y;

    if (x == y) cout << 0 << endl;
    else if (x == -y) cout << 1 << endl;
    else if (abs(x) <= abs(y)){
        int answer = 0;
        if (x < 0) answer++;
        answer += abs(y) - abs(x);
        if (y < 0) answer++;
        cout << answer << endl;
    }
    else{
        int answer = 0;
        if (x > 0) answer++;
        answer += abs(x) - abs(y);
        if (y > 0) answer++;
        cout << answer << endl;
    }

    return 0;
}
