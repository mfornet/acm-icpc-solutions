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

    int n; cin >> n;

    int mh = 0;

    vector<int> H(n), X(n), Y(n);

    for (int i = 0; i < n; ++i){
        cin >> H[i] >> X[i] >> Y[i];
        mh = max(mh, H[i]);
    }

    for (int i = 0; i < 1825 * mh; ++i){
        bool ok = true;

        for (int j = 0; j < n && ok; ++j){
            int t = i % H[j];

            if (X[j] < Y[j]){
               if (X[j] < t && t < Y[j])
                   ok = false;
            }
            else{
                if (t < Y[j] || t > X[j])
                    ok = false;
            }
        }

        if (ok){
            cout << i << endl;
            return 0;
        }
    }

    cout << "impossible" << endl;

    return 0;
}
