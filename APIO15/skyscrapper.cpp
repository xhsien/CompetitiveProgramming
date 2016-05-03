#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef pair<int,int> ii;

const int MAXN = 300005;

int N, M, S, E, x, p, dist[MAXN];
vector<int> B[MAXN];

int main() {

    scanf("%d%d",&N,&M);

    scanf("%d%d",&x,&p); S = x; B[x].push_back(p);
    scanf("%d%d",&x,&p); E = x; B[x].push_back(p);
    for (int i = 2; i < M; i++) {
        scanf("%d%d",&x,&p);

        B[x].push_back(p);
    }

    for (int i = 0; i < N; i++) {
        sort(B[i].begin(), B[i].end());
        B[i].erase(unique(B[i].begin(), B[i].end()),B[i].end());
    }

    memset(dist,-1,sizeof(dist)); dist[S] = 0;
    priority_queue< ii,vector<ii>,greater<ii> > pq; pq.push(ii(0,S));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();

        int u = front.se;
        int d = front.fi;

        if (d > dist[u]) continue;

        for (int i = 0; i < B[u].size(); i++) {
            p = B[u][i];
            for (int j = u + p; j < N; j += p) {
                if (dist[j] == -1 || dist[j] > dist[u] + (j - u) / p) {
                    dist[j] = dist[u] + (j - u) / p;
                    pq.push(ii(dist[j],j));
                }
                if (binary_search(B[j].begin(), B[j].end(),p))
                    break;
            }
            for (int j = u - p; j >= 0; j -= p) {
                if (dist[j] == -1 || dist[j] > dist[u] + (u - j) / p) {
                    dist[j] = dist[u] + (u - j) / p;
                    pq.push(ii(dist[j],j));
                }
                if (binary_search(B[j].begin(), B[j].end(),p))
                    break;
            }
        }

    }

    printf("%d\n", dist[E]);

    return 0;
}
