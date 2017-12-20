#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

vi adj[maxn];
int value[maxn];

bool open[maxn];

int64 dfs(int s, int p=-1){
    if (open[ value[s] ])
        return 0;

    int64 answer = 1;
    open[value[s]] = true;
    for (auto u : adj[s]){
        if (u == p) continue;
        answer += dfs(u, s);
    }
    open[value[s]] = false;
    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 2; i <= n; ++i){
        int p; cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }

    for (int i = 1; i <= n; ++i)
        cin >> value[i];

    int64 answer = 0;

    for (int i = 1; i <= n; ++i)
        answer += dfs(i);

    cout << answer << endl;

    return 0;
}