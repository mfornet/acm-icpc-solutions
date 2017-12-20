#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 solve(int64 a, int64 b){
    if (a > b) swap(a, b);

    int64 ans;
    
    if (b % a == 0)
        ans = 2 * b - a;
    else
        ans = 2 * a * (b / a) + solve(a, b % a);

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 n, x;

    cin >> n >> x;

    cout << n + solve(x, n - x) << endl;

    return 0;
}
