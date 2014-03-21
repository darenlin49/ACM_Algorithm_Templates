/*
	[2-SAT]给定N个组（每个组2个元素）、M个约数关系，每组里挑1个使得选出的N个元素符合满足所有约束.
	[分析]解决这类问题的关键还是在于建模，基本建模就是对于每一个约束关系，构图时连一条i->j的边，表示如果选i则必须选j.(不同约束关系需要连得边不同,下面POJ 3678列出了常用的约束关系的建边方法)
	[2-SAT判定]对原图求一次强连通分量，然后看每组中的两个点是否属于同一个强连通分量，如果存在这种情况，那么无解。

	[POJ 3678] N个布尔变量，M个AND\OR\XOR约束关系，判断是否能确定这N个变量的值使得其满足所有约束条件.
	[分析]标准的2-sta问题，每种约束关系连的边：
		AND 结果为1：建边 ~x->x,~y->y 				（两个数必须全为1）
		AND 结果为0：建边 y->~x,x->~y 				（两个数至少有一个为0）
		OR  结果为1：建边 ~x->y,~y->x 				（两个数至少有一个为1）
		OR  结果为0：建边 x->~x,y->~y 				（两个数必须全为0）
		XOR 结果为1：建边 x->~y,y->~x,~y->x,~x->y 	（两个数必须不同）
		XOR 结果为0：建边 x->y,y->x,~x->~y,~y->~x 	（两个数必须相同）
		(某个布尔值必须为1或者说某个元素必须选，则连一条~x -> x的边)
		(某个布尔值必须为0或者说某个元素必须不选，则连一条x -> ~x的边)
	然后就是2-sat判定了
*/

const int MAXN = 2005;
const int MAXE = MAXN * MAXN;
struct node{
    int u, v;
    int next;
}arc[MAXE];
int cnt, head[MAXN];
void init(){
    cnt = 0;
    mem(head, -1);
    return ;
}
void insert(int u, int v){
    arc[cnt].u = u;
    arc[cnt].v = v;
    arc[cnt].next = head[u];
    head[u] = cnt ++;
}
/* ---- Tarjan ---- */
int scc_num, scc[MAXN];
int dfn[MAXN], low[MAXN], id;
stack <int> st;
bool vis[MAXN], instack[MAXN];
void dfs(int u){
    vis[u] = instack[u] = 1;
    st.push(u);
    dfn[u] = low[u] = ++ id;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (!vis[v]){
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]){
        ++ scc_num;
        while(st.top() != u){
            scc[st.top()] = scc_num;
            instack[st.top()] = 0;
            st.pop();
        }
        scc[st.top()] = scc_num;
		instack[st.top()] = 0;
        st.pop();
    }
    return ;
}
void tarjan(int n){
	mem(vis, 0);
    mem(instack, 0);
    mem(dfn, 0);
    mem(low, 0);
    mem(scc, 0);
    id = scc_num = 0;
    while(!st.empty())
        st.pop();

    for (int i = 1; i <= n; i ++){   //枚举节点
        if (!vis[i])
            dfs(i);
    }
    return ;
}
/* ---- Tarjan ---- */
int opp[MAXN];                  //与i同组的标号i', 默认设为i+N;
void set_opp(int N){            //设定同组标号.
    for (int i = 1; i <= N; i ++)
        opp[i] = i + N;
    return ;
}
//根据y约束向构图中加边,N表示组数.
//(通常一组表示一个布尔变量的0\1值, 但也有题目表示的是一组互斥约束的布尔值)
void add_clause(int N, int m){
    init();
    set_opp(N);
    for (int i = 0; i < m; i ++){
        int a, b, c;
        char str[10];
        scanf("%d %d %d %s", &a, &b, &c, str);
        a ++, b ++;
        if (str[0] == 'A'){
            if (c == 0){
                insert(a, opp[b]);
                insert(b, opp[a]);
            }
            else{
                insert(opp[a], a);
                insert(opp[b], b);
            }
        }
        else if (str[0] == 'O'){
            if (c == 0){
                insert(a, opp[a]);
                insert(b, opp[b]);
            }
            else{
                insert(opp[a], b);
                insert(opp[b], a);
            }
        }
        else{
            if (c == 0){
                insert(a, b);
                insert(b, a);
                insert(opp[a], opp[b]);
                insert(opp[b], opp[a]);
            }
            else{
                insert(a, opp[b]);
                insert(opp[a], b);
                insert(b, opp[a]);
                insert(opp[b], a);
            }
        }
    }
    return ;
}
bool check(int N){              //2-SAT判定.N表示组数.opp[i]表示与i同互斥组的另一个点
    tarjan(2*N);
    for (int i = 1; i <= 2*N; i ++){
        if (scc[i] == scc[opp[i]]){
            return false;
        }
    }
    return true;
}
/* ------------------------------ 2-SAT -------------------------- */

int main(){
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        add_clause(n, m);
        if (check(n)){
            puts("YES");
        }
        else{
            puts("NO");
        }
    }
	return 0;
}