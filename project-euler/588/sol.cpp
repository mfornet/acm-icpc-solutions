#include <bits/stdc++.h>

using namespace std;

// #define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct SparseBase2Polinomia{
    vector<int64> coef;

    SparseBase2Polinomia(){
    }

    SparseBase2Polinomia(vector<int> v){
        for (int i = 0; i < (int)v.size(); ++i)
            if (v[i]) coef.push_back(i);
    }

    SparseBase2Polinomia operator*(const SparseBase2Polinomia &pol) const{
        unordered_map<int64,int> ncoef;

        // cout << "mult: " << size() << " " << pol.size() << endl;

        for (auto x : coef)
            for (auto y : pol.coef)
                ncoef[x+y] ^= 1;

        SparseBase2Polinomia ans;

        for (auto t : ncoef)
            if (t.second) ans.coef.push_back(t.first);

        return ans;
    }

    int size() const{
        return coef.size();
    }
};

SparseBase2Polinomia base2[64];

SparseBase2Polinomia fast_exp(int64 n){
    // while (n > 0 && n % 3 == 0) n /= 2;
    // cout << "calc: " << n << endl;

    SparseBase2Polinomia ans({1});

    for (int i = 0; n; ++i){
        if (n >> i & 1){
            ans = ans * base2[i];
            n ^= 1LL << i;
        }
    }

    return ans;
}

int64 calculate(int64 p){
    int64 answer = 1;

    while (p){
        while (p % 2 == 0)
            p >>= 1;

        int i = 0;
        while ((p >> i) & 3)
            i++;

        answer *= fast_exp(p & ((1LL << i) - 1)).size();
        p >>= (i + 2);
    }

    return answer;
}

vector<int64> faktor(int64 v){
    int64 l = 2;
    vector<int64> ans;

    while (l * l <= v){
        while (v % l == 0){
            ans.push_back(l);
            v /= l;
        }
        l++;
    }
    if (v > 1) ans.push_back(v);
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N = 20;

    SparseBase2Polinomia A({1});
    SparseBase2Polinomia P({1,1,1,1,1});

    base2[0] = P;
    for (int i = 1; i < 64; ++i){
        base2[i] = base2[i - 1] * base2[i - 1];
        // for (auto x : base2[i].coef)
        //     cout << x << " ";
        // cout << endl;
    }

    // int tmp[8] = {1, 5, 5, 7, 5, 17, 7, 19};

    // int nbase = 2;

    // for (int i = 0; i <= 500; i++){
    //     vector<int> bnbase;
    //     int k = i;
    //     while (k){
    //         bnbase.push_back(k & (nbase-1));
    //         k >>= __lg(nbase);
    //     }
    //     while (bnbase.size() < 6)
    //         bnbase.push_back(0);
    //     reverse(bnbase.begin(), bnbase.end());

    //     for (auto d : bnbase)
    //         cout << d;
    //     cout << " == " << i << " ";

    //     int sz = fast_exp(i).size();

    //     cout << sz << "  " << calculate(i) << `" ::";
    //     for (auto x : faktor(sz))
    //         cout << " " << x;
    //     cout << endl;


    //     if ((i & (nbase-1)) == (nbase-1)) cout << endl;

    //     // cout << fast_exp(8 * i).size() << " " << fast_exp(i).size() << endl;
    //     // auto T = fast_exp(i);
    //     // cout << i << " " << T.size() << endl;
    //     // for (auto x : T.coef) cout << x << " ";
    //     // cout << endl;

    //     // cout << fast_exp(i).size() << endl;
    // }

    // return 0;

    int64 answer = 0;
    int64 cur = 1;

    vector<int64> p10(19);
    p10[0] = 1;
    for (int i = 1; i < 19; ++i)
        p10[i] = p10[i - 1] * 10;

    for (int i = 1; i <= 18; ++i){
        cur = p10[i];
        int64 value = calculate(cur);
        answer += value;
        cout << i << " " << value << endl;
    }
    cout << endl;

    cout << "answer: " << answer << endl;

    return 0;
}