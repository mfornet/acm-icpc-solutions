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

    int h;
    string s; 

    cin >> h >> s;

    int start = 1;

    for (auto x : s)
    {
        start <<= 1;
        if (x == 'R')
            start++;
    }

    cout << (1 << (h + 1)) - start << endl;

    return 0;
}
