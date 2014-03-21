/*
POJ 3667 Hotel （区间合并入门）

题目大意：区间内最长连续房间数。

问题出来了，对于二叉树，或许某子树根的左孩子的右边跟右孩子的左边连续着呢，怎么办？

于是，我们开出三个数组 lsum[] rsum[] 和 sum[]。对于区间 [L, R]，lsum[rt]表示以 L为开头的最长连续房间数，rsum[rt]表示以R为结尾的最长连续房间数，sum[]表示[L,R]内的最长连续房间。

继续分析：当 lsum[rt<<1]等于左孩子区间总长度时，lsum[rt<<1]和lsum[rt<<1|1] (即左孩子的lsum和右孩子的lsum)是相连的；

同理得， 当 rsum[rt<<1|1]等于右孩子总长度时，rsum[rt<<1|1]和rsum[rt<<1]（即右孩子的rsum和左孩子的rsum）是相连的。

而对于一个 sum[rt]= max{ rsum[rt<<1]+lsum[rt<<1|1], sum[rt<<1], sum[rt<<1|1 }。

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

typedef long long LL;

const int N=50005;
int mmax[N<<2],lmax[N<<2],rmax[N<<2],cov[N<<2];

void BuildTree(int l,int r,int rt)
{
    mmax[rt]=lmax[rt]=rmax[rt]=r-l+1;
	cov[rt]=-1;
	if (l==r) return;
	int mid=MID(l,r);
	BuildTree(l,mid,rt<<1);
	BuildTree(mid+1,r,rt<<1|1);
}

void PushUp(int rt,int w)
{
    lmax[rt]=lmax[rt<<1];
    rmax[rt]=rmax[rt<<1|1];
    if (lmax[rt]==w-(w>>1)) lmax[rt]+=lmax[rt<<1|1];
    if (rmax[rt]==(w>>1))     rmax[rt]+=rmax[rt<<1];
    mmax[rt]=max(rmax[rt<<1]+lmax[rt<<1|1],max(mmax[rt<<1],mmax[rt<<1|1]));
}

void PushDown(int rt,int w)
{
    if (cov[rt]!=-1)        //cov的作用只是向下传递标记时区别是清空还是住满该区间。
    {                       //cov在区间修改时决定，而那时的Update区间意味着要么住满要么清空
        cov[rt<<1]=cov[rt<<1|1]=cov[rt];
        mmax[rt<<1]=lmax[rt<<1]=rmax[rt<<1]=cov[rt]?0:w-(w>>1); //cov=1，则mmax,lmax,rmax=0，表示住满
        mmax[rt<<1|1]=lmax[rt<<1|1]=rmax[rt<<1|1]=cov[rt]?0:(w>>1); //cov=0，则mmax,lmax,rmax=区间长度，表示清空
        cov[rt]=-1;         //一定要注意下放标记后要重置！
    }
}

void Update(int s,int t,int c,int l,int r,int rt)   //c=1表示要住进，c=0表示要清空
{
    if (s<=l && r<=t)
    {
        cov[rt]=c;
        mmax[rt]=lmax[rt]=rmax[rt]=c?0:(r-l)+1;
        return ;
    }

    PushDown(rt,r-l+1);
    int mid=MID(l,r);
    if (s<=mid) Update(s,t,c,l,mid,rt<<1);
    if (mid<t)  Update(s,t,c,mid+1,r,rt<<1|1);
    PushUp(rt,r-l+1);
}

int Query(int L,int l,int r,int rt)
{
    if (l==r)
        return l;
    PushDown(rt,r-l+1);
    int mid=MID(l,r);
    if (mmax[rt<<1]>=L)  return Query(L,l,mid,rt<<1);      //按从左向右的顺序选
    else if (rmax[rt<<1]+lmax[rt<<1|1]>=L) return mid-rmax[rt<<1]+1;
    else return Query(L,mid+1,r,rt<<1|1);
}

int main()
{
    //freopen("test.in","r+",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    BuildTree(1,n,1);
    for (int i=0;i<m;i++)
    {
        int p;
        scanf("%d",&p);
        if (p==1)
        {
            int L;
            scanf("%d",&L);
            if (mmax[1]<L)  printf("%d\n",0);
            else
            {
                int a=Query(L,1,n,1);
                printf("%d\n",a);
                Update(a,a+L-1,1,1,n,1);
            }
        }
        else
        {
            int a,b;
            scanf("%d%d",&a,&b);
            Update(a,a+b-1,0,1,n,1);
        }
    }
    return 0;
}
