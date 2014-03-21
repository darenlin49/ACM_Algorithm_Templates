/**
	���������㷨��
	����·(����·)����P��ͼG��һ����ͨ����δƥ�䶥���·������������M�ıߺͲ�����M�ı�(����ƥ��ʹ�ƥ��ı�)��P�Ͻ�����֣����PΪ�����M��һ������·������MΪһ��ƥ�䣩
	�㷨���̣�	(1)��MΪ��
����			(2)�ҳ�һ������·��P��ͨ����������ȥͬ���죩�޸�ƥ���ø����ƥ��M������M
����			(3)�ظ�(2)����ֱ���Ҳ�������·��Ϊֹ
	ʱ�临�Ӷȣ�O(VE)
	�ռ临�Ӷȣ�O(E)
**/

/** д��һ:	����д��,������������X�㼯,����ȷX\Y�㼯 **/
const int MAXV = 405;                   		//N1+N2
struct MatchingOfBipartiteGraph{
    int vn1, vn2;
	bool T[MAXV];
    int left[MAXV];                      		//Y��ƥ����Ӧ��X����
    vector <int> adj[MAXV];
    void init(int n1, int n2){          		//X��Y�㼯����
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

/** д���������ã�:	������㲻������X\Y�㼯 **/
const int MAXV = 2005;                   							//|V1|+|V2|
struct MaximumMatchingOfBipartiteGraph{
    int vn;
	vector <int> adj[MAXV];
    void init(int n){                   							//����ͼ���㼯��ĸ���
        vn = n;
        for (int i = 0; i <= vn; i ++)     adj[i].clear();
    }
    void add_uedge(int u, int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
    }
    bool vis[MAXV];
    int mat[MAXV];                      							//��¼��ƥ���Ķ�Ӧ��
    bool cross_path(int u){
        for (int i = 0; i < (int)adj[u].size(); i ++){
            int v = adj[u][i];
            if (!vis[v]){
                vis[v] = true;
                if (mat[v] == 0 || cross_path(mat[v])){				//����û������XY�㼯��һ���Ǵ�X�㼯��ʼ����
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
                /** һ��Ҫע��n1����1~n1��n2��Ҫ�ѱ��ת��Ϊn1+1~n1+n2**/
            }
        }
        printf("%d\n", match.hungary());
    }
	return 0;
}