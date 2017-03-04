#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<LL> VI;
typedef vector<VI> VVI;

const LL INF = (1LL << 60);

struct FloydWarshall {
  int n;
  VVI adjMat, par;

  FloydWarshall(int _n): n(_n) {
    adjMat = VVI(n, VI(n, INF));
    par = VVI(n, VI(n, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j)
          adjMat[i][j] = 0;

        par[i][j] = i;
      }
    }
  }

  void addEdge(int u, int v, LL w) {
    adjMat[u][v] = min(adjMat[u][v], w);
  }

  void AllPairShortestPath() {
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (adjMat[i][k] != INF && adjMat[k][j] != INF && adjMat[i][j] > adjMat[i][k] + adjMat[k][j]) {
            adjMat[i][j] = adjMat[i][k] + adjMat[k][j];
            par[i][j] = par[k][j];
          }
        }
      }
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (adjMat[i][k] != INF && adjMat[k][j] != INF && adjMat[k][k] < 0) {
            adjMat[i][j] = -INF;
          }
        }
      }
    }
  }

  /*
   *  INF : u cannot reach v
   * -INF : negative cycle
   *  Else : shortest distance between u and v
   */
  LL distance(int u, int v) {
    return adjMat[u][v];
  }

  void path(int u, int v, vector<int>& p) {
    if (distance(u, v) == INF || distance(u, v) == -INF)
      return;

    if (u != v) 
      path(u, par[u][v], p);
    p.push_back(v);
  }
};

/*
 * This program solves KATTIS ALLPAIRSPATH
 */

int main() { 

  int n, m, q;
  while (scanf("%d%d%d", &n, &m, &q), n || m || q) {
    
    FloydWarshall wf(n);

    for (int i = 0; i < m; i++) {
      int u, v; LL w;
      scanf("%d%d%Ld", &u, &v, &w);

      wf.addEdge(u, v, w);
    }

    wf.AllPairShortestPath();

    for (int i = 0; i < q; i++) {
      int u, v;
      scanf("%d%d", &u, &v);

      LL ans = wf.distance(u, v);

      if (ans == INF)
        printf("Impossible\n");
      else if (ans == -INF)
        printf("-Infinity\n");
      else 
        printf("%Ld\n", ans);
    }

    printf("\n");
  }

  return 0;
}