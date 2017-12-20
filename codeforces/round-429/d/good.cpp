#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 300000 + 10;
const int logmaxn = 20;
const int K = 5;

typedef vector<pii> info;

info data[maxn][logmaxn];

vector<pii> merge(info A, info B){
    // sort(B.begin(), B.end(), cmp);

    pii tmp[2 * K];
    int tot = 0;

    for (auto a : A)
        tmp[tot++] = a;

    for (auto b : B){
        bool ok = false;
        for (int i = 0; i < tot && !ok; ++i)
            if (tmp[i].first == b.first){
                tmp[i].second += b.second;
                ok = true;
            }
        if (!ok) tmp[tot++] = b;
    }

    while (tot >= K){
        int b = tot - K, e = tot;
        int mv = oo;

        for (int i = b; i < e; ++i)
            mv = min(mv, tmp[i].second);

        tot -= K;
        for (int i = b; i < e; ++i){
            tmp[i].second -= mv;
            if (tmp[i].second)
                tmp[tot++] = tmp[i];
        }
    }

    return vector<pii>(tmp, tmp + tot);
}

void build(vector<int> &value){
    int n = (int)value.size();
    for (int i = n - 1; i >= 0; --i){
        data[i][0] = {{value[i], 1}};
        for (int j = 1; i + (1 << j) <= n; ++j)
            data[i][j] = merge(data[i][j-1], data[i + (1<<(j-1))][j-1]);
    }
}

info query(int u, int v){
    info answer;

    int d = v - u;
    for (int i = 0; d; ++i){
        if (d >> i & 1){
            answer = merge(answer, data[u][i]);
            u += 1 << i;
            d ^= 1 << i;
        }
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> value(n);
    vector<vi> pos(n + 1);

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        pos[value[i]].push_back(i);
    }

    build(value);

    while (q--){
        int u, v, k;
        cin >> u >> v >> k;
        u--;
        int f = (v - u) / k;

        info cand = query(u, v);

        int answer = oo;

        for (auto _c : cand){
            int c = _c.first;

            int freq = lower_bound(pos[c].begin(), pos[c].end(), v)
                     - lower_bound(pos[c].begin(), pos[c].end(), u);
            if (freq > f)
                answer = min(answer, c);
        }

        cout << (answer == oo ? -1 : answer) << endl;
    }

    return 0;
}