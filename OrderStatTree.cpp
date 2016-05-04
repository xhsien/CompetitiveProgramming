#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

// old compiler
//typedef tree<int, null_mapped_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

pbds S;

int main() {

    S.insert(10);            // insert 10 to S
    S.erase(100);            // remove 100 from S
    S.find_by_order(0);      // returns pointer to the 0-th element (0-indexed)
    S.order_of_key(20);      // returns the number of elements strictly less than 20

    return 0;
}
