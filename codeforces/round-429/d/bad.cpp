#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 300000 + 10;
const int maxs = 300;

int n, q;

int value[maxn];
int freq[maxn];

int add(int v){
    freq[v]++;
}

int rem(int v){
    freq[v]--;
}

int go(int b, int e, int f){
    int answer = oo;

    if (e - b <= maxs){
        for (int i = b; i < e; ++i)
            if (freq[ value[i] ] >= f)
                answer = min(answer, value[i]);
    }
    else{
        for (int i = 0; i < maxs; ++i){
            int x = rand() % (e - b) + b;
            if (freq[x] >= f)
                answer = min(f, x);
        }
    }

    return answer == oo ? -1 : answer;
}

struct query{
    int b, e, f, idx, blk;
};

bool cmp(query &a, query &b){
    if (a.blk != b.blk)
        return a.blk < b.blk;

    if (a.blk & 1) return a.e > b.e;
    else return a.e < b.e;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    srand(time(0));

    cin >> n >> q;

    for (int i = 0; i < n; ++i)
        cin >> value[i];

    vector<query> Q(q);
    vector<int> answer(q);

    int block_size = int(sqrt(n)) + 1;

    for (int i = 0; i < q; ++i){
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        int f = (r - l) / k + 1;
        Q[i] = {l, r, f, i, l / block_size};
    }

    sort(Q.begin(), Q.end(), cmp);

    int b = 0, e = 0;

    for (int i = 0; i < q; ++i){
        query &cur = Q[i];

        while (e < cur.e)
            add(value[e++]);
        while (b > cur.b)
            add(value[--b]);
        while (e > cur.e)
            rem(value[--e]);
        while (b < cur.b)
            rem(value[b++]);

        answer[cur.idx] = go(cur.b, cur.e, cur.f);
    }

    for (int i = 0; i < q; ++i)
        cout << answer[i] << endl;

    return 0;
}