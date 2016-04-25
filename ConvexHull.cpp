#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class ConvexHull {
private:
    struct Line {
        ll m, c;

        Line (ll _m, ll _c, int _id) : m(_m), c(_c) {}

        ll pass(ll x) {
            return m * x + c;
        }
    };
    #define sz(x) (int)(x).size()
private:
    deque<Line> d;
private:
    bool irrelevant(Line Z) {
        if (sz(d) < 2) return false;
    
        Line X = d[sz(d)-2], Y = d[sz(d)-1];

        return (X.c - Z.c) * (Y.m - X.m) <= (X.c - Y.c) * (Z.m - X.m);
    }
public:
    void push_line(Line l) {
        while (irrelevant(l)) d.pop_back();
        d.push_back(l);
    }
    ll query(ll x) {
        while (sz(d) > 1 && (d[0].c - d[1].c <= x * (d[1].m - d[0].m))) d.pop_front();

        return d.front().pass(x);
    }
};

class ConvexHullDynamic {
private:
    struct Line {
        ll m, c, val; double xLeft;
        enum Type { line, maxQuery, minQuery } type;

        explicit Line(ll _m = 0, ll _c = 0) : m(_m), c(_c), xLeft(-INFINITY), type(Type::line), val(0) {}
        
        friend double intersectX(const Line& l1, const Line& l2) { 
            return l1.m == l2.m ? INFINITY : (double) (l2.c-l1.c) / (double) (l1.m-l2.m); 
        }
        
        ll pass(ll x) const { return m * x + c; }

        bool operator < (const Line& l) const {
            if (l.type == line)
                return this->m     < l.m;
            if (l.type == maxQuery)
                return this->xLeft < l.val;
            if (l.type == minQuery)
                return this->xLeft > l.val;
        }
    };
private:
    bool      MAXH;
    set<Line> hull;
private:
    bool hasPrev(set<Line>::iterator it) { return it != hull.begin(); }
    bool hasNext(set<Line>::iterator it) { return it != hull.end() && next(it) != hull.end(); }
    bool irrelevant(const Line& l1, const Line& l2, const Line& l3) { return intersectX(l1,l3) <= intersectX(l1,l2); }
    bool irrelevant(set<Line>::iterator it) {
        return hasPrev(it) && hasNext(it) && 
        ( MAXH && irrelevant(*prev(it), *it, *next(it)) || !MAXH && irrelevant(*next(it), *it, *prev(it)) );
    }
    set<Line>::iterator updateLeftBorder(set<Line>::iterator it) {
        if (MAXH && !hasPrev(it) || !MAXH && !hasNext(it)) return it;

        double val = intersectX(*it, MAXH ? *prev(it) : *next(it));
        Line buf(*it);
        it = hull.erase(it);
        buf.xLeft = val;
        it = hull.insert(it, buf);
        return it;
    }
public:
    explicit ConvexHullDynamic(bool MAXH): MAXH(MAXH) {}

    void addLine(ll m, ll c) {

        Line l3 = Line(m, c);
        auto it = hull.lower_bound(l3);

        //if parallel line is already in set, one of them becomes irrelevant
        if (it != hull.end() && it->m == l3.m) {
            if (MAXH && it->c < c || !MAXH && it->c > c) it = hull.erase(it);
            else return;
        }

        //try to insert
        it = hull.insert(it, l3);
        if (irrelevant(it)) { hull.erase(it); return; }

        //remove lines which became irrelevant after inserting line
        while (hasPrev(it) && irrelevant(prev(it))) hull.erase(prev(it));
        while (hasNext(it) && irrelevant(next(it))) hull.erase(next(it));

        //refresh 'xLine'
        it = updateLeftBorder(it);
        if (hasPrev(it))
            updateLeftBorder(prev(it));
        if (hasNext(it))
            updateLeftBorder(next(it));
    }

    ll getBest(ll x) const {
        Line q;
        q.val = x;
        q.type = MAXH ? Line::Type::maxQuery : Line::Type::minQuery;

        auto bestLine = hull.lower_bound(q);
        if (MAXH) --bestLine;
        return bestLine->pass(x);
    }
};

int main() {

    return 0;
}
