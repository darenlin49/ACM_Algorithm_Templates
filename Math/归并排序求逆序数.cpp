/*
序列逆序数：由1，2，…，n组成的一个有序数组称为一个n级排列。在一个排列中如果一对数的前后位置与大小顺序相反，即大数排在小数的前面，则称它们为一个逆序。一个排列中所有逆序的总和称为该排列的逆序数。

归并求逆序简单原理：
　　　　归并排序是分治的思想，具体原理自己去看书吧。利用归并求逆序是指在对子序列 s1和s2在归并时，若s1[i]>s2[j]（逆序状况），则逆序数加上s1.length-i,因为s1中i后面的数字对于s2[j]都是逆序的。
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

const int N = 1001;
int a[N];
int res;
void mmerge(int a[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int n = r - p + 1;
    int tmp[n], k = 0;
    int left[n1], right[n2];
    for (int i = 0; i < n1; i ++)
        left[i] = a[p + i];
    for (int i = 0; i < n2; i ++)
        right[i] = a[q + 1 + i];
    int i1 = 0, i2 = 0;
    while(i1 < n1 && i2 < n2){
        if (left[i1] <= right[i2]){
            tmp[k ++] = left[i1 ++];
        }
        else if (left[i1] > right[i2]){
            tmp[k ++] = right[i2 ++];
            res += n1 - i1;
        }
    }
    while (i1 < n1){
        tmp[k ++] = left[i1 ++];
    }
    while (i2 < n2){
        tmp[k ++] = right[i2 ++];
    }
    for (int i = 0; i < n; i ++){
        a[p + i] = tmp[i];
    }
}
void merge_sort(int a[], int l, int r){
    if (r <= l)
        return ;
    int mid = MID(l, r);
    merge_sort(a, l, mid);
    merge_sort(a, mid+1, r);
    mmerge(a, l, mid, r);
    return ;
}
int main(){
    int t;
    scanf("%d\n", &t);
    for (int caseo = 1; caseo <= t; caseo ++){
        int n;
        scanf("%d", &n);
        mem(a, 0);
        for (int i = 0; i < n; i ++)
            scanf("%d", &a[i]);
        res = 0;		//逆序数
        merge_sort(a, 0, n - 1);
//        for (int i = 0; i < n; i ++)
//            printf("%d\n", a[i]);
        printf("Scenario #%d:\n", caseo);
        printf("%d\n\n", res);
    }
	return 0;
}
