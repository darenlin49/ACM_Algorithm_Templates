/**
	[后缀数组1.0 - 2013.09.13]
	[注意]r[]可换为char[],在原字符串最后一位填一个0-比前面任何字符小的字符,调用da()时长度应为原字符串长度+1.
	[SPOJ Distinct Substrings 不同子串个数]	res = sigma(n-sa[i]-height[i]);
**/

//Suffix Array
const int maxn = 1005;
int wx[maxn], wy[maxn], wxy[maxn], hs[maxn];
int r[maxn], sa[maxn], ranks[maxn], height[maxn];
int cmp(int r[], int a, int b, int l){
    return (r[a] == r[b] && r[a+l] == r[b+l]);
}
//r is the string, and r[n-1] = 0, this means we should add a '0' at the end of the string.
void da(int r[], int sa[], int ranks[], int height[], int n, int m){
    //calculate sa[], begin at 1 because sa[0] = "0".
    int i, j, len, p, k = 0, *x = wx, *y = wy, *t;
    for (i = 0; i < m; i ++)    hs[i] = 0;
    for (i = 0; i < n; i ++)    hs[x[i] = r[i]] ++;
    for (i = 1; i < m; i ++)    hs[i] += hs[i-1];
    for (i = n-1; i >= 0; i --)    sa[-- hs[x[i]]] = i;
    for (len = 1, p = 1; p < n; len *= 2, m = p){
        for (p = 0, i = n - len; i < n; i ++)   y[p ++] = i;
        for (i = 0; i < n; i ++)    if (sa[i] >= len) y[p ++] = sa[i] - len;
        for (i = 0; i < n; i ++)    wxy[i] = x[y[i]];
        for (i = 0; i < m; i ++)    hs[i] = 0;
        for (i = 0; i < n; i ++)    hs[wxy[i]] ++;
        for (i = 1; i < m; i ++)    hs[i] += hs[i-1];
        for (i = n-1; i >= 0; i --)    sa[-- hs[wxy[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, i = 1, x[sa[0]] = 0; i < n; i ++)
            x[sa[i]] = cmp(y, sa[i-1], sa[i], len)?p-1:p ++;
    }
    //calculate height[], height[n-1] is null because we add a '0' at the end of the string.
    for (i = 1; i < n; i ++)    ranks[sa[i]] = i;
    for (i = 0; i < n - 1; height[ranks[i++]] = k)
        for (k?k--:0, j = sa[ranks[i]-1]; r[i+k] == r[j+k]; k ++);
}

int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        char tmps[1005] = {0};
        scanf("%s", tmps);
        MEM(r, 0);
        int n = strlen(tmps);
        for (int i = 0; i < n; i ++)    r[i] = tmps[i];
        da(r, sa, ranks, height, n + 1, 100);
        int res = 0;
        for (int i = 1; i <= n; i ++){
            res += n - sa[i] - height[i];
        }
        printf("%d\n", res);
    }
	return 0;
}

//LCP
int RMQ[maxn];
int mm[maxn];
int best[20][maxn];
void initRMQ(int n)
{
     int i,j,a,b;
     for(mm[0]=-1,i=1;i<=n;i++)
     mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
     for(i=1;i<=n;i++) best[0][i]=i;
     for(i=1;i<=mm[n];i++)
     for(j=1;j<=n+1-(1<<i);j++)
     {
       a=best[i-1][j];
       b=best[i-1][j+(1<<(i-1))];
       if(RMQ[a]<RMQ[b]) best[i][j]=a;
       else best[i][j]=b;
     }
     return;
}
int askRMQ(int a,int b)
{
    int t;
    t=mm[b-a+1];b-=(1<<t)-1;
    a=best[t][a];b=best[t][b];
    return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
    int t;
    a=rank[a];b=rank[b];
    if(a>b) {t=a;a=b;b=t;}
    return(height[askRMQ(a+1,b)]);
}