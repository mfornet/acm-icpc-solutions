#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

template<typename flow_type>
struct dinic
{
    struct edge
    {
        size_t src, dst, rev;
        flow_type flow, cap;
    };

    int n;
    vector<vector<edge>> adj;

    dinic(int n) : n(n), adj(n), level(n), q(n), it(n) {}

    void add_edge(size_t src, size_t dst, flow_type cap, flow_type rcap = 0)
    {
        adj[src].push_back({src, dst, adj[dst].size(), 0, cap});
        if (src == dst) adj[src].back().rev++;
        adj[dst].push_back({dst, src, adj[src].size() - 1, 0, rcap});
    }

    vector<int> level, q, it;

    bool bfs(int source, int sink)
    {
        fill(level.begin(), level.end(), -1);
        for (int qf = level[q[0] = sink] = 0, qb = 1; qf < qb; ++qf)
        {
            sink = q[qf];
            for (edge &e : adj[sink])
            {
                edge &r = adj[e.dst][e.rev];
                if (r.flow < r.cap && level[e.dst] == -1)
                    level[q[qb++] = e.dst] = 1 + level[sink];
            }
        }
        return level[source] != -1;
    }

    flow_type augment(int source, int sink, flow_type flow)
    {
        if (source == sink) return flow;
        for (; it[source] != (int)adj[source].size(); ++it[source])
        {
            edge &e = adj[source][it[source]];
            if (e.flow < e.cap && level[e.dst] + 1 == level[source])
            {
                flow_type delta = augment(e.dst, sink,
                                  min(flow, e.cap - e.flow));
                if (delta > 0)
                {
                    e.flow += delta;
                    adj[e.dst][e.rev].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }

    flow_type max_flow(int source, int sink, bool reset=true)
    {
        if (reset){
            for (int u = 0; u < n; ++u)
                for (edge &e : adj[u]) e.flow = 0;
        }

        flow_type flow = 0;
        flow_type oo = numeric_limits<flow_type>::max();

        while (bfs(source, sink))
        {
            fill(it.begin(), it.end(), 0);
            for (flow_type f; (f = augment(source, sink, oo)) > 0;)
                flow += f;

        }
        return flow;
    }
};

struct edge{
    int u, v, c;
};

int main(){
    int nNode, nEdge;
    double v, alpha;

    cin >> nNode >> nEdge;
    cin >> v >> alpha;

    vector<edge> idEdge( nEdge );
        map<pii,int> index;

    for (int i = 0; i < nEdge; ++i){
        int u, v, cap;
        cin >> u >> v >> cap;
        idEdge[i] = {u, v, cap};
                index[ pii(u,v) ] = i;
    }

    int FLAG = 0, FLUBBER = 1, WATER = 2, SINK = 3;

    dinic<double> network( nNode + 1 );
    network.add_edge(FLAG, WATER, 0, 0);

    for (auto e : idEdge)
        network.add_edge( e.u, e.v, e.c, e.c );

    double lo = 0, hi = network.max_flow(WATER, SINK);

    auto evaluate = [&](double x, bool print=false){
        network.adj[FLAG ][0].cap = x;
        network.adj[WATER][0].cap = x;
        double tWater = network.max_flow(FLAG, SINK);

        network.adj[FLAG][0].cap = network.adj[WATER][0].cap = 0.;
        network.adj[FLAG][0].flow = network.adj[WATER][0].flow = 0.;
        double tFlubber = network.max_flow(FLUBBER, SINK, false);

                if (print){
                    for (auto &u : network.adj){
                        for (auto &e : u){
                            e.cap = max(e.flow, 0.);
                            e.flow = 0;
                        }
                    }

            network.adj[ FLAG ][0].cap = x;
                    vector< pair<double,double> > answer( nEdge ); 
                    network.max_flow(FLAG, SINK);

                    for (auto &u : network.adj){
                        for (auto &e : u){
                            if (e.src == FLAG || e.dst == FLAG || e.cap < 1e-9) continue;

                            int a = e.src, b = e.dst, idx;
                            double sign = +1;
                            if (index.find( pii(a, b) ) != index.end())
                                idx = index[ pii(a, b) ];
                            else{
                                idx = index[ pii(b, a) ];
                                sign = -1;
                            }

                            answer[ idx ] = { sign * (e.cap - e.flow), sign * e.flow };
                        }
                    }

                    cout.precision(10);
                    for (auto p : answer)
                        cout << fixed << p.first / v << " " << p.second << endl;
                }

        return pow(tFlubber / v, alpha) * pow(tWater, 1. - alpha);
    };

    const int MAGIC = 50;

    for (int i = 0; i < MAGIC; ++i){
        double delta = (hi - lo) * 0.45;
        double u = lo + delta, v = hi - delta;

        double x = evaluate(u), y = evaluate(v);
        if (x > y) hi = v;
        else       lo = u;
    }

    double water = (hi + lo) / 2;

    cout.precision(11);
    cout << fixed << evaluate(water, true) << endl;

    return 0;
}