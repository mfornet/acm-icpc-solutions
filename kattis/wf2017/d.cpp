#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

void update(vector<pii> &L){
    sort(L.begin(), L.end());

    int size = 1, n = (int)L.size();

    for (int i = 1; i < n; ++i){
        if (L[i].second < L[size - 1].second) 
            L[ size++ ] = L[i];
    }

    L.resize( size );
}

long long solve(int optB, int optE, int b, int e, vector<pii> &A, vector<pii> &B){
    if (b >= e) return 0;
    int m = (b + e) / 2;

    int opt = -1;
    long long answer = -1;

    for (int i = optB; i < optE && A[i].first <= B[m].first; ++i){
        long long area = 1LL * (B[m].first - A[i].first) * (B[m].second - A[i].second);
        if (area > answer)
        {
            answer = area;
            opt = i;
        }
    }

    answer = max( answer, solve( optB, opt + 1, b, m, A, B ) );
    answer = max( answer, solve( opt, optE, m + 1, e, A, B ) );

    return answer;
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<pii> A(n), B(m);

    for (int i = 0; i < n; ++i)
        cin >> A[i].first >> A[i].second;

    for (int i = 0; i < m; ++i){
        cin >> B[i].first >> B[i].second;
        B[i].first *= -1;
        B[i].second *= -1;
    }

    update(A); update(B);
    n = (int)A.size(), m = (int)B.size();

    for (auto &p : B){
        p.first *= -1;
        p.second *= -1;
    }
    reverse(B.begin(), B.end());

    int size = 0;

    for (int i = 0; i < m; ++i){
        int pos = lower_bound(A.begin(), A.end(), pii( B[i].first + 1, -1 ) ) - A.begin();
        if (pos == 0 || A[--pos].second >= B[i].second)
            continue;
        B[size++] = B[i];
    }

    B.resize( size );

    long long answer = solve(0, n, 0, size, A, B);

    cout << answer << endl;
}

