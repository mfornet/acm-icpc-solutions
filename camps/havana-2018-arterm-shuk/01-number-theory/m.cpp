#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int SWAP = -1;
const int APLUSB = 0;
const int AMINUSB = 1;
const int BPLUSA = 2;
const int BMINUSA = 3;

pair<int, vector<pii>> solve(int a, int b){
    vector<pii> steps;

    auto add = [&](int op, int k=-1){
        steps.push_back({op, k});
        // cout << a << " " << b << endl; 
    };

    // convert to positives

    if (b <= 0){
        add(SWAP);
        swap(a, b);
    }
     
    // cout << a << " " << b << endl;

    while (a <= 0){
        if (a == 0){
            if (b < 0){
                add(AMINUSB, 1);
                a -= b;
            }
            else{
                add(APLUSB, 1);
                a += b;       
            }
            add(SWAP);
            swap(a, b);
        }
        else if (a < 0){
            if (b == 0){
                add(BMINUSA, 1);
                b -= a;
            }
            else if (b > 0){
                int k = (abs(a) + b - 1) / b;
                add(APLUSB, k);
                a += k * b;
            }
            else{
                int k = (abs(a) + abs(b) - 1) / abs(b);
                add(AMINUSB, k + 1);
                a -= (k + 1) * b;

                add(SWAP);
                swap(a, b);
            }
        }
        else{
            add(SWAP);
            swap(a, b);
        }

        assert(b > 0);
    }

    assert(a >= 0);
    assert(b >= 0);

    while (b != 0){
        if (b < a){
            add(SWAP);
            swap(a, b);
        }

        add(BMINUSA, b / a);
        b -= (b / a) * a;
    }

    // cout << a << " " << b << endl;
    // cout << endl;

    return {a, steps};    
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b, c, d;

    cin >> a >> b >> c >> d;

    if (a == b && b == 0){
        cout << "No solution." << endl;
        return 0;
    }

    if (c == d && d == 0){
        cout << "No solution." << endl;
        return 0;
    }

    auto ab_to_g = solve(a, b);
    auto cd_to_g = solve(c, d);

    if (ab_to_g.first != cd_to_g.first){
        cout << "No solution." << endl;
        return 0;
    }

    auto show = [&](pii cmd, bool rev=false){
        int op = cmd.first;
        int k = cmd.second;

        if (rev && op >= 0)
            op ^= 1;

        if (op == SWAP)
            cout << "swap(a, b)" << endl;
        else if (op == APLUSB)
            cout << "a += " << k << " * b" << endl;
        else if (op == AMINUSB)
            cout << "a -= " << k << " * b" << endl;
        else if (op == BPLUSA)
            cout << "b += " << k << " * a" << endl;
        else if (op == BMINUSA)
            cout << "b -= " << k << " * a" << endl;
        else
            assert(false);
    };

    cout << ab_to_g.second.size() + cd_to_g.second.size() << endl;

    for (auto x : ab_to_g.second)
        show(x);

    reverse(cd_to_g.second.begin(), cd_to_g.second.end());

    for (auto x : cd_to_g.second){
        show(x, true);
    }

    return 0;
}