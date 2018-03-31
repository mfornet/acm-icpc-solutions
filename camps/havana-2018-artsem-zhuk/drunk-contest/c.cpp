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

    int n, m;
    cin >> n >> m;

    vector<int> A(n);

    for (int i = 0; i < n; ++i)
        cin >> A[i];

    int answer = 0;
    int piece = 0;

    for (int j = 0, i = 0; j < m; ++j){
        int v; cin >> v;

        piece += v;

        while (piece > 0)
            piece -= A[i++];

        answer += piece == 0;
    }

    cout << answer << endl;

    return 0;
}