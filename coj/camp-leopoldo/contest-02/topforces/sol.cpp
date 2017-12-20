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

    vector<pii> P(n);
    vector<int> order(n);
    iota( order.begin(), order.end(), 0 );

    for (int i = 0; i < n; ++i)
        cin >> P[i].first >> P[i].second;

    sort( order.begin(), order.end(), [&](int a, int b){
            return P[a] < P[b];
        });

    vector<pii> A;

    for (int i = 0, t = 0; i < n; ++i){
        int u = order[i];

        A.push_back( pii(i, P[u].second) );
        t++;

        while (t > 1 && A[ t - 2 ].second > P[u].second ){
            A[ t - 2 ].first = A[ t - 1].first;
            A[ t - 2 ].second = max( A[t - 2].second, A[t - 1].second );
            A.pop_back();
            t--;
        }
    }

    vector<int> answer(n);
    int last = 0;

    for (auto a : A){
        for (int i = last; i <= a.first; ++i)
            answer[ order[i] ] = a.first;
        last = a.first + 1;
    }

    for (int i = 0; i < n; ++i)
        cout << answer[i] << endl;

    return 0;
}
