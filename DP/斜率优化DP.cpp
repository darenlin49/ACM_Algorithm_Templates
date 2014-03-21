/**
	 g[j,k] = [F(j)-F(k)]/[S(j)-S(k)]
	��g[j,k] <= sum[i]��ʾj>k��j��k���š���б���Ż���
		����k<j<i�����g[i,j] <= g[j,k]����ôj�����Զ�����ܳ�Ϊ���Ž⣬����ֱ�ӽ����߳����ǵ����Ž⼯��
		�ں���A[]ҲҪ���е�����(A[]��������Ҫ��������������Ե���Ϊ��)������������е�ͷ������Ϊi,j��б��g[j,i] <= A[i]����˵��j����i����������A��������������g[j,i]��С��A[]�����Կ���ֱ�Ӱ�i�ų���
		�ˡˡ�(��ñ�֤g[j,k]�ķ�ĸ����0,������Ҫע�ⲻ�Ⱥŵķ�������)
	
	�����ܽ����£�
		1����һ������������ά���⼯��
		2����������д�ͷ��β�Ѿ���Ԫ��a b c����ô��dҪ��ӵ�ʱ������ά�����е���(��)͹����(б�ʵ���)�������g[d,c]<g[c, b]����ô�ͽ�c��ɾ����ֱ���ҵ�g[d,x]>=g[x,y]Ϊֹ������d������ڸ�λ���С�
		3�����ʱ�򣬴Ӷ�ͷ��ʼ���������Ԫ��a b c����i��Ҫ���ʱ�����g[b,a]<A[i]����ô˵��b���a����ţ�a������ų�������a���ӡ����dp[i]=getDp(q[head])��
	
	��g[j,k] >= sum[i]��ʾj>k��j��k���š��������������������(��͹��б�ʵݼ�)��
		����k<j<i�����g[i,j] >= g[j,k]����ôj�����Զ�����ܳ�Ϊ���Ž⣬����ֱ�ӽ����߳����ǵ����Ž⼯��
		����A[]�ݼ�Ϊ��������������е�ͷ������Ϊi,j��б��g[j,i] >= A[i]����˵��j����i����������A�����ݼ�������g[j,i]�����A[]�����Կ���ֱ�Ӱ�i�ų���
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