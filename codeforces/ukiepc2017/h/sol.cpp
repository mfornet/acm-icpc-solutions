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

    int sep, p;

    cin >> sep >> p;

    vector<int> dist(p);

    for (int i = 0; i < p; ++i)
        cin >> dist[i];

    int n; cin >> n;

    vector<pii> hiker(n);
    vector<bool> queued(n);

    for (int i = 0; i < n; ++i){
        cin >> hiker[i].first >> hiker[i].second;
        hiker[i].second--;
    }

    function<bool(int)> islegal = [&](int u){
        int db = oo, df = oo;

        if (u + 1 < n)
            df = dist[hiker[u + 1].second] - dist[hiker[u].second + 1];

        if (u > 0)
            db = dist[hiker[u].second + 1] - dist[hiker[u - 1].second];

        if (u > 0 && db > sep)
            return false;

        if (u + 1 < n && hiker[u + 1].second != p - 1 && df < min(hiker[u].first, hiker[u + 1].first))
            return false;

        return true;
    };

    vector<int> q;
    int pnt = 0;

    for (int i = 0; i < n; ++i){
        if (islegal(i)){
            queued[i] = true;
            q.push_back(i);
            hiker[i].second++;
        }
    }

    while (pnt < q.size()){
        int u = q[pnt++];

        queued[u] = false;

        if (hiker[u].second < p - 1 && islegal(u)){
            queued[u] = true;
            q.push_back(u);
            hiker[u].second++;
        }

        if (u + 1 < n && hiker[u + 1].second < p - 1 &&
            !queued[u + 1] && islegal(u + 1)){
            queued[u + 1] = true;
            q.push_back(u + 1);
            hiker[u + 1].second++;
        }

        if (u > 0 && !queued[u - 1] && islegal(u - 1)){
            queued[u - 1] = true;
            q.push_back(u - 1);
            hiker[u - 1].second++;
        }
    }

    if (hiker[0].second == p - 1){
        for (int i = 0; i < (int)q.size(); ++i)
            cout << q[i] + 1 << " \n"[i + 1 == q.size()];
    }
    else{
        cout << "impossible" << endl;
    }


    return 0;
}
