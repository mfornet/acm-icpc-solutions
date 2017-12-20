#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define double long double

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

double _ = 0.;

struct polynomial{
    vector<double> coef;

    polynomial(vector<double> coef) : coef(coef) {}
    polynomial(int deg=1) {coef = vector<double>(deg);}
    int size()const{ return coef.size(); }

    double& operator[](int p){
        return p < size() ? coef[p] : _;
    }

    polynomial operator+(polynomial p){
        polynomial ans( max(size(), p.size()) );
        for (int i = 0; i < ans.size(); ++i)
            ans[i] = (*this)[i] + p[i];
        return ans;
    }

    polynomial operator*(polynomial p){
        polynomial ans(size() + p.size() - 1);
        for (int i = 0; i < size(); ++i)
            for (int j = 0; j < p.size(); ++j)
                ans[i + j] += (*this)[i] * p[j];
        return ans;
    }

    polynomial integrate(){
        polynomial ans(size() + 1);
        for (int i = 0; i < size(); ++i)
            ans[i + 1] = (*this)[i] / (i + 1);
        return ans;
    }

    polynomial diff(){
        polynomial ans(size() - 1);
        for (int i = 1; i < size(); ++i)
            ans[i - 1] = (*this)[i] * i;
        if (ans.size() == 0) return polynomial(1);
        else return ans;
    }

    double eval(){
        double ans = 0;
        for (auto u : coef)
            ans += u;
        return ans;
    }
    
    polynomial operator~(){
        polynomial ans(size());
        for (int i = 0; i < size(); ++i)
            ans[i] = -(*this)[i];
        ans[0] += 1.;
        return ans;
    }

    void print(){
        for (int i = 0; i < size(); ++i)
            cout << (*this)[i] << "x^" << i << "+ "[i + 1 == size()];
        cout << endl;
    }
};

polynomial parse(string &s, int &pos){
    if (s[pos] == 'x'){
        pos++;
        return polynomial({0,1.});
    }
    else{
        bool M = s[pos++] == 'M'; // max <--> true

        polynomial a = parse(s, pos);
        polynomial b = parse(s, pos);
        
        if (M)
            return a * b;
        else
            return ~((~a) * (~b));
    }
}

int main(){ ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;

    while (t--){
        string s; cin >> s;
        int pos = 0;
        polynomial ans = parse(s, pos);
        ans = (ans.diff() * polynomial({0., 1.})).integrate();
        cout.precision(17);
        cout << fixed << ans.eval() << endl;
    }

    return 0;
}
