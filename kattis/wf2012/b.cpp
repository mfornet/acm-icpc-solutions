#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout<<#x<<"="<<x<<endl;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;
const int MAGIC = 10000;
const double MPI = 3.141592653589793;

double simpson(double a, double b, int n, double (*f)(double))
{
    double h = (b - a) / ( 2.0 * n);
    double fa = f(a), nfa;
    double ans = 0;

    for (int i = 0; i < n; ++i)
    {
        nfa = f(a + 2.0 * h);
        ans += (fa + 4.0 * f(a + h) + nfa);
        fa = nfa;
        a += 2.0 * h;
    }

    ans = ans * h / 3.0;

    return ans;
}

double pol[20];
int degree;

double pol_eval(double v){
    double ans = 0;
    for (int i = degree; i >= 0; --i)
        ans = ans * v + pol[i];
    return ans * ans;
}

double integral(double a, double b){
    return simpson(a, b, MAGIC, pol_eval) * MPI;
}

double binary_search(double b, double lo, double hi, double rvol)
{
    for (int i = 0; i < 100; ++i)
    {
        if (lo + EPS > hi){
            break;
        }
        double mid = (lo + hi) / 2;
        double vol = integral(b, mid);
        if (vol < rvol) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tc = 1;
    cout.precision(2);
    while (cin >> degree)
    {
        for (int i = 0; i <= degree; ++i)
            cin >> pol[i];

        double le, ri, inc;
        cin >> le >> ri >> inc;

        cout << "Case " << tc++ << ": ";

        double tot_vol = integral(le, ri);

        cout << fixed << tot_vol << endl;

        bool ok = false;
        for (int i = 1; i <= 8; ++i){
            double cur_vol = inc * i;
            if (cur_vol > tot_vol + EPS)
                break;

            double pos = binary_search(le, le, ri, cur_vol);
            if (!ok) ok = true;
            else cout << " ";
            cout << pos - le;
        }
        if (!ok) cout << "insufficient volume";
        cout << endl;
    }

    return 0;
}

