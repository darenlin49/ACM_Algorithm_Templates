/*

	k·�鲢��������N����������У�Ҫ�����N����������кϲ���һ����������С�
	����:
		���ݺܴ󣬵���ֻҪ�����ǰN�������Կ����뵽�ö��Ż�
		ÿ�����Ԫ�ض��Ǵ����������±�
		��ÿ����ĵ�ǰԪ�ط���������, ÿ��ɾ����Сֵ�������±���, Ȼ���������е���һ��Ԫ��
		ÿ�β�����Ҫlogkʱ��, ����ܹ���Ҫnlogk��ʱ��
		���԰���Щ�Ϳ���n�������:
		A[1]+B[1] <= A[1]+B[2] <= A[1]+B[3] <=��
		A[2]+B[1] <= A[2]+B[2] <= A[2]+B[3] <=��
		��
		A[n]+B[1] <= A[n]+B[2] <= A[n]+B[3] <=��

	�������������Բ���K·�鲢��
	
	POJ 2442 ��M���б�ϲ�ȡ�±�ǰN��Ԫ��
	��������M���б��ϵ��������б�K·�鲢�ķ�����
	
*/

int m,n;
int a[2005], b[2005], tm[2005];

struct condition{
    int a, b;   //��ʾ��ǰkey����A[a] + B[b]����
    int key;
    friend bool operator < (condition n1, condition n2){
        return n2.key < n1.key;
    }
};

void k_merge(int A[], int B[], int n){      //K·�鲢,ɸ��ǰn��С��Ԫ�طŻ�A[],A[]��B[]Ҳֻ��n������
    priority_queue <condition , vector <condition> > Q;
    for (int i = 0; i < n; i ++){
        condition tmp;
        tmp.key = A[i] + B[0];
        tmp.a = i;
        tmp.b = 0;
        Q.push(tmp);
    }
    mem(tm, 0);
    for (int i = 0; i < n; i ++){
        condition t = Q.top();
        tm[i] = t.key;
        Q.pop();
        t.b ++;
        t.key = A[t.a] + B[t.b];
        Q.push(t);
    }
    for (int i = 0; i < n; i ++)
        A[i] = tm[i];
}

int main(){
    int t;
    scanf("%d", &t);
    while(t --){
        scanf("%d %d", &m, &n);
        for (int i = 0; i < n; i ++)
            scanf("%d", &a[i]);
        sort(a, a+n);
        for (int i = 1; i < m; i ++){
            for (int j = 0; j < n; j ++)
                scanf("%d", &b[j]);
            sort(b, b+n);
            k_merge(a, b, n);
        }
        for (int i = 0; i < n - 1; i ++)
            printf("%d ", a[i]);
        printf("%d\n", a[n-1]);
    }

    return 0;
}
