/*
	sgu 223 ��������ģ�ͣ���n*n(n<=10)�������Ϸ�k���������ɹ������ڵ�8�����ӣ�����ʹ�����޷��໥�����ķ�����.
	��������Ҫ�Ƚ�ÿһ�еĿ���״̬��DFS�����ö����Ʊ�ʾѹ����S[]������.Ȼ���Դ�Ϊ״̬DP.
	
	���������ڸ��Ӳ��ܷ�
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
    if (!(condition_num & 1))											//���ڸ��Ӳ��ܷ�
        dfs(p+1, condition_num << 1 | 1, condition_one_amount + 1);
    return ;
}
bool ifok(int s1, int s2){      //decide whether tha current condition and the last condition are comtradictry.
    if(s1 & s2) return false;         //�����Ϸ��ж�
    if(s1 & (s2<<1))return false;     //�����Ϸ��ж�
    if(s1 & (s2>>1))return false;     //�����Ϸ��ж�
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
	HDU4239��n*m(n<=100,m<=10)�������Ϸ�ʿ����ÿ��ʿ���������پ���2�ĵط������ܷű��ʿ����������Щ�ط����ܷ�ʿ����������ܷż���ʿ����
	
	�����������پ���Ϊ2�ĵ㲻�ܷ�
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
    if (!(condition_num & 2))												//��һ�����ܷ�
        dfs(p+1, condition_num << 1 | 1, condition_one_amount + 1);
    return ;
}
bool ifok(int s1, int s2){      //decide whether tha current condition and the last condition are comtradictry.
    //if(s1 & s3)     return false;         //�����Ϸ��ж�
    if(s1 & (s2<<1))    return false;     	//�����Ϸ��ж�
    if(s1 & (s2>>1))    return false;     	//�����Ϸ��ж�
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
