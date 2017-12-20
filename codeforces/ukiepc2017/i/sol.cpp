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

    vector<int> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i];

    int size; cin >> size;

    pii answer(size + 1, -1);

    for (auto v : value){
        pii cur(size % v, v);
        answer = min(answer, cur);
    }

    cout << answer.second << endl;

    return 0;
}
