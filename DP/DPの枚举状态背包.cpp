/*
POJ 1837
题目大意：有个天平，给定G个不同大小的力，C个天平两边的力臂，求把所有力放在力臂上后天平平衡的方案数.

 

很难从这道题中找到一般DP那样的最优子结构，所以这类问题也就需要我们来“枚举”所有的情况了.

一般情况下需要枚举状态的DP，我们会设bool f[i][j]表示某种状态存不存在。而这道题要求方案数，所以，

我们设f[i][j]表示前i种物品平衡度为j的方案数.并且因为存在负的平衡度，所以我们给他扩大一倍->15000.

初始f[0][7500] = 1(7500表示平衡度为0)

状态转移方程即为：f[i][j] += f[i-1][j-l[k]*w[i]]
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <climits>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)
using namespace std;
typedef long long LL;
LL f[30][20000];
int l[30], w[30];
int main(){
    int C, G;
    scanf("%d%d", &C, &G);
    for (int i = 0; i < C; i ++)
        scanf("%d", &l[i]);
    for (int i = 0; i < G; i ++)
        scanf("%d", &w[i]);
    for (int i = 0; i < 30; i ++)
        for (int j = 0; j < 20000; j ++)
            f[i][j] = 0;
    f[0][7500] = 1;
    for (int i = 1; i <= G; i ++){
        for (int j = 0; j < 15000; j ++){
            for (int k = 0; k < C; k ++)
                if (j - l[k]*w[i] >= 0)
                    f[i][j] += f[i-1][j-l[k]*w[i-1]];
        }
    }
    printf("%I64d\n", f[G][7500]);
	return 0;
}