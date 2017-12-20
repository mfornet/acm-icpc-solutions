#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100;

int pos[ maxn ][2];
int P = 5, Q = 7;

vector<pii>  go[ maxn ][ 2 ];
vector<pii> rev[ maxn ][ 2 ];
int degree[ maxn ][2];

void add_edge(int a, int b, int p){
    degree[a][p]++;
    //go[a][p].push_back({b, p^1});
    rev[b][p^1].push_back({a,p});
}

string s(int v){
    return v == 1 ? "+" : (v == -1 ? "-" : "o");
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
#endif

    for (int i = 1; i < maxn; ++i){
        // euclides
        if (i < P)
            add_edge(i, i + P, 0);
        else
            for (int j = i - P; j >= 0; j -= P)
                add_edge(i, j, 0);

        if (i < Q)
            add_edge(i, i + Q, 1);
        else
            for (int j = i - Q; j >= 0; j -= Q)
                add_edge(i, j, 1);
    }

    queue<pii> st;
    pos[0][0] = pos[0][1] = -1;

    st.push({0,0});
    st.push({0,1});

    while (!st.empty()){
        auto cur = st.front(); st.pop();
        int s = cur.first, p = cur.second;
        int v = pos[s][p];

        for (auto u : rev[s][p]){
            if (pos[u.first][u.second] != 0)
                continue;

            if (v == -1){
                pos[u.first][u.second] = +1;
                st.push(u);
            }
            else{
                if (!--degree[u.first][u.second])
                {
                    pos[u.first][u.second] = -1;
                    st.push(u);
                }
            }
        }
    }

    for (int i = 0; i < maxn; ++i)
        cout << i << " " << s(pos[i][0]) << " " << s(pos[i][1]) << endl;

    return 0;
}
