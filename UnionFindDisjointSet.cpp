#include <bits/stdc++.h>
using namespace std;

class UnionFindDisjointSet {
private:
  int n;
  vector<int> parent, size;
public:
  UnionFindDisjointSet(int _n) : n(_n) {
    parent.assign(n, 0);
    for (int i = 0; i < n; i++) 
      parent[i] = i;

    size.assign(n, 1);
  }

  int findSet(int i) {
    return parent[i] == i ? i : parent[i] = findSet(parent[i]);
  }

  bool isSameSet(int i, int j) {
    return findSet(i) == findSet(j);
  }

  int sizeOf(int i) {
    return size[findSet(i)];
  }

  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) {
      i = findSet(i);
      j = findSet(j);
      
      parent[i] = j;
      size[j] += size[i];
    } 
  }
};

int main() {

  return 0;
}