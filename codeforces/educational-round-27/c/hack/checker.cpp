#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// one token comparer

int main(int argc, char *argv[]){
    // input
    // answer
    // output

    // return 2;

    ifstream ans(argv[2]);
    ifstream out(argv[3]);

    string a, b;
    ans >> a;
    out >> b;

    if (a != b){
        cout << a << "-" << b << endl;
    }

    return (a == b) ? 0 : 1;
}