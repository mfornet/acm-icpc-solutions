#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct matrix{
    int d[3][3];

    matrix(){
        memset(d, 0, sizeof d);
    }

    matrix operator*(const matrix &m) const{
        matrix a;

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                for (int k = 0; k < 3; ++k)
                    a.d[i][j] += d[i][k] * m.d[k][j];

        return a;
    }

    pii eval(int x, int y){
        return pii( d[0][0] * x + d[0][1] * y + d[0][2],
                    d[1][0] * x + d[1][1] * y + d[1][2]);
    }

    void print(){
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j)
                cout << d[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }
};

matrix eye(){
    matrix a;
    for (int i = 0; i < 3; ++i)
        a.d[i][i]  = 1;
    return a;
}

matrix fromarray(vector<int> v){
    matrix a;
    for (int i = 0, t = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            a.d[i][j] = v[t++];
    return a;
}
string T[10] = {
   "v^><^v",
   "^v<>v^",
   "<>^v<>",
   "><v^><",
   "oooooo",
   "xxxxxx",
   "--||--",
   "||--||",
   "////\\\\",
   "\\\\\\\\//"
};

string op =  "<>|-\\/";
string val = "<>^vox|-\\/";

map<char,matrix> oper;

void prec(int n){
    oper['<'] = fromarray({0, -1, n - 1, 1, 0, 0, 0, 0, 1});
    oper['>'] = oper['<'] * oper['<'] * oper['<'];
    oper['-'] = fromarray({-1, 0, n - 1, 0, 1, 0, 0, 0, 1});
    oper['|'] = fromarray({1, 0, 0, 0, -1, n - 1, 0, 0, 1});
    oper['/'] = fromarray({0, -1, n-1, -1, 0, n-1, 0, 0, 1});
    oper['\\'] = fromarray({0, 1, 0, 1, 0, 0, 0, 0, 1});
}

void solve(int n){
    prec(n);

    vector<string> board(n);

    for (int i = 0; i < n; ++i)
    //for (int i = n - 1; i >= 0; --i)
        cin >> board[i];

    string comm;
    string _;

    getline(cin, _);
    getline(cin, comm);

    map<char,int> revpos;
    vector<char> per;

    for (int i = 0; i < 10; ++i)
    {
        revpos[val[i]] = i;
        per.push_back(val[i]);
    }

    matrix fin = eye();

//    fin.print();

    for (int i = 0; i < (int)comm.length(); i += 2){
        int p = 0;

        while (op[p] != comm[i])
            p++;

        fin = oper[op[p]] * fin;
        //fin.print();

        for (int j = 0; j < 10; ++j)
            per[j] = T[revpos[per[j]]][p];

    }

    vector<vector<char>> nboard(n, vector<char>(n));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            pii npos = fin.eval(i,j);
            int x = npos.first, y = npos.second;
            nboard[x][y] = per[revpos[board[i][j]]];
        }
    }
/*
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cout << board[i][j];
        cout << endl;
    }

    cout << endl;
*/
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j)
            cout << nboard[i][j];
        cout << endl;
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n)
        solve(n);

    return 0;
}
