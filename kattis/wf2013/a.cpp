#include <bits/stdc++.h>
#include <ext/algorithm>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#ifdef HOME
#define DB(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl << flush;
#else
#define DB(x)
#endif

#define all(c) (c).begin(),(c).end()
#define endl '\n'
#define mp make_pair

typedef long long i64;
typedef long double ld;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;

bool ady[52][52];
bool mk[52];

int nodeValue(string s){
    if (s[0] == '0') return -1;
    return s[0] - 'A' + 26 * (s[1] == '-');
}

int neg(int v){
    if (v < 26) return v + 26;
    return v - 26;
}

void print(int v){
    cout << (char)('A' + v % 26);
    if (v < 26) cout << "+";
    else cout << "-";
    cout << " ";
}

bool dfs(int s, int e, bool mode){
    if (mode) memset(mk, 0, sizeof mk);

    mk[s] = true;
    for (int i = 0; i < 52; ++i){
        if (!ady[s][i]) continue;

        if (i == e) return true;

        if (!mk[neg(i)]){
            if (dfs(neg(i), e, false)) return true;
        }

    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    while (cin >> n){
        memset(ady, 0, sizeof ady);
        for (int i = 0; i < n; ++i){
            string s;
            cin >> s;
            vector<int> val(4);
            for (int j = 0; j < 4; ++j){
                val[j] = nodeValue(s.substr(2 * j, 2));
                if (val[j] == -1) continue;
                for (int k = 0; k < j; ++k)
                {
                    if (val[k] == -1) continue;
                    ady[val[j]][val[k]] = ady[val[k]][val[j]] = true;
                }
            }
        }

        bool bounded = true;
        for (int i = 0; i < 52 && bounded; ++i){
            for (int j = 0; j < 52 && bounded; ++j){
                if (ady[i][j] && dfs(neg(i), neg(j), true)){
//                  print(i); print(j);
//                  cout << endl << flush;
                    bounded = false;
                }
            }
        }

        if (bounded) cout << "bounded" << endl;
        else cout << "unbounded" << endl;
        cout.flush();
    }

    return 0;
}

