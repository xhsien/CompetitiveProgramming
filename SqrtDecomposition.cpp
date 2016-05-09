#include <bits/stdc++.h>
using namespace std;

const int SQRT = 350;

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
