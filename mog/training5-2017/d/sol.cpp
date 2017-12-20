#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef complex<double> point;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;
const int magic = 1000;
const double pi = acos(-1);

struct circle{
    point c;
    double r;
};

double dot(point a, point b){
    return real(conj(a) * b);
}

double get(double r0, double r1, double d){
    double lo = 0, hi = pi / 2;

    //cout << r0 << " " << r1 << " " << d << " " << pi << " " << pi / 2 << " " << pi / 4 << endl;

    for (int _ = 0; _ < magic; ++_){
        double theta = (lo + hi) / 2;
        double dd = dot(point(0, d), polar(1., theta)); 
        //cout << theta << " " << dd << endl;
        //cout << abs(polar(1., theta)) << endl;
        (dd > (r0 + r1) ? hi : lo) = theta;
    }

    return (lo + hi) / 2;
}

pair<double,double> intersect(circle &a, circle &b){
    double d = abs(a.c - b.c); 

    point dir = b.c - a.c;
    double x = get(a.r, b.r, d);
    double t = atan2(imag(dir), real(dir));

    //cout << x << " " << t << endl;

    double o = x + t;
    double c = pi - x + t;

    return {o, c};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
/*
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            cout << i << " " << j << " " << atan2(i, j) << endl;

    exit(0);
*/

    int n; cin >> n;

    vector<circle> C(n);

    for (int i = 0; i < n; ++i){
        double x, y, r;
        cin >> x >> y >> r;
        C[i] = {point(x, y), r};
    }

    vector<pair<double,int>> events;
    int open = 0;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < i; ++j){
            auto x = intersect(C[i], C[j]);

            while (x.first < 0){
                x.first += pi;
                x.second += pi;
            }

            x.first -= pi;
            x.second -= pi;

            if (x.second > -eps){
                open++;
                events.push_back({x.second, -1});
            }


            for (int t = 0; t < 4; ++t){
                x.first += pi;
                x.second += pi;

                events.push_back({x.first, +1});
                events.push_back({x.second, -1});
            }
        }
    }

    sort(events.begin(), events.end());

    double last = 0;
    double ans = 0;

    int top = n * (n - 1) / 2;

    //cout << top << endl;

    for (auto e : events){
        //cout << open << " " << e.first << " " << e.second << endl;
        if (open == top){
            ans = max(ans, e.first - last);
        }
        open += e.second;
        last = e.first;
    }

    cout.precision(10);
    cout << fixed << ans << endl;

    return 0;
}
