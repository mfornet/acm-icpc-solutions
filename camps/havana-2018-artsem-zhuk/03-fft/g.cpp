#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 S(int64 a, int n){
    if (a <= 0) 
        return 0;
    
    int64 sum = 0;

    // cout << endl;
    // cout << "S: " << a << " " << n << endl;

    for (int i = 0; i < n; ++i){
        int64 prev = (a >> (i + 1)) << i;
        int64 cur = (a & ((1 << i) - 1)) + 1;

        if ((a >> i & 1) == 0)
            cur = 0;

        int64 total = prev + cur;

        // cout << i << ": " << prev << " " << cur << " " << total << endl;
        sum += total << (n - i - 1);
    }

    return sum;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // for (int i = 0; i < 16; ++i)
    //     cout << S(i, 4) << endl;
    // exit(0);

    int n; cin >> n;
    int k; cin >> k;

    for (int i = 0; i < k; ++i){
        int a, b;

        cin >> a >> b;
        cout << (S(b, n) - S(a - 1, n)) % 1000000007 << endl; // WTF this modulo
    }   

    return 0;
}