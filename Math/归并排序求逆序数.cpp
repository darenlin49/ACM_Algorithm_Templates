/*
��������������1��2������n��ɵ�һ�����������Ϊһ��n�����С���һ�����������һ������ǰ��λ�����С˳���෴������������С����ǰ�棬�������Ϊһ������һ������������������ܺͳ�Ϊ�����е���������

�鲢�������ԭ��
���������鲢�����Ƿ��ε�˼�룬����ԭ���Լ�ȥ����ɡ����ù鲢��������ָ�ڶ������� s1��s2�ڹ鲢ʱ����s1[i]>s2[j]������״������������������s1.length-i,��Ϊs1��i��������ֶ���s2[j]��������ġ�
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
        res = 0;		//������
        merge_sort(a, 0, n - 1);
//        for (int i = 0; i < n; i ++)
//            printf("%d\n", a[i]);
        printf("Scenario #%d:\n", caseo);
        printf("%d\n\n", res);
    }
	return 0;
}
