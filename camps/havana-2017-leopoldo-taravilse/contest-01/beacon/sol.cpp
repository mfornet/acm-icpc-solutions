#include <bits/stdc++.h>

using namespace std; 
#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 20; 

int val[ maxn ];
int64 dp[ 10 ][ 20 ][2];

int64 calc(int dig, int len, int mode)
{
    int64 &ans = dp[dig][len][mode];
    if (ans != -1) return ans;

    ans = 0;
    if (len == 1) return ans = 1;
    
    int b, e;
    if (mode == 0) //decrease
        b = 1, e = dig - 1;
    else //increase
        b = dig + 1, e = 9;

    for (int i = b; i <= e; ++i)
        ans += calc(i, len - 1, mode ^ 1);

    return ans;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; cin >> n;

    int64 answer = 0;
    memset( dp, -1, sizeof dp );

    for (int i = 0; i < n; ++i)
        cin >> val[i];

    for (int i = 1; i < val[0]; ++i){
        for (int l = 3; l <= 18; ++l){
            answer += calc(i, l, 0) + calc(i, l, 1);
        }
    }

    for (int i = 1; i < val[1]; ++i){
        if (i == val[0]) continue;

        for (int l = 2; l <= 17; ++l){
            if (i < val[0])
                answer += calc(i, l, 1);
            else
                answer += calc(i, l, 0);
        }
    }

    int s = val[1] < val[0];

    for (int i = 2; i < n; ++i){
        answer++;

        int b, e;
        if (s == 1) b = val[i - 1] + 1, e = 9;
        else b = 1, val[i - 1] - 1;

        for (int j = 1; j < val[i]; ++j){
            if (b <= j && j <= e)
                for (int l = 1; l <= 18 - i; ++l)
                    answer += calc(j, l, s ^ 1);
        }

        s ^= 1;
    }

    cout << answer << endl;

    return 0;
}
