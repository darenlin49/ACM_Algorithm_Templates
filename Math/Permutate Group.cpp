/**
	���û�Ⱥģ��1.0 - 2013.09.23��
	��������T^k=e(TΪһ�û�,eΪ��λ�û�(ӳ�亯��Ϊf(x)=x���û�)),��ôk����С����������T�Ĳ�ֵ�����ѭ�����ȵ���С������.
	�����ۡ�һ������Ϊlen��ѭ��T,��gcd(len,k)��ѭ���ĳ˻�,ÿ��ѭ���ֱ���ѭ��T���±�i mod gcd(len,k)=0,1,2����Ԫ�ص�����(˳��һ����ԭ��˳��).
	�������������O(n)�㷨��
		For Դ�û���ÿһ��ѭ��
			For ����ÿһ��δ���Ԫ�� Do
				���ϱ��
				����������
				ǰ��k��
			Until �ص����Ԫ��
		����������е�Ԫ��ȡ��,�õ��Ļ�,����Ŀ���û�������һ��ѭ��,�ٽ�ѭ��ת�����û�.
	��ע�⡿PG.A[] && PG.B[] ���±궼�Ǵ�1��ʼ

*/
const int MAXN = 205;
int gcd(int a, int b){
    return b ? gcd(b, a%b) : a;
}
struct PermutateGroup{
    int A[MAXN];        //The Permutate Group, begin with 1.
    bool vis[MAXN];
    //calculate k which makes T^k equals I
    inline int cal_k(int n){
        MEM(vis, false);
        int res = 1;
        for (int i = 1; i <= n; i ++){
            if (!vis[i]){
                vis[i] = 1;
                int len = 1;
                int p = i;
                while (1){
                    p = A[p];
                    if (vis[p]) break;
                    vis[p] = 1;
                    len ++;
                }
                res = res / gcd(res, len) * len;
            }
        }
        return res;
    }
    //calculate T^k
    int tmp[MAXN], pa[MAXN];
    bool viss[MAXN];
    inline void exp(int n, int k, int B[]){
        MEM(tmp, 0);    MEM(vis, 0);
        int len = 0;
        for (int i = 1; i <= n; i ++){
            if (!vis[i]){
                //���û�Ⱥ��ʾ������ѭ���ĳ˻�
                vis[i] = 1;
                int p = i;
                len = 0;
                tmp[len ++] = i;
                while(1){
                    p = A[p];
                    if (vis[p]) break;
                    vis[p] = 1;
                    tmp[len ++] = p;
                }
                //ÿ��ѭ���������ѭ����k����
                for(int j = 0; j < len; j ++)   viss[j] = 0;
                for(int j = 0; j < len; j ++){
                    int co = 0;
                    if (!viss[j]){
                        int tt = j;
                        while ((tt + k) % len != j){
                            pa[co ++] = tmp[tt];
                            viss[tt] = 1;
                            tt = (tt + k) % len;
                        }
                        pa[co ++] = tmp[tt];
                        viss[tt] = 1;
                        if (co == 1){
                            B[pa[0]] = pa[0];
                        }
                        else{
                            for (int j = 0; j < co; j ++){
                                B[pa[j]] = pa[j+1];
                            }
                            B[pa[co-1]] = pa[0];
                        }

                    }
                }
            }
        }
        return ;
    }
}PG;