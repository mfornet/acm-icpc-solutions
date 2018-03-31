#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

const int maxn = 100000 + 10;
const int mod = 2010;
const int cycle = 12;

int go[ mod ];
int nxt[ mod ][ cycle ];

int value[ maxn ];

struct block{
    bool ok;
    int begin, end;
    int position;

    int sum[ cycle ];

    block(int b, int e) : begin(b), end(e), ok(0), position(0) {}

    int getsum(){
        if (!ok) 
            compute();
        return sum[ position ];
    }

    int geti(int i){
        if (!ok) compute();
        return nxt[ value[i] ][ position ];
    }

    void advance(){
        if (!ok) compute();

        if (++position == cycle)
            position = 2;
    }

    void reset(){
        if (!ok)
            return;

        ok = false;
        for (int i = begin; i < end; ++i)
            value[i] = nxt[ value[i] ][ position ];
        position = 0;
    }

    void compute(){
        ok = true;
        position = 0;

        memset( sum, 0, sizeof sum);

        for (int i = begin; i < end; ++i){
            for (int j = 0; j < cycle; ++j)
                sum[j] += nxt[ value[i] ][j];
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < mod; ++i)
        go[i] = i * i % mod;

    for (int i = 0; i < mod; ++i){
        nxt[i][0] = i;
        for (int j = 1; j < cycle; ++j)
            nxt[i][j] = go[ nxt[i][j - 1] ];
        assert( nxt[i][2] == go[ nxt[i][11] ] );
    }

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
    }

    int size = 350;

    vector<block> B;

    for (int i = 0; i * size < n; ++i)
        B.push_back( block(i * size, min(n, (i + 1) * size) ) );

    int q; cin >> q;
    int step = 0;

    while (q--){
        step++;

        int m, u, v;
        cin >> m >> u >> v;
        u--;

        if (m == 1){ // update
            for (auto &b : B){
                int pb = max(u, b.begin);
                int pe = min(v, b.end);

                if (pb == b.begin && b.end == pe)
                    b.advance();
                else if (pe - pb > 0){
                    b.reset();

                    for (int i = pb; i < pe; ++i){
                        value[i] = go[ value[i] ];
                    }
                }
            }
        }
        else{ // query
            int answer = 0;
            int banswer = 0;

            for (auto &b : B){
                int pb = max(u, b.begin);
                int pe = min(v, b.end);

                if (pb == b.begin && b.end == pe){
                    answer += b.getsum();
                }
                else if( pe - pb > 0){
                    for (int i = pb; i < pe; ++i){
                        answer += b.geti(i);
                    }
                }
            }

            cout << answer << endl;
        }
    }

    return 0;
}
