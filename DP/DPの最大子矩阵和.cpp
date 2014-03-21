/*	
POJ 1050
思路：如果不是方阵而是一维数组，显然是最大连续子段和。如果已经确定这个矩形应该包含哪些行，而还不知道该包含哪些列，那么可以将每一列的各行元素相加，从而将矩阵转换为一维数组的最大连续子段和。因此，只要我们枚举矩阵应该从哪一行到哪一行，就可以将问题用最大连续子段和策略来求解了，O(N3)。
*/
int a[120][120];
int b[120],dp[120];
 
int main(){
    int maxn;
    int n;
    while(scanf("%d",&n) == 1){
        maxn = INT_MIN;
        for (int i = 0; i < n; i ++){
            for (int j = 0; j < n; j ++){
                scanf("%d",&a[i][j]);
                maxn = max(maxn, a[i][j]);
            }
        }
        for (int i = 0; i < n; i ++){
            memset(b,0,sizeof(b));
            for (int j = i; j < n; j ++){
                dp[0] = 0;
                for (int k = 0; k < n; k ++){
                    b[k] += a[j][k];
                    dp[k+1] = (dp[k] > 0 ? dp[k] : 0) + b[k];
                    maxn = max(maxn, dp[k+1]);
                }
            }
        }
        printf("%d\n",maxn);
    }
    return 0;
}