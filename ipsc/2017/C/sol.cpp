#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

void prec(){
	set<int64> nonboring;

	vector<int> v(10);
	iota(v.begin(), v.end(), 0);

	do{
		int64 value = 0;
		if (v[0] > 2)
			break;

		for (int i = 0; i < 10; ++i){
			value = 10 * value + v[i];
			nonboring.insert( value );
		}

	} while(next_permutation(v.begin(), v.end()));

	cout << nonboring.size() << endl;
	for (auto u : nonboring)
		cout << u << endl;
}

int64 n;
int64 v[2740028+10];

void load(){
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> v[i];
	cout << "here" << endl;
}

bool decompose(int64 num){
	if (binary_search(v, v + n, num)){
		cout << num << endl;
		return true;
	}

	bool found = false;
	int t = upper_bound(v, v + n, num) - v;

	do{
		int64 a = v[ rand() % t ];
		if (binary_search(v, v + n, num - a))
		{
			cout << a << " + " << num - a << " = " << num << endl;
			found = true;
		}

	} while (!found);

	return false;
}

int main(){
	load();
	for (int i = 0; i < 1000; ++i)
	decompose(rand() % 2000000000);
}