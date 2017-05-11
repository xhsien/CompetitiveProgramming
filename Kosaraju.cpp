#include <bits/stdc++.h>
using namespace std;

vector<int> visited, group;
stack<int> order;

void dfs(int u, vector<int> adjList[], int id = 0) {
  visited[u] = 1;
  order.push(u);
  for (int v : adjList[u]) {
    if (!visited[v]) {
      dfs(v, adjList, id);
    }
  }
  group[u] = id;
}

void Kosaraju(int n, vector<int> adjList[]) {
  visited.assign(n, 0); group.assign(n, 0);
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i, adjList);
    }
  }

  vector<int> adjListT[n];
  for (int i = 0; i < n; i++) {
    for (int v : adjList[i]) {
      adjListT[v].push_back(i);
    }
  }

  int groupNum = 0;
  visited.assign(n, 0); group.assign(n, 0);
  while (!order.empty()) {
    int node = order.top(); order.pop();
    if (!visited[node]) {
      dfs(node, adjListT, groupNum++);
    }
  }
}

int main() {

  return 0;
}