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

//Dancing Links
const int N = 350;
const int M = 20 ;
int R[M*N],L[M*N],U[M*N],D[M*N],O[M*N],S[M*N],C[M*N];
int h;      //head
int n,m;

void remove(int &c)
{
    L[R[c]]=L[c];
    R[L[c]]=R[c];
    for (int i=D[c];i!=c;i=D[i])
    //remove i that A[i,c]==1
        for (int j=R[i];j!=i;j=R[j])
        {
            //remove j that A[i,j]==1
            U[D[j]]=U[j];
            D[U[j]]=D[j];
            --S[C[j]];
            //decrese the count of column C[j];
        }
}

void resume(int &c)
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
    if (R[h] == h)
    {
        //one of the answers has been found.
        return true;
    }

    int c,s=INT_MAX;
    for (int i=R[h];i!=h;i=R[i])
        if (S[i]<s)
        {
            s=S[i];
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


//根据不同题目自己写构造链表函数
void Initialize_DancingLinks()
{
    h=0;

    //initialize the column head list.
    L[0]=m;
    for (int j=1;j<=m;j++)
    {
        R[j-1]=j;
        L[j]=j-1;
        S[j]=0;
    }
    R[m]=0;

    //initialize Dancing-Links
    for (int j=1;j<=m;j++)
    {
        for (int i=1;i<=n;i++)
        {
            U[i*m+j]=(i-1)*m+j;
            D[(i-1)*m+j]=i*m+j;
            C[i*m+j]=j;
            S[j]++;
        }
        D[n*m+j]=j;
        U[j]=n*m+j;
    }

    for (int i=1;i<=n;i++)
    {
        for (int j=2;j<=m;j++)
        {
            R[i*m+j-1]=i*m+j;
            L[i*m+j]=i*m+j-1;
        }
        R[i*m+m]=i*m+1;
        L[i*m+1]=i*m+m;
    }

    int d[20][305];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&d[i][j]);

    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if (d[i][j]==0)
            {
                D[U[i*m+j]]=D[i*m+j];
                U[D[i*m+j]]=U[i*m+j];
                S[C[i*m+j]]--;
                R[L[i*m+j]]=R[i*m+j];
                L[R[i*m+j]]=L[i*m+j];
            }
}

//在int main()里用Dance(0)调用程序。