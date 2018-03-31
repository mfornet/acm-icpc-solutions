#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

int solve(int A, int B, int a, int b){
    if (A < a || B < b)
        return oo;

    int answer = 0;
    while (A > a){
        answer++;
        A = (A + 1) / 2;
    }

    while (B > b){
        answer++;
        B = (B + 1) / 2;
    }

    return answer;
}

int sol1(int A, int B, int a, int b){
    if (A > B) swap(A, B);
    if (a > b) swap(a, b);
    return solve(A, B, a, b);
}

int sol2(int A, int B, int a, int b){
    return solve(A, B, a, b) + solve(B, A, a, b);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}
