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
int children[maxn];
int solution;

vi solve(int s, int d, int p=-1){
    vector<int> sum(d + 1, 0);
    vector<int> mnn(d + 1, 0);

    children[s] = 1;
    int size = 1;

    for (auto u : adj[s]) if (u != p){
        auto cur = solve(u, d, s);
        children[s] += children[u];

        size = max(size, (int)cur.size()+1);

        sum[0] += cur[0] + 1;

        for (int i = 0; i < min(d, (int)cur.size()); ++i){
            sum[i + 1] += cur[i]; 
            int h = i + 1;
            int hc = d - h;

            if (hc < h)
                mnn[h] = min(mnn[h], cur[i] - (hc ? cur[hc - 1] : cur[0] + 1));
        }
    }

    size = min(size, d+1);
    vector<int> answer(size);

    for (int i = 0; i < size; ++i){
        if (2 * i <= d) answer[i] = sum[i];
        else answer[i] = sum[d - i] + mnn[i];
        if (i) answer[i] = min(answer[i], answer[i-1]);
    }
/*
    cout << "solve: " << s << endl;
    for (int i = 0; i < size; ++i)
        cout << answer[i] << " ";
    cout << endl;
    for (int i = 0; i < size; ++i)
        cout << sum[i] << " ";
    cout << endl;
    for (int i = 0; i < size; ++i)
        cout << mnn[i] << " ";
    cout << endl;
*/

    solution = min(solution, answer.back() - children[s]);

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, d;
    cin >> n >> d;

    for (int i = 0; i < n-1; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    solution = oo;

    solve(1, d);

    cout << solution + n << endl;

    return 0;
}
