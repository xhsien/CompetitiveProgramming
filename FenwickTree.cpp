#include <bits/stdc++.h>
using namespace std;

#define LSONE(S) (S & (-S))

class FenwickTree {
private:
    vector<int> t;
public:
    FenwickTree(int n){
        t.assign(n+1,0);
    }
    void modify(int p, int v){
        for (; p < (int)t.size(); p += LSONE(p)) t[p] += v;
    }
    int query(int r) {                      // inclusive
        int sum = 0;
        for (; r; r -= LSONE(r)) sum += t[r];
        return sum;
    }
};

class FenwickTreeRange{
private:
    vector<int> fw, fw2;
    int size;
public:
    FenwickTreeRange(int N){
        fw.assign(N+1,0);
        fw2.assign(N+1,0);

        size = N+1;
    }
    void update(int l, int r, int val) {    // inclusive
        for (int tl = l; tl < size; tl += LSONE(tl))
            fw[tl] += val, fw2[tl] -= val * (l - 1);
        for (int tr = r + 1; tr < size; tr += LSONE(tr))
            fw[tr] -= val, fw2[tr] += val * r;
    }
    int sum(int r){                         // inclusive
        int res = 0;
        for (int tr = r; tr; tr -= LSONE(tr))
            res += fw[tr] * r + fw2[tr];
        return res;
    }
};

class Fenwick2D{
private:
    int R, C;
    vector< vector<int> > fw;
public:
    Fenwick2D(int r, int c) {
        R = r; C = c;
        fw.assign(R, vector<int>(C,0));
    }
    void update(int row, int col, int val) {
        for (int r = row; r < R; r += LSONE(r))
            for(int c = col; c < C; c += LSONE(c)) 
                fw[r][c] += val;
    }
    int sum(int row, int col) {                 // inclusive
        int res = 0;
        for (int r = row; r; r -= LSONE(r))
            for(int c = col; c; c -= LSONE(c)) 
                res += fw[r][c];
        return res;
    }
    int range_sum(int x1, int y1, int x2, int y2) { 
        return sum(x2, y2) - sum(x1-1, y2) - sum(x2, y1-1) + sum(x1-1, y1-1);
    }
};

int main(){
    
    return 0;
}
