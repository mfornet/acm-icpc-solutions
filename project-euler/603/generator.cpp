#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000000; 
const int N = 7;

bool p[maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int dig = 1;
    int nxt = 10;

    int total = 0;
    int counter = 0;

    int last = -1;

    for (int i = 2; counter < N; ++i){
        assert(i < maxn);
        if (i == nxt){
            dig++;
            nxt *= 10;
        }

        if (p[i]) continue;
        cout << i;

        counter++;
        total += dig;

        for (int j = 2 * i; j < maxn; j += i)
            p[j] = true;
    }

    cout << endl;

    return 0;
}
