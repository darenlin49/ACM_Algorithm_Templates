int gcd(int a, int b){
    return b ? gcd(b, a%b) : a;
}
int lcm(int a, int b){
    return a / gcd(a,b) * b;
}

/* ------- ��˹��Ԫ�����������Է�����(���������Է�����������ƣ�����Ҫ���ж��Ƿ�Ϊ0ʱ������EPS���������������⡣) ------------ */
//O(N^3)
//���巽�̽ṹ��EQU
//����gauss()��Ϊ��˹��Ԫ�����̡�	return 0��ʾ��Ψһ�⣬����������x[]�У� return -2��ʾ��ʵ���⵫�������⡣

const int MAX_EQU = 230;
typedef struct  equation_set{
    int equ, var;               	//���̸�������Ԫ�����������������equ�С�var+1��.
    int mat[MAX_EQU][MAX_EQU+1];  	//�������
    int x[MAX_EQU];            	 	//���̽�����
    bool free_x[MAX_EQU];       	//�ж��Ƿ��ǲ�ȷ����Ԫ

    void init(int in_equ, int in_var);
    void debug();
    int gauss();
}EQU;
void equation_set::init(int in_equ, int in_var){
    equ = in_equ;
	var = in_var;
    memset(mat, 0, sizeof(mat));
    memset(x, 0, sizeof(x));
    memset(free_x, 1, sizeof(free_x));
}
void equation_set::debug(){
    for (int i = 0; i < equ; i ++){
        for (int j = 0; j < var; j ++)
            cout << mat[i][j] << " ";
        cout << mat[i][var] << endl;
    }
}
int equation_set::gauss(){
    int row = 0, col = 0; 
    int max_row;
    while (row < equ && col < var){
        max_row = row;
        for (int i = row + 1; i < equ; i ++)
            if (abs(mat[i][col]) > abs(mat[max_row][col]))
                max_row = i;
        if (max_row != row){
            for (int j = 0; j <= var; j ++){
                int tmp = mat[row][j];
                mat[row][j] = mat[max_row][j];
                mat[max_row][j] = tmp;
            }
        }
        if (mat[row][col] == 0){
            col ++;
            continue;
        }
		//��ͨ�������н��ݻ�:
        for (int i = row + 1; i < equ; i ++){
            if (mat[i][col] != 0){
                int LCM = lcm(abs(mat[i][col]), abs(mat[row][col]));
                int ta = LCM  / abs(mat[i][col]), tb = LCM / abs(mat[row][col]);
                if (mat[i][col] * mat[row][col] < 0)    tb = -tb;
                for (int j = col; j <= var; j ++)
                    mat[i][j] = mat[i][j] * ta - mat[row][j] * tb;
            }
        }

        row++, col++;
    }
    //debug();

    //1. �޽�
    for (int i = row; i < equ; i++){
        if (mat[i][col] != 0) return -1;
    }
    //2.�����(����ֻ�Ǽ������ȷ����Ԫ�����ڶ��ļ��㣬��Ҫö�����ɱ�Ԫ��״̬���������������.)
    if (row < var){
		//����ȷ����Ԫ���������Ŀ����Ҫ
        int free_x_num = 0;
        int free_index;
        for (int i = row - 1; i >= 0; i --){
            for (int j = i; j < var; j ++)
                if (mat[i][j] != 0 && free_x[j])    free_x_num ++, free_index = j;
            if (free_x_num > 1) continue;
            int tmp = mat[i][var];
            for (int j = 0; j < var; j ++)
                if (free_index != j)    tmp -= mat[i][j] * x[j];
            if (tmp % mat[i][free_index] != 0)  return -2;  //�������⣬����Ŀ��û����Ҫ�ɡ�
            x[free_index] = tmp / mat[i][free_index];
            free_x[free_index] = 0;     					//������ȷ����Ԫ
        }
        return var - row;
    }
    //3.Ψһ��
    for (int i = row - 1; i >= 0; i --){
        int tmp = mat[i][var];
        for (int j = var - 1; j > i; j --)
            tmp -= x[j] * mat[i][j];
        x[i] = tmp / mat[i][i];
    }
    return 0;
}







/* ---------------------------------- ��˹��Ԫ����򷽳���+ö������Ԫ��� --- POJ 3185 ----------------------------------- */

#define MAX 25
typedef struct equation_set{
    int equ, var;
    int a[MAX][MAX];
    int x[MAX];

    void init(){
        equ = var = 20;
        memset(a, 0, sizeof(a));
        memset(x, 0, sizeof(x));
        for (int i = 0; i < 20; i ++){
            a[i][i] = 1;
            if (i > 0)
                a[i-1][i] = 1;
            if (i < 19)
                a[i+1][i] = 1;
        }
        return ;
    }
    void debug();
    int gauss();
    int dfs(int n, int row);
}EQU;
void EQU::debug(){
    for (int i = 0; i < 20; i ++){
        for (int j = 0; j < 20; j ++)
            cout << a[i][j] << " ";
        cout << a[i][20] << endl;
    }
}

//dfsö������Ԫ��������н�
int EQU::dfs(int n, int row){
    if (n == var){
        for (int i = row - 1; i >= 0; i --){
            int tmp = a[i][var];
            for (int j = i + 1; j < var; j ++)
                tmp ^= (a[i][j] && x[j]);
            x[i] = tmp;
        }
        int ans = 0;
        for (int i = 0; i < var; i ++)
            if (x[i])   ans ++;
        return ans;
    }
    x[n] = 0;
    int p1 = dfs(n+1, row);
    x[n] = 1;
    int p2 = dfs(n+1, row);
    return min(p1, p2);
}
int EQU::gauss(){
    int row = 0, col = 0;
    while(row < equ && col < var){
        int max_row = row;
        for (int i = row + 1; i < equ; i ++)
            if (a[i][col] > a[row][col])    max_row = i;
        if (max_row != row){
            for (int j = 0; j <= var; j ++){
                int tmp = a[row][j];
                a[row][j] = a[max_row][j];
                a[max_row][j] = tmp;
            }
        }
        if (a[row][col] == 0){
            col ++;
            continue;
        }

        for (int i = row + 1; i < equ; i ++){
            if (a[i][col]){
                for (int j = col; j <= var; j ++)
                    a[i][j] = a[i][j] ^ a[row][j];
            }
        }

        row ++, col ++;
    }
    //debug();
	
	//�޽�
    for (int i = row; i < equ; i ++)
        if (a[i][col])
            return -1;

	//��⣬dfsö������Ԫ
    if (row < var){
        return dfs(row, row);
    }
	
	//Ψһ��
    for (int i = col - 1; i >= 0; i --){
        int tmp = a[i][var];
        for (int j = i+1; j < var; j ++)
            tmp ^= (a[i][j] && x[j]);
        x[i] = tmp;
    }

    int ans = 0;
    for (int i = 0; i < var; i ++)
        if (x[i])   ans ++;
    return ans;
}
int main(){
    EQU E;
    E.init();
    for (int i = 0; i < 20; i ++)
        cin >> E.a[i][20];
    //E.debug();
    cout << E.gauss() << endl;
	return 0;
}