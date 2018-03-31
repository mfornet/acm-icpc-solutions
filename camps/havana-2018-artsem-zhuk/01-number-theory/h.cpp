#include <bits/stdc++.h>

using namespace std;

//#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct P{
    vector<int> d;

    P(int n){
        d = vector<int>(n);
        iota(d.begin(), d.end(), 0);
    }

    P(vector<int> &value){
        d = value;
    }

    int size() const {
        return d.size();
    }

    P operator*(const P &x) const{
        int n = size();

        P answer(n);

        for (int i = 0; i < n; ++i)
            answer.d[i] = d[x.d[i]];

        return answer;
    }

    P inverse(){
        int n = size();
        P answer(n);

        for (int i = 0; i < n; ++i)
            answer.d[ d[i] ] = i;

        // for (int i = 0; i < n; ++i)
        //     cout << answer.d[i] << " ";
        // cout << endl;

        return answer;
    }
};

/*
    x * a * x * a * x * a = b * a
*/

struct triple{
	int d, x, y;
};
//return d, xa, xb such that d = xa*a + xb*b
triple egcd( int a, int b ) {
    if( !b ) return (triple){ a, 1, 0  };
    triple q = egcd( b, a % b );
    return (triple) {q.d, q.y, q.x - a / b * q.y };
}
int inverse(int a, int n){
	int r = egcd(a, n).x;
	int x = ( r % n + n ) % n;
	return x;
}

int main(){
	#ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n >> t;
    P A(n), B(n);
    for (int i = 0; i < n; ++i){
        cin >> A.d[i]; A.d[i]--;
    }

    for (int i = 0; i < n; ++i){
       cin >> B.d[i]; B.d[i]--;
    }
    if (t % 2 == 0){
        t /= 2;
    }
    else{
        B = B * A;
        t = (t + 1) / 2;
    }

    map<int, vector<vi>> M;
    vector<bool> seen(n);

    for (int i = 0; i < n; ++i){
        if (seen[i])
            continue;

        vector<int> seq;

        int u = i;

        do{
            seen[u] = true;
            seq.push_back(u);
            u = B.d[u];
        } while (u != i);

        M[seq.size()].push_back(seq);
    }

    vector<int> faq;
    int tp = t;

    for (int i = 2; 1LL * i * i <= tp; ++i){
        if (tp % i == 0){
            faq.push_back(i);
            while (tp % i == 0)
                tp /= i;
        }
    }

    if (tp > 1) faq.push_back(tp);

    P final(n);

    for (auto x : M){
        int ai = x.first;
        int ci = x.second.size();

        int ti = t;

        for (auto p : faq)
            if (ai % p == 0){
                while (ti % p == 0)
                    ti /= p;
            }

        int ri = t / ti;


        if (ci % ri){
            cout << -1 << endl;
            return 0;
        }
        int offset = inverse(t, ri * ai);
        for (int i = 0; i < ci; i += ri){
            vector<int> qq;

            for (int k = 0; k < ai; ++k)
                for (int j = 0; j < ri; ++j)
                    qq.push_back(x.second[i + j][k]);
            if(ri > 1)
            	for (int j = 0; j < (int)qq.size(); ++j)
            		final.d[ qq[j] ] = qq[ (j + 1 ) % qq.size() ];
            else{
            	for (int j = 0; j < (int)qq.size(); ++j)
            		final.d[ qq[j] ] = qq[ (j + offset) % qq.size() ];
            }
        }
    }



    final = final * A.inverse();


    for (int i = 0; i < n; ++i)
        cout << final.d[i] + 1 << " \n"[i + 1 == n];

    return 0;
}
