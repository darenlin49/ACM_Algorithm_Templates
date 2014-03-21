/*
这个问题和求两点间经过N条边的路径数很相似，而我们知道如果用图的邻接矩阵A存储图的话，二分矩阵快速幂A^N即为所求。路径数能用矩阵乘法求是因为它的状态方程正好和矩阵乘法一样：设dp[i][j][p]表示i到j点经过p条边的路径数，则dp[i][j][p] = sigma(dp[i][k][p-1]*dp[k][j][1])，即A=B*C（把dp[p]看成A，dp[p-1]看成B……）；

但显然最短路的方程不是这样的。按照Floyd的方程它应该是dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j])。

那这样的方程能用类似上面的方法求么？答案是肯定的，只要修改一下“乘法”即可。显然，只要矩阵运算符合结合律，那么它就能用二分矩阵快速幂做。关于上面Floyd方程符合结合率的证明，俞华程的论文《矩阵乘法在信息学中的应用》有证明，不过他前面的我没看懂。。。

那么只要我们重新定义下矩阵“乘法”为：C[i][j] = min(C[i][j], A[i][k]+B[k][j])，问题迎刃而解。

假如我们设图的邻接矩阵为VE，则按上面的定义，VE * VE 显然就是两点到达经过两条边所需要的最短路径。然后同理VE ^ N就是到达经过N条边所需要的最短路径。为什么这个很类似Floyd的式子求出来的是确定了经过边数的最短距离？因为这个更新和Floyd不同的是更新到一个新的矩阵上去了而不是直接像Floyd的自己更新自己。所以在一更新时，不会出现自己刚更新的值又来继续更新。
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
 
typedef long long LL;
const int sup = 0x7fffffff;
const int inf = -0x7fffffff;
 
int hash[1000003], cnt;
struct mat{
    long long map[200][200];
    void init(){
        mem(map, -1);
    }
    void make_head(){
        mem(map, -1);
        for (int i = 0; i < cnt; i ++)
            map[i][i] = 0;
    }
}A;
int n, t, s, e;
mat floyd(mat &A, mat &B){
    mat res;
    res.init();
    for (int k = 0; k < cnt; k ++){
        for (int i = 0; i < cnt; i ++){
            if (A.map[i][k] != -1){
                for (int j = 0; j < cnt; j ++){
                    if(B.map[k][j] != -1){
                        if (res.map[i][j] == -1){
                            res.map[i][j] = A.map[i][k] + B.map[k][j];
                        }
                        else{
                            res.map[i][j] = min(res.map[i][j], A.map[i][k] + B.map[k][j]);
                        }
                    }
                }
            }
        }
    }
    return res;
}
long long work(mat &A, int n){
    mat res;
    res.make_head();
    while(n){
        if (n & 1){
            res = floyd(res, A);
        }
        n >>= 1;
        A = floyd(A, A);
    }
    return res.map[hash[s]][hash[e]];
}
int main(){
    mem(hash, -1);
    A.init();
    cnt = 0;
    scanf("%d %d %d %d", &n, &t, &s, &e);
    if (hash[s] == -1)
        hash[s] = cnt ++;
    if (hash[e] == -1)
        hash[e] = cnt ++;
    for (int i = 0; i < t; i ++){
        int l, a, b;
        scanf("%d %d %d", &l, &a, &b);
        if (hash[a] == -1)
            hash[a] = cnt ++;
        if (hash[b] == -1)
            hash[b] = cnt ++;
        A.map[hash[a]][hash[b]] = l;
        A.map[hash[b]][hash[a]] = l;
    }
    printf("%I64d\n", work(A, n));
	return 0;
}