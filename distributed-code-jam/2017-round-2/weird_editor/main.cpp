#include "message.h"
#include "weird_editor.h"
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

const int64 mod = 1000000007;

int64 modpow(int64 a, int64 n){
    int64 b = 1;
    while (n){
        if (n & 1)
            b = a * b % mod;
        n >>= 1;
        a = a * a % mod;
    }
    return b;
}

int main(){
    int64 nodeid = MyNodeId(), total = NumberOfNodes();
    int64 length = GetNumberLength();

    int64 chunk = (length + total - 1) / total;
    int64 B = chunk * nodeid, E = B + chunk;
    B = min(B, length), E = min(E, length);

    vector<int64> dig(10);

    for (int i = B; i < E; ++i){
        int64 d = GetDigit(i);
        for (int j = 0; j < d; ++j)
            dig[j] = 0;
        dig[d]++;
    }

    // for (int i = 0; i < 10; ++i)
    //     cout << dig[i] << " ";
    // cout << endl;

    if (nodeid != 0){
        for (int i = 9; i >= 0; --i)
            PutLL(0, dig[i]);
        Send(0);
    }
    else{
        for (int i = 1; i < total; ++i){
            Receive(i);

            for (int j = 9; j >= 0; --j){
                int64 v = GetLL(i);

                if (v){
                    for (int k = 0; k < j; ++k)
                        dig[k] = 0;
                    dig[j] += v;
                }
            }
        }

        int64 i9 = modpow(9, mod - 2);
        int64 curNum = 0;        
        for (int i = 0; i < 10; ++i)
            curNum += dig[i];
        curNum = length - curNum;

        int64 answer = 0;

        // for (int i = 0; i < 10; ++i)
        // cout << dig[i] << endl;
        
        for (int i = 0; i < 10; ++i){
            if (!dig[i]) continue;
            // cout << curNum << " " << dig[i] << " " << i << endl;
            int64 cur = 1LL * i * i9 % mod * modpow(10LL, curNum) % mod * 
                        (modpow(10, dig[i]) - 1) % mod;
            answer = (answer + cur) % mod;
            // cout << answer << endl;
            curNum += dig[i];
        }

        cout << answer << endl;
    }
}
