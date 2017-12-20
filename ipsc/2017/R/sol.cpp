#include <bits/stdc++.h>

using namespace std;

//#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000 + 10; 
const int magic = 1000;

int n, c, k;
double p[ maxn ][ maxn ];
double t[ maxn ];

int mod(int v, int m){
    return (v % m + m) % m;
}

void solve(){
    p[0][1] = 1.;

    for (int a = 2; a <= n; ++a){
        for (int x = 0; x < a; ++x)
            p[x][a] = 1. / n;

        for (int _ = 0; _ < magic; ++_){

            t[0] = (1. - 1. * (a - 1) / c) * p[ mod(-k, a) ][ a ]; 

            for (int x = 1; x < a; ++x){
                double pr = 1. * (a - 1) / c;
                double q = 1. - pr;
                t[x] = pr * p[x - 1][a - 1] + q * p[mod(x - k, a)][a];
            }

            for (int x = 0; x < a; ++x){
                p[x][a] = t[x];
            }
        }

        for (int x = 0; x < a; ++x)
            cout << p[x][a] << " ";
        cout << endl;
    }

    double best = 0;
    int answer = -1;

    for (int x = 0; x < n; ++x){
        if (p[x][n] > best){
            best = p[x][n];
            answer = x;
        }
    }

    cout.precision(12);
    cout << answer << " " << fixed << best << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
/*
    for (int i = 2; i <= 10; ++i){
        for (int j = 1; j <= i; ++j){
            n = i, c = i, k = j;

            cout << endl;
            cout << n << " " << c << " " << k << endl;
            solve();
        }
    }
    exit(0);
*/
    int t; cin >> t;

    while (t--){
        cin >> n >> c >> k;

        solve();
    }

    return 0;
}
