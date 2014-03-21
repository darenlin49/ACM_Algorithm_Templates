/*
	POJ 1523 题意：求出割点以及除去割点后的连通分量的数量(附带求出了点双连通分量(块))
	[求割点]对图深度优先搜索，定义DFS(u)为u在搜索树（以下简称为树）中被遍历到的次序号。定义Low(u)为u或u的子树中能通过非父子边追溯到的最早的节点，即DFS序号最小的节点。根据定义，则有：Low(u)=Min {DFS(u),DFS(v)|(u,v)为后向边(等价于DFS(v)<DFS(u)且v不为u的父亲节点),Low(v)|(u,v)为树枝边}
	
	[条件]一个顶点u是割点，当且仅当满足(1) u为树根，且u有多于一个子树。或(2) u不为树根，且满足存在(u,v)为树枝边(即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v)。
	[除去某点后产生的连通分量数]：对于(1)的割点，数量为子树的数量；(2)的数量就是满足条件的v的个数+1(它的父亲节点).
	[求点双连通分支]对于点双连通分支，实际上在求割点的过程中就能顺便把每个点双连通分支求出。建立一个栈，存储当前双连通分支，在搜索图时，每找到一条树枝边或后向边，就把这条边加入栈中。如果遇到某时满足DFS(u)<=Low(v)，说明u是一个割点，同时把边从栈顶一个个取出，直到遇到了边(u,v)，取出的这些边与其关联的点，组成一个点双连通分支。割点可以属于多个点双连通分支，其余点和每条边只属于且属于一个点双连通分支。
	
	[注]重边对求割点和点双连通分量没有影响.
*/
const int MAXE = 1000005;
const int MAXV = 1005;
struct node{
    int u, v;
    int next;
}arc[MAXE];
int cnt, head[MAXV];
void init(){
    cnt = 0;
    mem(head, -1);
}
void add(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    head[u] = cnt++;
    arc[cnt].u = v;
    arc[cnt].v = u;
    arc[cnt].next = head[v];
    head[v] = cnt++;
    return ;
}

int id, dfn[MAXV], low[MAXV];       //时间戳
int bcc_num;                        //点双联通分量个数
vector <int> bcc[MAXV];             //因为割点可以属于多个双联通分量，所以用数组存储每个双联通分量的节点而不是用标号数组表示每个节点所属的双联通分量
stack <int> st;                     //栈中存着树枝边或后向边
int res[MAXV];                      //割点连接的双联通分量个数，res[i]>1时i为割点.
void addbcc(int bcc_num, int u){
    for (int i = 0; i < (int)bcc[bcc_num].size(); i ++){
        if (bcc[bcc_num][i] == u)
            return ;
    }
    bcc[bcc_num].push_back(u);
}
void tarjan(int u, int father){
    dfn[u] = low[u] = ++id;
    int child = 0;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (v == father)    continue;
        if (dfn[v] < dfn[u]){   //求点双连通分量时避免向栈中添加正向边
            st.push(i);
            if (!dfn[v]){       //树枝边
                child ++;       //注意这里统计儿子节点时不要写在if外面
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (dfn[u] <= low[v]){
                    bcc_num ++;
                    res[u] ++;              //非树根节点连接的双联通分量个数
                    while(!st.empty()){
                        int su = arc[st.top()].u;
                        int sv = arc[st.top()].v;
                        st.pop();
                        addbcc(bcc_num, su);
                        addbcc(bcc_num, sv);
                        if((su == u && sv == v) || (su == v && sv == u)){
                            break;
                        }
                    }
                }
            }
            else{               //后向边
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    //统计割点连接的双联通分量个数，res[]>1的为割点~
    if (father == 0){
        if (child >= 2){        //树根大于一个子树才是割点
            res[u] = child;
        }
        else
            res[u] = 0;
    }
    else if (res[u] > 0)        //非树根节点答案还要+1(父亲节点)
        res[u] ++;
}
void solve(){
    id = bcc_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(res, 0);
    while(!st.empty())
        st.pop();
    tarjan(1, 0);				//树根，这里默认图是连通的，否则需要遍历每个点
}
int main(){
    int u, v;
    int t = 0;
    while(scanf("%d", &u) == 1){
        init();
        ++ t;
        if (u == 0)
            break;
        if (t > 1)
            puts("");
        scanf("%d", &v);
        add(u, v);
        while(scanf("%d", &u) == 1){
            if (u == 0)
                break;
            scanf("%d", &v);
            add(u, v);
        }
        solve();
		//输出双联通分量		
//        for (int i = 1; i <= bcc_num; i ++){
//            for (int j = 0; j < (int)bcc[i].size(); j ++){
//                printf("%d ", bcc[i][j]);
//            }
//            puts("");
//        }
        bool flag = 0;
        printf("Network #%d\n", t);
        for (int i = 1; i <= MAXV; i ++){
            if (res[i] > 0){
                printf("  SPF node %d leaves %d subnets\n", i, res[i]);
                flag = 1;
            }
        }
        if (!flag){
            puts("  No SPF nodes");
        }
    }
	return 0;
}