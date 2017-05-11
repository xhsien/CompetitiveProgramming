#include <bits/stdc++.h>
using namespace std;

/*
 * @param n: number of nodes
 * @param adjList[]: adjacency list representation of the graph
 * 
 * @return if the graph contains cycle
 * @return order of topological sort
 */
bool KahnAlgorithm(int n, vector<int> adjList[], queue<int>& order) {
  vector<int> inDegree; inDegree.assign(n, 0);
  for (int node = 0; node < n; node++) {
    for (int child : adjList[node]) {
      inDegree[child]++;
    }
  }

  queue<int> q;
  for (int node = 0; node < n; node++) {
    if (inDegree[node] == 0) {
      q.push(node);
    }
  }

  while (!q.empty()) {
    int node = q.front(); q.pop();
    order.push(node);

    for (int child : adjList[node]) {
      inDegree[child]--;
      if (inDegree[child] == 0) {
        q.push(child);
      }
    }
  }

  return order.size() == n;
}

int main() {

  return 0;
}