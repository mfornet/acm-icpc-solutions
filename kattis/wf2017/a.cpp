#include <bits/stdc++.h>

using namespace std;

#define PREV(x) ((x) == 0 ? n - 1 : (x) - 1)
#define NEXT(x) ((x) + 1 == n ? 0 : (x) + 1)

typedef long long int64;
typedef complex<int64> point;

int64 cross(point a, point b){
    return imag(conj(a) * b);
}

int side(point a, point b, point c){
    int64 value = cross(b - a, c - a);
    return value < 0 ? -1 : value > 0;
}

bool check(point a, point b, point c, point x){
    a -= b; c -= b; x -= b;
    if (cross(c, a) > 0)
        return cross(c, x) >= 0 && cross(x, a) >= 0;
    else
        return !(cross(a, x) > 0 && cross(x, c) > 0);
}

complex<double> d(complex<int64> x){
    return complex<double>(real(x), imag(x));
}

double dist(complex<double> a, complex<double> b){
    return abs(a - b);
}

struct line{
    complex<double> p, q;
};

complex<double> crosspoint(const line &l, const line &m){
    double A = imag( conj(l.q - l.p) * (m.q - m.p) );
    double B = imag( conj(l.q - l.p) * (l.q - m.p) );
    return m.p + B / A * (m.q - m.p);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<point> island(n);

    for (int i = 0; i < n; ++i){
        int64 x, y;
        cin >> x >> y;
        island[i] = point(x, y);
    }

    double answer = 0;

    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            point A = island[i], B = island[j];
            point PA = island[ PREV(i) ], NA = island[ NEXT(i) ];

            bool good = check(PA, A, NA, B);
            double aExtend = 1e9;
            double bExtend = 1e9;

            auto decrease = [&](complex<double> xPoint){
                double aDist = dist( d(A), xPoint ), bDist = dist( d(B), xPoint );
                if (aDist < bDist) aExtend = min(aExtend, aDist);
                else               bExtend = min(bExtend, bDist);
            };

            for (int k = 0; k < n && good; ++k){
                point U = island[k], V = island[ NEXT(k) ];
                int uSide = side(A, B, U), vSide = side(A, B, V);
                int aSide = side(U, V, A), bSide = side(U, V, B);

                if (uSide * vSide == -1){
                    // different sides

                    assert(aSide * bSide != 0);

                    if (aSide * bSide == -1)
                        good = false;
                    else{
                        auto xPoint = crosspoint({d(A), d(B)}, {d(U), d(V)});
                        decrease( xPoint );
                    }
                }
                else if (uSide == 0 && vSide == 0){
                    point T = island[ PREV(k) ], W = island[ NEXT(NEXT(k)) ];
                    // exhaustive

                    if (min(k, NEXT(k)) == i && max(k, NEXT(k)) == j){ // same line
                        if (A == U){
                            if (side(V, W, U) == +1) bExtend = 0;
                            if (side(U, V, T) == +1) aExtend = 0;
                        }
                        else{
                            if (side(V, W, U) == +1) aExtend = 0;
                            if (side(U, V, T) == +1) bExtend = 0;
                        }
                    }
                    else{
                        int tSide = side(A, B, T), wSide = side(A, B, W);

                        if (tSide * wSide == -1){
                            double auDist = dist(d(A), d(U)), avDist = dist(d(A), d(V));
                            double buDist = dist(d(B), d(U)), bvDist = dist(d(B), d(V));


                            if (buDist < auDist)
                                bExtend = min(bExtend, max(buDist, bvDist));
                            else
                                aExtend = min(aExtend, max(auDist, avDist));
                        }
                    }
                }
                else if (uSide == 0){
                    if (aSide * bSide == -1)
                        good = false;
                    else{
                        point T = island[ PREV(k) ];
                        int tSide = side(A, B, T);
                        if (tSide * vSide == -1)
                            decrease( d(U) );
                    }
                }
                else if (vSide == 0){
                    if (aSide * bSide == -1)
                        good = false;
                    else{
                        point W = island[ NEXT(NEXT(k)) ];
                        int wSide = side(A, B, W);
                        if (uSide * wSide == -1)
                            decrease( d(V) );
                    }
                }
                else{ // both U and V are on the same side
                    // nothing to do :)
                }
            }

            if (!good) continue;

            double curDist = aExtend + bExtend + dist( d(A), d(B) );
            answer = max(answer, curDist);
        }
    }

    cout.precision(9);
    cout << fixed << answer << endl;

    return 0;
}