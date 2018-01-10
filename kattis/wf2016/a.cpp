#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int64,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;

    int64 A = 0;

    vector<int64> a(n);

    for (int i = 0; i < n; ++i){
        cin >> a[i];
        A += a[i];
    }

    vector<int64> s( n );

    for (int i = 0; i < k; ++i){
        int v; cin >> v;
        s[ v - 1 ]++;
    }

    set<pii> blocked, active;

    function<int64(int64,int64)> calc_up = [](int64 a, int64 b){
        return a / b + 1;
    };

    function<int64(int64,int64)> calc_down = [](int64 a, int64 b){
        if (a % b == 0) return a / b - 1;
        else return a / b;
    };

    for (int i = 0; i < n; ++i){
        int64 getactive = calc_up( 1LL * s[i] * A, a[i] );
        int64 deadline = calc_down( 1LL * (s[i] + 1) * A, a[i] );

        if (getactive <= k + 1)
            active.insert( {deadline, i} );
        else
            blocked.insert( {getactive, i} );
    }

    for (int i = k + 1;; ++i){

        while (!blocked.empty() && blocked.begin()->first <= i ){
            auto cur = *blocked.begin();
            blocked.erase( cur );
            int t = cur.second;
            int64 deadline = calc_down( 1LL * (s[t] + 1) * A, a[t] );
            active.insert( {deadline, t} );
        }

        if (active.empty()){
            assert( false );
            cout << i - k - 1 << endl;
            return 0;
        }

        auto cur = *active.begin();
        active.erase( cur );

        if (cur.first < i - 1){
            cout << max(0LL, cur.first - k) << endl;
            return 0;
        }

        int t = cur.second;

        s[t]++;

        int64 getactive = calc_up( 1LL * s[t] * A, a[t] );
        blocked.insert( {getactive, t} );

        if (i % A == 0) break;
    }

    cout << "forever" << endl;

    return 0;
}