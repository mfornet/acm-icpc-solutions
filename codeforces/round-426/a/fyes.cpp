#include <iostream>

using namespace std;

int main(){
    string s;
    int answer = 0;
    while (cin >> s){
        if (s == "Yes")
            answer++;
    }
    cout << answer << endl;
    return 0;
}
