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
    
    int N; cin >> N;
    
    for (int i = 0; i < 500; ++i){
        int x = N - (N & (N-1));
        
        cout << x << endl;
        cout.flush();
        
        N = N - x;
        
        if (N == 0) break;
        
        int g; cin >> g;
        
        N = N - g;
    }
    
    return 0;
}