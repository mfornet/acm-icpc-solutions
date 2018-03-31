#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;


pii go(vi &rings, vector<vector<pii>> &memo, int B, int S, int COLOR){
    if (memo[B][S] != pii(-1, -1))
        return memo[B][S];

    assert(rings[B] >= S);

    set<int> target;

    int E = B;

    vector<bool> seen(COLOR + 1);

    while (E < (int)rings.size() && rings[E] >= S)
        seen[rings[E++]] = true;

    for (int i = S; i <= COLOR; ++i){
        if (!seen[i]) continue;

        int cur = 0;
        for (int j = B; j < E; ){
            if (rings[j] > i){
                pii T = go(rings, memo, j, i + 1, COLOR);
                cur ^= T.first;
                j = T.second;
                assert(j <= E);
            }
            else
                j++;
        }

        target.insert(cur);
    }

    int grundy = 0;
    while (target.find(grundy) != target.end())
        grundy++;

    memo[B][S] = {grundy, E};
    return memo[B][S];
}

pair<int,map<int,int>> solve(vi rings){
    int C = *max_element(rings.begin(), rings.end());
    vector<vector<pii>> memo(rings.size(), vector<pii>(C + 1, pii(-1, -1)));
    vector<int> seen(C + 1);

    for (int i = 0; i < (int)rings.size(); ++i){
        if (!seen[rings[i]])
            seen[rings[i]] = i + 1;
    }

    set<int> target;
    map<int,int> color_grundy;

    for (int i = 1; i <= C; ++i){
        if (!seen[i]) 
            continue;

        int cur = 0;

        for (int j = 0; j < (int)rings.size(); ){
            if (rings[j] > i){
                pii T = go(rings, memo, j, i + 1, C);
                cur ^= T.first;
                j = T.second;
            }
            else
                j++;
        }

        color_grundy[i] = cur;
        target.insert(cur);
    }

    int grundy = 0;
    while (target.find(grundy) != target.end())
        grundy++;

    return {grundy, color_grundy};
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; 
    cin >> t;

    int g = 0;

    vector<vi> chains;
    vector<map<int,int>> color_grundy;
    vector<int> cur_grundy;

    while (t-->0){
        int n; cin >> n;
        assert( 1 <= n && n <= 100 );
        vector<int> s(n);

        for (int i = 0; i < n; ++i){
            cin >> s[i];
            assert(1 <= s[i] && s[i] <= 100);
        }

        auto ans = solve(s);
        g ^= ans.first;

        cur_grundy.push_back(ans.first);
        chains.push_back(s);
        color_grundy.push_back(ans.second);
    }

    if (g == 0){
        cout << "S" << endl;
    }
    else{
        cout << "G" << endl;

        for (int i = 0; i < (int)chains.size(); ++i){
            for (int j = 0; j < (int)chains[i].size(); ++j){
                int ng = color_grundy[i][chains[i][j]];

                if ((g ^ ng ^ cur_grundy[i]) == 0){
                    cout << i + 1 << " " << j + 1 << endl;
                    exit(0);
                }
            }
        }

        assert(false);
    }

    return 0;
}
