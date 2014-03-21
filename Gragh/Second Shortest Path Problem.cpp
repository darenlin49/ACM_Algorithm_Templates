/*
��άDijkstra��ζ�·(k��Сʱ��k��·Ҳ����)��

����֪��Dijkstra���ǲ��ϵ����Ѿ�ȷ�����·�Ľڵ�(��ɫ)ȥ�ɳ�δȷ���ĵ�(��ɫ)������ѧ���ɷ�������֤��������ȷ�ġ����ĺ���˼�����ĳ���ڵ�����·һ��������ǰ���ڵ�����·��չ���ġ���ô���ڴζ�·Ҳ�������ƵĿ���һ���ڵ�Ĵζ�·һ��������ǰ���ڵ�����· or �ζ�·��չ�����ġ���ô���ǾͿ��԰ѽڵ�ֳ����㴦��һ�㴦���洢���·����һ�㴦���洢�ζ�·������, ���ڼ�¼״̬���������˶�ά, �Ž����е�״̬Ҳ������"��ά"��, �����"��ά"������Ҫ�㿪����ά����, ������Ҫ�ڷ�����еĽṹ������һ����Ǳ���, ���ڱ�ʶ���������·���Ǵζ�·, ��Ȼ, ���ڱ���Ѿ�ȷ�����·���ζ�·�ĵ��closed��ͬ��Ҫ��ɶ�ά�ġ�ѭ�����������Ƕ�Ϊ��, ��ΪҪ����, �ͱ�������������.

��������״̬ת�Ƶ�ʱ��, �õ���ǰ״̬, ��չ��һ״̬, �赱ǰ״̬����Ϊd, ��һ״̬���·�ʹζ�·״̬�ֱ���d0��d1, ��:

dС��d0, ��d1=d0,d0=d, ����������Ϊ������ֵ��Ӧ�ļ���.
d����d0, ���ۼ����·����.
dС��d1, ��d1=d, ���ôζ�·����Ϊ������ֵ��Ӧ�ļ���.
d����d1, ���ۼӴζ�·����.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cstring>
#define MID(x,y) ((x+y)>>1)
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
 
typedef long long LL;
const int sup = (1 << 30);
const int inf = -0x7fffffff;
 
const int MAXV = 1003;
const int MAXE = 10003;
struct Status{
    int v;
    int dis;
    int type;
    friend bool operator < (Status n1, Status n2){
        return n2.dis < n1.dis;
    }
};
struct node{
    int u, v, w;
    int next;
}edge[MAXE];
int n, m;
int s, f;
int cnt, head[MAXV];
int dis[MAXV][2], ans[MAXV][2];
bool vis[MAXV][2];
void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt ++;
    return ;
}
void init(int n, int m){
    mem(head, -1);
    for (int i = 0; i <= n; i ++)
        dis[i][0] = dis[i][1] = sup;
    mem(ans, 0);
    mem(vis, 0);
    cnt = 0;
}
priority_queue <Status, vector<Status> > PQ;
void Dij(int s, int f){
    while(!PQ.empty())
        PQ.pop();
    Status tmp;
    dis[s][0] = 0;
    ans[s][0] = 1;
    tmp.v = s;
    tmp.type = 0;
    tmp.dis = 0;
    PQ.push(tmp);
    while(!PQ.empty()){
        Status t = PQ.top();
        PQ.pop();
        if (vis[t.v][t.type])   continue;
        vis[t.v][t.type] = 1;
        int u = t.v;
        int type = t.type;
        for (int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            int w = dis[u][type] + edge[i].w;
            if (dis[v][0] > w){
                dis[v][1] = dis[v][0];
                ans[v][1] = ans[v][0];
                Status t0;
                t0.dis = dis[v][1];
                t0.type = 1;
                t0.v = v;
                PQ.push(t0);
 
                dis[v][0] = w;
                ans[v][0] = ans[u][type];
                t0.dis = dis[v][0];
                t0.type = 0;
                t0.v = v;
                PQ.push(t0);
            }
            else if (dis[v][0] == w){
                ans[v][0] += ans[u][type];
            }
            else if (dis[v][1] > w){
                dis[v][1] = w;
                ans[v][1] = ans[u][type];
                Status t0;
                t0.dis = dis[v][1];
                t0.type = 1;
                t0.v = v;
                PQ.push(t0);
            }
            else if (dis[v][1] == w){
                ans[v][1] += ans[u][type];
            }
        }
    }
    int res = ans[f][0];
    if (dis[f][0] == dis[f][1] - 1)
        res += ans[f][1];
    printf("%d\n", res);
}
int main(){
    int te;
    scanf("%d", &te);
    while (te --){
        scanf("%d %d", &n, &m);
        init(n, m);
        while (m --){
            int a, b, l;
            scanf("%d %d %d", &a, &b, &l);
            add(a, b, l);
        }
        scanf("%d %d", &s, &f);
        Dij(s, f);
    }
	return 0;
}