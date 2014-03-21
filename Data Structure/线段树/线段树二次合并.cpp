/*
HDU 4351 Digital root ★★(2012 Multi-University Training Contest 6) (线段树值得研究的一道好题)

区间合并->二次合并(pushup)->更新时要合并左右子区间,询问时要合并左右询问子区间（这是不一样的，比如在[1,8]中询问[1,6]，那么左右子区间分别是[1,4],[5,8]，而左右询问子区间是[1,4],[5,6]）。

预备知识：一个数的数字根就是这个数mod 9的余数 (余数为0则取9，当然如果这个数本身是0那就是0了……)

思路：因为题目中所查询的区间，是所有的子区间的结果的并。所以区间合并就很必要了。

每个结点，记录这个区间的和的数根， 记录本区间内从左端点为端点往右的连续区间出现的数根，从右端点为端点往左的连续区间出现的数根，以及整个区间能出现的数根。然后合并什么的。。。

但显然还没有结束，不然我也不会把他视作好题了。。。这道题用线段树会卡时限！需要各种优化------主要是算数字根的打表优化。

做了一天吧T_T。。。上午想好了思路，然后一下午+晚上完成了一个加上打表、输入输出优化还是TLE的代码。。。T_T。。。然后就捉鸡了。。。然后第二天上午终于找到哪儿超时了（我说怎么加了打表优化和输入输出优化还超T_T），竟然是开始回答询问时的那四个memset T_T，然后恍然大悟。。。我竟然sb的给ans也建了颗线段树！活该作死啊。。。T_T。。。

然后把ans改为节点，加上打表优化、输入输出外挂后终于A了T_T  （速度还不是很快啊。。。网上找了个程序1100MS呜呜。。。）：
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
int mul[10][10];    //合并i,j打表优化

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
//外挂优化。。。
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

//线段树部分
inline void pushUp(int rt)
{
    for (int i = 0; i < 10; i ++)
    {
        lsum[rt][i] = lsum[rt<<1][i];
        rsum[rt][i] = rsum[rt<<1|1][i];
        ssum[rt][i] = (ssum[rt<<1][i] == 1)?1:ssum[rt<<1|1][i];
    }
    //修改区间和数字根
    int k = mul[mmax[rt<<1]][mmax[rt<<1|1]];
    mmax[rt] = k,  ssum[rt][k] = 1;

    for (int i = 0; i < 10; i ++)
    {
        //右前缀+区间和扩展前缀数字根和子区间数字根
        if (lsum[rt<<1|1][i])
        {
            int k = mul[mmax[rt<<1]][i];
            lsum[rt][k] = 1,   ssum[rt][k] = 1;
        }
        //左后缀+区间和扩展后缀数字根和子区间数字根
        if (rsum[rt<<1][i])
        {
            int k = mul[mmax[rt<<1|1]][i];
            rsum[rt][k] = 1,   ssum[rt][k] = 1;

            //左后缀+右前缀扩展子区间数字根
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
    //查询时也要合并左右区间...
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