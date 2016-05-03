#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int N, A, B, a[MAXN];
long long sum[MAXN], dp[MAXN][MAXN], dp2[MAXN];

bool special(long long num) {
    fill(dp2+1,dp2+N+1,B+1);
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < i; ++j)
            if ((((sum[i] - sum[j]) & ~num) == 0) && (dp2[i] > dp2[j] + 1))
                dp2[i] = dp2[j] + 1;

    return dp2[N] <= B;
}

bool valid(long long num) {
    if (A == 1)
        return special(num);

    memset(dp,0,sizeof(dp)); dp[0][0] = 1;
    for (int k = 1; k <= B; ++k)
        for (int i = k; i <= N; ++i)
            for (int j = k-1; j < i; ++j)
                dp[i][k] |= dp[j][k-1] && (((sum[i] - sum[j]) & ~num) == 0);

    for (int i = A; i <= B; i++) 
        if (dp[N][i])
            return true;

    return false;
}

int main() {

    scanf("%d%d%d",&N,&A,&B);
    for (int i = 1; i <= N; i++) {
        scanf("%d",&a[i]);

        sum[i] = sum[i-1] + a[i];
    }

    long long ans = 0x1FFFFFFFFFFLL;

    for (long long pos = 0x10000000000LL; pos; pos >>= 1)
        if (valid(ans & ~pos))
            ans &= ~pos;

    printf("%lld\n", ans);

    return 0;
}
