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
    
    vector<int64> value(n);
    
    for (int i = 0; i < n; ++i)
    cin >> value[i];
    
    sort(value.begin(), value.end());
    
    int64 answer = 0, cur = 0;
    
    for (int i = n; i > 1; i -= 2){
        cur += value[i - 1] + value[i - 2];
        answer=  max(answer, cur);
    }
    
    cout << answer << endl;
    
    return 0;
}