/*
	[2-SAT]����N���飨ÿ����2��Ԫ�أ���M��Լ����ϵ��ÿ������1��ʹ��ѡ����N��Ԫ�ط�����������Լ��.
	[����]�����������Ĺؼ��������ڽ�ģ��������ģ���Ƕ���ÿһ��Լ����ϵ����ͼʱ��һ��i->j�ıߣ���ʾ���ѡi�����ѡj.(��ͬԼ����ϵ��Ҫ���ñ߲�ͬ,����POJ 3678�г��˳��õ�Լ����ϵ�Ľ��߷���)
	[2-SAT�ж�]��ԭͼ��һ��ǿ��ͨ������Ȼ��ÿ���е��������Ƿ�����ͬһ��ǿ��ͨ������������������������ô�޽⡣

	[POJ 3678] N������������M��AND\OR\XORԼ����ϵ���ж��Ƿ���ȷ����N��������ֵʹ������������Լ������.
	[����]��׼��2-sta���⣬ÿ��Լ����ϵ���ıߣ�
		AND ���Ϊ1������ ~x->x,~y->y 				������������ȫΪ1��
		AND ���Ϊ0������ y->~x,x->~y 				��������������һ��Ϊ0��
		OR  ���Ϊ1������ ~x->y,~y->x 				��������������һ��Ϊ1��
		OR  ���Ϊ0������ x->~x,y->~y 				������������ȫΪ0��
		XOR ���Ϊ1������ x->~y,y->~x,~y->x,~x->y 	�����������벻ͬ��
		XOR ���Ϊ0������ x->y,y->x,~x->~y,~y->~x 	��������������ͬ��
		(ĳ������ֵ����Ϊ1����˵ĳ��Ԫ�ر���ѡ������һ��~x -> x�ı�)
		(ĳ������ֵ����Ϊ0����˵ĳ��Ԫ�ر��벻ѡ������һ��x -> ~x�ı�)
	Ȼ�����2-sat�ж���
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

    for (int i = 1; i <= n; i ++){   //ö�ٽڵ�
        if (!vis[i])
            dfs(i);
    }
    return ;
}
/* ---- Tarjan ---- */
int opp[MAXN];                  //��iͬ��ı��i', Ĭ����Ϊi+N;
void set_opp(int N){            //�趨ͬ����.
    for (int i = 1; i <= N; i ++)
        opp[i] = i + N;
    return ;
}
//����yԼ����ͼ�мӱ�,N��ʾ����.
//(ͨ��һ���ʾһ������������0\1ֵ, ��Ҳ����Ŀ��ʾ����һ�黥��Լ���Ĳ���ֵ)
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
bool check(int N){              //2-SAT�ж�.N��ʾ����.opp[i]��ʾ��iͬ���������һ����
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