/*
题目链接：http://poj.org/problem?id=1398

题目大意：给定一个长度为s的数列a1,a2,a3,……,as，并知道它的通项可以用多项式P(n)表示出来，求数列的后c项。

思路：标准的做好像是数值分析的拉格朗日插值法，但求解这种数列问题我们有更好的差分方法，过程中完全不涉及浮点数操作。比如说，对于1 2 4 7 11 16 22 29这个数列，我们对于每一项做其和前一项的差，也就是2-1=1, 4-2=2, 7-4=3, ....这样，我们得到一个1阶差分：1, 2, 3, 4, 5, 6, 7。我们再求得2阶差分是：1, 1, 1, 1, 1, 1。这时，规律已经有些明显了。

也就是说，对于任意一个存在合理多项式通项的数列，用差分的方法是可以得到它的解的：只要求得这个n项数列的n-1阶差分，然后倒推回去就可以了。
*/

#include <cstdio>
#include <cstring>
using namespace std;
int main(){
    int a[110][110];
    int t, s, c;
    scanf("%d",&t);
    while(t --){
        memset(a, 0, sizeof(a));
        scanf("%d%d",&s, &c);
        for (int i = 0; i < s; i ++){
            scanf("%d", &a[0][i]);
        }
        for (int i = 1; i < s; i ++){
            for (int j = 0; j < s - i; j ++){
                a[i][j] = a[i-1][j+1] - a[i-1][j];
            }
        }
        for (int i = 1; i <= c; i ++)
            a[s-1][i] = a[s-1][0];
        for (int i = s - 2; i >= 0; i --){
            for (int j = 0; j < c; j ++){
                a[i][s-i+j] = a[i+1][s-i+j-1] + a[i][s-i+j-1];
            }
        }
        for (int i = 0; i < c - 1; i ++){
            printf("%d ", a[0][s+i]);
        }
        printf("%d\n",a[0][s+c-1]);
    }
    return 0;
}