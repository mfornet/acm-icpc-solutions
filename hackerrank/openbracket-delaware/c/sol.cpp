#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 500000 + 10;

int bit[ maxn ];

void update(int idx, int v){
    while (idx < maxn){
        bit[idx] += v;
        idx += idx & -idx;
    }
}

int query(int idx){
    int answer = 0;
    while (idx){
        answer += bit[idx];
        idx -= idx & -idx;
    }
    return answer;
}

int P[maxn];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<pii> V(n);
    for (int i = 1; i <= n; ++i){
        cin >> V[i-1].first;
        V[i-1].second = i;
    }

    sort(V.begin(), V.end());

    for (int i = 0; i < n; ++i){
        P[V[i].second-1] = i + 1;
    }

    int64 answer = 0;
    int64 slide = 0;

    for (int i = 0; i < m; ++i){
        slide += i - query(P[i]);
        update(P[i], +1);
    }

    answer += slide;

    for (int i = m; i < n; ++i){
        update(P[i-m], -1);
        slide += m - 1 - query(P[i]);
        slide -= query(P[i-m]);
        update(P[i], +1);
        answer += slide;
    }

    cout << answer << endl;

    return 0;
}