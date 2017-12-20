#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define forn(i,j) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
#define double long double

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int N = 20;

int gauss(vector<vector<double>> a, vector<double> &ans)
{
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < eps)
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row)
            {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] -= a[row][j] * c;
            }

        ++row;
    }

    ans.assign(m, 0);

    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i = 0; i < n; ++i)
    {
        double sum = 0;
        for (int j = 0; j < m; ++j)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > eps)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1)
            return oo;
    return 1;
}


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

        // int H = N / 2;
        // int x = i, y = j;

        // if (x > H) x = N - 1 - x;
        // if (y > H) y = N - 1 - y;
        // if (y > x) swap(x, y);

        // repr[i][j] = pii(x, y);
    }

    // forn(i,j){
    //     for (auto &t : adj[i][j])
    //         t = repr[t.first][t.second];
    // }
}

void build_I(vector<vector<double>> &A){
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j){
            int pos = i * N + j;
            A[pos][pos] = 1. / (size[i][j] + 1) - 1.;

            for (auto pl : adj[i][j]){
                int tpos = pl.first * N + pl.second;
                A[pos][tpos] = 1. / (size[pl.first][pl.second] + 1);
            }
        }
}

void build_II(vector<vector<double>> &A){
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j){
            int pos = i * N + j;
            A[pos][pos] = 1. / 2 - 1.;

            for (auto pl : adj[i][j]){
                int tpos = pl.first * N + pl.second;
                A[pos][tpos] = 1. / 2 / (size[pl.first][pl.second]);
            }
        }
}

void build_I_(vector<map<int,double>> &A){
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j){
            int pos = i * N + j;
            A[pos][pos] = 1. / (size[i][j] + 1) - 1.;

            for (auto pl : adj[i][j]){
                int tpos = pl.first * N + pl.second;
                A[pos][tpos] = 1. / (size[pl.first][pl.second] + 1);
            }
        }
}

void build_II_(vector<map<int,double>> &A){
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j){
            int pos = i * N + j;
            A[pos][pos] = 1. / 2 - 1.;

            for (auto pl : adj[i][j]){
                int tpos = pl.first * N + pl.second;
                A[pos][tpos] = 1. / 2 / (size[pl.first][pl.second]);
            }
        }
}

double solve_brute(int m){
    vector<vector<double>> A(N * N + 1, vector<double>(N * N + 1));
        for (int i = 0; i < N * N + 1; ++i)
        A[N * N][i] = 1.;

    m == 1 ? build_I(A) : build_II(A);

    // for (int i = 0; i < N * N + 1; ++i){
    //     for (int j = 0; j < N * N + 1; ++j){
    //         cout << A[i][j] << " ";
    //         // cout << ".X"[abs(A[i][j])>eps] << " ";
    //         // cout << ".X"[abs(A[i][j])>eps] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    vector<double> X(N * N);
    gauss(A, X);
    double answer = 0;
    for (int i = 1; i <= N; ++i)
        answer += X[i * i - 1];

    // for (auto x : X)
    //     cout << x << " ";
    // cout << endl;

    return answer;
}

void cancel(map<int,double> &a, map<int,double> &b, int col){
    assert(b.count(col));
    double fak = -a[col] / b[col];
    if (fabs(fak) < 1e-15) return;
    for (auto p : b)
        a[p.first] += p.second * fak;
}

void print(vector<map<int,double>> &A){
    for (int i = 0; i < N * N; ++i){
        for (int j = 0; j < N * N; ++j)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

double solve(int m){
    vector<map<int,double>> A(N * N);
    m == 1 ? build_I_(A) : build_II_(A);
    // print(A);

    for (int i = 0; i < N * N; ++i)
        A[N - 1][i] = 1;

    for (int r = 0; r < N; ++r){
        for (int piv = N; piv < N * N + r; ++piv)
            cancel(A[r], A[piv % (N * N)], piv - N);
    }

    // print(A);

    vector<double> X(N * N);
    X.back() = 1.;

    for (int i = N * N - 1, r = N - 1; ~i; --i, r = r ? r - 1 : N * N - 1){
        for (auto it = A[r].rbegin(); ; ++it){
            if (it->first == i){
                X[i] /= it->second;
                break;
            }
            else
                X[i] -= it->second * X[it->first];
        }
    }

    double answer = 0;

    for (int i = 1; i <= N; ++i)
        answer += X[i * i - 1];

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    prec();

    double valueI = solve_brute(1);
    double valueII = solve_brute(2);

    double a = solve(1);
    double b = solve(2);

    cout.precision(12);
    cout << fixed << (valueI + valueII) / 2 << endl;
    cout << fixed << (a + b) / 2 << endl;
    cout << fixed << 0.045874451754 << endl;

    return 0;
}