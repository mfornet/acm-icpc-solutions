#include <bits/stdc++.h>

using namespace std;

int main(){
    #ifdef MARX
    freopen("test.in", "r", stdin);
    #endif

    int n;
    double t;

    cin >> n >> t;

    vector< pair<double,double> > marks(n);

    double lo = -1e9, hi = 1e9;

    for (int i = 0; i < n; ++i){
        cin >> marks[i].first >> marks[i].second;
        lo = max(lo, -marks[i].second);
    }

    for (int it = 0; it < 100; ++it){
        double c = (lo + hi) / 2;
        double curtime = 0;

        for (int i = 0; i < n; ++i)
            curtime += marks[i].first / (marks[i].second + c);
    
        if (curtime > t)
            lo = c;
        else
            hi = c;
    }

    cout.precision(12);
    cout << fixed << hi << endl;
} 