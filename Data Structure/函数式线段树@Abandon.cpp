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

const int MAXN = 100010;
struct tree
{
    int l,r;
    int ls,rs;
    int sum;
}t[MAXN*20];
int tot,root[MAXN];

int build(int l, int r)
{
    int k = ++ tot;
    t[k].l = l, t[k].r = r;
    t[k].sum = 0;
    if (l == r) return k;
    int mid = MID(l,r);
    t[k].ls = build(l,mid);
    t[k].rs = build(mid+1,r);
    return k;
}
int change(int o, int x, int v)
{
    int k = ++ tot;
    t[k] = t[o];
    t[k].sum += v;
    if (t[o].l == x && t[o].r == x)
        return k;
    int mid = MID(t[o].l, t[o].r);
    if (x <= mid)   t[k].ls = change(t[o].ls, x, v);
    else    t[k].rs = change(t[o].rs, x, v);
    return k;
}
int query(int n,int o,int k)  	//询问区间[t1,t2]第k小
{
    if (t[n].l == t[n].r) return t[n].l;
    int res = t[t[n].ls].sum-t[t[o].ls].sum;
    if (k <= res)
        return query(t[n].ls,t[o].ls,k);
    else return query(t[n].rs,t[o].rs,k-res);
}

int b[MAXN],sortb[MAXN];
int q;
int main()
{
    //freopen("test.in","r+",stdin);
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for (int i = 1; i <= n; i ++)
            scanf("%d",&b[i]),sortb[i]=b[i];
        sort(sortb+1, sortb+n+1);
        int i;
        for (q = 1, i = 2; i <= n; ++ i)    //去重
            if (sortb[q] != sortb[i])
                sortb[++q] = sortb[i];
        root[0] = build(1,q);
        for (int i = 1; i <= n; i ++)
        {
            int p = lower_bound(sortb+1, sortb+n+1, b[i])-sortb;
            root[i] = change(root[i-1], p, 1);
        }

        for (int i = 0; i < m; i ++)
        {
            int a,b,k;
            scanf("%d%d%d",&a,&b,&k);
            printf("%d\n",sortb[query(root[b],root[a-1],k)]);
        }

    }
    return 0;
}
