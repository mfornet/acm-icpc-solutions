#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100;

string S[ 100 ];
pair<int,int> transition[ 100 ][ 100 ][ 100 ];
bool ok[ 100 ][ 100 ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n1, n2;
    cin >> n1 >> n2;

    assert(1 <= n1 && n1 <= 20);
    assert(1 <= n2 && n2 <= 20);

    int n = n1 + n2;

    for (int i = 0; i < n; ++i){
        cin >> S[ i ];
        assert( S[i].length() <= 40 );
    }

    for (int i = 0; i < n; ++i){
        int len = (int)S[ i ].length();
        for (int j = 0; j < len; ++j)

            for (int k = 0; k < n; ++k){
                int u = j, v = 0;
                bool ok = true;

                while (u < len && v < (int)S[k].length()){
                    if (S[i][u] != S[k][v]){
                        ok = false;
                        break;
                    }
                    u++;
                    v++;
                }

                if (!ok) 
                    transition[i][j][k] = pii(-2, -2);
                else{
                    if (u == len && v == (int)S[k].length())
                        transition[i][j][k] = pii(-1, -1);
                    else if (u == len)
                        transition[i][j][k] = pii(k, v);
                    else
                        transition[i][j][k] = pii(i, u);
                }
            }
    }

    queue<pii> q;
    for (int i = 0; i < n; ++i){
        ok[i][0] = true;
        q.push( pii(i,0) );
    }

    while (!q.empty()){
        pii cur = q.front();
        q.pop();

        int b = 0, e = n1;
        if (cur.first < e)
            b = n1, e = n2 + n1;

        for (int i = b; i < e; ++i){
            pii nxt = transition[ cur.first ][ cur.second ][ i ];
            if (nxt.first == -2) 
                continue;

            if (nxt.first == -1){
                cout << "S" << endl;
                exit(0);
            }

            int a = nxt.first, b = nxt.second;
            if (!ok[a][b]){
                ok[a][b] = true;
                q.push( pii(a, b) );
            }
        }
    }
        
    cout << "N" << endl;

    return 0;
}
