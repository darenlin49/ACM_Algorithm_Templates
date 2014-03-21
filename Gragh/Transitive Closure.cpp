/*
POJ 3660
题目大意：有N头奶牛，现在告诉你他们两头牛之间比赛的胜负结果M组，要你据此求出有多少头奶牛的排名可以确定下来。
解题思路：对于某个人而言，如果比他成绩好的人有lose（你输了），比他成绩差的有win（被你打败），如果lose+win的人数比总人数少一个（他自己），他的排名就可以确定了。所以只需要应用Floyd传递关系，最后计算出win的人数和lose的人数即可！
*/

/* -------------------------------求传递闭包模板部分------------------------------- */

/* calculate Transitive Closure By Warshall */
const int N = 103;
int R[N][N];
int TC[N][N];
void Warshall_init(){
    mem(TC, 0);
}
void Warshall(int n){
    Warshall_init();
    //To copy the original matrix to the matrix that will be calculated.
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            TC[i][j] = R[i][j];

    for (int k = 0; k < n; k ++)
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++){
                if (TC[i][j])   continue;
                TC[i][j] = TC[i][k] && TC[k][j];
            }
}

/* -------------------------------求传递闭包模板部分------------------------------- */

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i ++){
        int a, b;
        scanf("%d %d", &a, &b);
        R[a-1][b-1] = 1;
    }
    Warshall(n);
    int ans = 0;
    for (int i = 0; i < n; i ++){
        int win = 0, fail = 0;
        for (int j = 0; j < n; j ++){
            if (TC[i][j])
                win ++;
            else if (TC[j][i])
                fail ++;
        }
        if (win + fail == n-1)
            ans ++;
    }
    printf("%d\n", ans);
	return 0;
}