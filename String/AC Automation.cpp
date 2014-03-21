/**
	��AC Automationģ��  2013.10.10��
	һ���ȽϺõķ�������΢�޸�һ��next�Ķ��塣ԭ��next[i][j]��ʾ�ֵ�����i�ڵ���ַ�Ϊj�Ķ��ӽڵ��š�������չһ�¡����i�ڵ�û���ַ�Ϊj�Ķ��ӣ���ônext[i][j]����i�ڵ�����ʧ��ָ��һֱ�ߵ����ַ�Ϊj�Ķ��ӵĽڵ��ţ����û�У���ô��ָ�����
	�൱����һ��·��ѹ����˼��ɡ�����һ�����������Զ�����nextָ����Ǻ�ֱ�ӵ�ת�ƹ�ϵ�ˣ�����Ҫ�����������ʧ��ָ���ܰ��ܵġ�����д��ʵ�����������������ܷ��㡣
*/
const int KeyWordSize = 26;
const int PatternNum = 10002;
const int PatternMaxLength = 50;

struct AC_Automation{
    int next[PatternMaxLength*PatternNum][KeyWordSize], fail[PatternMaxLength*PatternNum];       // goto������ʧ��ָ��
    int val[PatternMaxLength*PatternNum];        // ��¼��Ŀ���Ĺؼ�����
    queue <int> Q;              // bfs��AC�Զ���ʱ��
    int cnt, root;              // ��ǰTrie�ڵ���������ڵ�
    int newnode(){
        memset(next[cnt], -1, sizeof(next[cnt]));
        val[cnt] = 0;
        return cnt ++;
    }
    // ���½�������Reset
    void reset(){
        cnt = 0;
        root = newnode();
    }
	//�ַ�����
    int getch(char c){
        return c-'a';
    }
    // ��ȨֵΪkey���ַ���a���뵽Trie��
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
    // ����AC�Զ���,ȷ��ÿ���ڵ��Ȩֵ�Լ�״̬ת��
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
                    //��չnext��
                    //���i�ڵ�û���ַ�Ϊj�Ķ��ӣ�next[i][j]����i�ڵ�����ʧ��ָ��һֱ�ߵ����ַ�Ϊj�Ķ��ӵĽڵ��ţ�
                    //���û�У���ô��ָ���
                }
                else{
                    int u = next[r][i], v = fail[r];
                    Q.push(u);
                    //��չnext��Ϳ���ֱ��ת����
                    fail[u] = next[v][i];
                    //���´��������Ŀval�ĺ���д,�ϲ������״̬��ʶ�������ģʽ��ʹ��ѯ��ʱ����Ҫ��ʧ��ָ��������к�׺���
					//��Ҫ�����������ʱ�Ͳ�д��
                    val[u] += val[fail[u]];
                }
            }
        }
    }
    // ����,������Ŀ���,�����д���ǻ�����ѯ��ƥ��
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
