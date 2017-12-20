#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

bool check(vector<int> path, int t){
    int d = 0;
    int l = path[0];
    for (auto x : path){
        d += abs(l - x);
        l = x;
    }
    return d <= t;
}

bool solve(int m, int l, int M, int L, int tm, int tl){
    if (check({0, m, M}, tm) &&
        check({0, m, M, l, L}, tl))
        return true;
    
    if (check({0, m, l, L}, tl) &&
        check({0, m, l, L, l, M}, tm))
        return true;

    return false;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, l;
    int M, L;
    int tm, tl;

    cin >> m >> l >> M >> L >> tm >> tl;

    if (!solve(m, l, M, L, tm, tl) && 
        !solve(l, m, L, M, tl, tm))
        cout << "im";
    cout << "possible" << endl;

    return 0;
}
