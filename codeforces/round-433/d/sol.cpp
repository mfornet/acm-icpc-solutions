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

    vector<int> value(n + 1);

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        value[i] += value[i - 1];
    }

    int answer = value[n];

    for (int i = 1; i <= n; ++i){
        answer = min(answer, value[i] + max(0, value[n] - value[i] - value[i] / 10));
    }

    int posit = -1;

    for (int i = 1; i <= n; ++i){
        if (value[i] - value[i - 1] == 1000 && value[i - 1] / 10 >= 1000){
            posit = i;
            break;
        }
    }

    if (posit != -1){
        int p = 0;

        while (p < n && value[p + 1] / 10 <= value[n] - value[p + 1])
            p++;

        answer = min(answer, value[n] - value[p] / 10);

        if (p < n && value[p + 1]  - value[p] == 2000){
            int x = value[p] + 1000;
            int y = value[n] - value[p + 1] + 1000;
            answer = min(answer, x - max(0, y - x / 10));
        }
    }

    cout << answer << endl;

    return 0;
}