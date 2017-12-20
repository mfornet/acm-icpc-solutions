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

    int a, b;
    cin >> a >> b;

    if (a <= 0 && b >= 0)
        cout << "Zero" << endl;
    else if (a > 0)
        cout << "Positive" << endl;
    else if ((b - a + 1) & 1)
        cout << "Negative" << endl;
    else
        cout << "Positive" << endl;

    return 0;
}
