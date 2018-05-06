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

    vector<string> M(n);

    for (int i = 0; i < n; ++i){
        cin >> M[i];
        M[i] += M[i];
    }

    int answer = 0;

    for (int k = 0; k < n; ++k){
        bool ok = true;
        for (int i = 0; i < n && ok; ++i)
            for (int j = 0; j < n && ok; ++j){
                if (M[i][j + k] != M[j][i + k])
                    ok = false;
            }

        if (ok) answer += n;
    }

    cout << answer << endl;

    return 0;
}