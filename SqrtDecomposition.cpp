#include <bits/stdc++.h>
using namespace std;

const int SQRT = 350;

/* --- SQRT Decomposition --- */

vector<int> v;

int block[SQRT][SQRT], val[SQRT];

void build() {
    for (int i = 0; i < v.size(); i++)
        block[i / SQRT][i % SQRT] = v[i];

    for (int i = 0; i < SQRT; i++)
        for (int j = 0; j < SQRT; j++)
            val[i] = max(val[i],block[i][j]);
}

void query(int l, int r) {          // inclusive
    int ans = 0, L = l / SQRT + 1, R = r / SQRT;
    if (L < R) {
        for (int i = l, end = L * SQRT; i < end; i++)
            ans = max(ans,v[i]);
        for (int i = L; i < R; i++)
            ans = max(ans,val[i]);
        for (int i = R * SQRT; i <= r; i++)
            ans = max(ans,v[i]);
    } else {
        for (int i = l; i <= r; i++)
            ans = max(ans,v[i]);
    }
}

void modify(int p, int x) {
    block[p / SQRT][p % SQRT] = v[p] = x;
    for (int i = 0, b = p / SQRT; i < SQRT; i++)
        val[p] = max(val[b],block[b][i]);
}

/* --- Mo's Algorithm --- */

struct Query {
    int l, r, id;

    Query (){}
    Query (int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}

    bool operator < (const Query& b) const {
        return (l / SQRT == b.l / SQRT ? r > b.r : l / SQRT < b.l / SQRT);
    }
};

int main() {

    return 0;
}
