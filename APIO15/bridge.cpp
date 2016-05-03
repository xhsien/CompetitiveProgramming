#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

typedef long long ll;
typedef pair<int,int> ii;
typedef priority_queue< ii >                        MAXPQ;
typedef priority_queue< ii,vector<ii>,greater<ii> > MINPQ;

const int MAXN = 100005;

int K, N;
vector<ii> p;

ll val1[MAXN], val2[MAXN], ans = 0, sum1, cnt1, sum2, cnt2;
MAXPQ maxHeap; MINPQ minHeap;

bool cmp(ii a, ii b) {
    return a.fi + a.se < b.fi + b.se;
}

int main() {

    scanf("%d%d",&K,&N);
    for (int i = 1, u, v; i <= N; i++) {
        char op1, op2;
        scanf(" %c %d %c %d",&op1,&u,&op2,&v);

        if (u > v)
            swap(u,v);

        ans += v - u;

        if (op1 == op2)
            continue;

        ans++;
        p.push_back(ii(u,v));
    }

    if (p.empty()) {
        printf("%lld\n", ans); return 0;
    }

    sort(p.begin(),p.end(),cmp);

    // prefix
    sum1 = cnt1 = sum2 = cnt2 = 0; maxHeap = MAXPQ(); minHeap = MINPQ();
    maxHeap.push(ii(p[0].fi,0));
    minHeap.push(ii(p[0].se,1));

    for (int i = 1; i < p.size(); i++) {
        
        int median = maxHeap.top().fi, c = maxHeap.top().se;
        if (p[i].fi >= median) {
            minHeap.push(ii(p[i].fi,0)); sum2 += p[i].fi; cnt2++;
            minHeap.push(ii(p[i].se,1));

            int shift = minHeap.top().fi, cc = minHeap.top().se;
            maxHeap.push(ii(shift,cc));  if (cc)  sum1 += shift, cnt1++;
            minHeap.pop();               if (!cc) sum2 -= shift, cnt2--;
        } else if (p[i].se <= median) {
            maxHeap.pop();               if (c)  sum1 -= median, cnt1--;
            minHeap.push(ii(median,c));  if (!c) sum2 += median, cnt2++;
            maxHeap.push(ii(p[i].fi,0));
            maxHeap.push(ii(p[i].se,1)); sum1 += p[i].se; cnt1++;
        } else {
            maxHeap.push(ii(p[i].fi,0));
            minHeap.push(ii(p[i].se,1));
        }

        val1[i] = 1LL * median * cnt1 - sum1 + sum2 - 1LL * median * cnt2;
    }

    // suffix
    sum1 = cnt1 = sum2 = cnt2 = 0; maxHeap = MAXPQ(); minHeap = MINPQ();
    maxHeap.push(ii(p[p.size()-1].fi,0));
    minHeap.push(ii(p[p.size()-1].se,1));

    for (int i = p.size()-2; i >= 0; i--) {
        
        int median = maxHeap.top().fi, c = maxHeap.top().se;
        if (p[i].fi >= median) {
            minHeap.push(ii(p[i].fi,0)); sum2 += p[i].fi; cnt2++;
            minHeap.push(ii(p[i].se,1));

            int shift = minHeap.top().fi, cc = minHeap.top().se;
            maxHeap.push(ii(shift,cc));  if (cc)  sum1 += shift, cnt1++;
            minHeap.pop();               if (!cc) sum2 -= shift, cnt2--;
        } else if (p[i].se <= median) {
            maxHeap.pop();               if (c)  sum1 -= median, cnt1--;
            minHeap.push(ii(median,c));  if (!c) sum2 += median, cnt2++;
            maxHeap.push(ii(p[i].fi,0));
            maxHeap.push(ii(p[i].se,1)); sum1 += p[i].se; cnt1++;
        } else {
            maxHeap.push(ii(p[i].fi,0));
            minHeap.push(ii(p[i].se,1));
        }

        val2[i] = 1LL * median * cnt1 - sum1 + sum2 - 1LL * median * cnt2;
    }

    if (K == 1) {
        ans += 2 * val1[p.size()-1];
        printf("%lld\n", ans);
    } else {
        ll min_num = LLONG_MAX;
        for (int i = 0; i < p.size(); i++)
            min_num = min(min_num,val1[i]+val2[i+1]);
        ans += 2 * min_num;
        printf("%lld\n", ans);
    }

    return 0;
}
