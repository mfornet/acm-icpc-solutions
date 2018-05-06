#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vector<int> cuts(vector<int> waffle, int h, int size){
    vector<int> pieces(1);

    for (int i = 1, cur = 0; i < (int)waffle.size(); ++i){
        cur += waffle[i];

        if (cur == size){
            pieces.push_back(i);
            cur = 0;
        }
        else if (cur > size){
            return {};
        }
    }

    if (pieces.size() < h + 1){
        assert(false);
        return {};
    }

    return pieces;
}

bool solve(){
    int r, c, h, v;
    cin >> r >> c >> h >> v;

    h++; v++;

    vector<vector<int>> M(r + 1, vector<int>(c + 1));

    vector<int> A(r + 1), B(c + 1);

    int total = 0;

    for (int i = 1; i <= r; ++i){
        string s; cin >> s;

        for (int j = 1; j <= c; ++j){
            if (s[j - 1] == '@')
                M[i][j]++, A[i]++, B[j]++, total++;
        }
    }

    if (total % h)
        return false;

    auto a = cuts(A, h, total / h);

    if (total % v)
        return false;

    auto b = cuts(B, v, total / v);

    if (a.empty() || b.empty())
        return false;

    int chocolate_per_piece = total / h / v;

    for (int i = 0; i < h; ++i){
        for (int j = 0; j < v; ++j){
            int total = 0;
            for (int x = a[i] + 1; x <= a[i + 1]; ++x)
                for (int y = b[j] + 1; y <= b[j + 1]; ++y)
                    total += M[x][y];

            if (total != chocolate_per_piece)
                return false;
        }
    }

    return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc)
        cout << "Case #" << tc << ": " << (solve() ? "POSSIBLE" : "IMPOSSIBLE") << endl;

    return 0;
}