/*
POJ 3660
��Ŀ���⣺��Nͷ��ţ�����ڸ�����������ͷţ֮�������ʤ�����M�飬Ҫ��ݴ�����ж���ͷ��ţ����������ȷ��������
����˼·������ĳ���˶��ԣ���������ɼ��õ�����lose�������ˣ��������ɼ������win�������ܣ������lose+win����������������һ�������Լ��������������Ϳ���ȷ���ˡ�����ֻ��ҪӦ��Floyd���ݹ�ϵ���������win��������lose���������ɣ�
*/

/* -------------------------------�󴫵ݱհ�ģ�岿��------------------------------- */

/* calculate Transitive Closure By Warshall */
const int N = 103;
int R[N][N];
int TC[N][N];
void Warshall_init(){
    mem(TC, 0);
}
void Warshall(int n){
    Warshall_init();
    //To copy the original matrix to the matrix that will be calculated.
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < n; j ++)
            TC[i][j] = R[i][j];

    for (int k = 0; k < n; k ++)
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++){
                if (TC[i][j])   continue;
                TC[i][j] = TC[i][k] && TC[k][j];
            }
}

/* -------------------------------�󴫵ݱհ�ģ�岿��------------------------------- */

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i ++){
        int a, b;
        scanf("%d %d", &a, &b);
        R[a-1][b-1] = 1;
    }
    Warshall(n);
    int ans = 0;
    for (int i = 0; i < n; i ++){
        int win = 0, fail = 0;
        for (int j = 0; j < n; j ++){
            if (TC[i][j])
                win ++;
            else if (TC[j][i])
                fail ++;
        }
        if (win + fail == n-1)
            ans ++;
    }
    printf("%d\n", ans);
	return 0;
}