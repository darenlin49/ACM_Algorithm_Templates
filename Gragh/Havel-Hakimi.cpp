/*
	Havel-Hakimi定理用来判定一个给定的度序列是否是可图的.
	[度序列]若把图 G 所有顶点的度数排成一个序列 S,则称 S 为图 G 的度序列.
	[可图]一个非负整数组成的有限序列如果是某个无向图的序列,则称该序列是可图的.
	[判定过程]
		①对当前数列排序，使其呈递减
		②从S[2]开始对其后S[1]个数字-1 ③一直循环直到当前序列出现负数（即不是可图的情况）或者当前序列全为0 （可图）时退出
	[举例]序列S：7,7,4,3,3,3,2,1  删除序列S的首项 7 ，对其后的7项每项减1，得到：6,3,2,2,2,1,0，继续删除序列的首项6，对其后的6项每项减1，得到：2,1,1,1,0，-1，到这一步出现了负数，因此该序列是不可图的.
*/

/* ------------------- Havel-Hakimi ------------------- */
const int N = 12;
struct DEG{
    int deg;
    int v;
}x[N];
bool cmp(DEG n1, DEG n2){
    return n1.deg > n2.deg;
}
int mat[N][N];
//函数返回一个度序列x[]是否可图
bool Havel(int n){
    sort(x, x+n, cmp);
    mem(mat, 0);                    //构图的邻接矩阵
    for (int i = 0; i < n; i ++){
        if (x[i].deg == 0)  return true;
        for (int j = i+1; j <= min(i+x[i].deg, n-1); j ++){
            x[j].deg --;
            if (x[j].deg < 0){
                return false;
            }
            mat[x[i].v][x[j].v] ++;
            mat[x[j].v][x[i].v] ++;
        }
        x[i].deg -= n-i-1;
        x[i].deg = max(0, x[i].deg);
        sort(x+i+1, x+n, cmp);
    }
    return true;
}
/* ------------------- Havel-Hakimi ------------------- */

int main(){
    int T, n;
    scanf("%d", &T);
    for (int t = 0; t < T; t ++){
        if (t > 0)
            puts("");
        scanf("%d", &n);
        for (int i = 0; i < n; i ++){
            scanf("%d", &x[i].deg);
            x[i].v = i;
        }
        if (Havel(n)){
            puts("YES");
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n - 1; j ++){
                    printf("%d ", mat[i][j]);
                }
                printf("%d\n", mat[i][n-1]);
            }
        }
        else{
            puts("NO");
        }
    }
	return 0;
}
