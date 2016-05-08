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

/* --- Segment Trees for range increment range gcd query --- */

class InvertedSegmentTree{
private:
    int n;
    vector<int> t;
public:
    InvertedSegmentTree() {}
    InvertedSegmentTree(int _n) {
        n = _n + 1;
        t.assign(n << 1, 0);
    }
    void modify(int l, int r, int val) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) t[l++] += val;
            if (r&1) t[--r] += val;
        }
    }
    int compute(int p) {
        int res = 0;
        for (p += n; p > 0; p >>=1 ) res += t[p];
        return res;
    }
} st1;

class SegmentTree {
private:
    int n;
    vector<int> t;
public:
    SegmentTree() {}
    SegmentTree(int _n) {
        n = _n + 1;
        t.assign(n << 1, 0);
    }
    void modify(int p, int val) {
        for (t[p+=n] = val; p >>= 1; ) t[p] = gcd(t[p<<1],t[p<<1|1]);
    }
    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1){
            if (l&1) res = gcd(res,t[l++]);
            if (r&1) res = gcd(res,t[--r]);
        }
        return res;
    }
} st2;

void modify(int l, int r, int val) {    // increase a[l..r) by val
    st1.modify(l, r, val);
    st2.modify(l,  val);
    st2.modify(r, -val);
}

int query(int l, int r) {               // gcd of range [l..r)
    return gcd(st1.compute(l), st2.query(l+1,r));
}

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

/* --- Recursive Implementation with Lazy Propagation --- */

int N;
vector<int> v, t, lazy;

int combine(int i, int j) {
    return i + j;
}

void update(int id, int l, int r, int val) {      // increase interval [l..r) by val
    lazy[id] += val;
    t[id] += (r - l) * val;
}

void shift(int id, int l, int r) {                // pass information to children
    int mid = (l + r) / 2;
    update(id<<1  , l, mid, lazy[id]);
    update(id<<1|1, mid, r, lazy[id]);
    lazy[id] = 0;
}

void modify(int x, int y, int val, int id = 1, int l = 0, int r = N) {
    if (x >= r || l >= y) return;
    if (x <= l && r <= y) {
        update(id, l, r, val);
        return;
    }

    shift(id, l, r);
    int mid = (l + r) / 2;
    modify(x, y, val, id<<1  , l, mid);
    modify(x, y, val, id<<1|1, mid, r);
    t[id] = combine(t[id<<1], t[id<<1|1]);
}

int query(int x, int y, int id = 1, int l = 0, int r = N) {
    if (x >= r || l >= y) return 0;
    if (x <= l && r <= y) return t[id];

    shift(id, l, r);
    int mid = (l + r) / 2;
    return combine(query(x,y,id<<1,l,mid), query(x,y,id<<1|1,mid,r));
}

/* --- Recursive Implementation with Persistency --- */

int NEXT_FREE_INDEX = 1;

int N;
vector<int> v, t, root;

vector<int> L, R;

int combine(int i, int j) {
    return i + j;
}

void build(int id = 0, int l = 0, int r = N) {
    if (r - l < 2) {
        t[id] = v[l];
        return;
    }

    int mid = (l + r) / 2;
    L[id] = NEXT_FREE_INDEX++;
    R[id] = NEXT_FREE_INDEX++;
    build(L[id], l, mid);
    build(R[id], mid, r);
    t[id] = combine(t[L[id]], t[R[id]]);
}

int modify(int p, int val, int id, int l = 0, int r = N) {  // root[i] = modify()
    int ID = NEXT_FREE_INDEX++;
    if (r - l < 2) {
        t[ID] = (v[p] += val);
        return ID;
    }

    int mid = (l + r) / 2;
    L[ID] = L[id], R[ID] = R[id];       // in case not updating L[ID] or R[ID]
    if (p < mid) 
        L[ID] = modify(p, val, L[ID], l, mid);
    else
        R[ID] = modify(p, val, R[ID], mid, r);
    return ID;
}

int query(int x, int y, int id, int l = 0, int r = N) {
    if (x >= r || l >= y) return 0;
    if (x <= l && r <= y) return t[id];

    int mid = (l + r) / 2;
    return combine(query(x, y, L[id], l, mid), query(x, y, R[id], mid, r));
}

int main() {

    return 0;
}
