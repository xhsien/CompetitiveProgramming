#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,int> PI;

#define fi first
#define se second

const LL INF = (1LL << 60);

int n, m, q, s;
LL dist[1005];

vector<PI> adjList[1005];

void dfs(int node) {
  dist[node] = -INF;
  for (int i = 0; i < adjList[node].size(); i++) {
    int neighbor = adjList[node][i].se;

    if (dist[neighbor] == -INF)
      continue;

    dfs(neighbor);
  }
}

int main() {

  while (scanf("%d%d%d%d", &n, &m, &q, &s), n || m || q || s) {
    for (int i = 0; i < 1005; i++) {
      adjList[i].clear();
    }

    for (int i = 0; i < m; i++) {
      int u, v; LL w;
      scanf("%d%d%Ld", &u, &v, &w);

      adjList[u].push_back(PI(w, v));
    }

    fill(dist, dist + n, INF); dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
      for (int u = 0; u < n; u++) {
        if (dist[u] == INF)
          continue;

        for (auto v : adjList[u]) {
          dist[v.se] = min(dist[v.se], dist[u] + v.fi);
        }
      }
    }

    // fix negative weight cycle
    for (int u = 0; u < n; u++) {
      for (auto v: adjList[u]) {
        if (dist[u] != INF && dist[v.se] > dist[u] + v.fi) {
          dfs(v.se);
        }
      }
    }

    for (int i = 0; i < q; i++) {
      int v;
      scanf("%d", &v);

      LL ans = dist[v];

      if (ans == INF) {
        printf("Impossible\n");
      } else if (ans == -INF) {
        printf("-Infinity\n");
      } else {
        printf("%Ld\n", ans);
      }
    }

    printf("\n");
  }

    return 0;
}