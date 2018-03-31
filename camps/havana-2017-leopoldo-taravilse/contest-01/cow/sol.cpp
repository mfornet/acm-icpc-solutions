#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;

int solve( vector<int> value ){
    int n = (int)value.size();
    vector<bool> ok(1 << n);
    vector<int> sum(1 << n);

    int a = min(11, n);
    int b = n - a;

    for (int i = 1; i < (1 << n); ++i){
        int u = __lg(i);
        sum[i] = sum[ i ^ (1 << u) ] + value[u];
        //cout << bitset<5>(i) << " "<< sum[i] << endl;
    }
    //cout << endl;

    map<int, set<int>> m;

    for (int i = 0; i < (1 << a); ++i){
        for (int j = i; j != -1; j = j == 0 ? -1 : ( (j - 1) & i )){
            int v = abs( sum[j] - sum[i ^ j] );
            //cout << bitset<5>(i) << " " << v << endl;
            m[v].insert( i );
        }
    }
/*
    for (auto x : m){
        cout << x.first << "::" << x.second.size() << endl;
        for (auto y : x.second)
            cout << bitset<4>(y) << " ";
        cout << endl;
    }
    cout << endl;

 */   
    for (int i = 0; i < (1 << b); ++i){
        set<int> s;
        int msk = i << a;

        for (int j = msk; j != -1; j = j == 0 ? -1 : ( (j - 1) & msk )){
            int v = abs( sum[j] - sum[ msk ^ j] );
    
            if (s.find(v) != s.end() || m.find(v) == m.end()) 
                continue;

            s.insert( v );

            for (auto x : m[v])
                ok[ msk ^ x ] = true;
        }
    }

    int answer = 0;
    for (int i = 1; i < (1 << n); ++i){
        //if(ok[i])cout << bitset<5>(i) << endl;
        answer += ok[i];
    }

    return answer;
}

int brute( vector<int> value ){
    int n = (int)value.size();
    vector<int> sum(1 << n);

    for (int i = 0; i < (1 << n); ++i){
        for (int j = 0; j < n; ++j)
            if (i >> j & 1)
                sum[i] += value[j];
    }
    
    int answer = 0;

    for (int i = 1; i < (1 << n); ++i){
        for (int j = i; j != -1; j = j ? (i & (j - 1)) : -1){
           if (sum[j] == sum[i ^ j]){
               answer++;
               break;
           }
        }
    }

    return answer;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n; 

    while (cin >> n){
        vector<int> value(n);
        for (int i = 0; i < n; ++i)
            cin >> value[i];

        int answer1 = solve( value );
//        int answer2 = brute( value );
        
        cout << answer1 << endl;
        /*
        cout << answer1 << " " << answer2 << endl;

        if (answer1 != answer2){
            cout << n << endl;
            for (auto v : value)
                cout << v << " ";
            cout << endl;
            exit(0);
        }
        */
    }

    return 0;
}
