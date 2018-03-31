#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int sign(int x){
    return x >= 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 a, b;

    cin >> a >> b;

    int64 q = a / b;
    int64 r = a - q * b;

    assert(a == q * b + r);

    if (sign(b)){
        if (!sign(r)){
            q--;
            r += b;
        }
    }
    else{
        if (sign(r)){
            q--;
            r += b;
        }
    }

    cout << q << " " << r << endl;

    return 0;
}