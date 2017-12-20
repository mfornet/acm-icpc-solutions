#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

pair<int64,int64> LL0;
int64 AA, BB;

int64 gcd(int64 a, int64 b, int64 &x, int64 &y)
{
	if(b == 0)
		return x = 1, y = 0, a;
	int64 r = gcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}

pair<int64,int64> merge(pair<int64,int64> ta, pair<int64,int64> tb, int64 m){
    int64 xa = ta.first, ma = ta.second;
    int64 xb = tb.first, mb = tb.second;
    int64 a;

    pair<int64,int64> cur(ma, mb);

    if (cur == LL0)
        a = AA;
    else
        a = BB;

    a = (a % m) * (xb - xa);

    int64 x = xa + ma * (a % m);
    //int64 m = ma * mb;

    x %= m;

    if (x < 0)
        x += m;

    return {x, m};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 m1, m2, m3;
    int64 x1, x2, x3;
    int64 a1, a2, a3;

    cin >> m1 >> m2 >> m3;
    cin >> x1 >> x2 >> x3;
    cin >> a1 >> a2 >> a3;

    int64 tmpa, tmpb;

    gcd(m1, m2, tmpa, tmpb);
    LL0 = {m1, m2};
    AA = tmpa;

    gcd(m1 * m2, m3, tmpa, tmpb);
    BB = tmpa;

    int64 answer = -1;

    vector<int> D1, D2, D3;

    for (int d = -a1; d <= a1; ++d)
        D1.push_back(((x1 + d) % m1 + m1) % m1);

    for (int d = -a2; d <= a2; ++d)
        D2.push_back(((x2 + d) % m2 + m2) % m2);
    
    for (int d = -a3; d <= a3; ++d)
        D3.push_back(((x3 + d) % m3 + m3) % m3);

    random_shuffle(D1.begin(), D1.end());
    random_shuffle(D2.begin(), D2.end());
    random_shuffle(D3.begin(), D3.end());

    int64 MM = m1 * m2;
    int64 MMM = MM * m3;

    for (int i = 0; i < (int)D1.size() && 1. * clock() / CLOCKS_PER_SEC < 2.94; ++i){
        int64 p1 = D1[i];

        for (int j = 0; j < (int)D2.size(); ++j){
            int64 p2 = D2[j];

            auto cur = merge({p1, m1}, {p2, m2}, MM);

            for (int k = 0; k < (int)D3.size(); ++k){
                int64 p3 = D3[k];

                auto fin = merge(cur, {p3, m3}, MMM);

                if (answer == -1) answer = fin.first;
                else answer = min(answer, fin.first);
            }
        }
    }

    cout << answer << endl;

    return 0;
}
