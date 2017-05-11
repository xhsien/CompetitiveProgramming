#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

/*
 * @param n: number of nodes
 * @param adjList: adjacency list representation of the graph
 * @param source: source for shortest path
 *
 * @return dist[i]: shortest distance from source to node i, -1 if unreachable
 */
void Dijkstra(int n, vector<ii> adjList[], int source, vector<int>& dist) {
  dist.assign(n, -1); dist[source] = 0;
  priority_queue<ii,vector<ii>,greater<ii>> pq; pq.push({0, source});
  while (!pq.empty()) {
    int cost, u;
    tie(cost, u) = pq.top(); pq.pop();

    if (cost > dist[u]) continue;

    for (ii neighbor : adjList[u]) {
      int w, v;
      tie(w, v) = neighbor;
      if (dist[v] == -1 || dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }
}

int main() {

  return 0;
}