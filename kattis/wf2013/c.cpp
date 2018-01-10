#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define SZ(x) ((int)x.size())
#define DB(x) cout << #x << "=" << x << endl
#define endl '\n'

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const double EPS = 1e-7;
const int MOD = (int)1e9 + 7;
const int MAXN = (int)1e5 + 10;

const int oo = 2000000000;

struct Edge
{
    int from, to, cap, flow, index;

    Edge(int from, int to, int cap, int flow, int index) :
        from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic
{
    int N;
    vector< vector<Edge> > G;
    vector<Edge*> dad;
    vector<int> Q;

    Dinic(int N) : N(N), G(N), dad(N), Q(N) {}

    void AddEdge(int from, int to, int cap)
    {
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        if(from == to) G[from].back().index++;
        G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
    }

    long long BlockingFlow(int s, int t)
    {
        fill(dad.begin(),dad.end(),(Edge*) NULL);
        dad[s] = &G[0][0] - 1;

        int head = 0, tail = 0;
        Q[tail++] = s;

        while(head < tail)
        {
            int x = Q[head++];

            for(int i = 0; i < (int) G[x].size(); ++i)
            {
                Edge &e = G[x][i];

                if(!dad[e.to] && e.cap - e.flow > 0)
                {
                    dad[e.to] = &G[x][i];
                    Q[tail++] = e.to;
                }
            }
        }

        if(!dad[t]) return 0;

        long long totflow = 0;

        for(int i = 0; i < (int) G[t].size(); ++i)
        {
            Edge *start = &G[G[t][i].to][G[t][i].index];
            int amt = oo;

            for(Edge *e = start; amt && e != dad[s]; e = dad[e->from])
            {
                if(!e) { amt = 0; break; }
                amt = min(amt,e->cap - e->flow);
            }

            if(amt == 0) continue;

            for(Edge *e = start; amt && e != dad[s]; e = dad[e->from])
            {
                e->flow += amt;
                G[e->to][e->index].flow -= amt;
            }

            totflow += amt;
        }

        return totflow;
    }

    long long GetMaxFlow(int s, int t)
    {
        long long totflow = 0;

        while(long long flow = BlockingFlow(s,t))
            totflow += flow;

        return totflow;
    }

    void clean(){
        for (auto &e : G){
            for (auto &n : e){
                n.flow = 0;
            }
        }
    }
};


int n, m, c;
vector<pii> ady[MAXN];
int dist[MAXN];

void dijkstra(int s){
    for (int i = 1; i <= n; ++i) dist[i] = oo;
    dist[s] = 0;
    priority_queue<pii> PQ;
    PQ.push(MP(0, s));

    while (!PQ.empty()){
        pii cur = PQ.top(); PQ.pop();
        int d = -cur.first;
        int cn = cur.second;

        if (dist[cn] < d) continue;

        for (auto nxt : ady[cn]){
            if (dist[nxt.first] > dist[cn] + nxt.second){
                dist[nxt.first] = dist[cn] + nxt.second;
                PQ.push(MP(-dist[nxt.first], nxt.first));
            }
        }
    }
}

bool compare(int a, int b){
    return dist[a] < dist[b];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> c;
    for (int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        ady[u].push_back(MP(v, w));
        ady[v].push_back(MP(u, w));
    }

    dijkstra(1);

    vector<int> V(c);
    for (int i = 0; i < c; ++i){
        cin >> V[i];
    }

    Dinic flow(n + c + 1);
    for (int i = 1; i <= n; ++i){
        for (auto &e : ady[i]){
            if (dist[i] == dist[e.first] + e.second)
                flow.AddEdge(i, e.first, 1);
        }
    }

    sort(V.begin(), V.end(), compare);
    int ans = 0, cursink = n + 1;
    for (int i = 0, j = 0; i < c; i = j){
        flow.clean();
        for (;j < c && dist[ V[i] ] == dist[ V[j] ]; ++j){
            flow.AddEdge(cursink, V[j], 1);
        }
        ans += flow.GetMaxFlow(cursink, 1);
        ++cursink;
    }
    cout << ans << endl;

    return 0;
}

