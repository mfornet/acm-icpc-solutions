#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(int n){

    vector<int> X;
    vector<vi> S;

    for (int i = 0; i < n; ++i){
        vector<int> C;

        int t; cin >> t;
        int p = -1;

        for (int j = 0; j < t; ++j){
            int v; cin >> v;
            if (p == v) continue;

            X.push_back(v);
            C.push_back(v);
            p = v;
        }

        S.push_back( C );
    }

    sort(X.begin(), X.end());
    X.resize( unique( X.begin(), X.end() ) - X.begin() );

    int answer = 0;

    vector<int> nxt( X.size(), -1 );
    vector<int> cnt( X.size() );
    int row = 0;

    for (auto &s : S){
        answer += 2 * s.size() - 1;

        int last = -2;
        for (auto v : s){
            int p = lower_bound(X.begin(), X.end(), v) - X.begin();
            assert( X[p] == v );
            
            if (last + 1 == p){
                if (nxt[ last ] == -1)
                    nxt[ last ] = row;
                else
                    nxt[ last ] = -2;
            }

            cnt[ p ]++;
            last = p;
        }

        row++;
    }

    int u = -1, g = 0;

    for (int i = 0; i < nxt.size(); ++i){
        if (nxt[i] == -1){
            u = -1;
        }
        else if (nxt[i] == -2){
            u = -1;
            g++;
        }
        else{
            if (u == nxt[i]){
                if (cnt[i] == 1)
                    g++;
                else
                    u = -1;
            }
            else{
                u = nxt[i];
                g++;
            }
        }
    }

    return answer - 2 * g - 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n; 
    int tc = 1;

    while (cin >> n){
        cout << "Case " << tc++ << ": " << solve(n) << endl;
    }

    return 0;
}