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

    int n;
    int64 s;

    cin >> n >> s;

    vector<int64> pos(n);
    vector<int64> pop(n);

    for (int i = 0; i < n; ++i){
        cin >> pos[i] >> pop[i];
    }

    int p = 0;
    while (p < n && pos[p] < s) p++; // pivot

    int a = 0, b = n - 1;

    int64 LEFT = 0;
    int64 RIGHT = 0;

    vector<int> path;

    while (a < p && b >= p){
        if (pop[a] + LEFT >= pop[b] + RIGHT){
            LEFT = RIGHT + LEFT + pop[b];
            RIGHT = 0;
            path.push_back(+1);
            b--;
        }
        else{
            RIGHT = RIGHT + LEFT + pop[a];
            LEFT = 0;
            path.push_back(-1);
            a++;
        }
    }

    while (a < p) path.push_back(-1), a++;
    while (b >= p) path.push_back(+1), b--;

    int64 answer = 0;

    reverse(path.begin(), path.end());

    for (auto u : path){
        if (u == -1){
            answer += abs(s - pos[--a]);
            s = pos[a];
        }
        else{
            answer += abs(s - pos[++b]);
            s = pos[b];
        }
    }

    assert(a == 0 && b == n - 1);

    cout << answer << endl;

    return 0;
}