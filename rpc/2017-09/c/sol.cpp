#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 1000000 + 10;

int ds[maxn];
int mtm[maxn], wh;

int& get(int a){
    if (mtm[a] != wh)
        mtm[a] = wh, ds[a] = 0;
    return ds[a];
}

int root(int a){
    return get(a) <= 0 ? a : get(a) = root(get(a));
}

void join(int a, int b){
    a = root(a), b = root(b);
    if (a == b) return;

    if (rand() & 1) swap(a, b);
    get(b) += get(a);
    get(a) = b;
}

char M[1010][1010];
int I[1000][1000];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0, k = 1; i < 1000; ++i)
        for (int j = 0; j < 1000; ++j)
            I[i][j] = k++;

    int n, m;

    while (cin >> n >> m){
        wh++;

        for (int i = 0; i < n; ++i){
            cin >> M[i];
            for (int j = 0; j < m; ++j)
            {
                int p = I[i][j];
                if (M[i][j] == '#') get(p) = -1;
                else if (M[i][j] == '.') get(p) = 0;
            }
        }

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j){
                if (M[i][j] == '*') continue;
                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy){
                        int x = i + dx, y = j + dy;
                        if (x < 0 || x >= n || y < 0 || y >= m || M[x][y] == '*') continue;
                        join( I[i][j], I[x][y] );
                    }
            }

        int answer = 0;
        set<int> roots;

        set<int> vis;
        queue<pii> q;

        auto add = [&](int p){
            int r = root(p);
            vis.insert(p);

            if (!roots.count(r)){
                answer -= get(r);
                roots.insert(r);
            }
        };

        int best = 0;

        auto check = [&](int x, int y){
            int value = 0;
            set<int> here;
            for (int dx = -1; dx <= 1; ++dx)
                for (int dy = -1; dy <= 1; ++dy){
                    int nx = x + dx, ny = y + dy;
                    if (0 <= nx && nx < n && 0 <= ny && ny < m && M[nx][ny] != '*')
                    {
                        int r = root(I[nx][ny]);
                        if (roots.count(r) == 0 && here.count(r) == 0)
                        {
                            value -= get(r);
                            here.insert(r);
                        }
                    }
                }
            return value;
        };

        for (int i = 0; i < n; ++i){
            if (M[i][0] != '*') add(I[i][0]), q.push(pii(i,0));
            if (M[i][m - 1] != '*') add(I[i][m - 1]), q.push(pii(i,m-1));
        }

        for (int j = 0; j < m; ++j){
            if (M[0][j] != '*') add(I[0][j]), q.push(pii(0,j));
            if (M[n - 1][j] != '*') add(I[n - 1][j]), q.push(pii(n-1,j));
        }

        for (int i = 0; i < n; ++i){
            if (M[i][0] == '*') best = max(best, check(i,0));
            if (M[i][m - 1] == '*') best = max(best, check(i, m-1));
        }

        for (int j = 0; j < m; ++j){
            if (M[0][j] == '*') best = max(best, check(0,j));
            if (M[n - 1][j] == '*') best = max(best, check(n-1,j));
        }

        while (!q.empty()){
            pii u = q.front(); q.pop();
            int x = u.first, y = u.second;

            for (int dx = -1; dx <= 1; ++dx)
                for (int dy = -1; dy <= 1; ++dy){
                    int nx = x + dx, ny = y + dy;
                    if (0 <= nx && nx < n && 0 <= ny && ny < m){
                        if (M[nx][ny] == '*')
                            best = max(best, check(nx, ny));
                        else{
                            int p = I[nx][ny];
                            if (!vis.count(p)){
                                vis.insert(p);
                                q.push(pii(nx, ny));
                            }
                        }
                    }
                }
        }

        cout << answer + best << endl; 
    }

    return 0;
}
