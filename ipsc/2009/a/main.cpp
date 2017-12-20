#include <iostream>

using namespace std;

int main(){
    int n; cin >> n;

    while (n--){
        long long answer; cin >> answer;

        while (true){
            string s; cin >> s;
            if (s == "=") break;

            long long cur; cin >> cur;

            if (s == "+") answer += cur;
            else if (s == "-") answer -= cur;
            else if (s == "/") answer /= cur;
            else answer *= cur;
        }

        cout << answer << endl;
    }


}
