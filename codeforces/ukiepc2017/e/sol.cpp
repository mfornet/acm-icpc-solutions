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

    int n, m;
    cin >> n >> m;

    vector<pii> value(n);
    vector<int> answer(n);

    for (int i = 0; i < n; ++i){
        int x; cin >> x;
        value[i] = {x, i};
    }

    sort(value.begin(), value.end());

    vector<pii> building(m);

    for (int i = 0; i < m; ++i)
        cin >> building[i].first;

    for (int i = 0; i < m; ++i)
        cin >> building[i].second;

    for (int i = n - 1; i >= 0; --i){
        int idx = -1;

        for (int j = 0; j < m; ++j){
            if (building[j].first >= value[i].first){
                if (idx == -1 || building[j].second < building[idx].second)
                    idx = j;
            }
        }

        if (idx == -1){
            cout << "impossible" << endl;
            return 0;
        }

        answer[value[i].second] = idx + 1;
        building[idx].first = -1;
    }

    for (int i = 0; i < n; ++i)
        cout << answer[i] << " ";
    cout << endl;

    return 0;
}
