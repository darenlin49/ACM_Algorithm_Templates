/*
	sgu 223 基本棋盘模型：在n*n(n<=10)的棋盘上放k个国王（可攻击相邻的8个格子），求使他们无法相互攻击的方案数.
	这类题需要先将每一行的可行状态先DFS出来用二进制表示压缩到S[]数组中.然后以此为状态DP.
	
	特征：相邻格子不能放
*/

int n, k;
const int NUM_OF_PLACEMENGT = 520;
int s[NUM_OF_PLACEMENGT], c[NUM_OF_PLACEMENGT], place_num;         //the placement of each line
long long dp[13][NUM_OF_PLACEMENGT][103];

void dfs(int p, int condition_num, int condition_one_amount){             //Store the placement of each line
    if (p == n){
        s[++ place_num] = condition_num;
        //cout << place_num << " " << s[place_num] << endl;
        c[place_num] = condition_one_amount;
        return ;
    }
    dfs(p+1, condition_num << 1, condition_one_amount);			
    if (!(condition_num & 1))											//相邻格子不能放
        dfs(p+1, condition_num << 1 | 1, condition_one_amount + 1);
    return ;
}
bool ifok(int s1, int s2){      //decide whether tha current condition and the last condition are comtradictry.
    if(s1 & s2) return false;         //和正上方判断
    if(s1 & (s2<<1))return false;     //和右上方判断
    if(s1 & (s2>>1))return false;     //和左上方判断
    return true;
}
int main(){
    while(scanf("%d %d", &n, &k) != EOF){
        //cout << n << " " << k << endl;
        mem(dp, 0);
        place_num = 0;
        dp[0][1][0] = 1;
        dfs(0, 0, 0);
        for (int i = 1; i <= n; i ++){
            for (int j1 = 1; j1 <= place_num; j1 ++){
                for (int j2 = 1; j2 <= place_num; j2 ++){
                    for (int w = 0; w <= k; w ++){
                        if (ifok(s[j1], s[j2]) && w-c[j1] >= 0)
                            dp[i][j1][w] += dp[i-1][j2][w-c[j1]];
                    }
                }
            }
        }
        long long res = 0;
        for (int j = 1; j <= place_num; j ++)
            res += dp[n][j][k];
        printf("%I64d\n", res);
    }
	return 0;
}

/*
	HDU4239在n*m(n<=100,m<=10)的棋盘上放士兵，每个士兵的曼哈顿距离2的地方都不能放别的士兵。并且有些地方不能放士兵。求最多能放几个士兵。
	
	特征：曼哈顿距离为2的点不能放
*/

int n, m;
const int NUM_OF_PLACEMENGT = 500;
int s[NUM_OF_PLACEMENGT], c[NUM_OF_PLACEMENGT], place_num;         //the placement of each line
int dp[2][NUM_OF_PLACEMENGT][NUM_OF_PLACEMENGT];
vector <int> dd[NUM_OF_PLACEMENGT];
int no[105];

void dfs(int p, int condition_num, int condition_one_amount){             //Store the placement of each line
    if (p == m){
        s[++ place_num] = condition_num;
        //cout << condition_num << endl;
        c[place_num] = condition_one_amount;
        return ;
    }
    dfs(p+1, condition_num << 1, condition_one_amount);
    if (!(condition_num & 2))												//隔一个不能放
        dfs(p+1, condition_num << 1 | 1, condition_one_amount + 1);
    return ;
}
bool ifok(int s1, int s2){      //decide whether tha current condition and the last condition are comtradictry.
    //if(s1 & s3)     return false;         //和正上方判断
    if(s1 & (s2<<1))    return false;     	//和右上方判断
    if(s1 & (s2>>1))    return false;     	//和左上方判断
    return true;
}
int main(){
    while(scanf("%d %d", &n, &m) == 2){
        mem(no, 0);
        place_num = 0;
        mem(dp, -1);
        dp[0][1][1] = 0;
        dfs(0, 0, 0);
        for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++){
            int tmp;
            scanf("%d", &tmp);
            if (tmp == 0)   no[i] += (1 << (m-j));
        }
        for (int i = 1; i <= n; i ++)
            for (int j1 = 1; j1 <= place_num; j1 ++){
                if(s[j1] & no[i])   continue;
                for (int j3 = 1; j3 <= place_num; j3 ++){
                    if (s[j1] & s[j3])  continue;
                    for (int j2 = 1; j2 <= place_num; j2 ++){
                        if (ifok(s[j1],s[j2]) && dp[(i-1)&1][j2][j3] != -1){
                            dp[i&1][j1][j2] = max(dp[i&1][j1][j2], dp[(i-1)&1][j2][j3] + c[j1]);;
                        }
                    }
                }
            }
        int res = 0;
        for (int j1 = 1; j1 <= place_num; j1 ++)
            for (int j2 = 1; j2 <= place_num; j2 ++)
                res = max(res, dp[n&1][j1][j2]);
        printf("%d\n", res);
    }
    return 0;
}
