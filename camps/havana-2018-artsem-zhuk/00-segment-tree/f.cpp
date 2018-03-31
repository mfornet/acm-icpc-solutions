#include <bits/stdc++.h>
const int MAX = 1e5 + 10;
typedef long long i64;
using namespace std;
const double EPS = 1e-6;
const int MOD = 1e9 + 7;
#define mul(a, b) ((i64)(a) * b % MOD)



int colors[MAX];
struct segment_tree{
	struct node{
		node* left, *right;
		int c;
		node(){left = right = NULL, c = -1;}
	};
	node* root;
	segment_tree(){
		root = new node();
	}

	void dfs(node* nnode, int a, int b){
	    if(nnode->c != -1){
	    	colors[nnode->c] += b - a + 1;
	    	return;
	    }
	    if(nnode->left == NULL)return;
	    dfs(nnode->left, a, (a + b) / 2);
	    dfs(nnode->right, (a + b) / 2 + 1, b);
	}
	void update(node* nnode, int a, int b, int i, int j, int c){
		if(j < a or i > b)return;
		if(i <= a and b <= j){
			nnode->c = c;
			nnode->left = nnode->right = NULL;
			return;
		}
		if(nnode->left == NULL){
			nnode->left = new node();
			nnode->right = new node();
			nnode->left->c = nnode->c;
			nnode->right->c = nnode->c;
		}
		update(nnode->left, a, (a + b) / 2, i, j, c);
		update(nnode->right, (a + b) / 2 + 1, b, i, j, c);
		nnode->c = -1;
	}
};


int main() {

    #ifdef LOCAL_DEBUG
    	freopen ("data.in", "r", stdin );
    	//freopen ("data.out", "w", stdout );
    #endif
    ios_base::sync_with_stdio(0); cin.tie(0);
    #define endl '\n'
    int n, k; cin >> n >> k;
    segment_tree S;
     int m ; cin >> m;
     while(m--){
    	 int x, y, c; cin >> c >> x >> y;
    	 S.update(S.root, 1, n, x, y, c);

     }
     S.dfs(S.root, 1, n);
     for(int i = 1; i <= k; i++)
    	 cout << colors[i] << (i == k ? '\n' : ' ');





}
