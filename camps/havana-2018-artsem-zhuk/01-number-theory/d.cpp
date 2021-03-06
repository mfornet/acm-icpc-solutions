#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 gcd(int64 a, int64 b, int64 &x, int64 &y){
    if (b == 0)
        return x = 1, y = 0, a;
    int64 r = gcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 a, b, c;

    int64 x, y;

    cin >> a >> b >> c;

    int64 g = gcd(a, b, x, y);

    if (c % g){
        cout << "Impossible" << endl;
    }
    else{
        x *= c / g;
        y *= c / g;

        while (x > 0){
            x -= b / g;
            y += a / g;
        }

        while (x < 0){
            x += b / g;
            y -= a / g;
        }

        cout << x << " " << y << endl;
    }


    return 0;
}