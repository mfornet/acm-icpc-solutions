#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

typedef vector<string> lcd;


int freq[7][21];

string line;
lcd hour[ 60 * 24 ];

string DIG[7] = {
    ".XX. .... .XX. .XX. .... .XX. .XX. .XX. .XX. .XX.",
    "X..X ...X ...X ...X X..X X... X... ...X X..X X..X",
    "X..X ...X ...X ...X X..X X... X... ...X X..X X..X",
    ".... .... .XX. .XX. .XX. .XX. .XX. .... .XX. .XX.",
    "X..X ...X X... ...X ...X ...X X..X ...X X..X ...X",
    "X..X ...X X... ...X ...X ...X X..X ...X X..X ...X",
    ".XX. .... .XX. .XX. .... .XX. .XX. .... .XX. .XX.",
};

void put(lcd &l, int p, int dig){
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 4; ++j)
            l[i][j + p] = DIG[i][5 * dig + j];
}

void generate(int t){
    int h = t / 60;
    int m = t % 60;
    hour[t] = vector<string>(7, line);


    if (h / 10) put(hour[t], 0, h / 10);
    put(hour[t], 5, h % 10);
    put(hour[t], 12, m / 10);
    put(hour[t], 17, m % 10);

    hour[t][2][10] = 'X';
    hour[t][4][10] = 'X';

}

bool one[7][21];
bool zero[7][21];
bool ok[7][21];

bool check(int t, vector<lcd> &V){
    vector<vector<bool>> _one(7, vector<bool>(21));
    vector<vector<bool>> _zero(7, vector<bool>(21));
    vector<vector<int>> _ok(7, vector<int>(21));

    for (auto v : V){
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 21; ++j){
                if (v[i][j] != hour[t][i][j] && freq[i][j] == 1)
                    return false;

                if (v[i][j] != hour[t][i][j]){
                    if (freq[i][j] == 2)
                        _one[i][j] = true;
                    else
                        _zero[i][j] = true;
                }
                else{
                    _ok[i][j]++;
                }
            }
        t = (t + 1) % (24 * 60);
    }

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 21; ++j){
            one[i][j] |= _one[i][j];
            zero[i][j] |= _zero[i][j];
            ok[i][j] |= _ok[i][j] == (int)V.size();
        }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

#ifdef MARX
    freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
#endif

    line = "";
    for (int i = 0; i < 21; ++i)
        line += ".";

    int n; cin >> n;

    vector<lcd> V( n );

    for (int i = 0; i < n; ++i){
        lcd a(7);
        
        for (int j = 0; j < 7; ++j){
            cin >> a[j];

            for (int k = 0; k < 21; ++k)
                freq[j][k] += a[j][k] == 'X';
        }

        V[i] = a;
    }

    for (int i = 0; i < 7; ++i){
        for (int j = 0; j < 21; ++j){
            freq[i][j] = freq[i][j] == 0 ? 0 : freq[i][j] == n ? 2 : 1;
            // cout << freq[i][j] << " ";
        }
        // cout << endl;
    }

    int total = 0;

    for (int i = 0; i < 60 * 24; ++i)
        generate(i);

    for (int i = 0; i < 60 * 24; ++i){
        if (check(i, V)){
            total++;
            // cout << i << endl;
            int h = i / 60, m = i % 60;
            // cout << h / 10 << " " << h % 10 << " : " << m / 10 << " " << m % 10 << endl;
        }
    }

    lcd mscreen = hour[0];
    put(mscreen, 0, 8);
    put(mscreen, 5, 8);
    put(mscreen, 12, 8);
    put(mscreen, 17, 8);

    if (total == 0){
        cout << "impossible" << endl;
    }
    else{
        for (int i = 0; i < 7; ++i){
            for (int j = 0; j < 21; ++j){
                if (mscreen[i][j] == '.'){
                    cout << '.';
                    continue;
                }
                // cout << ok[i][j];
                if (freq[i][j] == 1) cout << "W";
                else if (ok[i][j] && (one[i][j] || zero[i][j])) cout << "?";
                else if (one[i][j]) cout << "1";
                else if (zero[i][j]) cout << "0";
                else cout << "?";
            }
            cout << endl;
        }
    }

    return 0;
}