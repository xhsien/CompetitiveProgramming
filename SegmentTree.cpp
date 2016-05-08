#include <bits/stdc++.h>
using namespace std;

class SegmentTree{
private:
    int n;
    vector<int> t;
    
    int combine(int a, int b){
        return a + b;
    }

    /* --- ADDITIONAL POWER-UPS --- */

    // combine function for storing sorted segments
    void combine(vector<int>& a, vector<int>& b, vector<int>& newV){
        newV.assign(a.size()+b.size(),0);

        merge(a.begin(),a.end(),b.begin(),b.end(),newV.begin());
    }
public:
    SegmentTree(vector<int>& v){          // build tree
        n = v.size();
        t.assign(n << 1, 0);
        
        for (int i = 0; i < n; i++) t[n+i] = v[i];
        for (int i = n-1; i > 0; i--) t[i] = combine(t[i<<1], t[i<<1|1]);
    }
    void modify(int p, int val){          // set v[p] = val
        for (t[p+=n] = val; p >>= 1; ) t[p] = combine(t[p<<1],t[p<<1|1]);
    }
    int query(int l, int r){              // query in range v[l,r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) res = combine(res,t[l++]);
            if (r&1) res = combine(res,t[--r]);
        }
        return res;
    }
    int ncquery(int l, int r){            // query for non-commutative combine function
        int resl, resr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) resl = combine(resl, t[l++]);
            if (r&1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }

    /* --- ADDITIONAL POWER-UPS --- */

    // query routine minimum prefix sum that is larger or equal to K
    int query(int k) {
        if (t[1] < k)
            return -1;

        int p = 1;
        while (p < n)
            if (t[p<<=1] < k)
                k -= t[p++];
        return p - n + 1;
    }
};

class InvertedSegmentTree{
private:
    int n;
    vector<int> t;
public:
    InvertedSegmentTree(vector<int> v){
        n = v.size();
        t.assign(n << 1, 0);

        for (int i = 0; i < n; i++) t[n+i] = v[i];
    }
    void modify(int l, int r, int val){                 // set v[l,r) += val
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) t[l++] += val;
            if (r&1) t[--r] += val;
        }
    }
    int compute(int p){                                 // compute v[p]
        int res = 0;
        for (p += n; p > 0; p >>=1 ) res += t[p];
        return res;
    }
    void push(){                                        // apply every modification to v
        for (int i = 1; i < n; i++){
            t[i<<1]   += t[i];
            t[i<<1|1] += t[i];
            t[i] = 0;
        }
    }
};

/* --- Recursive Implementation --- */

int N;
vector<int> v, t;

int combine(int i, int j) {
    return i + j;
}

void build(int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        t[id] = v[l];
        return;
    }

    int mid = (l + r) / 2;
    build(id<<1  , l, mid);
    build(id<<1|1, mid, r);
    t[id] = combine(t[id<<1], t[id<<1|1]);
}

void modify(int p, int val, int id = 1, int l = 0, int r = N) {     // set v[p] = val
    if (r - l < 2) {
        t[id] += val;
        return;
    }

    int mid = (l + r) / 2;
    if (p < mid)
        modify(p, val, id<<1  , l, mid);
    else
        modify(p, val, id<<1|1, mid, r);
    
    t[id] = combine(t[id<<1], t[id<<1|1]);
}

int query(int x, int y, int id = 1, int l = 0, int r = N) {         // query in range [l,r)
    if (x >= r || l >= y) return 0;
    if (x <= l && r <= y) return t[id];

    int mid = (l + r) / 2;
    return combine(query(x,y,id<<1,l,mid), query(x,y,id<<1|1,mid,r));
}

int main() {

    return 0;
}
