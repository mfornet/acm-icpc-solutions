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

    int n;

    while (cin >> n){
        set<int> seen;

        for (int i = 0; i < n; ++i){
            string s; cin >> s;

            int mask = 0;

            for (auto c : s){
                int x = c - '0';
                mask |= 1 << x;
            }

            seen.insert(mask);
        }

        cout << seen.size() << endl;
    }


    return 0;
}
