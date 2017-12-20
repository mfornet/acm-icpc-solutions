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

    vector<vi> rem(n);

    for (int i = 0; i < n; ++i){
        int v; cin >> v;

        vector<vi> nrem(n);

        for (int j = 0; j < n; ++j){
            int x = (j + v) % n;

            if (!rem[j].empty() && rem[x].empty())
            {
                nrem[x] = rem[j];
                nrem[x].push_back(v);
            }
        }

        if (rem[v % n].empty()){
            rem[v % n].push_back(v);
        }

        for (int j = 0; j < n; ++j)
            if (!nrem[j].empty())
                rem[j] = nrem[j];

        if (!rem[0].empty()){
            cout << rem[0].size() << endl;
            for (auto u : rem[0])
                cout << u << endl;
            return 0;
        }
    }

    cout << "esto no funciona" << endl;

    return 0;
}