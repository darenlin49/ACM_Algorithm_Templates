/*
	Havel-Hakimi���������ж�һ�������Ķ������Ƿ��ǿ�ͼ��.
	[������]����ͼ G ���ж���Ķ����ų�һ������ S,��� S Ϊͼ G �Ķ�����.
	[��ͼ]һ���Ǹ�������ɵ��������������ĳ������ͼ������,��Ƹ������ǿ�ͼ��.
	[�ж�����]
		�ٶԵ�ǰ��������ʹ��ʵݼ�
		�ڴ�S[2]��ʼ�����S[1]������-1 ��һֱѭ��ֱ����ǰ���г��ָ����������ǿ�ͼ����������ߵ�ǰ����ȫΪ0 ����ͼ��ʱ�˳�
	[����]����S��7,7,4,3,3,3,2,1  ɾ������S������ 7 ��������7��ÿ���1���õ���6,3,2,2,2,1,0������ɾ�����е�����6��������6��ÿ���1���õ���2,1,1,1,0��-1������һ�������˸�������˸������ǲ���ͼ��.
*/

/* ------------------- Havel-Hakimi ------------------- */
const int N = 12;
struct DEG{
    int deg;
    int v;
}x[N];
bool cmp(DEG n1, DEG n2){
    return n1.deg > n2.deg;
}
int mat[N][N];
//��������һ��������x[]�Ƿ��ͼ
bool Havel(int n){
    sort(x, x+n, cmp);
    mem(mat, 0);                    //��ͼ���ڽӾ���
    for (int i = 0; i < n; i ++){
        if (x[i].deg == 0)  return true;
        for (int j = i+1; j <= min(i+x[i].deg, n-1); j ++){
            x[j].deg --;
            if (x[j].deg < 0){
                return false;
            }
            mat[x[i].v][x[j].v] ++;
            mat[x[j].v][x[i].v] ++;
        }
        x[i].deg -= n-i-1;
        x[i].deg = max(0, x[i].deg);
        sort(x+i+1, x+n, cmp);
    }
    return true;
}
/* ------------------- Havel-Hakimi ------------------- */

int main(){
    int T, n;
    scanf("%d", &T);
    for (int t = 0; t < T; t ++){
        if (t > 0)
            puts("");
        scanf("%d", &n);
        for (int i = 0; i < n; i ++){
            scanf("%d", &x[i].deg);
            x[i].v = i;
        }
        if (Havel(n)){
            puts("YES");
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < n - 1; j ++){
                    printf("%d ", mat[i][j]);
                }
                printf("%d\n", mat[i][n-1]);
            }
        }
        else{
            puts("NO");
        }
    }
	return 0;
}
