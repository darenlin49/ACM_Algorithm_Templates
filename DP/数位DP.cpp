/**
	【HDU 3555】
		求区间[1,n]内含有相邻49的数。
	【数位DP模板总结】【时间复杂度】O(10*|dp[][][]|)
		int dfs(int pos, int pre, int flag, bool limit) {
			if (pos == -1) return flag==target_flag;
			if (!limit && ~dp[pos][pre][flag]) return dp[pos][pre][flag];
			int res = 0;
			int end = limit?num[i]:9;
			for (int d = 0; d <= end; ++d)
				res += dfs(pos-1, d, (flag, d), limit&&d==end);
			return limit?res:dp[pos][pre][flag]=res;
		}
	其中：dp为记忆化数组；pos为当前处理串的第pos位；flag为之前数字的状态（如果要求后面的数满足什么状态，也可以再记一个目标状态target之类，for的时候枚举下）；pre为前一位数字的状态（有时根据需要也可以加上后一位数字的状态，for的时候枚举下）；limit表示之前的数是否是上界的前缀（即后面的数能否任意填）。

	for循环枚举数字时，要注意是否能枚举0，以及0对于状态的影响，有的题目前导0和中间的0是等价的，但有的不是，对于后者可以在dfs时再加一个状态变量z，表示前面是否全部是前导0，也可以看是否是首位，然后外面统计时候枚举一下位数。

	于是关键就在怎么设计状态。当然做多了之后状态一眼就可以瞄出来。

	注意：不满足区间减法性质的话（如hdu 4376），不能用solve(r)-solve(l-1)，状态设计会更加诡异。
**/
typedef long long LL;
typedef vector <int> VI;
typedef set <int> SETI;
typedef queue <int> QI;
typedef stack <int> SI;
 
VI dig;
LL dp[30][30][2];
LL dfs(int pos, int pre, int flag, int limit){
    if (pos == -1)  return flag;
    if (!limit && dp[pos][pre][flag] != -1){
        return dp[pos][pre][flag];
    }
    int end = limit?dig[pos]:9;
    LL ret = 0;
    for (int i = 0; i <= end; ++ i){
        ret += dfs(pos-1, i, (i == 9 && pre == 4)||flag, (i == end)&&limit);
    }
    if (!limit) dp[pos][pre][flag] = ret;
    return  ret;
}
 
int main(){
    int t;
    scanf("%d", &t);
	MEM(dp, -1);		/** 只需在一开始初始化即可.当然必须确保dp的值唯一确定一个区间 **/
    while(t --){
        LL n;
        scanf("%I64d", &n);
        dig.clear();
        while(n){
            dig.push_back(n%10);
            n /= 10;
        }
        printf("%I64d\n", dfs(dig.size()-1, 0, 0, 1));
    }
    return 0;
}