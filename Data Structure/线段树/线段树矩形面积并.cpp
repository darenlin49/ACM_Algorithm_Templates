/*
HDU 1542 Atlantis (���������������)

������󣺾��������

���������⣺POJ 1151 (��������⣬����POJ�����ݱȽ���...)��POJ 1389��POJ 3277(���о��εױ߶���һ��ˮƽ����)

˼·����������Ҫ��ɢ��; ����һ������(x1, y1, x2, y2)��ֻȡ�ϱߺ��±ߣ��ṹ��ss[] ��¼һ���ߵ����ҵ�����;�������ĸ߶ȣ�����һ������ ss[].s��¼���������ϱ߻����±ߣ��±߼�¼Ϊ1���ϱ߼�¼Ϊ-1�����߶����򣬶Ժ��Ὠ�����ӵ͵���ɨ��һ�顣���±ߣ�������߶��������ϱߣ�����߶�����ȥ������cnt��ʾ�������±߱��ϱ߶༸���߶�,sum����������ڱ����ǵĳ����ܺ͡�

�����߶�����һ����㲢�����߶ε�һ���˵�,���Ǹö˵����һ���˵����߶�,������Ŀ��r+1,r-1�ĵط�Ҫ�úõ���ĥһ�¡�
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
const int maxn = 500;
double X[maxn];
double sum[maxn<<2];
int cnt[maxn<<2];

struct Seg
{
    double l,r,h;
    int s;
    Seg(){}
    Seg(double a,double b,double c,int d):l(a),r(b),h(c),s(d){}
    bool operator < (const Seg &cmp) const
    {
        return h < cmp.h;
    }
}ss[maxn];

void pushup(int rt,int l,int r)
{
    if (cnt[rt])    sum[rt] = X[r+1] - X[l];
    else if (l == r)    sum[rt] = 0;
    else sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void update(int s,int t,int v,int l,int r,int rt)
{
    if (s <= l && r <= t)
    {
        cnt[rt] += v;
        pushup(rt,l,r);
        return ;
    }
    int mid = MID(l,r);
    if (s <= mid)   update(s,t,v,l,mid,rt<<1);
    if (mid < t)    update(s,t,v,mid+1,r,rt<<1|1);
    pushup(rt,l,r);
}
int binfind(double x,int n,double X[])
{
    int head = 0, tail = n - 1;
    while(head <= tail)
    {
        int mid = MID(head,tail);
        if (X[mid] == x)    return mid;
        if (X[mid] < x)     head = mid + 1;
        else    tail = mid - 1;
    }
    return -1;
}
int main()
{
    //freopen("data.txt","r+",stdin);

    int cas = 1;
    int n;
    while(~scanf("%d",&n) && n)
    {
        int tot = 0;
        while(n--)
        {
            double a,b,c,d;
            scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
            X[tot] = a;
            ss[tot ++] = Seg(a,c,b,1);
            X[tot] = c;
            ss[tot ++] = Seg(a,c,d,-1);
        }
        sort(X,X+tot);
        sort(ss,ss+tot);
        int ptot = 1;
        for (int i = 1; i < tot ; i ++)
            if (X[i]!=X[i-1])   X[ptot ++] = X[i];

        //build(1,ptot,1);
        memset(cnt , 0 , sizeof(cnt));
        memset(sum , 0 , sizeof(sum));
        double res = 0;
        for (int i = 0; i < tot - 1; i ++)
        {
            int l = binfind(ss[i].l, ptot, X);
            int r = binfind(ss[i].r, ptot, X) - 1;
            if (l <= r) update(l, r, ss[i].s, 0, ptot-1 , 1);
            res += sum[1] * (ss[i+1].h - ss[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",cas++ , res);
    }

    return 0;
}
