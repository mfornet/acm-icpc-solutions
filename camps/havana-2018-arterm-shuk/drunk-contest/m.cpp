#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int64> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vi __minus__(vi a, vi &b){
    for (int i = 0; i < 3; ++i)
        a[i] -= b[i];
    return a;
}

vi __add__(vi a, vi &b){
    for (int i = 0; i < 3; ++i)
        a[i] += b[i];
    return a;
}

int64 dot(vi &a, vi &b){
    int64 x = 0;
    for (int i = 0; i < 3; ++i)
        x += 1LL * a[i] * b[i];
    return x;
}

void print(vi a){
    cout << endl;
    for (auto x : a)
        cout << x << " ";
    cout << endl; cout.flush();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<vi> cube(8, vi(3));
    vector<vi> ccube(8, vi(3));

    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 3; ++j)
            cin >> cube[i][j];

        sort(cube[i].begin(), cube[i].end());
        ccube[i] = cube[i];
    }

    auto check = [&](vi &X, vi &Y, vi &Z){
        int total = 0;
        int taken = 0;
        vector<vi> answer(8);

        for (int i = 0; i < 8; ++i){
            vi B = cube[0];

            if (i & 1) B = __add__(B, X);
            if (i & 2) B = __add__(B, Y);
            if (i & 4) B = __add__(B, Z);

            auto L = B;
            sort(B.begin(), B.end());

            bool ok = false;

            for (int j = 0; j < 8; ++j){
                if (taken >> j & 1) continue;

                if (B == ccube[j]){
                    taken |= 1 << j;
                    total++;
                    answer[j] = L;
                    ok = true;
                    break;
                }
            }

            if (!ok) return;
        }

        assert(total == 8);
        assert(__builtin_popcount(taken) == 8);

        cout << "YES" << endl;
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 3; ++j)
                cout << answer[i][j] << " \n"[j + 1 == 3];
            sort(answer[i].begin(), answer[i].end());
            assert(answer[i] == ccube[i]);
            assert(ccube[i][0] <= ccube[i][1] && ccube[i][1] <= ccube[i][2]);
        }
        exit(0);
    };

    for (int i = 1; i < 8; ++i){
        sort(cube[i].begin(), cube[i].end());
        do{
            auto X = __minus__(cube[i], cube[0]);
            int64 sx = dot(X, X); if (sx == 0) continue;

            for (int j = i + 1; j < 8; ++j){
                sort(cube[j].begin(), cube[j].end());
                do{
                    auto Y = __minus__(cube[j], cube[0]);
                    int64 sy = dot(Y, Y); if (sy != sx) continue;
                    if (dot(X, Y)) continue;

                    for (int k = j + 1; k < 8; ++k){
                        sort(cube[k].begin(), cube[k].end());
                        do{
                            auto Z = __minus__(cube[k], cube[0]);
                            int64 sz = dot(Z, Z); if (sz != sx) continue;
                            if (dot(X, Z)) continue;
                            if (dot(Y, Z)) continue;

                            check(X, Y, Z);
                        } while (next_permutation(cube[k].begin(), cube[k].end()));
                    }
                } while (next_permutation(cube[j].begin(), cube[j].end()));
            }
        } while (next_permutation(cube[i].begin(), cube[i].end()));
    }        

    cout << "NO" << endl;

    return 0;   
}