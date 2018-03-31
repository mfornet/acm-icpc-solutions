#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int grundy(int a){
    int x = 0;

    if (a % 2 == 0){
        x = 1;
        while (!(a & 1))
            a >>= 1;
    }

    for (int j = 3; j * j <= a; j += 2){
        while (a % j == 0){
            x++;
            a /= j;
        }
    }

    if (a > 1) x++;

    return x;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    int a = 0;

    for (int i = 0; i < n; ++i)
    {
        int v; cin >> v;
        a ^= grundy(v);
    }

    cout << (a ? "Alice" : "Bob") << endl;

    return 0;
}