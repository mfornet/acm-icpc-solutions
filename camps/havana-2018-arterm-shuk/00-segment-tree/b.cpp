#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const double eps = 1e-9;
const int maxn = 100000 + 10;

struct ordered_set
{
    struct node
    {
        int64 pos;
        int64 sum;
        int64 val;

        int prio, size;
        node *l, *r;

        node(int p, int64 s) : pos(p), sum(s), val(s), prio(rand()), 
                        size(1), l(0), r(0) {}
    };

    node *root;

    int size(node *u)
    {
        return u ? u->size : 0;
    }

    int64 sum(node *u){
        return u ? u->sum : 0;
    }

    node *update(node *u)
    {
        if (u)
        {
            u->sum = u->val + sum(u->l) + sum(u->r);
            u->size = 1 + size(u->l) + size(u->r);
        }

        return u;
    }

    node *merge(node *u, node *v)
    {
        if (!u || !v) return u ? u : v;

        if (u->prio > v->prio)
        {
            u->r = merge(u->r, v);
            return update(u);
        }
        else
        {
            v->l = merge(u, v->l);
            return update(v);
        }
    }

    pair<node*, node*> split(node *u, int t)
    {
        if (!u) return make_pair(nullptr, nullptr);

        if (u->pos >= t)
        {
            auto p = split(u->l, t);
            u->l = p.second;
            return make_pair(p.first, update(u));
        }
        else
        {
            auto p = split(u->r, t);
            u->r = p.first;
            return make_pair(update(u), p.second);
        }
    }

    void insert(int pos, int64 value){
        if (!root){
            root = new node(pos, value);
        }
        else{
            auto xy = split(root, pos);
            root = merge(xy.first, new node(pos, value));
            root = merge(root, xy.second);
        }
    }

    void erase(int pos){
        auto xy = split(root, pos);
        auto yz = split(xy.second, pos + 1);
        root = merge(xy.first, yz.second);
    }

    int64 getsum(int pos){
        auto xy = split(root, pos);
        int64 answer = sum(xy.first);
        root = merge(xy.first, xy.second);
        return answer;
    }
};

struct bit{
    int m;
    vector<ordered_set> V;

    bit(int n){
        m = n;
        V = vector<ordered_set>(n);
    };

    void insert(int p, int x, int64 v){
        while (p < m){
            V[p].insert(x, v);
            p += p & -p;
        }
    }

    void erase(int p, int x){
        while (p < m){
            V[p].erase(x);
            p += p & -p;
        }
    }

    int64 count(int p, int t){
        int64 answer = 0;
        while (p){
            answer += V[p].getsum(t);
            p -= p & -p;
        }
        return answer;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    map<int, set<int>> positions;
    vector<int> value(n + 1);

    bit B(n + 1);

    for (int i = 1; i <= n; ++i){
        int u, x; cin >> u;
        value[i] = u;

        if (positions[u].empty())
            x = -u;
        else
            x = *positions[u].rbegin();
        
        B.insert(i, x, u);

        positions[u].insert(i);
    }

    int q; cin >> q;

    while (q-->0){
        char mode;
        int a, b;

        cin >> mode >> a >> b;

        if (mode == 'U'){
            int pos = a, new_value = b;
            int cur_value = value[pos];

            auto Y = positions[cur_value].lower_bound(pos);

            int x, y, z;
            
            if (Y != positions[cur_value].begin()){
                x = *--Y;
                ++Y;
            }
            else
                x = -cur_value;

            B.erase(pos, x);

            Y++;

            if (Y != positions[cur_value].end()){
                B.erase(*Y, pos);
                B.insert(*Y, x, cur_value);
            }

            positions[cur_value].erase(--Y);
            value[pos] = new_value;

            auto Z = positions[new_value].lower_bound(pos);

            if (Z != positions[new_value].begin()){
                x = *--Z;
                Z++;
            }
            else x = -new_value;

            if (Z != positions[new_value].end()){
                z = *Z;
                B.erase(z, x);
                B.insert(z, pos, new_value);
            }

            B.insert(pos, x, new_value);

            positions[new_value].insert(pos);
        }
        else{
            cout << B.count(b, a) - B.count(a - 1, a) << endl;
            cout.flush();
        }
    }

    return 0;
}