/*

	��ͨĸ������Ӧ��---������֣�
	HDU 1398 300������ȫƽ������ֵӲ�ң�1Ԫ��4Ԫ��9Ԫ�����м��ַ���ƴ��nԪ(n <= 300)
	
	(1+x+x^2+x^3+x^4+x^5+����)(1+x^4+x^8+x^12+x^16+����)(1+x^9+x^18+x^27+����) = a1+a2*x+a3*x^2+����+an*x^n+����
	x^n��ϵ����Ϊ����
	
	res�����������ÿ�γ���һ������ʽpro
*/

int a[17] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256, 289};
/* generating_function */
const int MAX = 400;
struct generating_function{
    int res[MAX];
    int pro[MAX];
    int mmax;   //x^n --- max(n);
    void init(int n){
        memset(res, 0, sizeof(res));
        memset(pro, 0, sizeof(pro));
        res[0] = 1;
		mmax = n;
    }
    void cal(int p);
}gf;
void generating_function::cal(int p){
    int tmp[MAX];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i <= mmax; i ++){
        for (int j = 0; j <= mmax; j += a[p]){		//����ķ�Χ���Ը��ݵ�ǰpro�Ż�һ��.
            if (i + j <= mmax)
            tmp[i+j] +=  res[i] * pro[j];
        }
    }
	memset(res, 0, sizeof(res));
    for (int i = 0; i <= mmax; i ++){
        res[i] = tmp[i];
    }
    return ;
}
/* generating_function */

int main(){
    int n;
    while(scanf("%d", &n) == 1, n){
        gf.init(n);
        for (int i = 0; i < 17; i ++){
            memset(gf.pro, 0, sizeof(gf.pro));
            if (a[i] > gf.mmax)
                break;
            int p = 0;
            while(p <= gf.mmax){
                gf.pro[p] = 1;
                p += a[i];
            }
            gf.cal(i);
        }
        printf("%d\n", gf.res[gf.mmax]);
    }
    return 0;
}


/*
	HDU 2069 ��������������Ӳ������---�����������⣺�������ܳ���100
	��������ĸ�������Σ���һά��ʾ������
*/

int a[5] = {1, 5, 10, 25, 50};
const int N = 300;
struct generating_function{
    int c1[N][101], c2[N][101];
    int maxn;
    void init(int n){
        memset(c1, 0, sizeof(c1));
        memset(c2, 0, sizeof(c2));
        c1[0][0] = 1;
        maxn = n;
    }
    void cal(int p);
}ef;
void generating_function::cal(int p){
    int tmp[N][101];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i <= maxn; i ++){
        for (int j = 0; j <= maxn; j += a[p]){
            int k1 = j/a[p];
            if (i + j <= maxn && c2[j][k1])
                for (int k2 = 0; k1+k2 <= 100; k2 ++)
                    tmp[i+j][k1+k2] += c1[i][k2] * c2[j][k1];
        }
    }
    memset(c1, 0, sizeof(c1));
    for (int i = 0; i <= maxn; i ++){
        for (int k = 0; k <= 100; k ++){
            c1[i][k] = tmp[i][k];
        }
    }
    return ;
}
int main(){
    int n;
    while(scanf("%d", &n) == 1){
        ef.init(n);
        for (int i = 0; i < 5; i ++){
            memset(ef.c2, 0, sizeof(ef.c2));
            for (int j = 0; j <= n; j += a[i]){
                ef.c2[j][j/a[i]] = 1;
            }
            ef.cal(i);
        }

        int res = 0;
        for (int k = 0; k <= 100; k ++){
            res += ef.c1[n][k];
        }
        printf("%d\n", res);
    }
	return 0;
}

/*
	ָ����ĸ������
	HDU 2065 ����ɫ���������� (ָ��ĸ���� && ̩�ռ���)
	��4����ĸ��ɣ�A��Cֻ�ܳ���ż���Ρ�
	����ָ�������ɺ�����(1+x/1!+x^2/2!+x^3/3!����)^2*(1+x^2/2!+x^4/4!+x^6/6!����)^2.
	ǰ����B��D���������������ȡ��������ͬ��ĸһ��������Ҫ��ȥ��������������A��C�������ֻ��ȡż���������
	����̩��չ����e^x��x0=0���n��̩�ն���ʽΪ 1+x/1!+x^2/2!+x^3/3!����
	������Ҳ���Խ��е�������Ҫ��������ȥ������e^(-x)��չ��ʽΪ1-x/1!+X^2/2!-X^3/3!����
	���Ժ��߿��Ի���Ϊ(e^x+e^(-x))/2����ԭʽΪ (e^x)^2   *  ((e^x*e^(-x))/2)^2
	����õ�1/4*(e^4x+2*e^2x+1)��
	���������̩��չ��
	e^4x = 1 + (4x)/1! + (4x)^2/2! + (4x)^3/3! + ... + (4x)^n/n!;
	e^2x = 1 + (2x)/1! + (2x)^2/2! + (2x)^3/3! + ... + (2x)^n/n!;
	����ϵ��Ϊn��ϵ��Ϊ(4^n+2*2^n)/4=4^(n-1)+2^��n-1��;
	�����ݸ�֮��
*/
int PowMod(int a,LL b){
    int ret=1;
    while(b){
        if(b&1)
            ret=(ret*a)%MOD;
        a=(a*a)%MOD;
        b>>=1;
    }
    return ret;
}
int main(){
    int t;
    while(scanf("%d",&t)!=EOF&&t){
        int cas=0;
        LL n;
        while(t--){
            scanf("%I64d",&n);
            printf("Case %d: %d\n",++cas,(PowMod(4,n-1)+PowMod(2,n-1))%MOD);
        }
        printf("\n");
    }
    return 0;
}