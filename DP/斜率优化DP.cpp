/**
	 g[j,k] = [F(j)-F(k)]/[S(j)-S(k)]
	【g[j,k] <= sum[i]表示j>k且j比k更优】的斜率优化：
		①设k<j<i，如果g[i,j] <= g[j,k]，那么j点便永远不可能成为最优解，可以直接将它踢出我们的最优解集。
		②函数A[]也要具有单调性(A[]单调增减要具体分析，这里以递增为例)，如果单调队列的头两个点为i,j，斜率g[j,i] <= A[i]，则说明j优于i，并且由于A单调递增，所以g[j,i]恒小于A[]，所以可以直接把i排除掉
		∷∷∷(最好保证g[j,k]的分母大于0,否则需要注意不等号的方向问题)
	
	做法总结如下：
		1，用一个单调队列来维护解集。
		2，假设队列中从头到尾已经有元素a b c。那么当d要入队的时候，我们维护队列的下(上)凸性质(斜率递增)，即如果g[d,c]<g[c, b]，那么就将c点删除。直到找到g[d,x]>=g[x,y]为止，并将d点加入在该位置中。
		3，求解时候，从队头开始，如果已有元素a b c，当i点要求解时，如果g[b,a]<A[i]，那么说明b点比a点更优，a点可以排除，于是a出队。最后dp[i]=getDp(q[head])。
	
	【g[j,k] >= sum[i]表示j>k且j比k更优】的情况反过来分析即可(上凸，斜率递减)：
		①设k<j<i，如果g[i,j] >= g[j,k]，那么j点便永远不可能成为最优解，可以直接将它踢出我们的最优解集。
		②以A[]递减为例，如果单调队列的头两个点为i,j，斜率g[j,i] >= A[i]，则说明j优于i，并且由于A单调递减，所以g[j,i]恒大于A[]，所以可以直接把i排除掉
*/
#define SIZE(Q) ( (int)Q.size() )
long long dp[50005], sum[50005];
vector <int> Q;
int n, L;
inline long long getDP(int i, int j){
    return dp[j] + (i+sum[i]-(j+1+sum[j])-L) * (i+sum[i]-(j+1+sum[j])-L);
}
inline double getUP(int j, int k){
    return (double)dp[j] + (double)(j+1+sum[j]) * (double)(j+1+sum[j]) - ((double)dp[k] + (double)(k+1+sum[k]) * (double)(k+1+sum[k]));
}
inline double getDOWN(int j, int k){
    return 2.0 * ((j+1+sum[j]) - (k+1+sum[k]));
}
inline double getRIGHT(int i){
    return (double)(sum[i] + i - L);
}
inline double slope(int j, int k){
    return getUP(j, k) / getDOWN(j, k);
}
int main(){
    scanf("%d %d", &n, &L);
    sum[0] = 0, dp[0] = 0;
    for (int i = 1; i <= n; i ++){
        scanf("%lld", &sum[i]);
        sum[i] += sum[i-1];
    }
    Q.clear();
    Q.push_back(0);
    for (int i = 1; i <= n; i ++){
        while( SIZE(Q) > 1 && slope(Q[1], Q[0]) <= getRIGHT(i))
            Q.erase(Q.begin());
        int tmp = Q[0];
        dp[i] = getDP(i, Q[0]);
        while( SIZE(Q) > 1 && slope(Q[SIZE(Q)-1], Q[SIZE(Q)-2]) >= slope(i, Q[SIZE(Q)-1]) )
            Q.pop_back();
        Q.push_back(i);
    }
    printf("%lld\n", dp[n]);
    return 0;
}