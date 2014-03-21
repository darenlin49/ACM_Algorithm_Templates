/*
HDU 4288 Coder ★(2012 ACM/ICPC Asia Regional Chengdu Online)

问题抽象：分组线段树求和。

思路:离线(离散化+排序)维护5颗线段树。sum[rt][5]的每棵树表示区间的数以该区间左端为起点mod 5的余数，cnt[rt]表示区间数的数目。一开始不知道怎么动态地维护插入、删除数据的位置的模5的余数，比如一开始插入1、3、5，5是要求的，但要是再插入个2变成1、2、3、5，那么就变成3了。。。这个让我想了好久，后来经过一些提示终于想到了思路:每个叶节点的值都附在sum[rt][0]里，即上面说的，sum[rt][i]表示以该区间左端点为起点mod 5的余数。那么在向上统计汇总时怎么转化呢？

答案是：sum[结点][i]=sum[左儿子][i]+sum[右儿子][((i+5)-cnt[左儿子]%5)%5]。

什么意思呢？从sum的意义出发，左儿子的区间左端点和父节点是一样的，所以他们的余数等价；然而需要把右儿子的左端点与父节点等价起来。设父区间左端点为a，则右儿子区间左端点即为a+cnt[左儿子]。若右儿子(pos-a)%5==i，则把它放到父区间(pos-a-cnt[])%5== i-cnt[]%5== (保证大于等于0小于5) ((i+5)-cnt[]%5)%5。

另外要注意这里离散化的方法~~~lower_bound()函数可以很方便的找到数在原数组中的位置。（或者自己写一个二分也可以。。。）

*/
const int N=100005;
int M;
LL sum[N<<2][5];
int cnt[N<<2];

void BuildTree(int n){
    for (M=1;M<=n+2;M<<=1);
    for (int i=1;i<N<<2;i++){
        for (int j=0;j<5;j++)
            sum[i][j]=0;
        cnt[i]=0;
    }
} 
void PushUp(int rt){
    cnt[rt]=cnt[rt<<1]+cnt[rt<<1|1];
    for (int i=0;i<5;i++)
         sum[rt][i]=sum[rt<<1][i]+sum[rt<<1|1][((i+5)-cnt[rt<<1]%5)%5];
}

void Update(int s,int num,int v,int l,int r,int rt){
    if (l==s && r==s){
        sum[rt][0]+=v*num;
        cnt[rt]+=num;
        return;
    }
    int mid=MID(l,r);
    if (s<=mid) Update(s,num,v,l,mid,rt<<1);
    else Update(s,num,v,mid+1,r,rt<<1|1);
    PushUp(rt);
}

char str[100005][5];
int pri[100005];
int a[100005];

int main(){
    //freopen("test.in","r+",stdin);
    int n;
    while(scanf("%d",&n)!=EOF){
        int tot=0;
        for (int i=0;i<n;i++){
            scanf("%s",str[i]);
            if (str[i][0]!='s'){
                scanf("%d",&pri[i]);
                a[tot++]=pri[i];
            }
        }
        sort(a,a+tot);
        BuildTree(tot);
        for (int i=0;i<n;i++){
            if (str[i][0]=='a'){
                int x=pri[i];
                int pos=lower_bound(a,a+tot,x)-a+1;
                Update(pos,1,x,1,M,1);
            }
            else if (str[i][0]=='d'){
                int x=pri[i];
                int pos=lower_bound(a,a+tot,x)-a+1;
                Update(pos,-1,x,1,M,1);
            } 
            else{
                printf("%I64d\n",sum[1][2]);
            }
        }   
    }
    return 0;
}
