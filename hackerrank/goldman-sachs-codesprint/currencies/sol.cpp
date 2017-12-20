#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int mod = 1000000007;

struct currency{
    double _log;
    int mod_value;

    currency operator*(const currency &c) const{
        return {_log + c._log, int(1LL * mod_value * c.mod_value % mod)};
    }

    bool operator<(const currency &c)const{
        return _log < c._log;
    }
};

typedef vector<vector<currency>> matrix;

const currency zero = {-1e9, 0};
const currency one  = {0., 1};

matrix merge(matrix &a, matrix &b){
    int n = (int)a.size();
    matrix c(n, vector<currency>(n, zero));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                c[i][j] = max(c[i][j], a[i][k] * b[k][j]);

    return c;
}


matrix solve(int n, matrix &exchange){
    int size = (int)exchange.size();

    matrix answer(size, vector<currency>(size, zero));
    for (int i = 0; i < size; ++i)
        answer[i][i] = one;

    while (n){
        if (n & 1)
            answer = merge(answer, exchange);
        exchange = merge(exchange, exchange);
        n >>= 1;
    }

    return answer;

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x, s, f, m;
    cin >> n >> x >> s >> f >> m;

    matrix exchange(n, vector<currency>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j){
            int v; cin >> v;
            if (v == 0) exchange[i][j] = zero;
            else        exchange[i][j] = {log(v), v};
        }

    exchange = solve(m, exchange);

    int answer = 1LL * x * exchange[s][f].mod_value % mod;

    cout << answer << endl;

    return 0;
}