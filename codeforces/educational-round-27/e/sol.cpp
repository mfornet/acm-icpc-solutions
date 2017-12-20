#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

int distance(pii a, pii b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

bool check(int n, int m, int size, vector<pii> &center){
   set<pii> s;

   for (int i = 1; i <= n; i += n - 1)
       for (int j = 1; j <= m; j += m - 1)
           s.insert(pii(i,j));

   int k = (int)center.size();
   for (int i = 0; i < k; ++i){
       int x = center[i].first, y = center[i].second;

       for (int k = 0; k < 4; ++k){
           int nx = x + size * dx[k], ny = y + size * dy[k];

           if (distance(center[i], pii(nx, ny)) <= size) continue;

           if (1 <= nx && nx <= n && 1 <= ny && ny <= m)
               s.insert(pii(nx, ny));
       }

       for (int j = i + 1; j < k; ++j){
           int jx = center[j].first, jy = center[j].second;

           int p = -1;

           for (int k = 0; k < 4 && p != -2; ++k){
                int njx = jx + dx[k] * size, njy = jy + dy[k] * size;
                if (distance(center[i], pii(njx, njy)) <= size){
                    if (p == -1) p = k;
                    else p = -2;
                }
           }

           if (p < 0) continue;

           pii cur = pii(jx + dx[k] * (size + 1), jy + dy[k] * (size + 1));

           int xpy = x + y;
           // intersect two rhombus

       }
   }

   int axpy = -oo;
   int bxpy = +oo;
   int axmy = -oo;
   int bxmy = +oo;

   for (auto p : s){
       bool ok = false;
       for (auto c : center)
           if (distance(c, p) <= size){
               ok = true;
               break;
           }

       if (ok) continue;

       int xpy = p.first + p.second;
       int xmy = p.first - p.second;

       axpy = max(axpy, xpy);
       bxpy = min(bxpy, xpy);
       axmy = max(axmy, xmy);
       bxmy = min(bxmy, xmy);
   }

   return axpy - bxpy <= 2 * size && axmy - bxmy <= 2 * size;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<pii> center(k);

    for (int i = 0; i < k; ++i){
        cin >> center[i].first >> center[i].second;
    }

    int lo = 0, hi = 1000000000;

    while (lo + 1 < hi){
        int mid = (lo + hi) >> 1;
        if (check(n, m, mid, center))
            hi = mid;
        else
            lo = mid;
    }

    cout << hi << endl;

    return 0;
}
