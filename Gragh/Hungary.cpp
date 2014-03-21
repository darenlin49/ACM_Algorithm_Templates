/**
	【匈牙利算法】
	增广路(交错路)：若P是图G中一条连通两个未匹配顶点的路径，并且属于M的边和不属于M的边(即已匹配和待匹配的边)在P上交替出现，则称P为相对于M的一条增广路径。（M为一个匹配）
	算法过程：	(1)置M为空
　　			(2)找出一条增广路径P，通过异或操作（去同存异）修改匹配获得更大的匹配M’代替M
　　			(3)重复(2)操作直到找不出增广路径为止
	时间复杂度：O(VE)
	空间复杂度：O(E)
**/

/** 写法一:	大众写法,增广起点必须是X点集,需明确X\Y点集 **/
const int MAXV = 405;                   		//N1+N2
struct MatchingOfBipartiteGraph{
    int vn1, vn2;
	bool T[MAXV];
    int left[MAXV];                      		//Y集匹配点对应的X集点
    vector <int> adj[MAXV];
    void init(int n1, int n2){          		//X、Y点集个数
        vn1 = n1;
        vn2 = n2;
        for (int i = 0; i <= n1+n2; i ++)     adj[i].clear();
    }
    void add_uedge(int u, int v){
        adj[u].push_back(v);    adj[v].push_back(u);
    }
    bool cross_path(int u){
        for (int i = 0; i < (int)adj[u].size(); i ++){
            int v = adj[u][i];
            if (!T[v]){
                T[v] = true;
                if (left[v] == 0 || cross_path(left[v])){
                    left[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int hungary(){
        mem(left, 0);
        int match_num = 0;
        for (int i = 1; i <= vn1; i ++){
            mem(T, 0);
            if (cross_path(i)){
                match_num ++;
            }
        }
        return match_num;
    }
}match;

/** 写法二（常用）:	增广起点不用区分X\Y点集 **/
const int MAXV = 2005;                   							//|V1|+|V2|
struct MaximumMatchingOfBipartiteGraph{
    int vn;
	vector <int> adj[MAXV];
    void init(int n){                   							//二分图两点集点的个数
        vn = n;
        for (int i = 0; i <= vn; i ++)     adj[i].clear();
    }
    void add_uedge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
    }
    bool vis[MAXV];
    int mat[MAXV];                      							//记录已匹配点的对应点
    bool cross_path(int u){
        for (int i = 0; i < (int)adj[u].size(); i ++){
            int v = adj[u][i];
            if (!vis[v]){
                vis[v] = true;
                if (mat[v] == 0 || cross_path(mat[v])){				//这里没有区分XY点集，一般是从X点集开始增广
                    mat[v] = u;
                    mat[u] = v;
                    return true;
                }
            }
        }
        return false;
    }
    int hungary(){
        MEM(mat, 0);
        int match_num = 0;
        for (int i = 1; i <= vn; i ++){
            MEM(vis, 0);
            if (!mat[i] && cross_path(i)){
                match_num ++;
            }
        }
        return match_num;
    }
	void print_edge(){
        for (int i = 1; i <= vn; i ++){
            for (int j = 0; j < (int)adj[i].size(); j ++){
                printf("u = %d v = %d\n", i, adj[i][j]);
            }
        }
    }
}match;

int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        match.init(n+m);
        for (int i = 1; i <= n; i ++){
            int num;
            scanf("%d", &num);
            for (int j = 0; j < num; j ++){
                int tmp;
                scanf("%d", &tmp);
                match.add_uedge(i, n+tmp);
                /** 一定要注意n1点标号1~n1，n2点要把标号转换为n1+1~n1+n2**/
            }
        }
        printf("%d\n", match.hungary());
    }
	return 0;
}