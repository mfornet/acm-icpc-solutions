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
    
    for (int i = 2; i <= N; ++i){
        int x = 0;
        
        while (!x){
            cout << "Q 1 " << i << endl;
            cout.flush();
            cin >> x;
        }
    }
    
    cout << "A" << endl;
    
    return 0;
}