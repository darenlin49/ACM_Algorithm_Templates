/**
	【置换群模板1.0 - 2013.09.23】
	【定理】设T^k=e(T为一置换,e为单位置换(映射函数为f(x)=x的置换)),那么k的最小正整数解是T的拆分的所有循环长度的最小公倍数.
	【结论】一个长度为len的循环T,是gcd(len,k)个循环的乘积,每个循环分别是循环T中下标i mod gcd(len,k)=0,1,2…的元素的连接(顺序不一定按原来顺序).
	【求整幂运算的O(n)算法】
		For 源置换中每一个循环
			For 环中每一个未标记元素 Do
				做上标记
				放入结果数组
				前进k格
			Until 回到这个元素
		将结果数组中的元素取出,得到的环,便是目标置换包含的一个循环,再将循环转换成置换.
	【注意】PG.A[] && PG.B[] 的下标都是从1开始

*/
const int MAXN = 205;
int gcd(int a, int b){
    return b ? gcd(b, a%b) : a;
}
struct PermutateGroup{
    int A[MAXN];        //The Permutate Group, begin with 1.
    bool vis[MAXN];
    //calculate k which makes T^k equals I
    inline int cal_k(int n){
        MEM(vis, false);
        int res = 1;
        for (int i = 1; i <= n; i ++){
            if (!vis[i]){
                vis[i] = 1;
                int len = 1;
                int p = i;
                while (1){
                    p = A[p];
                    if (vis[p]) break;
                    vis[p] = 1;
                    len ++;
                }
                res = res / gcd(res, len) * len;
            }
        }
        return res;
    }
    //calculate T^k
    int tmp[MAXN], pa[MAXN];
    bool viss[MAXN];
    inline void exp(int n, int k, int B[]){
        MEM(tmp, 0);    MEM(vis, 0);
        int len = 0;
        for (int i = 1; i <= n; i ++){
            if (!vis[i]){
                //把置换群表示成若干循环的乘积
                vis[i] = 1;
                int p = i;
                len = 0;
                tmp[len ++] = i;
                while(1){
                    p = A[p];
                    if (vis[p]) break;
                    vis[p] = 1;
                    tmp[len ++] = p;
                }
                //每个循环单独求解循环的k次幂
                for(int j = 0; j < len; j ++)   viss[j] = 0;
                for(int j = 0; j < len; j ++){
                    int co = 0;
                    if (!viss[j]){
                        int tt = j;
                        while ((tt + k) % len != j){
                            pa[co ++] = tmp[tt];
                            viss[tt] = 1;
                            tt = (tt + k) % len;
                        }
                        pa[co ++] = tmp[tt];
                        viss[tt] = 1;
                        if (co == 1){
                            B[pa[0]] = pa[0];
                        }
                        else{
                            for (int j = 0; j < co; j ++){
                                B[pa[j]] = pa[j+1];
                            }
                            B[pa[co-1]] = pa[0];
                        }

                    }
                }
            }
        }
        return ;
    }
}PG;