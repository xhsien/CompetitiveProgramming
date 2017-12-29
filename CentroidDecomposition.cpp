#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> ii;

#define fi first
#define se second

const int MAXN = 100005;
const int LOGN = 20;
const int INF = 1e9;

int par[MAXN], size[MAXN];
vector<int> adjList[MAXN];

// for centroid
int c_par[MAXN]; bool isCentroid[MAXN];
vector<int> c_adjList[MAXN];

// compute the size and parent of each subtree
// initial call with preprocess(root)
int preprocess(int u) {
    size[u] = 1;
    for (int v : adjList[u]) {
        if (v == par[u])
            continue;
    
        par[v] = u;
        size[u] += preprocess(v);
    }

    return size[u];
}

// return centroid of the tree rooted at u of size n
int find_centroid(int u, int n) {
    isCentroid[u] = true;

    int maxChildSize = 0, maxChildId = 0;
    for (int v : adjList[u]) {
        if (v == par[u] || isCentroid[v])
            continue;

        if (maxChildSize < size[v]) {
            maxChildSize = size[v];
            maxChildId = v;
        }
    }

    if (maxChildSize <= n / 2) {
        return u;
    } else {
        isCentroid[u] = false;

        int centroid = find_centroid(maxChildId, n);
        
        size[u] -= size[centroid]; // update size
        
        return centroid;
    }
}

// must call preprocess before centroid_decomposition
// resulting tree is stored in c_adjList
// initial call with centroid_decomposition(root)
int centroid_decomposition(int u) {
    int u_centroid = find_centroid(u, size[u]);

    for (int v : adjList[u_centroid]) {
        if (isCentroid[v])
            continue;

        int v_centroid = centroid_decomposition(v == par[u_centroid] ? u : v);

        c_adjList[u_centroid].push_back(v_centroid);
        c_par[v_centroid] = u_centroid;
    }

    return u_centroid;
}

int main() {

    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    preprocess(0);
    centroid_decomposition(0);

    // centroid tree view
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int v : c_adjList[i]) {
            cout << v << " ";
        } cout << endl;
    }

    return 0;
}