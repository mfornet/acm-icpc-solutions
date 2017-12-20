#include <bits/stdc++.h>

using namespace std;
ifstream fin1("r1.out");
ifstream fin2("r1.py.out");

int a, c;
double b, d;

int main(){
	while(fin1 >> a >> b){
		fin2 >> c >> d;

		assert(a == c);
		assert(fabs(b-d) < 1e-9); 
	}    
}
