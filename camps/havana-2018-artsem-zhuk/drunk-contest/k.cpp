#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> value(n);
    vector<vi> who(n);
    vector<int> pnt(n);

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        
        if (value[i] >= n){
            cout << "Impossible" << endl;
            exit(0);
        }

        who[value[i]].push_back(i + 1);
    }

    vector<int> answer;

    for (int i = 0, j = 0; i < n; ++i){
        while (j >= 0 && pnt[j] == who[j].size()){
            j -= 3;
        }

        if (j < 0){
            cout << "Impossible" << endl;
            exit(0);
        }

        answer.push_back(who[j][pnt[j]++]);
        j++;
    }

    cout << "Possible" << endl;

    for (auto x : answer)
        cout << x << " ";
    cout << endl;


    return 0;
}