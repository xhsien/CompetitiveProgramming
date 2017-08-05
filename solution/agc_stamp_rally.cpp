#include <cstdio>
#include <vector>
#include <set>
#include <queue>
using namespace std;

const int maxn = 100005;

int n, m, q, a[maxn], b[maxn];
int x[maxn], y[maxn], z[maxn], ans[maxn];

struct node {
    int l;
    int r;
    set<int> s;
};

queue<node> Q;

class UnionFindDS {
private:
    vector<int> p, sz;   // parent, size
public:
    UnionFindDS() {}
    UnionFindDS(int N){
        p.assign(N,0); for (int i = 0; i < N; i++) p[i] = i;
        sz.assign(N,1);
    }
    int findSet(int i) { return p[i] == i ? i : p[i] = findSet(p[i]); }
    int sizeSet(int i) { return sz[findSet(i)]; }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
        if ((i = findSet(i)) == (j = findSet(j))) return;

        p[j] = i; sz[i] += sz[j];
    }
} uf;

int cur = 0;

void addEdges(int idx) {
    if (cur > idx) {
        cur = 0;
        uf = UnionFindDS(n);
    }

    while (cur < idx) {
        uf.unionSet(a[cur], b[cur]);
        cur++;
    }
}

int main() {

    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", a + i, b + i);

        a[i]--; b[i]--;
    }

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d%d%d", x + i, y + i, z + i);

        x[i]--; y[i]--;
    }

    uf = UnionFindDS(n);

    set<int> s;
    for (int i = 0; i < q; i++) 
        s.insert(i);

    // dfs
    Q.push({0, m, s});
    while (!Q.empty()) {
        node front = Q.front(); Q.pop();

        int l = front.l;
        int r = front.r;

        if (front.s.empty()) {
            continue;
        }

        if (r - l == 1) {
            for (auto idx : front.s)
                ans[idx] = l;
        } else if (r - l > 1) {
            int mid = (l + r) / 2;

            addEdges(mid);

            set<int> s1, s2;
            for (auto idx : front.s) {
                int size = uf.sizeSet(x[idx]) + (uf.isSameSet(x[idx], y[idx]) ? 0 : uf.sizeSet(y[idx]));
                if (size >= z[idx]) {
                    s1.insert(idx);
                } else {
                    s2.insert(idx);
                }
            }

            Q.push({l, mid, s1});
            Q.push({mid, r, s2});
        }
    }

    for (int i = 0; i < q; i++) {
        printf("%d\n", ans[i] + 1);
    }

    return 0;
}
