/*
题目大意：给定n个数，每次选连续的m个数，选3次且选的数不能重复，求选出的这些数的和的最大值.

思路：网上说是01背包，恕本菜没看出来= =……我倒觉得他像3个最大连续子段和，但是限制每次只能选m个数，所以姑且叫他3次最大连续m子段和吧……

设dp[i][j]表示在前i个数中选j次的最大和，首先预处理一下sum[i]表示以i为结尾的连续m个数的和，则方程为：

dp[i][j] = max(dp[i-1][j]， dp[i-m][j-1] + sum[i] )
*/

#include <cstdio>
#include <cstring>
using namespace std;
 
const int N = 50010;
int a[N], sum[N], f[N][4];
 
int main(){
    int t, n, m;
    scanf("%d",&t);
    while(t --){
        scanf("%d",&n);
        for (int i = 0; i < n; i ++){
            scanf("%d",&a[i]);
        }
        scanf("%d",&m);
 
        int s = 0;
        for (int i = 0; i < n; i ++){
            s += a[i];
            if (i > m - 1){
                s -= a[i - m];
                sum[i] = s;
            }
            else{
                sum[i] = s;
            }
        }
        memset(f, 0, sizeof(f));
        for (int i = m; i <= n; i ++){
            for (int j = 1; j <= 3; j ++){
                f[i][j] = f[i-1][j];
                if (f[i-m][j-1] + sum[i-1] > f[i][j]){
                        f[i][j] = f[i-m][j-1] + sum[i-1];
                }
            }
        }
        printf("%d\n", f[n][3]);
    }
    return 0;
}