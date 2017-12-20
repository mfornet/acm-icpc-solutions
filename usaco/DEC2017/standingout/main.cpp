#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct SuffixArray
{
    int n;
    vector<int> sa, rank, lcp;

    SuffixArray(vector<int> &s) :
        n(s.size() + 1), sa(n), rank(n), lcp(n)
    {
        vector<int> _sa(n), bucket(n);

        iota(sa.rbegin(), sa.rend(), 0);
        sort(next(sa.begin()), sa.end(),
            [&](int i, int j) { return s[i] < s[j]; });

        for (int i = 1, j = 0; i < n; ++i)
        {
            rank[sa[i]] = rank[sa[i - 1]] +
                          (i == 1 || s[sa[i - 1]] < s[sa[i]]);
            if (rank[sa[i]] != rank[sa[i - 1]])
                bucket[++j] = i;
        }

        for (int len = 1; len <= n; len += len)
        {
            for (int i = 0, j; i < n; ++i)
            {
                if ((j = sa[i] - len) < 0) j += n;
                _sa[bucket[rank[j]]++] = j;
            }

            sa[_sa[bucket[0] = 0]] = 0;

            for (int i = 1, j = 0; i < n; ++i)
            {
                if (rank[_sa[i]] != rank[_sa[i - 1]] ||
                    rank[_sa[i] + len] != rank[_sa[i - 1] + len])
                    bucket[++j] = i;

                sa[_sa[i]] = j;
            }

            copy(sa.begin(), sa.end(), rank.begin());
            sa.swap(_sa);

            if (rank[sa[n - 1]] == n - 1) break;
        }

        for (int i = 0, j = rank[lcp[0] = 0], k = 0; i < n - 1; ++i, ++k)
            while (k >= 0 && s[i] != s[sa[j - 1] + k])
                lcp[j] = k--, j = rank[sa[j] + 1];
    }
};

int main(){
    freopen("standingout.in", "r", stdin);
    freopen("standingout.out", "w", stdout);

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, size = 0;
    cin >> n;

    vector<int> len(n);

    vector<int> word;
    int flag = 27;

    for (int i = 0; i < n; ++i){
        string cur; cin >> cur;
        len[i] = cur.length();
        size += len[i];

        for (auto x : cur)
            word.push_back(x - 'a' + 1);
        word.push_back(flag++);
    }

    vector<int> who(size + n), suff(size + n);

    for (int i = 0, idx = 0; i < n; ++i){
        for (int j = 0; j <= len[i]; ++j){
            who[idx] = i;
            suff[idx] = len[i] - j;
            idx++;
        }
    }

    SuffixArray S(word);

    // S.sa.push_back(size);
    // S.lcp.push_back(0);
    // who.push_back(-1);

    // debug area

    // for (auto x : word)
    //     cout << x << " ";
    // cout << endl;

    // for (int i = 0; i <= size; ++i)
    //     cout << S.sa[i] << " " << S.rank[i] << " " << S.lcp[i] << endl;

    // end debug

    deque<pii> minq;

    vector<int64> answer(n);

    for (int i = 1, j = 1; i <= size; ++i){
        while (who[S.sa[i]] == who[S.sa[j]]){
            j++;

            while (!minq.empty() && minq.back().second >= S.lcp[j])
                minq.pop_back();

            minq.push_back({j, S.lcp[j]});
        }

        if (minq.front().first == i)
            minq.pop_front();

        int cur_answer = max(0, suff[S.sa[i]] - max(S.lcp[i], minq.front().second));

        // int cur_answer = min(minq.front().second, max(0, suff[S.sa[i]]-S.lcp[i]));

        // cout << i << " " << j << " :: "
        //      << S.sa[i] << " " << suff[S.sa[i]] << " " << S.lcp[i] << " " << minq.front().second << " :: "
        //      << cur_answer << endl;

        answer[who[S.sa[i]]] += cur_answer;
    }

    for (int i = 0; i < n; ++i)
        cout << answer[i] << endl;

    return 0;
}