#include <bits/stdc++.h>
using namespace std;

class UnionFindDS{
private:
    vector<int> p, sz;   // parent, size
    int num;
public:
    UnionFindDS(int N){
        p.assign(N,0); for (int i = 0; i < N; i++) p[i] = i;
        sz.assign(N,1); num = N;
    }
    int numSets(){ return num; }
    int findSet(int i){ return p[i] == i ? i : p[i] = findSet(p[i]); }
    int sizeSet(int i){ return sz[findSet(i)]; }
    bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }
    void unionSet(int i, int j){
        if ((i = findSet(i)) == (j = findSet(j))) return;
        
        num--;
        p[j] = i; sz[i] += sz[j];
    }
};

int main() {

    return 0;
}
