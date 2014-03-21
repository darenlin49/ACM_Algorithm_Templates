/*
POJ 1837
��Ŀ���⣺�и���ƽ������G����ͬ��С������C����ƽ���ߵ����ۣ�������������������Ϻ���ƽƽ��ķ�����.

 

���Ѵ���������ҵ�һ��DP�����������ӽṹ��������������Ҳ����Ҫ��������ö�١����е������.

һ���������Ҫö��״̬��DP�����ǻ���bool f[i][j]��ʾĳ��״̬�治���ڡ��������Ҫ�󷽰��������ԣ�

������f[i][j]��ʾǰi����Ʒƽ���Ϊj�ķ�����.������Ϊ���ڸ���ƽ��ȣ��������Ǹ�������һ��->15000.

��ʼf[0][7500] = 1(7500��ʾƽ���Ϊ0)

״̬ת�Ʒ��̼�Ϊ��f[i][j] += f[i-1][j-l[k]*w[i]]
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