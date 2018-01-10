#include <bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double eps = 1e-9;
const int oo = 0x3f3f3f3f;
const int maxn = 100000 + 10;

pair<int,int> ask(vector<int> &S){
    cout << "Q " << S.size();
    for (auto x : S)
        cout << " " << x;
    cout << endl;
    cout.flush();

    int a; cin >> a;

    return {a, S.size() - a};
}

bool iscomplete(vector<int> &X, vector<int> &Y, int k){
    cout << "Q " << X.size() + k;

    for (auto v : X) cout << " " << v;
    for (int i = 0; i < k; ++i) cout << " " << Y[i];
    cout << endl; cout.flush();

    int a; cin >> a;
    int b = (X.size() + k - a);

    return min(a, b) == 0;
}

bool othercomplete(vector<int> &A, int k, int b){
    cout << "Q " << k + 1 << " " << b;

    for (int i = 0; i < k; ++i)
        cout << " " << A[i];
    cout << endl;
    cout.flush();

    int a; cin >> a;
    int b = (k + 1 - a);

    return min(a, b) == 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<int> A, B;

    for (int i = 0; ; ++i){
        vector<int> S0, S1;

        for (int j = 0; j < n; ++j)
            ((j >> i & 1) ? S0 : S1).push_back(j);

        pii s0 = ask(S0);

        if (min(s0.first, s0.second) != 0)
            continue;

        pii s1 = ask(S1);

        if (min(s1.first, s1.second) != 0)
            continue;

        A = S0;
        B = S1;

        if (s0.first == 0)
            A.swap(B);
        break;
    }

    int lo = 0, hi = B.size();

    while (lo + 1 < hi){
        int m = (lo + hi) / 2;

        if (iscomplete(A, B, m))
            lo = m;
        else
            hi = m;
    }

    int b = B[lo];

    lo = 0, hi = A.size();

    while (lo + 1 < hi){
        int m = (lo + hi) / 2;

        if (othercomplete(A, m, b))
            lo = m;
        else
            hi = m;
    }

    int a = A[lo];

    cout << "A " << a << " " << b << endl;

    return 0;
}