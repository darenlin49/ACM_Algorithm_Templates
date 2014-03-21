const int MAXNUM = 505;
int C[MAXNUM][MAXNUM];
void cal_C(int n, int mod){
    mem(C, 0);
    C[0][0] = 1;
    for (int i = 1; i <= n; i ++){
        C[i][0] = 1;
        for (int j = 1; j <= i; j ++){
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
        }
    }
}