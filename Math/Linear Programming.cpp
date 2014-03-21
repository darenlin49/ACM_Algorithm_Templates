/**
Simplex C(n+m)(n)
maximize:
    c[1]*x[1]+c[2]*x[2]+...+c[n]*x[n]+ans
subject to
    a[1,1]*x[1]+a[1,2]*x[2]+...a[1,n]*x[n] <= rhs[1]
    a[2,1]*x[1]+a[2,2]*x[2]+...a[2,n]*x[n] <= rhs[2]
    ......
    a[m,1]*x[1]+a[m,2]*x[2]+...a[m,n]*x[n] <= rhs[m]
����:
    ����ľ�������Ǳ�׼��ʽ��, ��Ŀ�꺯��Ҫ��󻯣�Լ������ʽ��Ϊ<= ��xiΪ�Ǹ���(>=0).
simplex���ز�����
	OPTIMAL		        ��Ψһ���Ž�
	UNBOUNDED	        ����ֵ�ޱ߽�
	FEASIBLE	        �п��н�
	INFEASIBLE		    �޽�
nΪԪ�ظ���,mΪԼ������
���Թ滮��	
	max c[]*x;
	a[][]<=rhs[];
ans��Ϊ���,x[]Ϊһ���(���Ž�or���н�)
**/

const double eps = 1e-8;
const double inf = 1e15;

#define OPTIMAL -1          //��ʾ��Ψһ�����Ż������н�
#define UNBOUNDED -2        //��ʾĿ�꺯�������ֵ�ޱ߽�
#define FEASIBLE -3         //��ʾ�п��н�
#define INFEASIBLE -4       //��ʾ�޽�
#define PIVOT_OK 1          //�������ɳ�
#define maxn 1000

struct LinearProgramming{
    int basic[maxn], row[maxn], col[maxn];
    double c0[maxn];

    double dcmp(double x){
        if (x > eps)    return 1;
        else if (x < -eps)   return -1;
        return 0;
    }
    void init(int n, int m, double c[], double a[maxn][maxn], double rhs[], double &ans) { //��ʼ��
        for(int i = 0; i <= n+m; i++) {
            for(int j = 0; j <= n+m; j++)   a[i][j]=0;
            basic[i]=0; row[i]=0; col[i]=0;
            c[i]=0; rhs[i]=0;
        }
        ans=0;
    }
    //ת�����
    int Pivot(int n, int m, double c[], double a[maxn][maxn], double rhs[], int &i, int &j){
        double min = inf;
        int k = -1;
        for (j = 0; j <= n; j ++)
            if (!basic[j] && dcmp(c[j]) > 0)
                if (k < 0 || dcmp(c[j] - c[k]) > 0)     k = j;
        j = k;
        if (k < 0)  return OPTIMAL;
        for (k = -1, i = 1; i <= m; i ++)   if (dcmp(a[i][j]) > 0)
            if (dcmp(rhs[i] / a[i][j] - min) < 0){  min = rhs[i]/a[i][j]; k = i;  }
        i = k;
        if (k < 0)  return UNBOUNDED;
        else    return PIVOT_OK;
    }
    int PhaseII(int n, int m, double c[], double a[maxn][maxn], double rhs[], double &ans, int PivotIndex){
        int i, j, k, l; double tmp;
        while(k = Pivot(n, m, c, a, rhs, i, j), k == PIVOT_OK || PivotIndex){
            if (PivotIndex){    i = PivotIndex; j = PivotIndex = 0; }
            basic[row[i]] = 0;  col[row[i]] = 0;    basic[j] = 1;   col[j] = i;     row[i] = j;
            tmp = a[i][j];
            for (k = 0; k <= n; k ++)   a[i][k] /= tmp;
            rhs[i] /= tmp;
            for (k = 1; k <= m; k ++)
                if (k != i && dcmp(a[k][j])){
                    tmp = -a[k][j];
                    for (l = 0; l <= n; l ++)   a[k][l] +=  tmp*a[i][l];
                    rhs[k] += tmp*rhs[i];
                }
            tmp = -c[j];
            for (l = 0; l <= n; l ++)   c[l] += a[i][l]*tmp;
            ans -= tmp * rhs[i];
        }
        return k;
    }
    int PhaseI(int n, int m, double c[], double a[maxn][maxn], double rhs[], double &ans){
        int i, j, k = -1;
        double tmp, min = 0, ans0 = 0;
        for (i = 1; i <= m; i ++)
            if (dcmp(rhs[i]-min) < 0){min = rhs[i]; k = i;}
        if (k < 0)  return FEASIBLE;
        for (i = 1; i <= m; i ++)   a[i][0] = -1;
        for (j = 1; j <= n; j ++)   c0[j] = 0;
        c0[0] = -1;
        PhaseII(n, m, c0, a, rhs, ans0, k);
        if (dcmp(ans0) < 0) return INFEASIBLE;
        for (i = 1; i <= m; i ++)   a[i][0] = 0;
        for (j = 1; j <= n; j ++)
            if (dcmp(c[j]) && basic[j]){
                tmp = c[j];
                ans += rhs[col[j]] * tmp;
                for (i = 0; i <= n; i ++)   c[i] -= tmp*a[col[j]][i];
            }
        return FEASIBLE;
    }
    //standard form
    //n:ԭ��������   m:ԭԼ����������
    //c:Ŀ�꺯��ϵ������-[1~n],c[0] = 0;
    //a:Լ������ϵ������-[1~m][1~n]      rhs:Լ����������ʽ�ұ߳���������-[1~m]
    //ans:����ֵ   x:���Ž�||���н�����-[1~n]
    int simplex(int n, int m, double c[], double a[maxn][maxn], double rhs[], double &ans, double x[]){
        int i, j, k;
        //��׼��ʽ���ɳ���ʽ
        for (i = 1; i <= m; i ++){
            for (j = n+1; j <= n+m; j ++)   a[i][j] = 0;
            a[i][n+i] = 1;  a[i][0] = 0;
            row[i] = n+i;   col[n+i] = i;
        }
        k = PhaseI(n+m, m, c, a, rhs, ans);
        if (k == INFEASIBLE)    return k;
        k = PhaseII(n+m, m, c, a, rhs, ans, 0);
        for (j = 0; j <= n+m; j ++) x[j] = 0;
        for (i = 1; i <= m; i ++)   x[row[i]] = rhs[i];
        return k;
    }
}ps;    //Primal Simplex

int n,m;
double c[maxn], ans, a[maxn][maxn], b[maxn], x[maxn];

int main(){
	//freopen("test.in", "r", stdin);
	//freopen("test.out", "w", stdout);
	while(scanf("%d %d", &n, &m) != EOF){
        double ans;
        ps.init(n, m, c, a, b, ans);
        for (int i = 1; i <= n; i ++)
            scanf("%lf", &c[i]);
        for (int i = 1; i <= m; i ++){
            for (int j = 1; j <= n; j ++){
                scanf("%lf", &a[i][j]);
            }
            scanf("%lf", &b[i]);
        }
        ps.simplex(n,m,c,a,b,ans,x);
        printf("Nasa can spend %.0f taka.\n", ceil(m*ans));
	}
	return 0;
}