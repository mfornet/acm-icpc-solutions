#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int maxn = 4100100;

string s;
int A[maxn];
int N;

string solve(int size){
	map<int64,int64> freq;

	int64 mask = (1LL << (size - 1)) - 1;
	int64 value = 0;

	int last2 = -1;
	for (int j = 0; j < size && last2 == -1; ++j)
		if (A[j] == 2)
			last2 = j;

	for (int i = 0; i + size - 1 < N; ++i){
		bool clean = true;

		if (A[i + size - 1] == 2)
			last2 = i + size - 1;

		if (last2 >= 0)
			continue;

		freq[ value ] += 2 * A[i + size - 1] - 1;
	}

	int value = 0;
	int mask = (1 << (size - 1)) - 1;

	string answer = "";

	for (int i = 0; i < N; ++i){
		int cur = A[i];
		if (cur == 2){
			cur = freq[ value ] > 0;
			answer += (char)('0' + cur);
		}
		value = ((value << 1) | cur) & mask; 
	}
	return answer;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string s; cin >> s;
	int a, b, c, d;

	for(auto ch : s){
		ch -= 33;d = ch % 3;
		ch /= 3;c = ch % 3;
		ch /= 3;b = ch % 3;
		ch /= 3;a = ch % 3;		
		A[N++] = a; A[N++] = b; A[N++] = c; A[N++] = d;
	}

	// string prev = solve(9);
	// int len = (int)prev.length();

	// for (int i = 10; i < 100; ++i){
	// 	string cur = solve(i);
	// 	int diff = 0;

	// 	for (int j = 0; j < len; ++j)
	// 		diff += cur[j] != prev[j];

	// 	cout << i << " " << diff << endl;
	// 	prev = cur;
	// }

	cout << solve(20) << endl;
}
