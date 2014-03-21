/*
HDU 4351 Digital root ���(2012 Multi-University Training Contest 6) (�߶���ֵ���о���һ������)

����ϲ�->���κϲ�(pushup)->����ʱҪ�ϲ�����������,ѯ��ʱҪ�ϲ�����ѯ�������䣨���ǲ�һ���ģ�������[1,8]��ѯ��[1,6]����ô����������ֱ���[1,4],[5,8]��������ѯ����������[1,4],[5,6]����

Ԥ��֪ʶ��һ���������ָ����������mod 9������ (����Ϊ0��ȡ9����Ȼ��������������0�Ǿ���0�ˡ���)

˼·����Ϊ��Ŀ������ѯ�����䣬�����е�������Ľ���Ĳ�����������ϲ��ͺܱ�Ҫ�ˡ�

ÿ����㣬��¼�������ĺ͵������� ��¼�������ڴ���˵�Ϊ�˵����ҵ�����������ֵ����������Ҷ˵�Ϊ�˵����������������ֵ��������Լ����������ܳ��ֵ�������Ȼ��ϲ�ʲô�ġ�����

����Ȼ��û�н�������Ȼ��Ҳ����������������ˡ�������������߶����Ῠʱ�ޣ���Ҫ�����Ż�------��Ҫ�������ָ��Ĵ���Ż���

����һ���T_T���������������˼·��Ȼ��һ����+���������һ�����ϴ����������Ż�����TLE�Ĵ��롣����T_T������Ȼ���׽���ˡ�����Ȼ��ڶ������������ҵ��Ķ���ʱ�ˣ���˵��ô���˴���Ż�����������Ż�����T_T������Ȼ�ǿ�ʼ�ش�ѯ��ʱ�����ĸ�memset T_T��Ȼ���Ȼ���򡣡����Ҿ�Ȼsb�ĸ�ansҲ���˿��߶��������������������T_T������

Ȼ���ans��Ϊ�ڵ㣬���ϴ���Ż������������Һ�����A��T_T  ���ٶȻ����Ǻܿ찡�������������˸�����1100MS���ء���������
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
const int maxn = 100100;
int mmax[maxn<<2],lsum[maxn<<2][10],rsum[maxn<<2][10],ssum[maxn<<2][10];
int mul[10][10];    //�ϲ�i,j����Ż�

struct ANS
{
    int ls[10], rs[10];
    int res[10];
    int all;
    ANS()
    {
        memset(ls,0,sizeof(ls));
        memset(rs,0,sizeof(rs));
        memset(res,0,sizeof(res));
        all = 0;
    }
};

void initial()
{
    for (int i = 0; i < 10; i ++)
        for (int j = 0; j < 10; j ++)
        {
            int k = i + j;
            while (k > 9)
                k -= 9;
            mul[i][j] = k;
        }
}
//����Ż�������
inline void scanf_(int &num)
{
    char in;
    bool neg = false;
    while(((in = getchar()) > '9' || in <'0') && in != '-') ;
    if(in == '-')
    {
        neg = true;
        while((in = getchar()) >'9' || in < '0');
    }
    num = in - '0';
    while(in = getchar(),in >= '0' && in <= '9')
        num *= 10, num += in - '0';
    if(neg)
        num = 0 - num;
}
inline void printf_(int num)
{
    if(num < 0)
    {
        putchar('-');
        num =- num;
    }
    int ans[10],top = 0;
    while(num != 0)
    {
        ans[top ++] = num % 10;
        num /= 10;
    }
    if(top == 0)
        putchar('0');
    for(int i = top - 1; i >= 0; i --)
    {
        char ch = ans[i] + '0';
        putchar(ch);
    }
    //putchar('\n');
}

//�߶�������
inline void pushUp(int rt)
{
    for (int i = 0; i < 10; i ++)
    {
        lsum[rt][i] = lsum[rt<<1][i];
        rsum[rt][i] = rsum[rt<<1|1][i];
        ssum[rt][i] = (ssum[rt<<1][i] == 1)?1:ssum[rt<<1|1][i];
    }
    //�޸���������ָ�
    int k = mul[mmax[rt<<1]][mmax[rt<<1|1]];
    mmax[rt] = k,  ssum[rt][k] = 1;

    for (int i = 0; i < 10; i ++)
    {
        //��ǰ׺+�������չǰ׺���ָ������������ָ�
        if (lsum[rt<<1|1][i])
        {
            int k = mul[mmax[rt<<1]][i];
            lsum[rt][k] = 1,   ssum[rt][k] = 1;
        }
        //���׺+�������չ��׺���ָ������������ָ�
        if (rsum[rt<<1][i])
        {
            int k = mul[mmax[rt<<1|1]][i];
            rsum[rt][k] = 1,   ssum[rt][k] = 1;

            //���׺+��ǰ׺��չ���������ָ�
            for (int j = 0; j < 10; j ++)
                if (lsum[rt<<1|1][j])
                {
                    int k = mul[i][j];
                    ssum[rt][k] = 1;
                }
        }
    }
}

inline void pushUpAns(int rt,ANS &p,ANS &lp,ANS &rp)
{
    //��ѯʱҲҪ�ϲ���������...
    for (int i = 0; i < 10; i ++)
    {
        p.ls[i] = lp.ls[i];
        p.rs[i] = rp.rs[i];
        p.res[i] = (lp.res[i] == 1)?1:rp.res[i];
    }
    for (int i = 0; i < 10; i ++)
    {
        if (rp.ls[i])
        {
            int k = mul[lp.all][i];
            p.ls[k] = 1,   p.res[k] = 1;
        }
        if (lp.rs[i])
        {
            int k = mul[rp.all][i];
            p.rs[k] = 1,   p.res[k] = 1;
        }
        if (lp.rs[i])
            for (int j = 0; j < 10; j ++)
                if (rp.ls[j])
                {
                    int k = mul[i][j];
                    p.res[k] = 1;
                }
    }
}

void build(int l,int r,int rt)
{
    if (l == r)
    {
        mmax[rt] = 0;
        for (int i = 0; i < 10; i ++)
        {
            lsum[rt][i] = 0;
            rsum[rt][i] = 0;
            ssum[rt][i] = 0;
        }
        int a;
        scanf_(a);
        //scanf("%d",&a);
        if (!a) {   mmax[rt] = 0; lsum[rt][0] = 1;   rsum[rt][0] = 1;   ssum[rt][0] = 1;   }
        else
        {
            a = a % 9;
            if (!a) {   mmax[rt] = 9; lsum[rt][9] = 1;   rsum[rt][9] = 1;   ssum[rt][9] = 1;  }
            else {  mmax[rt] = a; lsum[rt][a] = 1;   rsum[rt][a] = 1;    ssum[rt][a] = 1; }
        }
        return ;
    }
    int mid = MID(l,r);
    build(l, mid, rt<<1);
    build(mid+1, r, rt<<1|1);
    pushUp(rt);
}

int query(int s,int t,int l,int r,int rt,ANS &p)
{
    if (s <= l && r <= t)
    {
        for (int i = 9; i >= 0; i --)
        {
            if (ssum[rt][i])
                p.res[i] = 1;
            if (lsum[rt][i])
                p.ls[i] = 1;
            if (rsum[rt][i])
                p.rs[i] = 1;
        }
        p.all = mmax[rt];
        while (p.all > 9)   p.all -= 9;
        return p.all;
    }
    int res = 0;
    int mid = MID(l,r);
    ANS lp,rp;
    if (s <= mid)   res += query(s,t,l,mid,rt<<1,lp);
    if (mid < t)    res += query(s,t,mid+1,r,rt<<1|1,rp);
    p.all = res;
    while (p.all > 9)   p.all -= 9;
    pushUpAns(rt,p,lp,rp);
    return res;
}

int main()
{
//    freopen("data.txt","r+",stdin);
//    freopen("ans.txt","w+",stdout);
    initial();
    int t, caseo = 1;
    scanf_(t);
    //scanf("%d",&t);
    while(t--)
    {
        printf("Case #%d:\n",caseo ++);
        int n;
        scanf_(n);
        //scanf("%d",&n);
        build(1,n,1);
        int Q;
        scanf_(Q);
        //scanf("%d",&Q);
        while(Q--)
        {
            ANS ans;
            int l,r;
            scanf_(l),scanf_(r);
            //scanf("%d%d",&l,&r);
            query(l,r,1,n,1,ans);
            int tot = 0;
            for (int i = 9; i >= 0; i --)
                if (ans.res[i] && tot < 5)
                {
                    tot ++;
                    //tot == 5?printf("%d\n",i):printf("%d ",i);
                    if (tot == 5)
                        printf_(i),putchar('\n');
                    else    printf_(i),putchar(' ');
                }
            while(tot < 5)
            {
                tot ++;
                //tot == 5?printf("-1\n"):printf("-1 ");
                if (tot == 5)
                    puts("-1");
                else
                {
                    putchar('-');
                    putchar('1');
                    putchar(' ');
                }
            }
        }
        if (t)  printf("\n");
    }
    return 0;
}