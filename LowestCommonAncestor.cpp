/* --- <O(nlgn),O(1)> --- */

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;
typedef vector<int> vi;

const int MAXN = 100005;
const int LOGN = 20;

int H[MAXN];        // index of node i in dfs path
ii path[MAXN<<1];
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

/* --- <O(nlgn),O(lgn)> --- */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int TC, N, Q;
int T[MAXN], L[MAXN], P[MAXN][20];	// direct parent, depth, ancestor
vector<int> adjList[MAXN];

void dfs(int node, int depth) {
	L[node] = depth;
	for (int i = 0; i < adjList[node].size(); i++) {
		int child = adjList[node][i];
		dfs(child,depth+1);
	}
}

int query(int u, int v) {
	int tmp;
	if (L[u] < L[v])
		tmp = u, u = v, v = tmp;

	int LOG2;
	for (LOG2 = 1; 1 << LOG2 <= L[u]; LOG2++); LOG2--;

	for (int i = LOG2; i >= 0; i--)
		if (L[u] - (1 << i) >= L[v])
			u = P[u][i];

	if (u == v)
		return u;

	for (int i = LOG2; i >= 0; i--)
		if (P[u][i] != -1 && P[u][i] != P[v][i])
			u = P[u][i], v = P[v][i];

	return T[u];
}

int main() {

	scanf("%d",&TC);
	for (int t = 1; t <= TC; t++) {

		// init
		memset(T,0,sizeof(T));
		memset(L,0,sizeof(L));
		memset(P,-1,sizeof(P));
		for (int i = 0; i < 1005; i++)
			adjList[i].clear();

		scanf("%d",&N);
		for (int i = 1, num_child; i <= N; i++) {
			scanf("%d",&num_child);
			for (int j = 0, child; j < num_child; j++) {
				scanf("%d",&child);

				T[child] = i;
				adjList[i].push_back(child);
			}
		}

		// find root
		int root;
		for (int i = 1; i <= N; i++)
			if (T[i] == 0)
				root = i;

		dfs(root,1);

		for (int i = 1; i <= N; i++)
			P[i][0] = T[i];
		for (int j = 1; 1 << j < N; j++)
			for (int i = 1; i <= N; i++)
				if (P[i][j-1] != -1)
					P[i][j] = P[P[i][j-1]][j-1];

		scanf("%d",&Q); printf("Case %d:\n", t);
		for (int i = 0, u, v; i < Q; i++) {
			scanf("%d%d",&u,&v);
			printf("%d\n", query(u,v));
		}
	}

	return 0;
}
