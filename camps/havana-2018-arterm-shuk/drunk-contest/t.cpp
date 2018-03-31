#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int64 oo = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    vector<pair<int64,bool>> answer(10);



    for (int i = 0; i < n; ++i){
        string s; cin >> s;
        answer[s[0] - 'a'].second = true;
        int64 ten = 1;

        for (int j = (int)s.length() - 1; j >= 0; --j){
            answer[s[j] - 'a'].first += ten;
            ten *= 10;
        }
    }

    sort(answer.begin(), answer.end());

    int j = 9;

    while (j >= 0 && answer[j].second)
        j--;

    if (j == -1){
        cout << -1 << endl;
        return 0;
    }

    int64 ans = 0;

    for (int i = 9, n = 1; i >= 0; --i){
        if (i == j) continue;
        ans += answer[i].first * (n++);
    }

    cout << ans << endl;

    return 0;
}