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

    int t; cin >> t;

    while (t--){
        int c, s;
        cin >> c >> s;
        
        int v = 1;
        while (v * v < s)
            v += 1;

        int g = __gcd(v, c);
        c /= g;
        v /= g;

        vector<int> cur(c, 0);

        int total = 0;
        int beg = 0;

        const int magic = 100000;

        auto m = [&](int a){
            return (a % c + c) % c;
        };

        while (true){
            total++;
            vector<int> ncur = cur;

            for (int i = 0; i < v; ++i){
                ncur[m(i + beg)] = cur[ m(beg + v - i - 1) ] ^ 1;
            }

            beg = m(beg + v);

            int sum = 0;

            cur = ncur;

            for (int i = 0; i < c; ++i)
                sum += cur[i];

            if (sum == 0)
                break;
        }

        if (total == magic){
            cout << "never" << endl;
        }
        else
            cout << total << endl;
    }

    return 0;
}
