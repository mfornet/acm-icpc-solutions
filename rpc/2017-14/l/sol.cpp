#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

string board[26];
int freq[26];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;

    while (cin >> n){
        for (int i = 0; i < n; ++i)
            cin >> board[i];

        memset(freq, 0, sizeof freq);

        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n; ++j){
                int v = board[i][j] - 'A';
                freq[v]++;
            }
        }

        int A = -1;

        for (int i = 0; i < 26; ++i){
            if (freq[i] + 1 == n){
                assert(A == -1);
                A = i;
            }
        }

        int R = -1, C = -1;

        for (int i = 0; i < n; ++i){
            bool row = true, col = true;

            for (int j = 0; j < n; ++j){
                if (board[i][j] - 'A' == A)
                    row = false;
                if (board[j][i] - 'A' == A)
                    col = false;
            }

            if (row){
                assert(R == -1);
                R = i;
            }

            if (col){
                assert(C == -1);
                C = i;
            }
        }

        cout << R + 1 << " " << C + 1 << " " << (char)('A' + A) << endl;
    }

    return 0;
}
