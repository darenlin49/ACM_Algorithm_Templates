/*
	POJ 1523 ���⣺�������Լ���ȥ�������ͨ����������(��������˵�˫��ͨ����(��))
	[����]��ͼ�����������������DFS(u)Ϊu�������������¼��Ϊ�����б��������Ĵ���š�����Low(u)Ϊu��u����������ͨ���Ǹ��ӱ�׷�ݵ�������Ľڵ㣬��DFS�����С�Ľڵ㡣���ݶ��壬���У�Low(u)=Min {DFS(u),DFS(v)|(u,v)Ϊ�����(�ȼ���DFS(v)<DFS(u)��v��Ϊu�ĸ��׽ڵ�),Low(v)|(u,v)Ϊ��֦��}
	
	[����]һ������u�Ǹ�㣬���ҽ�������(1) uΪ��������u�ж���һ����������(2) u��Ϊ���������������(u,v)Ϊ��֦��(��uΪv���������еĸ���)��ʹ��DFS(u)<=Low(v)��
	[��ȥĳ����������ͨ������]������(1)�ĸ�㣬����Ϊ������������(2)��������������������v�ĸ���+1(���ĸ��׽ڵ�).
	[���˫��ͨ��֧]���ڵ�˫��ͨ��֧��ʵ����������Ĺ����о���˳���ÿ����˫��ͨ��֧���������һ��ջ���洢��ǰ˫��ͨ��֧��������ͼʱ��ÿ�ҵ�һ����֦�߻����ߣ��Ͱ������߼���ջ�С��������ĳʱ����DFS(u)<=Low(v)��˵��u��һ����㣬ͬʱ�ѱߴ�ջ��һ����ȡ����ֱ�������˱�(u,v)��ȡ������Щ����������ĵ㣬���һ����˫��ͨ��֧�����������ڶ����˫��ͨ��֧��������ÿ����ֻ����������һ����˫��ͨ��֧��
	
	[ע]�ر߶�����͵�˫��ͨ����û��Ӱ��.
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

int id, dfn[MAXV], low[MAXV];       //ʱ���
int bcc_num;                        //��˫��ͨ��������
vector <int> bcc[MAXV];             //��Ϊ���������ڶ��˫��ͨ����������������洢ÿ��˫��ͨ�����Ľڵ�������ñ�������ʾÿ���ڵ�������˫��ͨ����
stack <int> st;                     //ջ�д�����֦�߻�����
int res[MAXV];                      //������ӵ�˫��ͨ����������res[i]>1ʱiΪ���.
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
        if (dfn[v] < dfn[u]){   //���˫��ͨ����ʱ������ջ����������
            st.push(i);
            if (!dfn[v]){       //��֦��
                child ++;       //ע������ͳ�ƶ��ӽڵ�ʱ��Ҫд��if����
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (dfn[u] <= low[v]){
                    bcc_num ++;
                    res[u] ++;              //�������ڵ����ӵ�˫��ͨ��������
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
            else{               //�����
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    //ͳ�Ƹ�����ӵ�˫��ͨ����������res[]>1��Ϊ���~
    if (father == 0){
        if (child >= 2){        //��������һ���������Ǹ��
            res[u] = child;
        }
        else
            res[u] = 0;
    }
    else if (res[u] > 0)        //�������ڵ�𰸻�Ҫ+1(���׽ڵ�)
        res[u] ++;
}
void solve(){
    id = bcc_num = 0;
    mem(dfn, 0);
    mem(low, 0);
    mem(res, 0);
    while(!st.empty())
        st.pop();
    tarjan(1, 0);				//����������Ĭ��ͼ����ͨ�ģ�������Ҫ����ÿ����
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
		//���˫��ͨ����		
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