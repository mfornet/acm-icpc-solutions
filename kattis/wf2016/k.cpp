#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
typedef long long int64;
typedef vector<int64> vi;
typedef pair<int64, int64> pii;

bool solve(vi V, int k, int n){
    int a = 0;
    int b = n - 1;
    for (int p = k; p; --p){
        if (a > b)
            return false;
        if (a == b && V[a] < 2 * p)
            return false;
        if (V[a] < p || V[b] < p)
            return false;
        V[a] -= p;
        V[b] -= p;
        if (!V[a])
            a++;
        if (!V[b])
            b--;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vi V(n);

    int64 sm = 0;
    for (int i = 0; i < n; ++i){
        cin >> V[i];
        sm += V[i];
    }

    if (sm & 1){
        cout << "no quotation" << endl;
        return 0;
    }

    for (int k = 100; k > 1; --k){
        if (solve(V, k, n)){
            cout << k << endl;
            return 0;
        }
    }

    if (sm == 2)
        cout << 1 << endl;
    else
        cout << "no quotation" << endl;

    return 0;
}