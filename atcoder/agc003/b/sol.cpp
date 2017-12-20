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

    int n; cin >> n;

    int64 rem = 0;
    int64 answer = 0;

    for (int i = 0; i < n; ++i){
        int64 value; cin >> value;
        if (value && rem){
            value--; rem = 0; answer++;
        }

        answer += value / 2;
        rem = value & 1; 
    }

    cout << answer << endl;

    return 0;
}
