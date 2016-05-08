#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOGN = 20;

int A[MAXN], ST[LOGN][MAXN];

void build(int n) {

    int h = ceil(log2(n)) + 1;

    for (int i = 0; i < n; i++) ST[0][i] = A[i];
    for (int i = 1; i < h; i++)
        for (int j = 0; j + (1<<i) <= n; j++)
            ST[i][j] = min(ST[i-1][j], ST[i-1][j+(1<<(i-1))]);
}

int RMQ(int l, int r) {    // range [l,r)
    int p = 31 - __builtin_clz(r-l);
    return min(ST[p][l],ST[p][r-(1<<p)]);
}

int main() {

    return 0;
}
