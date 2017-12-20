#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

void solve(){
    int n, m; // candidates, company
    cin >> n >> m;

    vector<int> min_salary(n);
    for (int i = 0; i < n; ++i)
        cin >> min_salary[i];

    vector<int> salary(m), maxjobs(m);
    for (int i = 0; i < m; ++i)
        cin >> salary[i] >> maxjobs[i];

    vector<vector<bool>> qual(n, vector<bool>(m));
    for (int i = 0; i < n; ++i){
        string s; cin >> s;

        for (int j = 0; j < m; ++j)
            qual[i][j] = s[j] == '1';
    }

    int empolyees = 0;
    int64 total_salary = 0;
    int unlucky_companies = 0;

    vector<int> totaljobs(m);
    for (int i = 0; i < n; ++i){
        int best = -1;

        for (int j = 0; j < m; ++j){
            if (totaljobs[j] < maxjobs[j] &&
                qual[i][j] &&
                (best == -1 || salary[j] > salary[best])
                )

                best = j;
        }

        if (best != -1 && salary[best] >= min_salary[i]){
            empolyees++;
            total_salary += salary[best];
            totaljobs[best]++;
        }
    }

    for (int i = 0; i < m; ++i)
        unlucky_companies += totaljobs[i] == 0;

    cout << empolyees << " " << total_salary << " " << unlucky_companies << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--)
        solve();

    return 0;
}