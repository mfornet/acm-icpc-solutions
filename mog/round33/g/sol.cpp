#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int64 func(int64 x){
    return x * (x - 1) * (x - 2) / 6;
}

int64 T[2000];

int64 solve(int a, int b){
    assert(a * b <= 1024);

    int64 answer = T[a * b];

    for (int dx = 0; dx < a; ++dx)
        for (int dy = 0; dy < b; ++dy){
            if (dx == 0 && dy == 0) continue;
            int g = __gcd(dx, dy); if (g > 1) continue;

            for (int x = 0; x < a; x++)
                for (int y = 0; y < b; ++y){
                    if (dx <= x && dy <= y) 
                        continue;

                    int lx = dx == 0 ? oo : (a - (x+1)) / dx;
                    int ly = dy == 0 ? oo : (b - (y+1)) / dy;
                    int l = min(lx, ly) + 1;

                    if (dx && dy)
                        answer -= 2 * T[l];
                    else
                        answer -= T[l];
                }
        }

    assert(answer >= 0);

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 2000; ++i)
        T[i] = func(i);

    int t; cin >> t;

    while (t-->0){
        int n, m;
        cin >> n >> m;
        cout << solve(n, m) << endl;
    }


    return 0;
}