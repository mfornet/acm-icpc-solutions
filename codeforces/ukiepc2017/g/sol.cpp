#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void print(vector<int> A){
    for (int i = 0; i < 6; ++i){
        if (i == 0) cout << "(";
        else if (i == 3) cout << ") (";
        else cout << " ";
        cout << A[i];
    }

    cout << ")" << endl;
}

void go(vector<int> A, vector<int> B){
    while (true){
        vector<int> x, y;

        for (int i = 0; i < 3; ++i){
            if (A[i] != B[i]) x.push_back(i);
            if (A[i + 3] != B[i + 3]) y.push_back(i + 3);
        }

        if (x.empty() && y.empty()) break;

        if (!x.empty()){
            int u = x[rand() % x.size()];
            if (B[u] > A[u]) A[u]++;
            else A[u]--;
        }

        if (!y.empty()){
            int u = y[rand() % y.size()];
            if (B[u] > A[u]) A[u]++;
            else A[u]--;
        }

        print(A);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vector<int> start(6), fin(6), tmp(6);

    int delta = 30;

    cin >> start[0] >> start[1] >> start[2] >> fin[0] >> fin[1] >> fin[2];
    cin >> start[3] >> start[4] >> start[5] >> fin[3] >> fin[4] >> fin[5];

    for (int i = 0; i < 6; ++i)
        tmp[i] = fin[i] + rand() % (2 * delta) - delta;

    print(start);

    go(start, tmp);
    go(tmp, fin);

    return 0;
}
