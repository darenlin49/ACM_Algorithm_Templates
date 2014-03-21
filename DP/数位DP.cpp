/**
	��HDU 3555��
		������[1,n]�ں�������49������
	����λDPģ���ܽ᡿��ʱ�临�Ӷȡ�O(10*|dp[][][]|)
		int dfs(int pos, int pre, int flag, bool limit) {
			if (pos == -1) return flag==target_flag;
			if (!limit && ~dp[pos][pre][flag]) return dp[pos][pre][flag];
			int res = 0;
			int end = limit?num[i]:9;
			for (int d = 0; d <= end; ++d)
				res += dfs(pos-1, d, (flag, d), limit&&d==end);
			return limit?res:dp[pos][pre][flag]=res;
		}
	���У�dpΪ���仯���飻posΪ��ǰ�����ĵ�posλ��flagΪ֮ǰ���ֵ�״̬�����Ҫ������������ʲô״̬��Ҳ�����ټ�һ��Ŀ��״̬target֮�࣬for��ʱ��ö���£���preΪǰһλ���ֵ�״̬����ʱ������ҪҲ���Լ��Ϻ�һλ���ֵ�״̬��for��ʱ��ö���£���limit��ʾ֮ǰ�����Ƿ����Ͻ��ǰ׺������������ܷ��������

	forѭ��ö������ʱ��Ҫע���Ƿ���ö��0���Լ�0����״̬��Ӱ�죬�е���Ŀǰ��0���м��0�ǵȼ۵ģ����еĲ��ǣ����ں��߿�����dfsʱ�ټ�һ��״̬����z����ʾǰ���Ƿ�ȫ����ǰ��0��Ҳ���Կ��Ƿ�����λ��Ȼ������ͳ��ʱ��ö��һ��λ����

	���ǹؼ�������ô���״̬����Ȼ������֮��״̬һ�۾Ϳ����������

	ע�⣺����������������ʵĻ�����hdu 4376����������solve(r)-solve(l-1)��״̬��ƻ���ӹ��졣
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
	MEM(dp, -1);		/** ֻ����һ��ʼ��ʼ������.��Ȼ����ȷ��dp��ֵΨһȷ��һ������ **/
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