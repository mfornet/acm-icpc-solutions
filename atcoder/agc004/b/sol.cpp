#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 2000 + 10;

int value[2 * maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        value[i + n] = value[i];
    }

    int64 answer = 1LL << 60;

    for (int i = 0; i < n; ++i){
        deque<pii> dq;
        int64 curanswer = 1LL * i * x;

        for (int j = 0; j < 2 * n; ++j){
            while (!dq.empty() && dq.back().first >= value[j])
                dq.pop_back();
            dq.push_back(pii(value[j], j));

            while (dq.front().second < j - i) dq.pop_front();
            if (j >= n) curanswer += dq.front().first;
        }

        answer = min(answer, curanswer);
    }

    cout << answer << endl;

    return 0;
}
