#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int value[maxn][maxn];
int maxdp[maxn][maxn];
int __left[maxn];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(value, -1, sizeof value);
	int n, m;

	while (cin >> n >> m){
		int answer = 0;
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				cin >> value[i][j];
				if (value[i][j] == value[i - 1][j] + 1)
					maxdp[i][j] = maxdp[i - 1][j] + 1;
				else
					maxdp[i][j] = 1;
			}

			int pos = 0;
			stack<int> stk; 
			for (int j = 1; j <= m; ++j){
				if (value[i][j - 1] + 1 != value[i][j]){
					while (!stk.empty()) stk.pop();
					stk.push(j - 1);
					pos = j - 1;
				}

				while (stk.top() > pos && maxdp[i][ stk.top() ] >= maxdp[i][j])
					stk.pop();
				__left[j] = stk.top();
				stk.push(j);
			}

			for (int j = m; j; --j){
				if (value[i][j + 1] - 1 != value[i][j]){
					while (!stk.empty()) stk.pop();
					stk.push(j + 1);
					pos = j + 1;
				}

				while (stk.top() < pos && maxdp[i][ stk.top() ] >= maxdp[i][j])
					stk.pop();
				int right = stk.top();
				stk.push(j);

				answer = max(answer, (right - __left[j] - 1) * maxdp[i][j]); 
			}
		}
		cout << answer << '\n';
	}

	return 0;
}
