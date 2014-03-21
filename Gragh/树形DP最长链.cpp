/**
	【HDU 4607】题意：N个城市形成一棵树，相邻城市之间的距离是1，问访问K个城市的最短路程是多少，共有M次询问(1 <= N, M <= 100000, 1 <= K <= N)。
**/
const int MAXN = 200005;
struct node{
    int u, v;
    int next;
}arc[MAXN];
int en, head[MAXN];
void init(){
    en = 0;
    mem(head, -1);
}
void insert(int u, int v){
    arc[en].u = u;
    arc[en].v = v;
    arc[en].next = head[u];
    head[u] = en ++;
}

/** DP最长链过程 **/
int dp[MAXN];
int maxlen;
bool vis[MAXN];
void dfs(int u){
    vis[u] = 1;
    int max1 = 0, max2 = 0;
    int num = 0;
    for (int i = head[u]; i != -1; i = arc[i].next){
        int v = arc[i].v;
        if (!vis[v]){
            num ++;
            dfs(v);
            if (dp[v] > max1){
                max2 = max1;
                max1 = dp[v];
            }
            else{
                if (dp[v] > max2){
                    max2 = dp[v];
                }
            }
        }
    }
    if (0 == num){
        dp[u] = 0;
    }
    else{
        if (num == 1)
            maxlen = max(maxlen, max1+1);
        else
            maxlen = max(maxlen, max1+max2+2);
        dp[u] = max1 + 1;
    }
    return ;
}
int main(){
    //freopen("test.in", "r", stdin);
    //freopen("test.out", "w", stdout);
    int t;
    scanf("%d", &t);
    while(t --){
        init();
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n - 1; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            insert(u, v);
            insert(v, u);
        }
		
		
		//DP找最长链
        mem(vis, 0);
        mem(dp, 0);
        maxlen = 0;
        dfs(1);
		
		
        for (int i = 0; i < m; i ++){
            int tmp;
            scanf("%d", &tmp);
            if (tmp - 1 <= maxlen){
                printf("%d\n", tmp - 1);
            }
            else{
                printf("%d\n", maxlen + 2*(tmp-1-maxlen));
            }
        }
    }
    return 0;
}