#include <bits/stdc++.h>

using namespace std;

const int alpha = 26;

bool path[alpha][alpha];

int main(){
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; ++i){
        char x, y;
        cin >> x >> y;
        path[ x - 'a' ][ y - 'a' ] = true;
    }

    for (int i = 0; i < alpha; ++i)
        path[i][i] = true;

    for (int k = 0; k < alpha; ++k)
        for (int i = 0; i < alpha; ++i)
            for (int j = 0; j < alpha; ++j)
                path[i][j] |= path[i][k] & path[k][j];

    while (k--){
        string a, b;
        cin >> a >> b;

        bool ok = a.length() == b.length();

        for (int i = 0; i < (int)a.length() && ok; ++i)
            ok = path[ a[i] - 'a' ][ b[i] - 'a' ];

        cout << (ok ? "yes" : "no") << endl;
    }

}