#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;
typedef vector<int> vi;

const int MAXN = 100005;
const int LOGN = 20;

int H[MAXN];        // index of node i in dfs path
ii path[MAXN << 1];
vi adjList[MAXN];

ii ST[LOGN][MAXN<<1];

void build(int n) {
    int h = ceil(log2(n+1));

    for (int i = 0; i < n; i++) ST[0][i] = path[i];
    for (int i = 1; i < h; i++)
        for (int j = 0; j + (1<<i) <= n; j++)
        ST[i][j] = min(ST[i-1][j], ST[i-1][j+(1<<(i-1))]);
}

int RMQ(int l, int r) {     // range [l,r)
    int p = 31 - __builtin_clz(r-l);
    return min(ST[p][l],ST[p][r-(1<<p)]).se;
}

int cnt = 0;
void dfs(int node, int depth){
    H[node] = cnt;

    path[cnt++] = ii(depth,node);
    for (int i = 0; i < adjList[node].size(); i++) {
        dfs(adjList[node][i],depth+1);

        path[cnt++] = ii(depth,node);
    }
}

int N, M, Q, v;

int main(){

    scanf("%d",&N);
    for (int u = 0; u < N; u++){
        scanf("%d",&M);
        for (int i = 0; i < M; i++){
            scanf("%d",&v);
            adjList[u].push_back(v);
        }
    }

    // rooted at 0
    dfs(0,0);
    build(cnt);

    scanf("%d",&Q);
    for (int i = 0, u, v, l, r; i < Q; i++){
        scanf("%d%d",&u,&v);

        l = H[u], r = H[v]; if (l > r) swap(l,r);

        printf("%d\n",RMQ(l,r+1));
    }

    return 0;
}
