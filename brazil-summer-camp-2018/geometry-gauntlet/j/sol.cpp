#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef complex<double> point;

struct circle{
    point center;
    double r;

    bool contain(point &p){
        return abs(center - p) < r + eps;
    }
};

point three_point_circle(point a, point b, point c)
{
    point x = 1.0 / conj(b - a), y = 1.0 / conj(c - a);
    return (y - x) / (conj(x) * y - x * conj(y)) + a;
}

circle min_circle(vector<point> &cloud, int a, int b){
    point center = (cloud[a] + cloud[b]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < b; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        center = three_point_circle( cloud[a], cloud[b], cloud[i] );
        rat = abs(center - cloud[a]);
        C = {center, rat};
    }
    return C;
}

circle min_circle(vector<point> &cloud, int a){
    point center = (cloud[a] + cloud[0]) / double(2.);
    double rat = abs(center - cloud[a]);
    circle C = {center, rat};

    for (int i = 0; i < a; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, a, i);
    }

    return C;
}

circle min_circle(vector<point> cloud){
    random_shuffle(cloud.begin(), cloud.end());

    int n = (int)cloud.size();

    for (int i = 1; i < n; ++i){
        int u = rand() % i;
        swap(cloud[u], cloud[i]);
    }

    point center = (cloud[0] + cloud[1]) / double(2.);
    double rat = abs(center - cloud[0]);
    circle C = {center, rat};
    for (int i = 2; i < n; ++i){
        point x = cloud[i];
        if (C.contain(x)) continue;
        C = min_circle(cloud, i);
    }
    return C;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    srand(10);

    int n; cin >> n;

    vector<point> V(n);

    for (int i = 0; i < n; ++i){
        double x, y;
        cin >> x >> y;
        V[i] = point(x, y);
    }

    cout.precision(17);
    auto c = min_circle(V);

    cout << fixed << c.center.real() << endl;
    cout << fixed << c.center.imag() << endl;
    cout << fixed << c.r << endl;

    return 0;
}
