#include "message.h"
#include "flagpoles.h"
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

int main(){
	long long nodeid = MyNodeId(), totalN = NumberOfNodes();
	long long length = GetNumFlagpoles() - 1;
	long long chunk = (totalN + length - 2) / (totalN - 1);

	if (nodeid == 0){
		long long last, freq, answer = 0;
		bool start = true;

		for (int id = 1; id < totalN; ++id){
			Receive(id);
			long long ok = GetLL(id);
			if (!ok) continue;

			vector<long long> msg(6);
			//cout << "id: " << id << " :: ";
			for (int i = 0; i < 6; ++i){
				msg[i] = GetLL(id);
				//cout << msg[i] << " ";
			}
			//cout << endl;

			long long best = msg[0], bValue = msg[1], bFreq = msg[2];
			long long eValue = msg[3], eFreq = msg[4], size = msg[5];

			answer = max(answer, best);

			if (start){
				last = eValue;
				freq = eFreq;
				start = false;
			}
			else{
				if (bValue == last){
					answer = max(answer, freq + bFreq);
				}

				if (best == size && eValue == last){
					freq += best;
				}
				else
					freq = eFreq, last = eValue;
			}
			//cout << last << " " << freq << endl;

			answer = max(answer, freq);
		}

		cout << answer + 1 << endl;
	}
	else{
		long long beg = chunk * (nodeid - 1), end = beg + chunk;
		beg = min(beg, length), end = min(length, end);

		if (beg == end){
			PutLL(0, 0); Send(0); return 0;
		}

		//cout << beg << " " << end << endl;


		long long prev = GetHeight(beg);
		long long start = 0;

		long long bValue, bFreq = 0;
		long long eValue, eFreq = 0;
		long long best = 0;

		for (int i = beg + 1; i <= end; ++i){
			long long cur = GetHeight(i);
			long long value = cur - prev; prev = cur;

			if (start == 0){
				start = 1;
				eValue = bValue = value;
				best = eFreq = bFreq = 1;
				continue;
			}

			if (value == eValue){
				if (start == 1)
					bFreq++;
				eFreq++;
			}
			else{
				start = 2;
				eFreq = 1;
				eValue = value;
			}

			best = max(best, eFreq);
		}

		vector<long long> msg = {1, best, bValue, bFreq, eValue, eFreq, end - beg};
		for (auto u : msg)
			PutLL(0, u);
		Send(0);
	}
}
