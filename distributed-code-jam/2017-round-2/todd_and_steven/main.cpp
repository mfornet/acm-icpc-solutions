#include "message.h"
#include "todd_and_steven.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int64;

const int64 mod = 1000000007;
const int64 oo = 10000000000LL;

void add(int64 &a, int64 b){
    a += b;
    if (a >= mod)
        a -= mod;
}

int64 tlen, slen;

pair<int64,int64> getLimit(int64 v){    
    int64 lo = -1, hi = tlen;

    while (lo + 1 < hi){
        int64 mid = (lo + hi) >> 1;

        int64 A = mid == 0 ? -1 : GetToddValue(mid - 1);
        int64 B = mid == tlen ? oo + 1 : GetToddValue(mid);

        if (mid > v)
            hi = mid;
        else{
            int64 pos = v - mid, C;

            if (pos > slen) C = oo;
            else C = pos == 0 ? -2 : GetStevenValue(pos - 1);
            // int64 D = pos == slen ? oo : GetStevenValue(pos);

            if (A > C){
                hi = mid;
            }
            else{
                if (B < C) lo = mid;
                else hi = mid;
            }
        }
    }

    return make_pair(hi, v - hi);
}

int64 getAnswer(int64 b, int64 e){
    pair<int64,int64> blimit = getLimit(b);
    pair<int64,int64> elimit = getLimit(e);

    vector<int64> todd(elimit.first - blimit.first);
    vector<int64> steven(elimit.second - blimit.second);
    vector<int64> sortedlst( todd.size() + steven.size() );

    // cout << "here" << endl;
    // cout << elimit.first << " " << blimit.first << endl;
    // cout << elimit.second << " " << blimit.second << endl;

    for (int64 i = blimit.first; i < elimit.first; ++i)
        todd[i - blimit.first] = GetToddValue(i);

    for (int64 i = blimit.second; i < elimit.second; ++i)
        steven[i - blimit.second] = GetStevenValue(i);

    merge(todd.begin(), todd.end(), steven.begin(), steven.end(), sortedlst.begin());

    // cout << "::";
    // for (auto u : sortedlst)
    //     cout << u << " ";
    // cout << endl;
    
    int64 answer = 0;

    for (int64 i = b; i < e; ++i)
        add(answer, i ^ sortedlst[i - b]);

    return answer;
}

int main(){
    int64 nodeid = MyNodeId(), total = NumberOfNodes();
    tlen = GetToddLength(), slen = GetStevenLength();
    int64 len = tlen + slen;
    int64 chunk = (len + total - 1) / total;

    int64 B = chunk * nodeid, E = B + chunk;
    B = min(B, len), E = min(E, len);

    if (B == E){
        PutLL(0, 0);
        Send(0);
        return 0;
    }

    // cout << "--> " << B << " " << E << endl;

    int64 answer = getAnswer(B, E);

    // cout << "answer: " << answer << endl;

    if (nodeid != 0){
        PutLL(0, answer);
        Send(0);
    }
    else{
        for (int64 i = 1; i < total; ++i){
            Receive(i);
            answer = (answer + GetLL(i)) % mod;
        }
        cout << answer << endl;
    }
}