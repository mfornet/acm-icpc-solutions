#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

string value[8] = {
    "empty", "red", "yellow", "green", "brown", "blue", "pink", "black"
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    int maxvalue = 0, sum = 0, red = 0;

    for (int i = 0; i < n; ++i){
        string k; 
        cin >> k;

        int p = 0;
        while (value[p] != k)
            p++;

        //cout << k << " " << p << endl;

        if (p == 1) red++;
        sum += p;
        maxvalue = max(maxvalue, p);
    }

    //cout << maxvalue << " " << sum << " " << red << endl;

    if (maxvalue > 1)
        sum += maxvalue * red;

    if (maxvalue <= 1)
        sum = 1;

    cout << sum << endl;

    return 0;
}
