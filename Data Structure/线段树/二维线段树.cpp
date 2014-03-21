/*
HDU 1823 Luck and Love (��ά�߶�������)

��Ϊ���������Ʒ�Χ��������Ҫ��ά���߶�����Ҳûʲô��˵�ĵط���

��Ҫע�⼸�����⣺1.��ʼ��sum = -1����Ȼ���еķ��ؽ������>=0���������Ҳ�������������жϡ�

2.������С�Ҵ���Ϊ����װ׹��׼���WA����������

3.�п��ܴ���ͬһ��ߡ����öȵ��ˣ����Ը���ʱ����ֱ�Ӹ�ֵ����ѡ��Ե��ֵ���ġ�
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)

using namespace std;

const int maxn1 = 105;
const int maxn2 = 1050;
int sum[maxn1<<2][maxn2<<2];
int n1 = 100, n2 = 1000;

void build()
{
    memset(sum,-1,sizeof(sum));
}
void update2(int p,int c,int l,int r,int rt1,int rt2)
{
    if (l == p && r == p)
    {
        sum[rt1][rt2] = max(sum[rt1][rt2], c);      //��Ҫ�����п��ܴ�����ߡ����ö�һ������Ů��ҪѡԵ��ֵ�ߵ�
        return ;
    }

    int mid = MID(l,r);
    if (p <= mid)   update2(p,c,l,mid,rt1,rt2<<1);
    else    update2(p,c,mid+1,r,rt1,rt2<<1|1);
    sum[rt1][rt2] = max(sum[rt1][rt2<<1],sum[rt1][rt2<<1|1]);
}
void update1(int h,int p,int c,int l,int r,int rt)  //h��ߣ�p���ö�
{
    update2(p,c,0,n2,rt,1);
    if (l == h && r == h)
        return ;
    int mid = MID(l,r);
    if (h <= mid)   update1(h,p,c,l,mid,rt<<1);
    else    update1(h,p,c,mid+1,r,rt<<1|1);
}
int query2(int p1,int p2,int l,int r,int rt1,int rt2)
{
    if (p1 <= l && r <= p2)
    {
        return sum[rt1][rt2];
    }
    int mid = MID(l,r);
    int res = -1;
    if (p1 <= mid)   res = max(res, query2(p1,p2,l,mid,rt1,rt2<<1));
    if (mid < p2)    res = max(res, query2(p1,p2,mid+1,r,rt1,rt2<<1|1));
    return res;
}
int query1(int h1,int h2,int p1,int p2,int l,int r,int rt)
{
    if (h1 <= l && r <= h2)
        return query2(p1,p2,0,n2,rt,1);
    int mid = MID(l,r);
    int res = -1;
    if (h1 <= mid)  res = max(res, query1(h1,h2,p1,p2,l,mid,rt<<1));
    if (mid < h2)   res = max(res, query1(h1,h2,p1,p2,mid+1,r,rt<<1|1));
    return res;
}
int main()
{
    //freopen("data.txt","r+",stdin);

    int m;
    while(scanf("%d",&m),m)
    {
        build();
        while(m--)
        {
            char s[2];
            scanf("%s",s);
            if (s[0] == 'I')
            {
                int h;
                double p,num;
                scanf("%d%lf%lf",&h,&p,&num);
                update1(h,int(p*10),int(num*10),n1,n1+100,1);
            }
            else
            {
                int h1,h2;
                double p1,p2;
                scanf("%d%d%lf%lf",&h1,&h2,&p1,&p2);
                if (h1 > h2)    swap(h1,h2);
                if (p1 > p2)    swap(p1,p2);
                int res = query1(h1,h2,int(p1*10),int(p2*10),n1,n1+100,1);
                if (res < 0)    printf("-1\n");
                else printf("%.1lf\n",res*1.0/10.0);
            }
        }
    }

    return 0;
}
