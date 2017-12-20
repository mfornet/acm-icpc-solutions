#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct lizard{
    int64 x, y, r, h;

    bool operator<(const lizard &l)const{
        if (x != l.x) return x < l.x;
        if (y != l.y) return y < l.y;
        return r < l.r;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int64 tx, ty;
    cin >> tx >> ty;

    int n; cin >> n;

    vector<lizard> V(n);

    for (int i = 0; i < n; ++i){
        int64 x, y, h;
        cin >> x >> y >> h;
        x -= tx; y -= ty;
        int64 g = __gcd(abs(x), abs(y));
        int64 r = x * x + y * y;
        x /= g; y /= g;
        V[i] = {x, y, r, h};

    }

    sort(V.begin(), V.end());

    int answer = 0;

    for (int i = 0, j; i < n; i = j){
        vector<int64> lis;

        for (j = i; j < n && V[j].x == V[i].x && V[j].y == V[i].y; ++j){
            int64 cur = V[j].h;

            auto pos = lower_bound(lis.begin(), lis.end(), cur);
            if (pos == lis.end()) lis.push_back(cur);
            else *pos = cur;
        }

        answer += lis.size();
    }

    cout << answer << endl;

    return 0;
}
