#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int maxp = 400;
const int mod = 1000000007;

int fix(int v){
    int answer = 1;
    for (int i = 2; i * i <= v; ++i){
        if (v % i == 0){
            int f = 0;
            while (v % i == 0){
                v /= i;
                f ^= 1;
            }
            if (f) answer *= i;
        }
    }

    if (v > 1) answer *= v;
    return answer;
}

int fak[maxp], ifak[maxp];

int modpow(int a, int n){
    int c = 1;
    while (n){
        if (n & 1)
            c = 1LL * c * a % mod;
        a = 1LL * a * a % mod;
        n >>= 1;
    }
    return c;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fak[0] = ifak[0] = 1;

    for (int i = 1; i < maxp; ++i){
        fak[i] = 1LL * fak[i - 1] * i % mod;
        ifak[i] = modpow(fak[i], mod - 2);
    }

    int n; cin >> n;

    map<int,int> freq;

    // vector<int> curval(n);

    for (int i = 0; i < n; ++i){
        int v; cin >> v;
        v = fix(v);
        freq[v]++;

        // curval[i] = v;
    }

    // sort(curval.begin(), curval.end());
    // int curanswer = 0;
    // do{
    //     bool bad = false;
    //     for (int i = 1; i < n && !bad; ++i)
    //         if (curval[i] == curval[i - 1])
    //             bad = true;
    //     if (!bad){
    //         for (auto u : curval)
    //             cout << u << " ";
    //         cout << endl;
    //     }
    //     curanswer += !bad;
    // }while(next_permutation(curval.begin(), curval.end()));
    // cout << curanswer << endl;
    // return 0;

    int answer = 1;

    vector<int> value;
    for (auto p : freq)
        value.push_back(p.second);

    sort(value.begin(), value.end());
    reverse(value.begin(), value.end());

    for (auto k : value){

        cout << n << " " << k << " " << endl;

        if (n - 2 * k + 1 < 0){
            answer = 0;
            break;
        }

        answer = 1LL * answer * fak[n - k + 1] % mod * ifak[n - 2 * k + 1] % mod;
        n -= k;
    }

    cout << answer << endl;

    return 0;
}