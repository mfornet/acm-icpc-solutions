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

    default_random_engine gen;
    uniform_real_distribution<double> dist(0., 1.);

    int n; cin >> n;

    vector<int> pos;
    vector<int> neg;
    vector<string> name;

    map<string,int> index;

    pos.push_back(0);
    neg.push_back(0);
    name.push_back("");
    index[""] = 0;

    auto getindex = [&](string s){
        if (index.find(s) == index.end()){
            index[s] = pos.size();
            name.push_back(s);
            pos.push_back(0);
            neg.push_back(0);
        }
        return index[s];
    };

    vector<vector<int>> user;

    for (int i = 0; i < n; ++i){
        int t; cin >> t;

        vector<int> current;

        for (int j = 0; j < t; ++j){
            string s; cin >> s;
            
            int idx = getindex(s.substr(1));

            if (s[0] == '+') pos[idx]++;
            else{
                neg[idx]++;
                idx *= -1;
            }

            current.push_back(idx);
        }

        user.push_back(current);
    }

    int t = name.size();

    vector<double> prob(t);

    for (int i = 0; i < t; ++i)
        prob[i] = 1. * pos[i] / (pos[i] + neg[i]);

    double k = 1.001; 

    while (true){
        vector<bool> value(t);

        for (int i = 1; i < t; ++i){
            double x = dist(gen);

            if (x < prob[i])
                value[i] = true;
        }

        bool ok = true;

        for (auto u : user){
            int r = 0;
            for (auto v : u){
                if (v > 0 && value[v])
                    r++;
                else if (v < 0 && !value[-v])
                    r++;
            }

            if (3 * r <  u.size()){
                ok = false;
                break;
            }
        }

        if (ok){
            for (int i = 1; i < t; ++i)
                if (value[i])
                    cout << name[i] << endl;
            break;
        }
        else{
            for (int i = 1; i < t; ++i){
                if (prob[i] > .5001)
                    prob[i] *= k;
                else if (prob[i] < .4999)
                    prob[i] /= k;
            }
        }
    }

    return 0;
}
