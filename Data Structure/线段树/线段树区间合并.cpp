/*
POJ 3667 Hotel ������ϲ����ţ�

��Ŀ���⣺�������������������

��������ˣ����ڶ�����������ĳ�����������ӵ��ұ߸��Һ��ӵ�����������أ���ô�죿

���ǣ����ǿ����������� lsum[] rsum[] �� sum[]���������� [L, R]��lsum[rt]��ʾ�� LΪ��ͷ���������������rsum[rt]��ʾ��RΪ��β���������������sum[]��ʾ[L,R]�ڵ���������䡣

������������ lsum[rt<<1]�������������ܳ���ʱ��lsum[rt<<1]��lsum[rt<<1|1] (�����ӵ�lsum���Һ��ӵ�lsum)�������ģ�

ͬ��ã� �� rsum[rt<<1|1]�����Һ����ܳ���ʱ��rsum[rt<<1|1]��rsum[rt<<1]�����Һ��ӵ�rsum�����ӵ�rsum���������ġ�

������һ�� sum[rt]= max{ rsum[rt<<1]+lsum[rt<<1|1], sum[rt<<1], sum[rt<<1|1 }��

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
    if (cov[rt]!=-1)        //cov������ֻ�����´��ݱ��ʱ��������ջ���ס�������䡣
    {                       //cov�������޸�ʱ����������ʱ��Update������ζ��Ҫôס��Ҫô���
        cov[rt<<1]=cov[rt<<1|1]=cov[rt];
        mmax[rt<<1]=lmax[rt<<1]=rmax[rt<<1]=cov[rt]?0:w-(w>>1); //cov=1����mmax,lmax,rmax=0����ʾס��
        mmax[rt<<1|1]=lmax[rt<<1|1]=rmax[rt<<1|1]=cov[rt]?0:(w>>1); //cov=0����mmax,lmax,rmax=���䳤�ȣ���ʾ���
        cov[rt]=-1;         //һ��Ҫע���·ű�Ǻ�Ҫ���ã�
    }
}

void Update(int s,int t,int c,int l,int r,int rt)   //c=1��ʾҪס����c=0��ʾҪ���
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
    if (mmax[rt<<1]>=L)  return Query(L,l,mid,rt<<1);      //���������ҵ�˳��ѡ
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
