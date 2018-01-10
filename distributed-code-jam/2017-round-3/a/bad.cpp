#include "message.h"
#include "flagpoles.h"
#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

int main(){
	long long nodeid = MyNodeId(), totalN = NumberOfNodes();
	long long length = GetNumFlagpoles();
	long long chunk = (totalN + length - 2) / (totalN - 1);

	if (nodeid == 0){
		long long answer = 0;

		long long last, diff = length > 1 ? GetHeight(1) - GetHeight(0) : 0, total;
		bool start = true;

		for (int i = 1; i < totalN; ++i){
			Receive(i);
			long long ok = GetLL(i);
			if (!ok) continue;

			vector<long long> message(7);
			for (int j = 0; j < 7; ++j){
				message[j] = GetLL(i);
				//cout << message[j] << " ";
			}
			//cout << endl;

			answer = max(answer, message[0]);

			if (start){
				start = false;
				last = message[4], diff = message[0] > 1 ? message[5] : diff, total = message[6];
			}
			else{
				if (message[0] == 1){
					if (message[1] - last == diff){
						total++;
						last = message[1];
					}
					else{
						diff = message[1] - last;
						total = 2;
						last = message[1];
					}
					answer = max(answer, total);
					continue;

				}

				if (message[1] - last == diff){
					if (diff == message[2]){
						answer = max(answer, total + message[3]);
					}
					else{
						answer = max(answer, total + 1);
					}
				}

				if (message[0] == message[6]){
					if (message[1] - last == message[2]){
						if (diff == message[2]){
							total += message[0];
							last = message[4];
						}
						else{
							total = message[0] + 1;
							last = message[4];
							diff = message[5];
						}
					}
					else{
						last = message[4];
						diff = message[5];
						total = message[6]; 
					}
				}
				else{
					last = message[4];
					diff = message[5];
					total = message[6];
				}
			}

			//cout << last << " " << diff << " " << total << endl;
			//cout << endl;

		}
		cout << answer << endl;
	}
	else{
		long long beg = chunk * (nodeid - 1), end = beg + chunk;
		end = min(end, length);
		beg = min(beg, length);

		if (beg == end){
			PutLL(0, 0); Send(0); return 0;
		}

		//cout << beg << " " << end << endl;

		// best
		// begin, difference, total
		// end, difference, total

		long long prev = 0, diff;
		long long best = 0, cur;
		long long start = 0;

		long long bestprefix = -1;
		long long diffprefix = 0;

		for (int i = beg; i < end; ++i, ++start){
			long long value = GetHeight(i);

			if (start == 0){
				cur = 1;
			}
			else if (start == 1){ cur = 2;
			}
			else{
				if (value - prev == diff)
					cur++;
				else{
					if (bestprefix == -1){
						bestprefix = cur;
						diffprefix = diff;
					}
					cur = 2;
				}
			}

			diff = value - prev;
			prev = value;
			best = max(best, cur);
		}

		if (bestprefix == -1){
			bestprefix = best;
			diffprefix = diff;
		}

		PutLL(0, 1);
		vector<long long> message = {best, GetHeight(beg), diffprefix, bestprefix,
							GetHeight(end - 1), diff, cur};

		for (auto u : message)
			PutLL(0, u);
		Send(0);
	}
}
