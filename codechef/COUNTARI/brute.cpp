#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int value[ maxn ];
int freq[ maxn ];

int get(int p, int freq[maxn]){
    return 0 <= p && p < maxn ? freq[p] : 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    for (int i = 0; i < n; ++i){
        cin >> value[i];
        freq[ value[i] ]++;
    }

    int64 answer = 0;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
                if (value[j] - value[i] == value[k] - value[j]){
                    answer++;
                    cout << i << " " << j << " " << k << endl;
                    cout << value[i] << " " << value[j] << " " << value[k] << endl;
                    cout << endl;
                }

    cout << answer << endl;
    return 0;

    for (int i = 0; i < n; ++i){
        freq[ value[i] ]--;
        for (int j = 0; j < i; ++j){
            answer += get(2 * value[i] - value[j], freq);
            // cout << value[j] << " " << value[i] << " " << 2 * value[i] - value[j] << " :: " << get(2 * value[i] - value[j], freq) << endl;
        }
    }

    cout << answer << endl;

    return 0;
}
