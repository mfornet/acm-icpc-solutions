#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

vector<string> S;
vector<int> evolPath[2];
vector<int> head;

int last(int mode = -1){
    if (mode == -1) return head[head.size() - 1];
    return evolPath[mode][evolPath[mode].size() - 1];
}

void push(int n){
    for (int i = 0; i < SZ(head); ++i)
        evolPath[n].push_back(head[i]);
    head.clear();
}

bool subs(string &a, string &b){
    int i = 0, pnt = 0;
    for (;i < SZ(b) && pnt < SZ(a); ++i){
        if (a[pnt] == b[i]) ++pnt;
    }
    return pnt == SZ(a);
}

bool compare(string a, string b){
    return a.length() < b.length();
}

void impossible(){
    cout << "impossible" << endl;
    exit(0);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string top; cin >> top;

    S = vector<string>(n + 1);
    S[0] = "";
    for (int i = 1; i <= n; ++i)
        cin >> S[i];

    sort(S.begin(), S.end(), compare);

    evolPath[0].push_back(0);
    evolPath[1].push_back(0);


    for (int i = 1; i <= n; ++i){
        if (!head.empty()){
            if (subs(S[last()], S[i]))
                head.push_back(i);
            else{
                if (subs(S[last(0)], S[i])){
                    push(1);
                    evolPath[0].push_back(i);
                }
                else if (subs(S[last(1)], S[i])){
                    push(0);
                    evolPath[1].push_back(i);
                }
                else{
                    impossible();
                }
            }
        }
        else{
            int mask = 0;
            if (subs(S[last(0)], S[i])) mask |= 1;
            if (subs(S[last(1)], S[i])) mask |= 2;

            if (mask == 0) impossible();
            else if (mask == 1) evolPath[0].push_back(i);
            else if (mask == 2) evolPath[1].push_back(i);
            else head.push_back(i);
        }
    }

    push(0);
    if (!subs(S[last(0)], top) || !subs(S[last(1)], top))
        impossible();

    cout << SZ(evolPath[0]) - 1 << " " << SZ(evolPath[1]) - 1 << endl;

    for (int j = 0; j < 2; ++j)
        for (int i = 1; i < SZ(evolPath[j]); ++i)
            cout << S[evolPath[j][i]] << endl;

    return 0;
}