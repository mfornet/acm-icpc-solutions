#include <bits/stdc++.h>

using namespace std;

int calc(vector<int> &v){
	int n = (int)v.size();
	vector<int> lis(n, 1);

	int l = 0;

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < i; ++j)
			if (v[j] < v[i])
				lis[i] = max(lis[i], lis[j] + 1);
		l = max(l, lis[i]);
	}
	return n - l;
}

string suit = "dshc";
string num = "23456789TJQKA";

pair<int,int> parse(string s){
	return pair<int,int>(suit.find(s[1]), num.find(s[0]));
}

int main(){
	int n; cin >> n;

	vector<pair<int,int>> card(n);

	for (int i = 0; i < n; ++i)
	{
		string s; cin >> s;
		card[i] = parse(s);
	}

	int answer = 1000;

	vector<int> order = {0, 1, 2, 3};

	do{
		for (int i = 0; i < (1 << 4); ++i){
			auto cmp = [&](int a, int b){
				auto aCard = card[a], bCard = card[b];

				if (aCard.first != bCard.first)
					return order[ aCard.first ] < order[ bCard.first ];

				if (i >> aCard.first & 1)
					return aCard.second < bCard.second;
				else
					return aCard.second > bCard.second;

			};

			vector<int> tCard(n);
			iota(tCard.begin(), tCard.end(), 0);
			sort(tCard.begin(), tCard.end(), cmp);
			answer = min(answer, calc( tCard ));
		}

	} while (next_permutation(order.begin(), order.end()));

	cout << answer << endl;
}
