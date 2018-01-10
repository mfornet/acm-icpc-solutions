#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct corner{
    int x, y, idx;

    bool operator<(const corner &c) const{
        if (x != c.x) return x > c.x;
        return y > c.y;
    }
};

struct segment{
    int line, beg, end;

    bool operator<(const segment &seg) const{
        if (line != seg.line) return line < seg.line;
        return beg < seg.beg;
    }
};

#define HORIZONTAL 1
#define VERTICAL 2

struct event{
    int mode;
    int a, b, c; 
    // HORIZONTAL (x, y, +-1)
    // VERTICAL (x, y1, y2)

    bool operator<(const event &e) const{
        if (a != e.a) return a < e.a;
        
        if (mode != e.mode){
            if (mode == HORIZONTAL)
                return c == -1;
            else
                return e.c == +1;
        }
        else if (mode == HORIZONTAL && c != e.c)
            return c < e.c;

        return false;
    }
};

void error(){
    cout << "syntax error" << endl;
    exit(0);
}

bool check(vector<segment> &S){
    sort(S.begin(), S.end());
    int n = (int)S.size();
    for (int i = 0, j; i < n; i = j){
        int last = -1;
        for (j = i; j < n && S[j].line == S[i].line; ++j){
            if (S[j].beg <= last) return false;
            last = S[j].end;
        }
    }
    return true;
}

bool intersect(vector<segment> hor, vector<segment> ver){
    if ( !check(hor) || !check(ver) )
        return true;

    vector<event> E;

    for (auto h : hor){
        if (h.beg < h.end){
            E.push_back({HORIZONTAL, h.beg, h.line, +1});
            E.push_back({HORIZONTAL, h.end, h.line, -1});
        }
    }

    for (auto v : ver){
        E.push_back({VERTICAL, v.line, v.beg, v.end});
    }

    sort(E.begin(), E.end());

    set<int> open;

    for (auto e : E){
        if (e.mode == HORIZONTAL){
            if (e.c == +1) open.insert( e.b );
            else open.erase( e.b );
        }
        else{
            auto it = open.lower_bound(e.b);
            if (it != open.end() && *it <= e.c)
                return true;
        }
    }

    return false;
}

int main(){
#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<corner> U(n), L(n);

    for (int _ = 0; _ < 2; ++_){
        for (int i = 1; i <= n; ++i){
            cin >> U[i-1].x >> U[i-1].y;
            U[i-1].idx = i;
        }
        U.swap(L);
    }

    sort(U.begin(), U.end());
    sort(L.begin(), L.end());

    vector<int> mate(n);
    set<pii> lowercorner;

    for (int i = 0, j = 0; i < n; ++i){
        while (j < n && L[j].x >= U[i].x){
            lowercorner.insert({L[j].y, L[j].idx});
            j++;
        }

        auto it = lowercorner.lower_bound({U[i].y, -1});
        if (it == lowercorner.end()) error();

        mate[ U[i].idx - 1 ] = it->second;
        lowercorner.erase( it );
    }

    auto idxcmp = [](corner &a, corner &b){
        return a.idx < b.idx;
    };

    sort(U.begin(), U.end(), idxcmp);
    sort(L.begin(), L.end(), idxcmp);

    vector<segment> hor, ver;

    for (int i = 0; i < n; ++i){
        int j = mate[i] - 1;

        hor.push_back( {U[i].y, U[i].x, L[j].x} );
        if (L[j].y != U[i].y) hor.push_back( {L[j].y, U[i].x, L[j].x} );

        ver.push_back( {U[i].x, U[i].y, L[j].y} );
        if (L[j].x != U[i].x) ver.push_back( {L[j].x, U[i].y, L[j].y} );
    }

    if (intersect(hor, ver))
        error();

    for (int i = 0; i < n; ++i)
        cout << mate[i] << endl;
}