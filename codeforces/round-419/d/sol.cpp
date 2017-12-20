#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 get_area(set<pii>::iterator it){
    pii b = *it;
    ++it; pii c = *it;
    --it; --it; pii a = *it;
    return (b.first - a.first) * (b.second - c.second);
}

int64 interior;

pii solve(vector<int64> x, vector<int64> y, vector<int64> z, int64 height){
    int n = (int)x.size();
    vector<int> idx(n);
    iota( idx.begin(), idx.end(), 0 );

    sort( idx.begin(), idx.end(), [&](int a, int b){
            return z[a] > z[b];
    });

    int64 answer = 0;
    int64 curarea = 0;
    int64 prev = 0;

    set<pii> S;
    S.insert( pii(0, oo) );
    S.insert( pii(oo, 0) );

    int64 common = 0;
    int64 tX = 0, tY = 0;

    for (int i = 0; i < n; ++i){
        int u = idx[ i ];

        assert( tX * tY >= curarea );
        answer += curarea * (prev - z[u]);
        common += tX * tY * (prev - z[u]);
        prev = z[u];

        pii pos( x[u], y[u] );
        tX = max( tX, x[u] );
        tY = max( tY, y[u] );

        auto it = S.lower_bound(pos);
        if (it->second >= y[u]) continue;

        while (true){
            auto it = S.lower_bound(pos);
            it--;

            if (it->second <= y[u]){
                // erase
                curarea -= get_area( it );
                S.erase( it );
            }
            else
                break;
        }

        S.insert( pos );
        curarea += get_area( S.find( pos ) );
    }

    answer += curarea * prev;
    common += tX * tY * prev;
/*
    cout << endl; cout << "answer: " << answer << endl; cout << "area: " << curarea << endl;
    cout << "height: " << height << endl;
    cout << "common: " << common << endl;
*/
    interior = answer;

    return {curarea * height, common};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    int64 X, Y, Z;
    cin >> X >> Y >> Z;

    int64 a = X, b = Y, c = Z;

    vector<int64> x(n), y(n), z(n);

    for (int i = 0; i < n; ++i){
        cin >> x[i] >> y[i] >> z[i];

        a = min(x[i], a);
        b = min(y[i], b);
        c = min(z[i], c);
    }

    // brute answer

    int64 BRUTE = 0;

    for (int i = 1; i <= X; ++i)
        for (int j = 1; j <= Y; ++j)
            for (int k = 1; k <= Z; ++k){
                bool ok = true;
                for (int t = 0; t < n && ok; ++t)
                    ok = (0 + (i > x[t]) + (j > y[t]) + (k > z[t]) ) >= 2;
                BRUTE += ok;
            }

    cout << BRUTE << endl;

    auto zValue = solve(x, y, z, Z);
    auto xValue = solve(y, z, x, X);
    auto yValue = solve(z, x, y, Y);

    cout << endl;
    cout << zValue.first << " " << zValue.second << endl;
    cout << xValue.first << " " << xValue.second << endl;
    cout << yValue.first << " " << yValue.second << endl;
    cout << "interior: " << interior << endl;

    int64 answer =  X * Y * Z 
                    - zValue.first - xValue.first - yValue.first 
                    + zValue.second + xValue.second + yValue.second
                    - interior;

    cout << answer << endl;

    return 0;
}
