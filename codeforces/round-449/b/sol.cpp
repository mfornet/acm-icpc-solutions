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

    int n, m, c;

    cin >> n >> m >> c;

    vector<int> value(n, -1);

    if (c & 1) c++;

    int counter = n;

    for (int i = 0; i < m && counter; ++i){
        int x; cin >> x;
        
        if (2 * x <= c){
            int j = 0;
            while (value[j] != -1 && value[j] <= x)
                    j++;

            if (value[j] == -1)
                counter--;

            value[j] = x;
            cout << j + 1 << endl;
            cout.flush();
        }
        else{
            int j = n - 1;
            while (value[j] != -1 && value[j] >= x)
                j--;

            if (value[j] == -1)
                counter--;

            value[j] = x;
            cout << j + 1 << endl;
            cout.flush();
        }
    }

    return 0;
}
