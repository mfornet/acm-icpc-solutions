#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

const int SIZE = 500;

struct S{
    int b, e, B, idx;

    bool operator<(const S &x) const{
        if (B != x.B) return B < x.B;
        if (B & 1) return e < x.e;
        else return e > x.e;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> value(n);
    vector<int> A(n, -1), B(n, -1);

    map<int,int> last;

    for (int i = 0; i < n; ++i){
        cin >> value[i];

        if (last.find(value[i]) == last.end()){
            last[value[i]] = i;
        }
        else{
            int p = last[value[i]];
            int d = i - p;
            A[i] = d;
            B[p] = d;
            last[value[i]] = i;
        }
    }

    // for (int i = 0; i < n; ++i)
    //     cerr << i << " " << A[i] << " " << B[i] << endl;

    vector<S> Q(m);

    for (int i = 0; i < m; ++i){
        int b, e;
        cin >> b >> e;
        b--;
        Q[i] = {b, e, b / SIZE, i};
    }

    sort(Q.begin(), Q.end());

    int p1 = 0, p2 = 0;

    vector<int> freq(n);
    vector<int> bfreq((n + SIZE - 1) / SIZE);

    vector<int> answer(m);

    int t = 0;

    for (auto q : Q){
        while (p1 > q.b){
            p1--;
            int d = B[p1];
            if (d == -1 || p1 + d >= p2) continue;
            // cerr << "ADD: " << d << endl;
            freq[d]++;
            bfreq[d / SIZE]++;
            t++;
        }

        while (p2 < q.e){
            int d = A[p2]; p2++;
            if (d == -1 || p2 - d <= p1) continue;
            freq[d]++;
            // cerr << "ADD: " << d << endl;
            bfreq[d / SIZE]++;
            t++;
        }

        while (p1 < q.b){
            int d = B[p1]; p1++;
            if (d == -1 || p1 - 1 + d >= p2) continue;
            freq[d]--;
            // cerr << "REMOVE: " << d << endl;
            bfreq[d / SIZE]--;
            t--;
        }

        while (p2 > q.e){
            p2--;
            int d = A[p2];
            if (d == -1 || p2 + 1 - d <= p1) continue;
            // cerr << "REMOVE: " << d << endl;
            freq[d]--;
            t--;
            bfreq[d / SIZE]--;
        }

        if (t == 0){
            answer[q.idx] = -1;
        }
        else{
            int p = 0;
            while (bfreq[p] == 0)
                p++;
            p *= SIZE;
            while (freq[p] == 0)
                p++;
            answer[q.idx] = p;
        }
    }

    for (int i = 0; i < m; ++i)
        cout << answer[i] << endl;

    return 0;
}