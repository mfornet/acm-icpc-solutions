#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 4000000 + 10;

int ls[ maxn ];
int mp[ maxn ];

struct segment_tree{
    struct node{
        int value, lazy;
        bool zero;
    };

    vector<node> data;

    segment_tree(int n){
        data = vector<node>(4 * n);
    }

    node merge(node &u, node &v){
        return {u.value + v.value, 0, 0};
    }

    void push(int p, int l, int r, int b, int m, int e){
        if (data[p].zero){
            data[l].value = data[l].lazy = 0;
            data[r].value = data[r].lazy = 0;
            data[l].zero = data[r].zero = 1;
            data[p].zero = 0;
        }

        if (data[p].lazy){
            int &lz = data[p].lazy;
            data[l].value += lz * (m - b);
            data[l].lazy += lz;
            data[r].value += lz * (e - m);
            data[r].lazy += lz;
            lz = 0;
        }
    }

    void setzero(int p, int b, int e, int x, int y){
        if (x <= b && e <= y){
            data[p].value = 0;
            data[p].lazy = 0;
            data[p].zero = true;
            return;
        }

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r, b, m, e);
        if (x < m) setzero(l, b, m, x, y);
        if (m < y) setzero(r, m, e, x, y);
        data[p] = merge(data[l], data[r]);
    }

    void add(int p, int b, int e, int x, int y, int v){
        if (x <= b && e <= y){
            data[p].value += v * (e - b);
            data[p].lazy += v;
            return;
        }

        int m = (b + e) >> 1, l = p << 1, r = l | 1;
        push(p, l, r, b, m, e);

        if (x < m) add(l, b, m, x, y, v);
        if (m < y) add(r, m, e, x, y, v);
        data[p] = merge(data[l], data[r]);
    }
};

vector<vi> T(vector<vi> &M){
    int n = M.size(), m = M[0].size();
    vector<vi> ans(m, vi(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            ans[j][i] = M[i][j];
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vi> mat(n+1, vi(m+1));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> mat[i][j];

    // if (m > n){
    //     mat = T(mat);
    //     swap(n, m);
    // }

    int64 answer = 0;

    for (int row = n, hm = 0; row; --row){
        ls[row] = 1;

        if (row < n && mat[row][1] > mat[row+1][1]){
            hm = 0;
            mp[row] = 2;
        }
        else
            mp[row] = 1;

        hm++;
        answer += hm;

        // cout << row << " " << 1 << " " << hm << endl;
    }

    int N = m + 1;

    segment_tree st(N);

    for (int col = 2; col <= m; ++col){
        st.setzero(1, 0, N, 0, N);

        for (int row = n; row; --row){
            if (mat[row][col] >= mat[row][col-1]){

            }
            else
                ls[row] = col;

            if (row < n){
                if (ls[row+1] == col || ls[row] == col)
                    mp[row] = mat[row][col] <= mat[row+1][col] ? col : col + 1;
                else{
                    while (mp[row] <= col && mat[row+1][mp[row]] < mat[row][col])
                        mp[row]++;
                }
            }

            st.setzero(1, 0, N, 0, mp[row]);
            st.add(1, 0, N, ls[row], col + 1, +1);
            answer += st.data[1].value;

            // cout << endl;
            // cout << row << " " << col << " " << st.data[1].value << endl;
            // cout << ls[row] << " " << mp[row] << endl;
        }
    }

    cout << answer << endl;

    return 0;
}