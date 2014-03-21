#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <climits>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

typedef long long LL;
const double EPS = 1e-11;

//Dancing Links X解数独

//列(N+N+N)*N+N*N=4*N*N.
#define N 750   //>9*9*9
#define M 350   //>4*9*9
const int P=9;  //p阶数独
int h;
int L[N*M],R[N*M],U[N*M],D[N*M],S[N*M],C[N*M],O[N*M];

int n,m;
void remove (const int &c)
{
    L[R[c]]=L[c];
    R[L[c]]=R[c];
    for (int i=D[c];i!=c;i=D[i])
        for (int j=R[i];j!=i;j=R[j])
        {
            U[D[j]]=U[j];
            D[U[j]]=D[j];
            --S[C[j]];
        }
}

void resume (const int &c)
{
    for (int i=U[c];i!=c;i=U[i])
        for (int j=L[i];j!=i;j=L[j])
        {
            U[D[j]]=j;
            D[U[j]]=j;
            ++S[C[j]];
        }
    L[R[c]]=c;
    R[L[c]]=c;
}

bool Dance(int k)
{
    if (R[h]==h)
    {
        sort(O,O+k);
        for (int i=0;i<k;i++)
            printf("%d",(O[i]-1)/m%P==0?P:((O[i]-1)/m%P));
        printf("\n");

        return true;
    }

    int c,ss=INT_MAX;

    for (int i=R[h];i!=h;i=R[i])
        if (S[i]<ss)
        {
            ss=S[i];
            c=i;
        }

    remove(c);
    for (int i=D[c];i!=c;i=D[i])
    {
        O[k]=i;
        for (int j=R[i];j!=i;j=R[j])
            remove(C[j]);
        if (Dance(k+1))
            return true;
        for (int j=L[i];j!=i;j=L[j])
            resume(C[j]);
    }
    resume(c);

    return false;
}

//Initialize
void Link(char s[])
{
    int d[N][M];
    memset(d,0,sizeof(d));
    memset(O,0,sizeof(O));

    //preprocess the sudoku 数独转换精确覆盖问题矩阵形式
    int q=0;
    for (int i=1;i<=P;i++)
        for (int j=1;j<=P;j++)
        {
            if (s[q]=='.')
            {
                for (int k=1;k<=P;k++)
                {
                    int rr=((i-1)*P+j-1)*P+k;                   //行。(9*9*9)行 表示数独第i行第j列数填k
                    d[rr][(i-1)*P+k]=1;                         //列。前(9*9)列 表示数独第i行有数k
                    d[rr][(j-1)*P+k+P*P]=1;                     //列。(9*9)列 表示数独第j行有数k
                    d[rr][((i-1)/3*3+(j-1)/3)*P+k+2*P*P]=1;     //列。(9*9)列 表示数独第p个九宫格有数k
                    d[rr][(i-1)*P+j+3*P*P]=1;                   //列。(9*9)列 表示数独第i行第j行有一个数（防止一个格子填多个数）
                }
            }
            else
            {
                int num=s[q]-'0';
                int rr=((i-1)*P+j-1)*P+num;                 //行。(9*9*9)行 表示数独第i行第j列数填k
                d[rr][(i-1)*P+num]=1;                       //列。前(9*9)列 表示数独第i行有数k
                d[rr][(j-1)*P+num+81]=1;                    //列。(9*9)列 表示数独第j行有数k
                d[rr][((i-1)/3*3+(j-1)/3)*P+num+162]=1;     //列。(9*9)列 表示数独第p个九宫格有数k
                d[rr][(i-1)*P+j+243]=1;                     //列。(9*9)列 表示数独第i行第j行有一个数（防止一个格子填多个数）
            }

            q++;
        }

    //Initialize the all matrix to list.
    
    int x[N],row[N],col[M];           //x表示当前行中的第一个链,row表示当前行中上一个插入的链、col表示当前列中上一个插入的链。
    h=0;
    for (int i=1;i<=m;i++)
    {
        R[i-1]=i;
        L[i]=i-1;
        S[i]=0;
        col[i]=i;
    }
    col[0]=0;
    L[h]=m;
    R[m]=h;

    for (int i=1;i<=n;i++)
    {
        x[i]=0;                             //行第一个链表
        for (int j=1;j<=m;j++)
            if (d[i][j])
            {
                int index=i*(4*P*P)+j;      //带插入的列表下标。
                if (!x[i])
                {
                    row[i]=x[i]=index;
                }
                else
                {
                    R[row[i]]=index;
                    L[index]=row[i];
                }
                D[col[j]]=index;
                U[index]=col[j];
                row[i]=col[j]=index;
                C[index]=j;
                S[j]++;
            }
    }

    for (int i=1;i<=n;i++)
        if (x[i])
        {
            L[x[i]]=row[i];
            R[row[i]]=x[i];
        }
    for (int j=1;j<=m;j++)
    {
        D[col[j]]=j;
        U[j]=col[j];
    }
}

int main()
{
    //freopen("test.in","r+",stdin);
    //freopen("test.out","w+",stdout);

    char s[100];
    n=P*P*P;
    m=4*P*P;
    while(~scanf("%s",s))
    {
        if (!strcmp(s,"end"))
            return 0;
        Link(s);
        Dance(0);
    }
    return 0;
}
