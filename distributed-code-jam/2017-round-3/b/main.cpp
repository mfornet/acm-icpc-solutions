#include "message.h"
#include "number_bases.h"
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

int main(){
	long long nodeid = MyNodeId(), totalN = NumberOfNodes();
	long long len = GetLength();
	long long chunk = (len + totalN - 2) / (totalN - 1);

	if (nodeid == 0){
	}
	else{
		int beg = chunk * (nodeid - 1), end = beg + chunk;
		beg = min(beg, len); end = min(end, len);

		// detect base
		bool found = false;
		for (int i = beg; i < end; ++i){
			long long x = GetDigitX(i), y = GetDigitY(i), z = GetDigitZ(i);

			if (x + y != z){
				long long base = x + y - z; 
				PutLL(0, 1);
				PutLL(0, base);
				found = true;
				Send(0);
				break;
			}
		}

		if (!found){
			PutLL(0, 0);
			Send(0);
		}

		// check base
		Receive(0);

		long long ok = GetLL(0);
		if (ok == 0) return 0;

		long long base = GetLL(0);

		for (long long r = 0; r < 2; ++r){
			long long rem = r;
			bool good = true;

			for (int i = beg; i < end; ++i){
				long long x = GetDigitX(i), y = GetDigitY(i), z = GetDigitZ(i);
				
				if ( (x + y + rem) % base != z ){
					PutLL(0, -1);
					good = false;
					break;
				}

				rem = (x + y + rem) > z;
			}
			if (good){
				PutLL(0, 1);
				PutLL(0, rem);
			}
		}

		Send(0);
	}
}
