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
    
    vector<int> primes = {2, 3, 5, 7};
    
    int a = 1;
    
    for (int i = 0; i < 4; ++i){
        cout << "Q " << primes[i] << endl;
        cout.flush();
        
        int v; cin >> v;
        
        for (int j = 0; j < v; ++j)
            a *= primes[i];
    }
    
    cout << "A " << a << endl;
    cout.flush();
    
    return 0;
}