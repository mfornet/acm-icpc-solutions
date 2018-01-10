#include <bits/stdc++.h>

using namespace std;

vector<int> overlap(string &s){
    int n = (int)s.length(); 

    vector<int> pi(n + 1, 0);
    pi[0] = -1;

    for (int i = 2; i <= n; ++i){
        int f = pi[i - 1];
        while (f >= 0 && s[f] != s[i - 1])
            f = pi[f];
        pi[i] = f + 1;
    }

    vector<int> answer;

    int pos = n;

    do{
        pos = pi[ pos ];
        answer.push_back( pos );
    } while(pos);

    return answer;
}

int main(){
    int n, s;
    cin >> n >> s;

    vector<string> word(s);
    vector<vector<int>> overlap_seq(s);
    vector<int> order(s);

    for (int i = 0; i < s; ++i){
        cin >> word[i];
        overlap_seq[i] = overlap( word[i] );

        int l = (int)word[i].length();

        while (!overlap_seq[i].empty() && overlap_seq[i].back() < 2 * l - n)
            overlap_seq[i].pop_back();
    }

    iota( order.begin(), order.end(), 0 );
    sort( order.begin(), order.end(), [&](int a, int b){
            return make_pair(overlap_seq[a], a) < make_pair(overlap_seq[b], b);
    });

    for (int i = 0; i < s; ++i)
        cout << word[ order[i] ] << endl;
}

