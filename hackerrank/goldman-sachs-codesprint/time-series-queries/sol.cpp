#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<pii> proc(vector<pii> &value){
    vector<pii> answer;
    for (auto p : value){
        if (answer.empty() || p.first > answer.back().first)
            answer.push_back(p);
    }
    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<pii> P(n);

    for (int i = 0; i < n; ++i)
        cin >> P[i].second;

    for (int i = 0; i < n; ++i)
        cin >> P[i].first;

    vector<pii> A = proc(P);
    reverse(P.begin(), P.end());
    vector<pii> B = proc(P);
    reverse(B.begin(), B.end());

    for (int i = 0; i < q; ++i){
        int x, v;
        cin >> x >> v;

        if (x == 1){
            int p = lower_bound(A.begin(), A.end(), pii(v, 0)) - A.begin();
            if (p == A.size()) cout << -1 << endl;
            else cout << A[p].second << endl;
        }
        else{
            if (B.back().second < v)
                cout << -1 << endl;
            else{
                int lo = -1, hi = B.size() - 1;
                while (lo + 1 < hi){
                    int m = (lo + hi) >> 1;
                    if (B[m].second >= v)
                        hi = m;
                    else
                        lo = m;
                }
                cout << B[hi].first << endl;
            }
        }
    }

    return 0;
}