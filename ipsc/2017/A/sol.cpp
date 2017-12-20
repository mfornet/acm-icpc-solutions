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

    int t; cin >> t;

    while (t--){
    	int a, b;
    	cin >> a >> b;

    	vector<pii> answer;

    	for (int i = 0; i < min(a, b); ++i){
    		answer.push_back(pii(i,i));
    	}

    	for (int i = 1; i < b - a; i += 2){
    		answer.push_back(pii(a - 1, a + i));
    	}

    	for (int i = 1; i < a - b; i += 2){
    		answer.push_back(pii(b + i, b - 1));
    	}

    	if (answer.back() != pii(a - 1, b - 1))
    		answer.push_back(pii(a - 1, b - 1));

    	cout << answer.size() << endl;
    	for (auto p : answer)
    		cout << p.first << " " << p.second << endl;
    }

    return 0;
}
