#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'
#define forn(i,j) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
#define sforn(i,j) for (int i = 0; i <= H; ++i) for (int j = 0; j <= i; ++j)
// #define double long double

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int N = 1000;
const int H = N / 2;

double mat[N][N];
double tmp[N][N];
int size[N][N];
pii repr[N][N];

vector<pii> adj[N][N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void prec(){
    forn(i,j){
        for (int k = 0; k < 4; ++k){
            int x = i + dx[k], y = j + dy[k];
            if (0 <= x && x < N && 0 <= y && y < N){
                adj[i][j].push_back(pii(x,y));
                size[i][j]++;
            }
        }

        int H = N / 2;
        int x = i, y = j;

        if (x > H) x = N - 1 - x;
        if (y > H) y = N - 1 - y;
        if (y > x) swap(x, y);

        repr[i][j] = pii(x, y);
    }

    forn(i,j){
        for (auto &t : adj[i][j])
            t = repr[t.first][t.second];
    }
}

void _fin(){
    sforn(i,j)
        mat[i][j] = tmp[i][j], tmp[i][j] = 0;
}

void init(){
    forn(i,j) mat[i][j] = 1. / N / N;
}

void criteriaI(){
    sforn(i,j){
        tmp[i][j] += mat[i][j] / (size[i][j] + 1);
        for (auto pl : adj[i][j])
            tmp[i][j] += mat[pl.first][pl.second] / (size[pl.first][pl.second] + 1);
    }
    _fin();
}

void criteriaII(){
    sforn(i,j){
        tmp[i][j] += mat[i][j] / 2;
        for (auto pl : adj[i][j])
            tmp[i][j] += mat[pl.first][pl.second] / 2 / size[pl.first][pl.second];
    }
    _fin();
}

void criteria(int p){
    p ? criteriaI() : criteriaII();
}

double go(){
    const int STEPS = 20;

    double answer = 0;

    for (int i = 0; i < 2; ++i){
        double prob = 0;

        init();

        for (int s = 0;; ++s){
            criteria(i);

            double cur = 0;

            for (int i = 1; i <= N; ++i){
                int p = i * i - 1;
                int x = p % N, y = p / N;

                pii r = repr[x][y];
                cur += mat[r.first][r.second];
            }

            double error = fabs(cur - prob);

            if (error < 1e-13){
                cout << "steps: " << s + 1 << endl;
                break;
            }

            prob = cur;

            if ((s & 3) == 3)
                cout << s << " " << fixed << prob << " " << error << endl;
        }

        answer += prob;
    }

    return answer / 2;

    // init();
    // for (int s = 0; s < STEPS; ++s)
    //     criteriaII();
    // for (int i = 1; i <= N; ++i){
    //     int p = i * i - 1;
    //     int x = p % N, y = p / N;
    //     answer += mat[x][y];
    // }

    // return answer / 2;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout.precision(12);
    prec();
    cout << fixed << go() << endl;

    return 0;
}