#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef complex<int64> point;

int64 cross(point a, point b) { return imag(conj(a) * b); }
int64 dot(point a, point b) { return real(conj(a) * b); }
int64 area2(point a, point b, point c) { return cross(b - a, c - a); }

namespace std
{
    bool operator<(const point &a, const point &b)
    {
        return real(a) < real(b) || (real(a) == real(b) && imag(a) < imag(b));
    }
}

const int64 oo = 0x3f3f3f3f3f3f3f3f;

struct dynamic_hull
{
    dynamic_hull() : hulls() {}

    void add_point(point p)
    {
        hull h;
        h.add_point(p);

        for (hull &_h : hulls)
            if (_h.empty())
            {
                h.swap(_h);
                break;
            }
            else h = merge(h, _h), _h.clear();

        if (!h.empty()) hulls.emplace_back(h);
    }

    int64 max_dot(point p)
    {
        int64 best = -oo;

        for (hull &h : hulls)
            if (!h.empty()) best = max(best, h.max_dot(p));

        return best;
    }

private:
    struct hull : vector<point>
    {
        void add_point(point p)
        {
            for (int s = size(); s > 1; --s)
                if (area2(at(s - 2), at(s - 1), p) < 0) break;
                else pop_back();
            push_back(p);
        }

        int64 max_dot(point p)
        {
            int lo = 0, hi = (int) size() - 1, mid;

            while (lo < hi)
            {
                mid = (lo + hi) / 2;

                if (dot(at(mid), p) <= dot(at(mid + 1), p))
                    lo = mid + 1;
                else hi = mid;
            }

            return dot(at(lo), p);
        }
    };

    static hull merge(const hull &a, const hull &b)
    {
        hull h;
        size_t i = 0, j = 0;

        while (i < a.size() && j < b.size())
            if (a[i] < b[j]) h.add_point(a[i++]);
            else h.add_point(b[j++]);

        while (i < a.size()) h.add_point(a[i++]);

        while (j < b.size()) h.add_point(b[j++]);

        return h;
    }

    vector<hull> hulls;
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    dynamic_hull dh0, dh1;

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;

        point p(x, y);
        dh0.add_point(p);
        dh1.add_point(-p);
    }

    int q; cin >> q;

    while (q-->0){
        string cmd;
        int x, y;
        cin >> cmd >> x >> y;

        point p(x, y);

        if (cmd == "add")
        {
            dh0.add_point(p);
            dh1.add_point(-p);
        }
        else{
            int64 a0 = dh0.max_dot(p);
            int64 a1 = dh1.max_dot(-p);

            cout << max(a0, a1) << endl;
        }
    }

    return 0;
}