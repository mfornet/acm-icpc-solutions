#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

map<ld,int64> M;
int64 Fact[21];

int64 fact(int n){
    return Fact[n];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Fact[0] = 1;
    for (int i = 1; i <= 20; ++i)
        Fact[i] = Fact[i - 1] * i;

    int n; cin >> n;
    ld p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;

    for (int i1 = 0; i1 <= n; ++i1){
        for (int i2 = 0; i2 <= n; ++i2){
            if (i1 + i2 > n) break;
            for (int i3 = 0; i3 <= n; ++i3){
                if (i1 + i2 + i3 > n) break;
                int i4 = n - (i1 + i2 + i3);
                M[ pow(p1, i1) * pow(p2, i2) * pow(p3, i3) * pow(p4, i4) ] +=
                        fact(n) / (fact(i1) * fact(i2) * fact(i3) * fact(i4));
            }
        }
    }

    ld ans = 0;

    bool mode = false;
    ld value = 0;

    while (!M.empty()){
        auto cur = M.begin();
        if (mode){
            mode = false;
            ans += cur->first + value;
            cur->second--;

            M[cur->first + value] += 1;

            if (!cur->second){
                M.erase(cur);
            }
        }
        else{
            ans += cur->first * 2 * (cur->second / 2);

            if (cur->second / 2){
                M[cur->first * 2] += cur->second / 2;
            }

            cur->second &= 1;
            if (cur->second){
                mode = true;
                value = cur->first;
            }
            M.erase(cur);
        }
    }

    cout.precision(9);
    cout << fixed << ans << endl;

    return 0;
}