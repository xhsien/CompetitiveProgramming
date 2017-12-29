#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000;

struct Edge {
    int u, v, w;

    Edge(int u, int v, int w) : u(u), v(v), w(w) {}

    // order edges by weight
    bool operator <(const Edge& x) const {
        return w < x.w;
    }
};

int edmonds(vector<Edge>& edgeList, int V, int R) {
    
    // determine min cost of edge entering each vertex
    vector<Edge> minInEdge(V, Edge(-1, -1, INF));
    for (Edge e : edgeList) {
        minInEdge[e.v] = min(minInEdge[e.v], e);
    } minInEdge[R] = Edge(-1, R, 0);

    // assign vertices to their cyclic group
    vector<int> group(V, 0);
    vector<bool> visited(V, false), isCycleGroup(V, false); int cnt = 0;
    for (int i = 0; i < V; i++) {
        if (visited[i])
            continue;

        int node = i; vector<int> path;
        while (node != -1 && !visited[node]) {
            visited[node] = true;
            path.push_back(node);
            node = minInEdge[node].u;
        }

        bool isCycle = false;
        for (int v : path) {
            group[v] = cnt;
            if (v == node)
                isCycleGroup[cnt] = isCycle = true;
            if (!isCycle)
                cnt++;
        }

        if (isCycle)
            cnt++;
    }

    // when there are no cycles
    if (cnt == V) {
        int result = 0;
        for (Edge e : minInEdge)
            result += e.w;
        return result;
    }

    int result = 0;
    for (Edge e : minInEdge)
        if (isCycleGroup[group[e.v]])
            result += e.w;

    // form new graph with groups
    vector<Edge> n_edgeList;
    for (Edge e : edgeList) {
        int u = group[e.u], v = group[e.v], w = e.w;
        if (u == v)
            continue;
        else
            n_edgeList.push_back(Edge(u, v, w - (isCycleGroup[v] ? minInEdge[e.v].w : 0)));
    }

    return result + edmonds(n_edgeList, cnt, group[R]);
}

int main() {

    int V, E, R; vector<Edge> edgeList;
    scanf("%d%d%d", &V, &E, &R);
    for (int i = 0, u, v, w; i < E; i++) {
        scanf("%d%d%d", &u, &v, &w);

        edgeList.push_back(Edge(u, v, w));
    }

    int result = edmonds(edgeList, V, R);

    printf("%d\n", result);

    return 0;
}
