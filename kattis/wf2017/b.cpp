#include <bits/stdc++.h>

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct Round{
    int question;
    int passed;
    int final;

    Round(){
        question = passed = final = 0;
    }
};

Round read(){
    Round answer;

    for (int i = 0; i < 3; ++i){
        string s; cin >> s;
        answer.question |= 1 << (s[0] - 'A');
    }

    answer.final = -1;

    for (int i = 0; i < 3; ++i){
        string s; cin >> s;
        answer.passed++;
        
        if (s == "*"){
            answer.final = -2;
            break;
        }
        else if (s != "-"){
            answer.final = s[0] - 'A';
            break;
        }
    }

    return answer;
}

const int A = (1 << 6) - 1;
const int B = ((1 << 6) - 1) << 6;
const int C = ((1 << 9) - 1) << 12;

bool p2(int a){
    return a && ((a & (a - 1)) == 0);
}

bool good(int mask){
    return p2(mask & A) && p2(mask & B) && p2(mask & C);
}

bool check(vector<Round> Rounds, int hand, int player){
    for (int i = 0; i < (int)Rounds.size(); ++i){
        int cPlayer = i & 3; // i % 4

        if (player == cPlayer){
            // if (hand & Rounds[i].question)
            //  return false;
        }
        else{
            if (Rounds[i].final != -1 &&
                ((cPlayer + Rounds[i].passed) & 3) == player){
                
                if (Rounds[i].final == -2){
                    if ( (Rounds[i].question & hand) == 0 )
                        return false;
                }
                else{
                    if ((hand >> Rounds[i].final & 1) == 0)
                        return false;
                }
            }

            if (Rounds[i].passed + (Rounds[i].final == -1) > ((player - cPlayer + 4) & 3))
                if (hand & Rounds[i].question)
                    return false;
        }
    }

    return true;
}

void print(int num){
    for (int i = 0; i < 21; ++i)
        if (num >> i & 1) cout << (char)('A' + i);
    cout << endl;
}

int main(){
#ifdef MARX
    freopen("test.in", "r", stdin);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int nRound;
    cin >> nRound;

    int hand = 0;
    for (int i = 0; i < 5; ++i){
        string s; cin >> s;
        hand |= 1 << (s[0] - 'A');
    }

    vector<Round> Rounds(nRound);

    for (int i = 0; i < nRound; ++i){
        Rounds[i] = read();
    }

    vector<int> p2, p3, p4;

    vector<bool> valid( 1 << 21 );

    for (int i = 0; i < (1 << 21); ++i){
        int size = __builtin_popcount(i);
        if (size < 4 || size > 5) continue;
        if (hand & i) continue;

        if (size == 4){
            if (check(Rounds, i, 2))
                p3.push_back( i );

            if (check(Rounds, i, 3))
                p4.push_back( i );
        }
        else{ // size (5)
            if (check(Rounds, i, 1)){
                valid[ i ] = true;
            }
        }
    }

    int x = -1, y = -1, z = -1;

    int to = (1 << 21) - 1;

    for (int i = 0; i < 6; ++i)
        for (int j = 6; j < 12; ++j)
            for (int k = 12; k < 21; ++k){
                int mask = (1 << i) | (1 << j) | (1 << k);
                if (mask & hand) continue;
                mask |= hand;

                for (auto u : p3) if (!(mask & u)){
                    int masku = mask | u;

                    for (auto v : p4) if (!(masku & v)){
                        int maskv = masku | v;

                        if (valid[ to ^ maskv ]){
                            if (x == -1) x = i;
                            else if (x != i) x = -2;
                            if (y == -1) y = j;
                            else if (y != j) y = -2;
                            if (z == -1) z = k;
                            else if (z != k) z = -2;
                        }
                    }
                }
            }

    cout << (x < 0 ? '?' : (char)('A' + x));
    cout << (y < 0 ? '?' : (char)('A' + y));
    cout << (z < 0 ? '?' : (char)('A' + z));
    cout << endl;
}