#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(int n){
    vector<pii> value(n);

    for (int i = 0; i < n; ++i)
        cin >> value[i].first >> value[i].second;

    int c; cin >> c;

    for (int x = 0; x < c; ++x){
        int answer = 0;

        string cmp, agr;
        int v;

        cin >> cmp >> agr >> v;

        deque<pii> mindq, maxdq;
        int cumsum = 0;
        int total = 0;

        auto predicate = [&](int cv){
            if (total == 0) return false;

            int tocomp;

            if (agr == "min")
                tocomp = mindq.front().second - cv;
            else if (agr == "max")
                tocomp = maxdq.front().second - cv;
            else
                tocomp = cumsum - total * cv;

            if (cmp == "gt")
                return tocomp < 0;
            else
                return tocomp > 0;
        };

        for (int i = 0, j = 0; i < n; ++i){
             while (value[j].first + v < value[i].first){
                cumsum -= value[j].second;
                total--;

                if (mindq.front() == value[j])
                    mindq.pop_front();

                if (maxdq.front() == value[j])
                    maxdq.pop_front();

                j++;
            }

           if (predicate(value[i].second))
                answer++;

           cumsum += value[i].second;
            total++;

            while (!mindq.empty() && value[i].second <= mindq.back().second)
                mindq.pop_back();
            mindq.push_back(value[i]);

            while (!maxdq.empty() && value[i].second >= maxdq.back().second)
                maxdq.pop_back();
            maxdq.push_back(value[i]);
        }

        cout << answer << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; 

    while (cin >> n)
        solve(n);

    return 0;
}
