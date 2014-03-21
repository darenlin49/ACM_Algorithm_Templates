//NOIP 2000 方格取数
//多线程DP  
int n;
int f[31][11][11];
int a[11][11];
int main(){
    scanf("%d",&n);
    int x,y,c;
    while(scanf("%d%d%d",&x,&y,&c)){
        if (x == 0 && y == 0 && c == 0)
             break;
        a[x][y] = c;
    }
    for (int k = 1; k < n + n; k ++)
        for (int i = 1; i <= min(n,k); i ++)
            for (int j = 1; j <= min(n,k); j ++){
                f[k][i][j] = max(f[k-1][i][j], f[k-1][i-1][j]);
                f[k][i][j] = max(f[k][i][j], f[k-1][i][j-1]);
                f[k][i][j] = max(f[k][i][j], f[k-1][i-1][j-1]);
                if (i == j)
                    f[k][i][j] += a[i][k+1-i];
                else    f[k][i][j] += a[i][k+1-i] + a[j][k+1-j];
            }
    printf("%d\n",f[n+n-1][n][n]);
    return 0;
}
