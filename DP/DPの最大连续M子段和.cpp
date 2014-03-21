/*
��Ŀ���⣺����n������ÿ��ѡ������m������ѡ3����ѡ���������ظ�����ѡ������Щ���ĺ͵����ֵ.

˼·������˵��01������ˡ����û������= =�����ҵ���������3����������Ӷκͣ���������ÿ��ֻ��ѡm���������Թ��ҽ���3���������m�ӶκͰɡ���

��dp[i][j]��ʾ��ǰi������ѡj�ε����ͣ�����Ԥ����һ��sum[i]��ʾ��iΪ��β������m�����ĺͣ��򷽳�Ϊ��

dp[i][j] = max(dp[i-1][j]�� dp[i-m][j-1] + sum[i] )
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