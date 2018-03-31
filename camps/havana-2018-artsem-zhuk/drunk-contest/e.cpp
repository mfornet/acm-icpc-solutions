#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

bool ok(int girl, int boy){
    if (girl > boy + 1) return false;
    if (boy > 2 * girl + 2) return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int al, ar;
    int bl, br;

    cin >> al >> ar >> bl >> br;

    cout << (ok(al, br) || ok(ar, bl) ? "YES" : "NO") << endl;

    return 0;
}