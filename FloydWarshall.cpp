#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
const long long INF = 1e9;

/*
 * @param          n: number of nodes
 * @param adjMat[][]: adjacency matrix representation of the graph
 *                    mark adjMat[u][v] to INF if no edge exist between them
 * 
 * @return adjMat[u][v]: shortest path between u and v 
 * @return parent[u][v]: parent of v in shortest path u->v
 */
void floydWarshall(int n, int adjMat[MAXN][MAXN], int parent[MAXN][MAXN]) {
  for (int k = 0; k < n; k++) 
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (adjMat[i][k] != INF && adjMat[k][j] != INF && adjMat[i][j] > adjMat[i][k] + adjMat[k][j])
            adjMat[i][j] = adjMat[i][k] + adjMat[k][j], parent[i][j] = parent[k][j];
}

int main() {

  return 0;
}