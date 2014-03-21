//NOI 1995 石子合并
//区间划分DP

 #include <cstdio>
 #include <algorithm>
 using namespace std;
 
 int n;
 int a[205],s[205][205],t[205][205];
 int num[205][205];
 int calnum()
 {
     for (int i = 0; i < 2 * n - 1 ; i ++)
         num[i][i] = a[i];
     for (int p = 1; p < n; p ++)
         for (int i = 0; i < 2 * n - 1; i ++)
         {
             if (i + p < 2 * n - 1)
             {
                 int j = i + p;
                 num[i][j] = num[i][i] + num[i + 1][j];
             }
         }
 }
 int calmin()
 {
     for (int i = 0; i < 205; i ++)
         for (int j = 0; j < 205; j ++)
             s[i][j] = 1e8;
     for (int i = 0; i < 2 * n - 1 ; i ++)
         s[i][i] = 0;
     for (int k = 1; k < n; k ++)
         for (int i = 0; i < 2 * n - 1; i ++)
         {
             if (i + k < 2 * n - 1)
             {
                 int j = i + k;
                 for (int p = i; p < j; p ++)
                     s[i][j] = min(s[i][j], s[i][p] + s[p + 1][j] + num[i][p] + num[p + 1][j]);
             }
         }
     int res = 1e8;
     for (int i = 0; i < n; i ++)
         if (s[i][i + n - 1] < res)
             res = s[i][i + n - 1];
     return res;
 }
 int calmax()
 {
     for (int p = 1; p < n; p ++)
         for (int i = 0; i < 2 * n - 1; i ++)
         {
             if (i + p < 2 * n - 1)
             {
                 int j = i + p;
                 for (int k = i; k < j; k ++)
                     t[i][j] = max(t[i][j], t[i][k] + t[k + 1][j] + num[i][k] + num[k + 1][j]);
             }
         }
     int res = 0;
     for (int i = 0; i < n; i ++)
         if (t[i][i + n - 1] > res)
             res = t[i][i + n - 1];
     return res;
 }
 int main()
 {
     scanf("%d",&n);
     for (int i = 0; i < n; i ++)
     {
         scanf("%d",&a[i]);
         a[i + n] = a[i];
     }
     calnum();
     printf("%d\n%d\n",calmin(),calmax());
     return 0;
 }