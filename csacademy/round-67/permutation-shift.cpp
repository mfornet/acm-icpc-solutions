#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n; cin >> n;
    
    vector<int> v(n);
    
    for (int i = 0; i < n; ++i)
    cin >> v[i];
    
    int answer = 0;
    
    for (int i = 0; i < n; ++i){
        int cur = 0;
        for (int j = 0; j < n; ++j){
            if (v[(i + j)%n] == j+1)
            cur++;
        }
        answer = max(answer, cur);
    }
    cout << answer << endl;
    
    return 0;
}