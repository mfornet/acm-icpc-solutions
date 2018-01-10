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
const int MAGIC = 200;
const double PI = acos(-1);

struct circ{
    double x, y, z, r;

    circ(){
        x = y = z = r = 0;
    }

    circ(double X, double Y, double Z, double R){
        x = X / 1000, y = Y / 1000, z = Z / 1000;
        r = R / 1000;
    }

    double getVol(double pos){
        pos = pos - (z - r);
        pos = max(pos, 0.0);
        pos = min(pos, 2 * r);
        return PI * (r * pos * pos - pos * pos * pos / 3);
    }
};

int n, s;
vector<circ> H;

double eval(double pos){
    double curVol = pos * 100.0 * 100.0;
    for (int i = 0; i < n; ++i)
        curVol -= H[i].getVol(pos);
    return curVol;
}

double getPos(double vol){
    double lo = 0, hi = 100.0;
    for (int i = 0; i < MAGIC; ++i){
        double mid = (lo + hi) / 2;
        if (eval(mid) < vol) lo = mid;
        else hi = mid;
    }
    return (lo + hi) / 2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> s;

    H = vector<circ>(n);

    double volum = pow(100.0, 3);

    for (int i = 0; i < n; ++i){
        double x, y, z, r;
        cin >> r >> x >> y >> z;
        H[i] = circ(x, y, z, r);

        volum -= H[i].getVol(100.0);
    }

    volum /= s;

    vector<double> cutPos(s + 1);

    for (int i = 1; i <= s; ++i){
        cutPos[i] = getPos(volum * i);
        cout.precision(9);
        cout << fixed << cutPos[i] - cutPos[i - 1] << endl;
    }

    return 0;
}

