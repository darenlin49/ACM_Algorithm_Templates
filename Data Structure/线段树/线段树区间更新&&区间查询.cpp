const int N=100005;				//������

int M;
__int64 sum[N*4];					//M*2���������M��ӽ�2*N������N=1023[1,1023]����M=2048---zkw��ͳ�Ƶ�������
__int64 add[N*4];

void PushUp(int rt) 			//ͳ�ƻ��ܣ�rtΪ��ǰ�ڵ�
{
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];	//�����������ֵ�� sum[n]=max(sum[n*2],sum[n*2+1])
}

void BuildTree(int n)
{
    mem(sum, 0);
	mem(add, 0);
}

void PushDown(int rt,int l)		//����·ţ�rtΪ��ǰ�ڵ㣬lΪ�޸����䳤��
{
    if (add[rt])
    {
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        sum[rt<<1]+=add[rt]*(l-(l>>1));
        sum[rt<<1|1]+=add[rt]*(l>>1);
        add[rt]=0;
    }
}

void Update(int s,int t,int v,int l,int r,int rt)
{
    if (s<=l && r<=t)
    {
        add[rt]+=v;
        sum[rt]+=v*(r-l+1);
        return ;
    }
    PushDown(rt,r-l+1);
    int m=(l+r)>>1;
    if (s<=m)   Update(s,t,v,l,m,rt<<1);
    if (m<t)    Update(s,t,v,m+1,r,rt<<1|1);
    PushUp(rt);
}

__int64 Query(int s,int t,int l,int r,int rt)
{
    if (s<=l && r<=t)
        return sum[rt];
    PushDown(rt,r-l+1);
    __int64 ans=0;
    int m=(l+r)>>1;
    if (s<=m)   ans+=Query(s,t,l,m,rt<<1);
    if (m<t)    ans+=Query(s,t,m+1,r,rt<<1|1);
    return ans;
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    BuildTree(n);
    for (int i=0;i<q;i++)
    {
        char c;
        int a,b,d;
        scanf("%*c%c",&c);
        if (c=='Q')
        {
            scanf("%d%d",&a,&b);
            printf("%I64d\n",Query(a,b,1,M,1));
        }
        else
        {
            scanf("%d%d%d",&a,&b,&d);
            Update(a,b,d,1,M,1);
        }
    }
    return 0;
}
