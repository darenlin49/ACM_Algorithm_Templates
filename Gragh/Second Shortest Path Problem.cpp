/*
二维Dijkstra求次短路(k很小时的k短路也适用)：

我们知道Dijkstra就是不断地用已经确定最短路的节点(黑色)去松弛未确定的点(白色)，用数学归纳法很容易证明这是正确的。它的核心思想就是某个节点的最短路一定是由它前驱节点的最短路扩展来的。那么对于次短路也可以类似的看：一个节点的次短路一定是由它前驱节点的最短路 or 次短路扩展而来的。那么我们就可以把节点分成两层处理：一层处理、存储最短路，另一层处理、存储次短路。这样, 用于记录状态的数组变成了二维, 放进堆中的状态也必须是"二维"的, 这里的"二维"并不是要你开个二维数组, 而是需要在放入堆中的结构体里多加一个标记变量, 用于标识到底是最短路还是次短路, 当然, 用于标记已经确定最短路、次短路的点的closed表同样要变成二维的。循环结束条件是堆为空, 因为要计数, 就必须遍历所有情况.

具体在做状态转移的时候, 拿到当前状态, 扩展下一状态, 设当前状态长度为d, 下一状态最短路和次短路状态分别是d0和d1, 则:

d小于d0, 则d1=d0,d0=d, 计数都重置为所赋的值对应的计数.
d等于d0, 则累加最短路计数.
d小于d1, 则d1=d, 重置次短路计数为所赋的值对应的计数.
d等于d1, 则累加次短路计数.
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