#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<string> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i];

    vector<int> perm(10);
    iota(perm.begin(), perm.end(), 0);

    int64 answer = oo;

    do{
        int64 cur = 0;
        bool invalid = false;

        for (int i = 0; i < n; ++i){
            if (perm[value[i][0] - 'a'] == 0){
                invalid = true;
                break;
            }

            int64 ten = 1;

            for (int j = (int)value[i].size() - 1; j >= 0; --j){
                cur += ten * perm[value[i][j] - 'a'];
                ten *= 10;
            }
        }        

        if (invalid) continue;

        answer = min(answer, cur);


    }while(next_permutation(perm.begin(), perm.end()));

    cout << answer << endl;

    return 0;
}