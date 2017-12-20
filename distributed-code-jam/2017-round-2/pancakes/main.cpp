#include "message.h"
#include "pancakes.h"
#include <iostream>

using namespace std;

typedef long long int64;

int main(){
    int size = GetStackSize(), diners = GetNumDiners();
    int nodeid = MyNodeId(), total = NumberOfNodes();
    int chunk = (size + total - 1) / total;    
    int B = nodeid * chunk, E = B + chunk;

    B = min(B, size);
    E = min(E, size);

    if (B == E){
        PutLL(0, -1);
        Send(0);
        return 0;
    }

    // pre
    int first_number, last_number, round = 1;

    for (int i = B; i < E; ++i){
        int value = GetStackItem(i);

        if (i == B) 
            first_number = last_number = value;

        if (value < last_number)
            round++;
        last_number = value;
    }

    // cout << nodeid << " " << first_number << " " << last_number << " " << round << endl;
    // cout << B << " " << E << endl;

    if (nodeid != 0){
        PutLL(0, first_number);
        PutLL(0, last_number);
        PutLL(0, round);
        Send(0);
    }
    else{
        for (int i = 1; i < total; ++i){
            Receive(i);
            int a = GetLL(i);
            if (a == -1) continue;

            int b = GetLL(i);
            int c = GetLL(i);

            round += c;
            if (a >= last_number)
                round--;
            last_number = b;
        }

        cout << round << endl;
    }
}
