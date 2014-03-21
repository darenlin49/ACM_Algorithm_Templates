/**
	【AC Automation模板  2013.10.10】
	一个比较好的方法是稍微修改一下next的定义。原来next[i][j]表示字典树中i节点的字符为j的儿子节点编号。现在拓展一下。如果i节点没有字符为j的儿子，那么next[i][j]就是i节点沿着失败指针一直走到有字符为j的儿子的节点编号，如果没有，那么就指向根。
	相当于是一个路径压缩的思想吧。这样一来，建立完自动机后，next指针就是很直接的转移关系了，不需要再特意的沿着失败指针跑啊跑的。这种写法实现起来和用起来都很方便。
*/
const int KeyWordSize = 26;
const int PatternNum = 10002;
const int PatternMaxLength = 50;

struct AC_Automation{
    int next[PatternMaxLength*PatternNum][KeyWordSize], fail[PatternMaxLength*PatternNum];       // goto函数和失败指针
    int val[PatternMaxLength*PatternNum];        // 记录题目给的关键数据
    queue <int> Q;              // bfs建AC自动机时用
    int cnt, root;              // 当前Trie节点个数、根节点
    int newnode(){
        memset(next[cnt], -1, sizeof(next[cnt]));
        val[cnt] = 0;
        return cnt ++;
    }
    // 重新建树需先Reset
    void reset(){
        cnt = 0;
        root = newnode();
    }
	//字符译码
    int getch(char c){
        return c-'a';
    }
    // 将权值为key的字符串a插入到Trie中
    void insert(char *s, int value){
        int len = strlen(s);
        int now = root;
        for (int i = 0; i < len; i ++){
            if (next[now][getch(s[i])] == -1){
                next[now][getch(s[i])] = newnode();
            }
            now = next[now][getch(s[i])];
        }
        val[now] += value;
    }
    // 建立AC自动机,确定每个节点的权值以及状态转移
    void build(){
        CLEAR(Q);
        fail[root] = root;
        for (int i = 0; i < KeyWordSize; i ++){
            if (next[root][i] == -1){
                next[root][i] = root;
            }
            else{
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }
        while(!Q.empty()){
            int r = Q.front();
            Q.pop();
            for (int i = 0; i < KeyWordSize; i ++){
                if (next[r][i] == -1){
                    next[r][i] = next[fail[r]][i];
                    //拓展next：
                    //如果i节点没有字符为j的儿子，next[i][j]就是i节点沿着失败指针一直走到有字符为j的儿子的节点编号，
                    //如果没有，那么就指向根
                }
                else{
                    int u = next[r][i], v = fail[r];
                    Q.push(u);
                    //扩展next后就可以直接转移了
                    fail[u] = next[v][i];
                    //以下代码根据题目val的含义写,合并到达该状态能识别的所有模式串使得询问时不需要沿失败指针回溯所有后缀情况
					//需要回溯所有情况时就不写了
                    val[u] += val[fail[u]];
                }
            }
        }
    }
    // 解题,具体题目设计,下面的写法是基本的询问匹配
    int query(char *str){
        int now = root;
        int len = strlen(str);
        int res = 0;
        for (int i = 0; i < len; i ++){
            now = next[now][getch(s[i])];
            res += val[now];
        }
        return res;
    }
}AC;

char s[1000003];
int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	int t;
	scanf("%d", &t);
	while(t --){
        int n;
        scanf("%d", &n);
        AC.reset();
        char tmps[55];
        for (int i = 0; i < n; i ++){
            scanf("%s", tmps);
            AC.insert(tmps, 1);
        }
        AC.build();
        scanf("%s", s);
        printf("%d\n", AC.query(s));
	}
	return 0;
}
