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

    int n, x;
    cin >> n >> x;
    n = 2 * n - 1;

    if (x == 1 || x == n){
        cout << "No" << endl;
        return 0;
    }

    vector<int> value(n);

    int center = n / 2;
    value[center] = x;

    for (int i = 1, a = 1, b = n; i <= center; ++i, ++a, --b){
        if (a == x) a++;
        if (b == x) b--;
        value[center - i] = a;  
        value[center + i] = b;
    }

    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i)
        cout << value[i] << " ";
    cout << endl;

    return 0;
}
