/*	
POJ 1050
˼·��������Ƿ������һά���飬��Ȼ����������Ӷκ͡�����Ѿ�ȷ���������Ӧ�ð�����Щ�У�������֪���ð�����Щ�У���ô���Խ�ÿһ�еĸ���Ԫ����ӣ��Ӷ�������ת��Ϊһά�������������Ӷκ͡���ˣ�ֻҪ����ö�پ���Ӧ�ô���һ�е���һ�У��Ϳ��Խ���������������ӶκͲ���������ˣ�O(N3)��
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