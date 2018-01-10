#include <bits/stdc++.h>

using namespace std;

const int maxn = 500;

char M[ maxn ][ maxn ];

bool A[ maxn ][ maxn ];
bool B[ maxn ][ maxn ];

void compress(int &n, int &m){
    // remove redundant borders
    int bn = n, en = -1, bm = m, em = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (A[i][j]){
                bn = min(bn, i);
                en = max(en, i);
                bm = min(bm, j);
                em = max(em, j);
            }

    for (int i = 0; i <= en - bn; ++i)
        for (int j = 0; j <= em - bm; ++j)
            A[i][j] = A[i + bn][j + bm];

    n = en - bn + 1, m = em - bm + 1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    swap(n, m);

    for (int i = 0; i < n; ++i){
        cin >> M[i];
        for (int j = 0; j < m; ++j)
            A[i][j] = M[i][j] == '#';
    }

    int error = 0;
    int r = -1, c = -1;

    while (min(n, m) > 2){
        memset(B, 0, sizeof B);

        bool fin = true;
        int tr, tc;

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                int x = A[i][j];

                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy){
                        int px = i + dx - 1, py = j + dy - 1;
                        if (0 <= px && px < n && 0 <= py && py < m)
                            x ^= B[px][py];
                    }

                B[i][j] = x;
            }

            if (B[i][m - 2] || B[i][m - 1]){
                fin = false;
                error++;
                tr = i;
                break;
            }
        }

        // second error
        if (error == 2){
            A[r][c] ^= 1;
            break;
        }

        if (fin){
            // reduce ok
            error = 0;
            for (int i = 0; i < n - 2; ++i)
                for (int j = 0; j < m - 2; ++j)
                    A[i][j] = B[i][j];
            n -= 2;
            m -= 2;
            compress(n, m);
            continue;
        }
        else{
            // find and fix error
            fin = true;

            memset(B, 0, sizeof B);

            for (int j = 0; j < m; ++j){
                for (int i = 0; i < n; ++i){
                    int x = A[i][j];

                    for (int dx = -1; dx <= 1; ++dx)
                        for (int dy = -1; dy <= 1; ++dy){
                            int px = i + dx - 1, py = j + dy - 1;
                            if (0 <= px && px < n && 0 <= py && py < m)
                                x ^= B[px][py];
                        }
                    B[i][j] = x;
                }

                if (B[n - 2][j] || B[n - 1][j]){
                    tc = j;
                    fin = false;
                    break;
                }
            }

            assert( !fin );

            r = tr, c = tc;
            A[r][c] ^= 1;
        }
    }

    compress(n, m);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            cout << ".#"[A[i][j]];
        cout << endl;
    }

    return 0;
}