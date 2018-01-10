#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

char M[60][60];
int dist[60][60][10100];
int r, c;
string s;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

bool inside(int x, int y){
    return 0 <= x && x < r && 0 <= y && y < c;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> r >> c;
    for (int i = 0; i < r; ++i)
        cin >> M[i];

    cin >> s;

    s += "*";

    memset(dist, oo, sizeof dist);
    dist[0][0][0] = 0;

    queue<pair<pii,int>> Q;
    Q.push(MP(MP(0,0), 0));

    while (!Q.empty()){
        auto cur = Q.front(); Q.pop();
        int x = cur.first.first;
        int y = cur.first.second;
        int p = cur.second;

        if (p == (int)s.length()){
            cout << dist[x][y][p] << endl;
            return 0;
        }

        if (M[x][y] == s[p] && dist[x][y][p + 1] > dist[x][y][p] + 1){
            dist[x][y][p + 1] = dist[x][y][p] + 1;
            Q.push(MP(MP(x,y), p + 1));
        }

        for (int i = 0; i < 4; ++i){
            int cx = x, cy = y;
            while (inside(cx + dx[i], cy + dy[i]) && M[cx + dx[i]][cy + dy[i]] == M[x][y])
                cx += dx[i], cy += dy[i];

            if (!inside(cx + dx[i], cy + dy[i])) continue;
            cx += dx[i], cy += dy[i];

            if (dist[cx][cy][p] > dist[x][y][p] + 1){
                dist[cx][cy][p] = dist[x][y][p] + 1;
                Q.push(MP(MP(cx, cy), p));
            }
        }
    }

    return 0;
}

