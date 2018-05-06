#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define double long double

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-12;
const int maxn = 100000 + 10;

struct segment{
    double b, e;

    segment(double b=0, double e=0) : b(b), e(e){}

    bool operator<(const segment &s) const{
        return b < s.b;
    }
};

double solve(){
    int n;
    double x;

    cin >> n >> x;

    double p = 0;

    vector<segment> holder;

    for (int i = 0; i < n; ++i){
        double w, h;
        cin >> w >> h;

        double b = 2 * min(w, h);
        double e = 2 * sqrt(w * w + h * h);

        p += 2 * (w + h);

        holder.push_back({b, e});
    }

    x -= p;

    assert(x >= 0);

    vector<segment> segs(1);

    for (int i = 0; i < n; ++i){
        double b = holder[i].b, e = holder[i].e;

        int t = (int)segs.size();

        for (int j = 0; j < t; ++j)
            segs.push_back({segs[j].b + b, segs[j].e + e});

        sort(segs.begin(), segs.end());

        vector<segment> nseg;

        segment last;

        for (auto s : segs){
            if (s.b <= last.e)
                last.e = max(last.e, s.e);
            else{
                nseg.push_back(last);
                last = s;
            }

            if (last.e >= x)
                break;
        }

        nseg.push_back(last);
        segs.swap(nseg);
    }

    if (segs.back().e < x){
        return segs.back().e + p;
    }
    else if (segs.back().b <= x && x <= segs.back().e)
        return x + p;
    else{
        segs.pop_back();
        return segs.back().e + p;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cout.precision(17);

    int t; cin >> t;

    for (int tc = 1; tc <= t; ++tc)
        cout << "Case #" << tc << ": " << fixed << solve() << endl;

    return 0;
}