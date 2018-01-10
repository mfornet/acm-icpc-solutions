#include <bits/stdc++.h>
#include <ext/algorithm>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#ifdef HOME
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl << flush;
#else
#define DB(x)
#endif

#define all(c) (c).begin(),(c).end()
#define endl '\n'
#define mp make_pair

typedef unsigned long long int64;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = (1LLU << 63) + (1LLU << 62);

map<int64, int64> M;

vector<int64> primes;
int64 pascal[65][65];

void dfs(int pi, int e, int s, int64 k, int64 f)
{
    if (pi == 63) return;

    if (s == 0){
        if (!M.insert({f, k}).second)
            M[f] = min(M[f], k);
        return;
    }

    int64 val = k;
    for (int i = 0; i <= min(e, s); ++i){

        if (i){
            if (val <= oo / primes[pi]) val *= primes[pi];
            else break;
        }

        if (pascal[s][i] <= oo / f){
            dfs(pi + 1, i, s - i, val, f * pascal[s][i]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 2; primes.size() < 63; ++i){
        bool prime  = true;
        for (int j = 2; j * j <= i && prime; ++j)
            if (i % j == 0) prime = false;
        if (prime){
            primes.push_back(i);
        }
    }

    for (int i = 0; i < 65; ++i){
        for (int j = 0; j <= i; ++j){
            if (!j || (i == j)) pascal[i][j] = 1;
            else{
                pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
            }
        }
    }

    for (int i = 1; i <= 63; ++i)
        dfs(0, 63, i, 1, 1);

    int64 n;

    while (cin >> n){
        assert(M.count(n));
        cout << n << " " << M[n] << endl << flush;
    }

    return 0;
}

