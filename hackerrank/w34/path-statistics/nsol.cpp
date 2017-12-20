#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int maxv = 50000 + 10;
const int maxsqrtv = 320;


/*
    Name:           SQRT LIST

    Description:    Insertar, y elimina valores en O(1)
                    y responde el k-ésimo valor del conjunto
                    en O(sqrt(M)), donde M es el máximo valor.

                    La memoria necesaria es O(M) donde M es el
                    máximo valor que se puede insertar en la lista.

    Tested:         ???
*/
struct SqrtList{
    const int bitSize = 10; // bucket size 2^10 = 1024
    int _count;
    vector<int> freq, bucketFreq;

    SqrtList(int n=0){
        int size = 1 << bitSize;
        n = (n + size - 1) / size * size, _count = 0;
        freq = vector<int>(n);
        bucketFreq = vector<int>(n / bitSize);
    }

    int count(){
        return _count;
    }

    void add(int v){
        _count++;
        freq[v]++;
        bucketFreq[v >> bitSize]++;
    }

    void remove(int v){
        _count--;
        freq[v]--;
        bucketFreq[v >> bitSize]--;
    }

    int getKth(int k){
        int p = (int)bucketFreq.size() - 1;

        while (k > bucketFreq[p])
            k -= bucketFreq[p--];

        p = ((p + 1) << bitSize) - 1;
        while (k > freq[p])
            k -= freq[p--];

        return p;
    }
};

int value[ maxn ];
int real_value[ maxn ];
vi adj[ maxn ];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i){
        cin >> value[i];
        real_value[i - 1] = value[i];
    }

    // compressing
    sort(real_value, real_value + n);
    int total = unique(real_value, real_value + n) - real_value;
    for (int i = 1; i <= n; ++i)
        value[i] = lower_bound(real_value, real_value + total, value[i]) - real_value;

    for (int i = 1; i < n; ++i){
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }


    return 0;
}