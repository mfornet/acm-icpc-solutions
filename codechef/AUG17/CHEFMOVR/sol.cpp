#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int64,int64> pii;
typedef vector<int64> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

pii check(vector<int64> &value){
    int64 sum = 0, answer = 0;

    for (auto v : value) sum += v;
    int n = (int)value.size();

    if (sum % n) return pii(-1, -1);
    sum /= n;

    int64 side = 0;

    for (int i = 0; i < n; ++i){
        side += value[i];
        answer += abs(side - sum * (i + 1));
    }

    return pii(answer, sum);
}

int64 solve(){
    int n, d;
    cin >> n >> d;

    vector<vi> value(d);

    for (int i = 0; i < n; ++i){
        int64 v; cin >> v;
        value[i % d].push_back(v);
    }

    int64 answer = 0;
    int64 mean = -1;

    for (int i = 0; i < d; ++i){
        pii cur = check(value[i]);
        if (cur.first == -1) return -1;
        answer += cur.first;

        if (mean == -1) mean = cur.second;
        if (cur.second != mean) return -1;
    }

    return answer;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--)
        cout << solve() << endl;

    return 0;
}