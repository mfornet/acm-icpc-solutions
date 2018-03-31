#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const int oo = 1e6;
const double EPS = 1e-7;
int matchL[ MAX ] , matchR[ MAX ];
bool seen[ MAX ];
vector< int > ady[ MAX ];
vector<int> adyr[MAX];
bool badl[MAX], badr[MAX];
bool bpm( int left ){
    if( seen[ left ] ) return 0;
    seen[ left ] = 1;
    int right;
    for(int i = 0 ; i < (int)ady[ left ].size() ; ++i ){
        right = ady[ left ][ i ];
        if( matchR[ right ] == -1 || bpm( matchR[ right ] ) ){
            matchR[ right ] = left;
            matchL[ left ] = right;
            return 1;
        }
    }
    return 0;
}
int kuhn(int L){// from 0 to L-1 are the nodes in the left component
    bool change = true;
    memset( matchR , -1 , sizeof( matchR ) );
    memset( matchL , -1 , sizeof( matchL ) );
    while( change ){
        change = false;
        memset( seen , 0 , sizeof( seen ) );
        for(int i = 0; i < L ; ++i ){
            if( matchL[ i ] == -1) change |= bpm( i );
        }
    }
    int ret = 0;
    for( int i = 0 ; i < L ; ++i )
        if( matchL[ i ] != -1 ) ret++;
    return ret;
}
void dfsl( int left ){
    if( seen[ left ] ) return;
    seen[ left ] = 1;
    for(int i = 0 ; i < (int)ady[ left ].size() ; ++i ){
        int right = ady[ left ][ i ];
        dfsl(matchR[ right ]);
        badl[matchR[ right ]] = true;
    }
}
void dfsr( int right ){
    if( seen[ right ] ) return;
    seen[ right ] = 1;
    for(int i = 0 ; i < (int)adyr[ right ].size() ; ++i ){
        int left = adyr[ right ][ i ];
        dfsr(matchL[ left ]);
        badr[matchL[ left ]] = true;
    }
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
	#endif
	#define endl '\n'
	int n1, n2, m; cin >>n1 >> n2 >> m;
	while(m--){
		int a , b; cin >> a >> b;a--, b--;
		ady[a].push_back(b);
		adyr[b].push_back(a);
	}
	kuhn(n1);
	memset(seen, 0, sizeof(seen));
	for(int i = 0; i <n1; i++)
		if(matchL[i] == -1){
			badl[i] = true;
			dfsl(i);
		}
	memset(seen, 0, sizeof(seen));
	for(int i = 0; i <n2; i++)
		if(matchR[i] == -1){
			badr[i] = true;
			dfsr(i);
		}
	for(int i = 0; i < n1; i++)
		cout << (badl[i] ? "P" : "N");
	cout << endl;
	for(int i = 0; i < n2; i++)
		cout << (badr[i] ? "P" : "N");

}
