/*
HDU 4288 Coder ��(2012 ACM/ICPC Asia Regional Chengdu Online)

������󣺷����߶�����͡�

˼·:����(��ɢ��+����)ά��5���߶�����sum[rt][5]��ÿ������ʾ��������Ը��������Ϊ���mod 5��������cnt[rt]��ʾ����������Ŀ��һ��ʼ��֪����ô��̬��ά�����롢ɾ�����ݵ�λ�õ�ģ5������������һ��ʼ����1��3��5��5��Ҫ��ģ���Ҫ���ٲ����2���1��2��3��5����ô�ͱ��3�ˡ���������������˺þã���������һЩ��ʾ�����뵽��˼·:ÿ��Ҷ�ڵ��ֵ������sum[rt][0]�������˵�ģ�sum[rt][i]��ʾ�Ը�������˵�Ϊ���mod 5����������ô������ͳ�ƻ���ʱ��ôת���أ�

���ǣ�sum[���][i]=sum[�����][i]+sum[�Ҷ���][((i+5)-cnt[�����]%5)%5]��

ʲô��˼�أ���sum���������������ӵ�������˵�͸��ڵ���һ���ģ��������ǵ������ȼۣ�Ȼ����Ҫ���Ҷ��ӵ���˵��븸�ڵ�ȼ��������踸������˵�Ϊa�����Ҷ���������˵㼴Ϊa+cnt[�����]�����Ҷ���(pos-a)%5==i��������ŵ�������(pos-a-cnt[])%5== i-cnt[]%5== (��֤���ڵ���0С��5) ((i+5)-cnt[]%5)%5��

����Ҫע��������ɢ���ķ���~~~lower_bound()�������Ժܷ�����ҵ�����ԭ�����е�λ�á��������Լ�дһ������Ҳ���ԡ�������

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
