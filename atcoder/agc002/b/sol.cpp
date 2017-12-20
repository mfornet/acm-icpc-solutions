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

    int n, m;
    cin >> n >> m;

    vector<int> freq(n, 1);
    vector<bool> red(n, false);
    red[0] = true;

    for (int i = 0; i < m; ++i){
        int x, y;
        cin >> x >> y;
        x--; y--;

        if (red[x]){
            red[y] = true;
        }
        freq[x]--;
        freq[y]++;
    
        if (freq[x] == 0)
            red[x] = false;
    }

    int answer = 0;
    for (auto u : red) answer += u;

    cout << answer << endl;

    return 0;
}
