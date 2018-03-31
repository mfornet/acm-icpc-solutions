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

    vector<double> value(n);
    double sum = 0;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        sum += value[i];
    }

    for (int i = 0; i < n; ++i){
        value[i] /= sum;
    }

    vector<double> answer(1 << n);

    for (int i = (1 << n) - 2; i >= 0; --i){
        double A = 1., B = 0.;

        for (int j = 0; j < n; ++j){
            if (i >> j & 1) B += value[j];
            else A += value[j] * answer[i | (1 << j)];
        }

        answer[i] = A / (1. - B);
    }

    cout.precision(17);
    cout << fixed << answer[0] << endl;

    return 0;
}