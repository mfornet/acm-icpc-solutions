#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int A[maxn], T;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n; n--;

    D[1] = 1;

    for (int i = 2; i <= n; ++i){
        for (int j = i; j; --j)
            D[j] = D[j - 1] * 2 * (j - 1);
        for (int j = 1; j <= i; ++j)
            cout << D[j] << " ";
        cout << endl;
    }

    return 0;
}