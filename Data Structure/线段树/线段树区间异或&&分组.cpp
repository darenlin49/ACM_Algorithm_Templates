/*
CodeForces Round #149 E XOR on Segment ��(�������&&�����߶���)

��Ŀ���⣺����a��n������ʵ����������������[l,r]����͡����ڶ�ĳ������[l,r]���������һ����x��

˼·���Ƚ������뵽�����߶�������Ϊÿ������С��10^6�����԰�ÿһλ���20λ���棬��������20���߶�������ô�����ת��Ϊ����01������⣺0����κ������䣬�����޸ģ�1���һ����x�����1-x��������ϸ��⻹�ǿ�����ɡ���

*/

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#define MID(l,r)    (l + r)/2
using namespace std;

const int N = 100010;
long long sum[22][N<<2],cnt[N<<2],ans[22];

void pushup(int rt){
    for (int i = 0; i < 20; i ++){
        sum[i][rt] = sum[i][rt<<1] + sum[i][rt<<1|1];
    }
}
void pushdown(int rt,int w){
    if (cnt[rt]){
        cnt[rt<<1] ^= cnt[rt];
        cnt[rt<<1|1] ^= cnt[rt];
        for (int i = 0; i < 20; i ++){
            if (cnt[rt] >> i & 1){
                sum[i][rt<<1] = w - (w >> 1) - sum[i][rt<<1];
                sum[i][rt<<1|1] = (w >> 1) - sum[i][rt<<1|1];
            }
        }
        cnt[rt] = 0;
    }
}
void build(int l,int r,int rt){
    if (l == r){
        long long x;
        cin>>x;
        for (int i = 0; i < 20; i ++){
            sum[i][rt] = x >> i & 1;
        }
        return ;
    }
    int mid = MID(l,r);
    build(l,mid,rt<<1);
    build(mid+1,r,rt<<1|1);
    pushup(rt);
    return ;
}

void update(int s,int t,int c,int l,int r,int rt){
    if (s <= l && r <= t){
        cnt[rt] ^= c;
        for (int i = 0; i < 20; i ++){
            if (c >> i & 1){
                sum[i][rt] = r - l + 1 - sum[i][rt];
            }
        }
        return ;
    }
    pushdown(rt,r-l+1);
    int mid = MID(l,r);
    if (s <= mid)   update(s,t,c,l,mid,rt<<1);
    if (mid < t)    update(s,t,c,mid+1,r,rt<<1|1);
    pushup(rt);
}

void query(int s,int t,int l,int r,int rt){
    if (s <= l && r <= t){
        for (int i = 0; i < 20; i ++){
            ans[i] += sum[i][rt];
        }
        return ;
    }
    pushdown(rt,r-l+1);
    int mid = MID(l,r);
    if (s <= mid)   query(s,t,l,mid,rt<<1);
    if (mid < t)    query(s,t,mid+1,r,rt<<1|1);
}

long long getquery(int s,int t,int l,int r){
    memset(ans,0,sizeof(ans));
    query(s,t,l,r,1);
    long long res = 0;
    for (int i = 0; i < 20; i ++){
        res += (1LL << i) * ans[i];
    }
    return res;
}
int main(){
    int n;
    scanf("%d",&n);
    memset(sum,0,sizeof(sum));
    memset(cnt,0,sizeof(cnt));
    build(1,n,1);
    int q;
    scanf("%d",&q);
    for (int i = 0; i < q; i ++){
        int w;
        scanf("%d",&w);
        if (w == 1){
            int a,b;
            cin>>a>>b;
            cout<<getquery(a,b,1,n)<<endl;
        }
        else{
            int a,b,c;
            cin>>a>>b>>c;
            update(a,b,c,1,n,1);
        }
    }
    return 0;
}

