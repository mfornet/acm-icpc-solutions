#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define DB(x) cout << #x << " = " << x << endl << flush;
#define SZ(x) (int)((x).size())
#define MP make_pair

typedef long long int64;
typedef pair<int,int> pii;
typedef vector<int> vi;

const int oo = 0x3f3f3f3f;
const int INF = oo;
const double EPS = 1e-9;
const int MAXN = (int)1e5 + 10;

namespace MCF
{
    struct edge
    {
        int dest, cap, flow;
        int64 cost;
        int next;
        edge() {}
        edge(int dest, int cap, int64 cost, int next) :
            dest(dest), cap(cap), cost(cost), next(next)
            {
                flow = 0;
            }
    };
    const int MAXV = 1005;
    const int MAXE = 1000000;
    int nodes, source, sink;
    int size;
    edge g[ MAXE ];
    int first[ MAXV ];
    int nLast[ MAXV ]; //last node
    int eLast[ MAXV ]; //last edge
    int64 cst[ MAXV ];
    void initialize(int __nodes, int __source, int __sink)
    {
        size = 0;
        nodes = __nodes;
        source = __source;
        sink = __sink;
        for (int i = 0; i < nodes; i++)
            first[ i ] = -1;
    }
    void addEdge(int u, int v, int c, int64 cost)
    {
//      cout << u << " " << v << " " << c << " " << cost << endl;
        g[ size ] = edge(v, c, +cost, first[u]);
        first[u] = size++;
        g[ size ] = edge(u, 0, -cost, first[v]);
        first[v] = size++;
    }
    pair<int,int64> maxFlowMinCost()
    {
        int flow = 0;
        int64 flowCost = 0;
        while (true)
        {
            priority_queue<pair<int64,int> > Q;
            for (int i = 0; i < nodes; i++)
                cst[i] = INF;
            cst[source] = 0;
            Q.push(make_pair(0, source));

            while (!Q.empty())
            {
                int u = Q.top().second;
                int64 c = -Q.top().first;
                Q.pop();
                if (u == sink) break;
                for (int k = first[u]; k != -1; k = g[k].next)
                {
                    int newU = g[k].dest;
                    int64 newC = g[k].cost + c;
                    if (g[k].cap> g[k].flow&& newC < cst[newU])
                    {
                        cst[newU] = newC;
                        //keep track//
                        nLast[newU] = u;
                        eLast[newU] = k;
                        //keep track//
                        Q.push(make_pair(-newC, newU));
                    }
                }
            }
            if (cst[sink] == INF) break;

            int push = INF;
            for (int u = sink; u != source; u = nLast[u])
                push = min(push, g[ eLast[u] ].cap
                                 - g[ eLast[u] ].flow);

            flow += push;
            flowCost += cst[sink] * push;
            for (int u = sink; u != source; u = nLast[u])
            {
                g[ eLast[u]   ].flow += push;
                g[ eLast[u]^1 ].flow -= push;
            }
        }
        return make_pair(flow, flowCost);
    }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    MCF::initialize(2 * n + 4, 0, 1);

    MCF::addEdge(0, 2, k, 0);
    MCF::addEdge(3, 1, 1, 0);

    for (int i = 0; i < n; ++i){
        MCF::addEdge(0, 2 * (i + 2), 1, 0);
        MCF::addEdge(2 * (i + 2) + 1, 1, 1, 0);

        for (int j = 0; j < n - i; ++j){
            int v; cin >> v;
            MCF::addEdge(2 * (i + 1), 2 * (i + 1) + 2 * j + 3, 1, v);
        }
    }

    auto ans = MCF::maxFlowMinCost();

    cout << ans.second << endl;

    return 0;
}