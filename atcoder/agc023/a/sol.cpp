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

    int64 answer = 0;
    int64 cumsum = 0;

    map<int64,int> freq;
    freq[cumsum]++;

    for (int i = 0; i < n; ++i){
        int64 v; cin >> v;
        cumsum += v;

        answer += freq[cumsum]++;
    }

    cout << answer << endl;

    return 0;
}