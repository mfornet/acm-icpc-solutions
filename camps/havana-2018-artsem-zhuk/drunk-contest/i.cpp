#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 w, m;

void backtrack(int64 M, int64 W){
    if (M == 0){
        cout << "YES" << endl;
        exit(0);
    }
    if (W > oo / w) return;
    if (M % W) return;

    backtrack(M, W * w);
    backtrack(M + W, W * w);
    backtrack(abs(M - W), W * w);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> w >> m;

    backtrack(m, 1);

    cout << "NO" << endl;

    return 0;
}