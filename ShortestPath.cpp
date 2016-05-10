/* --- Single-Source Shortest Path --- */

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int, int> ii;

const int MAXN = 100005;
const int INF = 1 << 30;
 
int V, E, S, d[MAXN];
vector<ii> adjList[MAXN];
 
int main() {

    scanf("%d%d%d",&V,&E,&S);
    for (int i = 0, u, v, w; i < E; i++) {
        scanf("%d%d%d",&u,&v,&w);

        adjList[u].push_back(ii(w,v));
      //adjList[v].push_back(ii(w,u));
    }
 
    fill(d,d+V,INF); d[S] = 0;
    priority_queue< ii,vector<ii>,greater<ii> > pq; pq.push(ii(0,S));
    while(!pq.empty()) {
        ii p = pq.top(); pq.pop();
        int dist = p.fi, u = p.se;
 
        if(dist > d[u]) continue;
 
        for (int i = 0; i < adjList[u].size(); i++) {
            ii &v = adjList[u][i];
 
            if (d[v.se] > d[u] + v.fi) {
                d[v.se] = d[u] + v.fi;
                pq.push(ii(d[v.se], v.se));
            }
        }
    }
 
    for (int i = 0; i < V; i++)
        if (d[i] == INF)
            puts("INF");
        else
            printf("%d\n",d[i]);
 
    return 0;
}

/* --- Shortest Path in Tree --- */

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;

const int MAXN = 100005;
const int LOGN = 20;

int H[MAXN], D[MAXN];        // index of node i in dfs path
ii path[MAXN<<1];
vector<ii> adjList[MAXN];

ii ST[LOGN][MAXN<<1];

void build(int n) {
    int h = ceil(log2(n+1));

    for (int i = 0; i < n; i++) ST[0][i] = path[i];
    for (int i = 1; i < h; i++)
        for (int j = 0; j + (1<<i) <= n; j++)
        ST[i][j] = min(ST[i-1][j], ST[i-1][j+(1<<(i-1))]);
}

int LCA(int l, int r) {     // range [l,r)
    int p = 31 - __builtin_clz(r-l);
    return min(ST[p][l],ST[p][r-(1<<p)]).se;
}

int cnt = 0;
void dfs(int node = 0, int par = 0, int depth = 0, int dist = 0){
    H[node] = cnt;
    D[node] = dist;

    path[cnt++] = ii(depth,node);
    for (int i = 0; i < adjList[node].size(); i++) {
        int child = adjList[node][i].se;
        if (child == par) continue;

        dfs(child,node,depth+1,dist+adjList[node][i].fi);

        path[cnt++] = ii(depth,node);
    }
}

int N, Q;

int main(){

    scanf("%d",&N);
    for (int i = 1, u, v, w; i < N; i++) {
        scanf("%d%d%d",&u,&v,&w);

        adjList[u].push_back(ii(w,v));
        adjList[v].push_back(ii(w,u));
    }

    dfs();
    build(cnt);

    scanf("%d",&Q);
    for (int i = 0, u, v, l, r; i < Q; i++){
        scanf("%d%d",&u,&v);

        l = H[u], r = H[v]; if (l > r) swap(l,r);

        int lca = LCA(l,r+1);

        long long ans = D[u] + D[v] - 2 * D[lca];

        printf("%lld\n",ans);
    }

    return 0;
}
