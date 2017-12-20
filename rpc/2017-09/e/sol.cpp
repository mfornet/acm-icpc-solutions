#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const string vowel = "aeiou";

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    getline(cin, s);

    while (getline(cin, s)){
        for (auto c : s){
            cout << c;
            if (vowel.find(c) < 5)
                cout << "p" << c;
        }
        cout << endl;
    }

    return 0;
}
