#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOGN = 20;

/*
 * @param arr: static array
 * @param   n: size of arr
 *
 * @return sparseTable
 */
void build(int arr[], int n, int sparseTable[LOGN][MAXN]) {

    int h = ceil(log2(n)) + 1;

    for (int i = 0; i < n; i++)
    	sparseTable[0][i] = arr[i];
    for (int i = 1; i < h; i++)
        for (int j = 0; j + (1<<i) <= n; j++)
            sparseTable[i][j] = min(sparseTable[i-1][j], sparseTable[i-1][j+(1<<(i-1))]);
}

/*
 * @param range[l,r)
 * @param sparseTable
 *
 * @return range minimum query
 */
int RMQ(int l, int r, int sparseTable[LOGN][MAXN]) {    // range [l,r)
    int p = 31 - __builtin_clz(r-l);

    return min(sparseTable[p][l], sparseTable[p][r - (1 << p)]);
}

int main() {

    return 0;
}