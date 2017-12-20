#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int mod = 1000000007;

int o(int a, int b){
    return (a >> b & 1) == 0;
}

int add(int &a, int b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int A[ 16 ][ 16 ];
int B[ 16 ][ 16 ];
int T[ 16 ][ 16 ];

    void mult(int X[16][16], int Y[16][16]){
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j){
                T[i][j] = 0;
                for (int k = 0; k < 16; ++k)
                    add( T[i][j], 1LL * X[i][k] * Y[k][j] % mod );
            }
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                X[i][j] = T[i][j];
    }

void print(int m[16][16]){
        for (int i = 0; i < 16; ++i)
            for (int j = 0; j < 16; ++j)
                cout << m[i][j] << " \n"[j == 15];
}

void mpow(int64 c){
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j)
            B[i][j] = i == j;

    while (c){
        if (c & 1)
            mult(B, A);
        mult(A, A);
        c >>= 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

     int64 n; 
    while (cin >> n){

        memset(A, 0, sizeof A);
   int f = 15;
    A[0][0]++;

    for (int i = 0; i < 16; ++i){
        if (o(i, 0) && o(i, 1))
            A[i][ f ^ i ^ 3 ]++;
        if (o(i, 1) && o(i, 2))
            A[i][ f ^ i ^ 6 ]++;
        if (o(i, 2) && o(i, 3))
            A[i][ f ^ i ^ 12 ]++;
        A[i][f^i]++;
    }
/*
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j)
            cout << A.m[i][j] << " \n"[j == 15];
*/
        mpow(n);
        cout << B[0][0] << endl;
    }

    return 0;
}
