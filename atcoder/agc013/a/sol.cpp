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

    int last; cin >> last;

    int answer = 1;
    int mode = 0;

    for (int i = 1; i < n; ++i){
        int cur; cin >> cur;

        if (cur == last) continue;

        int curmode = cur > last ? +1 : -1;

        if (curmode * mode == -1){
            answer++;
            mode = 0;
        }
        else
            mode = curmode;

        last = cur;
    }

    cout << answer << endl;

    return 0;
}
